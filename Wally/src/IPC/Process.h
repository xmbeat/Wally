/*
 * Process.h
 *
 *  Created on: 24/02/2014
 *      Author: xmbeat
 */
#ifndef PROCESS_H_
#define PROCESS_H_
#include <Utils/ArrayList.h>
#include <Utils/String.h>
class Process {
public:
	Process();
	static String getPathToExeFile(int pid);
	static int getPID();
	static int createProcessFromArray(const char* path, char* const argv[], bool wait);
	static int createProcess(const char* path, const char* arg, ...);
	virtual ~Process();
};

#endif /* PROCESS_H_ */
