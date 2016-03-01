/*
 * InstanceManager.cpp
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#include "InstanceManager.h"

static ReceiveCallback callback = NULL;

InstanceManager::~InstanceManager() {
	// TODO Auto-generated destructor stub
}

static void signalHandler(int signum, siginfo_t * info, void* context){
	int key = info->si_value.sival_int;
	if (callback)
		callback(key);
}

static void init(int signal){
	/*
	 *Indico que el proceso manejará la señal
	 */
	static bool init = false;
	if (!init){
		struct sigaction s_act;
		s_act.sa_sigaction = &signalHandler;
		sigemptyset(&s_act.sa_mask);
		s_act.sa_flags = SA_SIGINFO;
		if (sigaction(signal, &s_act, NULL) == -1){
			throw Exception("InstanceManager::No se pudo asociar la interrupción con la señal (sigaction)");
		}
		init = true;
	}
}
InstanceManager::InstanceManager(int key, ReceiveCallback callback, int signal):
		mMemory(key, 1024), mSignal(signal), mIndex(-1){
	if (::callback){
		throw Exception("InstanceManager::Solo una instancia puede ser creada");
	}
	::callback = callback;
	init(mSignal);
}

bool InstanceManager::send(int pid, const char* message, int size){
	SHMemory memory(pid, size);
	memory.setRemovable(false);
	memory.syncWrite(0,message, size);
	union sigval val;
	val.sival_int = memory.getKey();
	if (sigqueue(pid, mSignal, val) == 0){
		return true;
	}
	else{
		memory.setRemovable(true);
		return false;
	}
}

int InstanceManager::getPID(int index){
	if (index < 0){
		return (int) getpid();
	}
	else{
		mMemory.lock();
		int *pid = (int*)((char*)mMemory);
		int ret = 0;
		while(*pid != 0 && index >= 0){
			if (kill(*pid, 0)==0){
				index--;
			}
		}
		if (index < 0){
			ret = *pid;
		}
		mMemory.unlock();
		return ret;
	}
}

int InstanceManager::getInstancesCount(){
	mMemory.lock();
	int *pid = (int*)((char*)mMemory);
	int count = 0;
	while (*pid != 0){
		if (kill(*pid, 0) == 0){
			count++;
		}
		pid++;
	}
	mMemory.unlock();
	return count;
}

void InstanceManager::registerInstance(){
	if (mIndex == -1){
		mMemory.lock();
		int *pid = (int*)((char*)mMemory);
		mIndex = 0;
		while(*pid != 0){
			if (kill(*pid, 0) == -1){
				break;
			}
			mIndex++;
			pid++;
		}
		*pid = (int)getpid();
		mMemory.unlock();
	}
}
void InstanceManager::unRegisterInstance(){
	mMemory.lock();
	int *pid = (int*)((char*)mMemory);
	int i = mIndex+1;
	while(pid[i] != 0){
		pid[i-1] = pid[i];
		i++;
	}
	pid[i] = 0;
	mMemory.unlock();
}
