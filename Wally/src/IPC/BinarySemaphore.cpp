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

/*
 * ejecuta una operacion sobre el semaforo especificado.
 */
static int inline binarySemOp(int semId, int index, int op, int flags = SEM_UNDO){
	struct sembuf operations[1];
	operations[0].sem_num = index;
	operations[0].sem_op = op;
	operations[0].sem_flg = flags;
	return semop(semId, operations, 1);
}

/*
 * Crea e inicializa un semáforo binario.
 * Aunque el semáforo es binario, se usan dos valores extras para
 * controlar, la creación/eliminación del semáforo.
 *  */
BinarySemaphore::BinarySemaphore(int key): mSemId(0) {
	/* valores para los semaforos */
	unsigned short values[3] = {1,1,0};
	/* conseguimos un identificador válido en este bucle */
	do{
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
			if (binarySemOp(mSemId, 1, -1) == -1){
				mSemId = -1;
				continue;
			}
			/*Incrementamos el contador*/
			binarySemOp(mSemId, 2, 1);
			/*liberamos el recurso (semáforo en el índice 1)*/
			binarySemOp(mSemId, 1, 1);
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
			binarySemOp(mSemId, 1, -1);
			binarySemOp(mSemId, 2, 1);
			binarySemOp(mSemId, 1, 1);
			break;
		}
	}while(mSemId == -1);
}

BinarySemaphore::~BinarySemaphore() {
	int ignored = 0;
	/*
	 * Obtenemos el semáforo 1, para poder decrementar el contador.
	 * Si el proceso está por terminar, estás líneas son innecesarias debido
	 * a que especificamos el parámetro SEM_UNDO.
	 */
	binarySemOp(mSemId, 1,-1);
	binarySemOp(mSemId, 2, -1);
	/*Si se llegó a cero, lo debemos eliminar */
	int count = semctl(this->mSemId, 2, GETVAL);
	if (count == 0){
		semctl(this->mSemId, 3, IPC_RMID, ignored);
	}else{
		binarySemOp(mSemId, 1, 1);
	}
}

bool BinarySemaphore::wait(bool canUndo){
	return binarySemOp(this->mSemId, 0, -1, canUndo?SEM_UNDO:0)!=-1;
}
bool BinarySemaphore::post(bool canUndo){
	return binarySemOp(this->mSemId, 0, 1, canUndo?SEM_UNDO:0)!=-1;
}
