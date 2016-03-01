/*
 * Timer.cpp
 *
 *  Created on: 24/02/2014
 *      Author: xmbeat
 *      -lrt
 */

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "Timer.h"

static void timerHandler(int signum, siginfo_t * info, void* context){
	TimerCallback *fn = (TimerCallback*)info->si_value.sival_ptr;
	if (fn && *fn){
		(*fn)();
	}
}

static void timerInitializer(){
	/*
	 *Indico que el proceso manejará la señal SIGRTMIN, esta señal es
	 *definida por el usuario como SIGUSR1 o SIGUSR2
	 */
	static bool init = false;
	if (!init){
		struct sigaction s_act;
		s_act.sa_sigaction = &timerHandler;
		sigemptyset(&s_act.sa_mask);
		s_act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGRTMIN, &s_act, NULL) == -1){
			throw "No se pudo crear el timer, sigaction falló";
		}
		init = true;
	}
}

Timer::Timer(TimerCallback callback):
		mSeconds(0), mMiliseconds(0),
		mTimerId(0), mRunning(false),
		mCallback(callback) {
	timerInitializer();
	/*
	 * Indicamos que señal enviar cuando el tiempo expire, en este caso la
	 * que se supone manejaremos para gestionar los timers (SIGRTMIN). Ademas
	 * en el campo "sigev_value.sigval_ptr" se almacena el puntero a función que
	 * se debe llamar (Este valor es almacenado en el segundo argumento de timerHandler).
	 */
	struct sigevent s_evt;
	s_evt.sigev_notify = SIGEV_SIGNAL;
	s_evt.sigev_signo = SIGRTMIN;
	s_evt.sigev_value.sival_ptr = (void*) &mCallback;
	if (timer_create(CLOCK_REALTIME, &s_evt, (timer_t *)&mTimerId) == -1){
		throw "No se pudo crear el timer, timer_create falló";
	}

}
//Timer::Timer(TimerCallback callback):mSeconds(0), mMiliseconds(0), mCallback(callback){}

Timer::~Timer() {
	timer_delete((timer_t) mTimerId);
}

void Timer::setCallback(TimerCallback callback){
	mCallback = callback;
}

bool Timer::setTime(int seconds, int miliseconds){
	/*
	 * Indicamos el tiempo de inicio y de intervalo: iniciamos inmediatamente,
	 * y el intervalo lo ponemos a lo especificado por el usuario.
	 */
	struct itimerspec value;
	value.it_value.tv_sec = seconds;
	value.it_value.tv_nsec = miliseconds* 1000;
	value.it_interval.tv_sec = seconds;
	value.it_interval.tv_nsec = miliseconds * 1000;
	if (timer_settime((timer_t)mTimerId, 0, &value, NULL) == 0){
		mSeconds = seconds;
		mMiliseconds = miliseconds;
		return true;
	}
	else{
		return false;
	}
}

void Timer::getTime(int *seconds, int* miliseconds){
	*seconds = mSeconds;
	*miliseconds = mMiliseconds;
}
