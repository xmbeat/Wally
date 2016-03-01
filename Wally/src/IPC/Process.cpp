/*
 * Process.cpp
 *
 *  Created on: 24/02/2014
 *      Author: xmbeat
 */
#include <unistd.h>		/* vfork, execv, pipe2 */
#include <sys/types.h> 	/* pid_t */
#include <fcntl.h>		/* O_CLOEXEC */
#include <stdlib.h>     /* getenv */
#include <ctype.h>		/* isspace */
#include <string.h>		/* strlen */
#include <signal.h>		/* sigaction */
#include <stdarg.h>		/* valist */
#include "Process.h"
#include <stdio.h>
int Process::createProcess(const char* command, const char* arg, ...){
	ArrayList<char*> buffer;
	va_list argumentList;
	va_start(argumentList, arg);
	buffer.add((char*) command);
	buffer.add((char*) arg);
	//mientras haya argumentos q leer
	while(arg!=NULL){
		arg = va_arg(argumentList, char*);
		buffer.add((char*) arg);
	}
	int wait = va_arg(argumentList, int);
	va_end(argumentList);
	return createProcessFromArray(command, buffer.toArray(), wait);
}

int Process::createProcessFromArray(const char* path, char* const argv[], bool wait){
	if (!wait){
		struct sigaction s_act;
		s_act.sa_sigaction = (void(*)(int, siginfo_t*, void*)) SIG_IGN;
		sigemptyset(&s_act.sa_mask);
		s_act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGCHLD, &s_act, NULL) == -1){
			return 0;
		}
	}
	pid_t pid;
	int fds[2];
	/* Creamos una tubería que se cierra si usamos exec o exit */
	pipe2(fds, O_CLOEXEC);
	/* Creamos un proceso hijo */
	pid = vfork();
	if (pid == 0){
		/* Este es el proceso hijo. Cerramos el extremo de lectura */
		close(fds[0]);
		/* Intercambiamos la imagen del proceso por el nuevo programa.
		 * Si la llamada a execvp tiene éxito, entonces la tubería se
		 * cierra, lo que provoca que el proceso padre no reciba datos
		 */

		execvp (path, argv);
		int code = 0xBADC0DE;
		write(fds[1], &code, sizeof(code));
		close(fds[1]);
		_exit(0);
		return 0;
	}
	else{
		/* Este es el proceso padre. Cerramos el extremo de escritura */
		close(fds[1]);
		int code;
		/* si podemos leer desde la tubería, entonces exec falló */
		if (read (fds[0], &code, sizeof(code)) == sizeof(code)){
			return 0;
		}
		return pid;
	}

}

Process::Process() {
	// TODO Auto-generated constructor stub

}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

