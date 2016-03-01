/*
 * InstanceManager.h
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#ifndef INSTANCEMANAGER_H_
#define INSTANCEMANAGER_H_
#include "SHMemory.h"
#include <Utils/Timer.h>
#include <unistd.h>
#include <signal.h>
#include <Exception/Exception.h>

typedef void (*ReceiveCallback)(int keyMemory);
class InstanceManager {
public:
	virtual ~InstanceManager();
	InstanceManager(int key, ReceiveCallback callback, int signal = SIGUSR1);
	bool send(int pid, const char* message, int size);
	void registerInstance();
	int getPID(int index);
	int getInstancesCount();
	void unRegisterInstance();
protected:

private:
	SHMemory mMemory;
	int mSignal;
	int mIndex;
};

#endif /* INSTANCEMANAGER_H_ */
