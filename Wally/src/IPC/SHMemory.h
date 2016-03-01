/*
 * SHMemory.h
 *
 *  Created on: 23/02/2014
 *      Author: xmbeat
 */

#ifndef SHMEMORY_H_
#define SHMEMORY_H_
#include "BinarySemaphore.h"
class SHMemory {
public:
	SHMemory(int key, int preferedSize);
	virtual ~SHMemory();
	virtual int getSize();
	virtual int getKey();
	virtual int getAttachCount();
	virtual void setRemovable(bool value);
	virtual int write(int offset, const char* data, int len);
	virtual int read(int offset, char* buffer, int len);
	virtual int syncWrite(int offset, const char* data, int len);
	virtual int syncRead(int offset, char* buffer, int len);
	virtual bool lock();
	virtual bool unlock();
	virtual operator char*();
	virtual char& operator [](const int index);
private:
	int mSegmentId;
	int mKey;
	char* mMemory;
	bool mRemovable;
	bool mLocked;
	BinarySemaphore *mSemaphore;
};

#endif /* SHMEMORY_H_ */
