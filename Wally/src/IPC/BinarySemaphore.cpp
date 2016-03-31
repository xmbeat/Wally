/*
 * BinarySemaphore.cpp
 *
 *  Created on: 23/02/2014
 *      Author: xmbeat
 */

#include "BinarySemaphore.h"
#include <sys/stat.h>
#include <sys/sem.h>
#include <errno.h>


static void checkForSemopError(){
	switch(errno){
	case E2BIG:
		throw "The argument nsops is greater than SEMOPM, the maximum number "
			"of operations allowed per system call.";
		break;

	case EACCES:
		throw "The calling process does not have the permissions required to "
			"perform the specified semaphore operations, and does not have "
			"the CAP_IPC_OWNER capability.";
		break;
	case EAGAIN:
		throw "An operation could not proceed immediately and either "
			"IPC_NOWAIT was specified in sem_flg or the time limit "
			"specified in timeout expired.";
		break;
	case EFAULT:
		throw "An address specified in either the sops or the timeout argument isn't accessible.";
		break;
	case EFBIG:
		throw "For some operation the value of sem_num is less than 0 or "
			"greater than or equal to the number of semaphores in the set.";
		break;
	case EIDRM:
		throw "The semaphore set was removed.";
		break;
	case EINTR:
		throw "While blocked in this system call (semop), the thread caught a signal";
		break;
	case EINVAL:
		throw "The semaphore set doesn't exist, or semid is less than zero, "
			"or nsops has a nonpositive value.";
		break;
	case ENOMEM:
		throw "The sem_flg of some operation specified SEM_UNDO and the "
			"system does not have enough memory to allocate the undo "
			"structure.";
		break;
	case ERANGE:
		throw "For some operation sem_op+semval is greater than SEMVMX, the "
			"implementation dependent maximum value for semval.";
		break;
	}
}


/*
 * ejecuta una operacion sobre el semaforo especificado.
 */
static int semaphoreOperation(int semId, int index, int op, int flags = SEM_UNDO, bool throwException = false){
	struct sembuf operations[1];
	operations[0].sem_num = index;
	operations[0].sem_op = op;
	operations[0].sem_flg = flags;
	int result = semop(semId, operations, 1);
	if  (result == -1 && throwException){
		checkForSemopError();
	}
	return result;
}

/*
 * Crea e inicializa un semáforo binario.
 * Aunque el semáforo es binario, se usan dos valores extras para
 * controlar, la creación/eliminación del semáforo.
 *  */
BinarySemaphore::BinarySemaphore(int key): mSemId(-1) {
	/* valores para los semaforos */
	unsigned short values[3] = {1,1,0};
	/* conseguimos un identificador válido en este bucle */
	while(mSemId == -1){
		/* tratamos de crearlo primero, si falla quiere decir que ya había sido creado antes */
		mSemId = semget(key, 3, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
		if (mSemId == -1){
			mSemId = semget(key, 3, S_IRUSR | S_IWUSR);
			if (mSemId == -1 && errno == EACCES){
				throw "El semáforo existe para la llave, pero los permisos no coinciden";
			}
			/*
			 * Hacemos un wait al semaforo en el índice 1, si falla, quiere decir que
			 * el semáforo fue eliminado en el transcurso de la llamada anterior y esta,
			 * es dificil que pase, pero aun así puede pasar.
			 */
			if (semaphoreOperation(mSemId, 1, -1) == -1){
				mSemId = -1;
				continue;
			}
			/*Incrementamos el contador*/
			semaphoreOperation(mSemId, 2, 1);
			/*liberamos el recurso (semáforo en el índice 1)*/
			semaphoreOperation(mSemId, 1, 1);
		}
		else{ /*inicializamos los semáforos*/
			if (semctl(this->mSemId, 0, SETALL, values) == -1){
				throw "Error inicializando semáforo";
			}
			/*
			 * Incrementamos el contador de procesos que usan el semáforo (indice 2).
			 * Para esto nos apoyamos del semáforo que hay en el índice 0, de esta
			 * manera si otro proceso quiere incrementar/decrementar el contador deberá esperar
			 */
			semaphoreOperation(mSemId, 1, -1);
			semaphoreOperation(mSemId, 2, 1);
			semaphoreOperation(mSemId, 1, 1);
			break;
		}
	}
}

BinarySemaphore::~BinarySemaphore() {
	int ignored = 0;
	/*
	 * Obtenemos el semáforo 1, para poder decrementar el contador.
	 * Si el proceso está por terminar, estás líneas son innecesarias debido
	 * a que especificamos el parámetro SEM_UNDO.
	 */
	semaphoreOperation(mSemId, 1,-1);
	semaphoreOperation(mSemId, 2, -1);
	/*Si se llegó a cero, lo debemos eliminar */
	int count = semctl(this->mSemId, 2, GETVAL);
	if (count == 0){
		semctl(this->mSemId, 3, IPC_RMID, ignored);
	}else{
		semaphoreOperation(mSemId, 1, 1);
	}
}

bool BinarySemaphore::wait(bool canUndo){
	return semaphoreOperation(this->mSemId, 0, -1, canUndo?SEM_UNDO:0);
}

bool BinarySemaphore::post(bool canUndo){
	return semaphoreOperation(this->mSemId, 0, 1, canUndo?SEM_UNDO:0);
}
