/*
 * SHMemory.cpp
 *
 *  Created on: 23/02/2014
 *      Author: xmbeat
 */

#include "SHMemory.h"
#include "BinarySemaphore.h"
#include <sys/shm.h>
#include <sys/stat.h>


SHMemory::SHMemory(int key, int preferedSize):
mKey(key),	mMemory(0), mRemovable(true), mLocked(false), mSemaphore(0) {
	try{
		mSemaphore = new BinarySemaphore(key);
	}
	catch(const char* e){
		throw e;
	}
	mSemaphore->wait();
	mSegmentId = shmget(key, preferedSize, S_IRUSR | S_IWUSR);
	if (mSegmentId == -1){
		mSegmentId = shmget(key, preferedSize, S_IRUSR | S_IWUSR | IPC_CREAT);
		if (mSegmentId == -1){
			throw "No se pudo reservar la memoria compartida";
		}
		mMemory = (char*) shmat(mSegmentId, 0, 0);
		//Momento de poner la firma
	}
	else{
		mMemory = (char*) shmat(mSegmentId, 0, 0);
		//Momento de corroborar la firma
	}
	mSemaphore->post();
}

void SHMemory::setRemovable(bool value){
	mRemovable = value;
}

SHMemory::~SHMemory() {
	if (mMemory){
		mSemaphore->wait();
		if (getAttachCount() == 1 && mRemovable){
			shmdt(mMemory);
			shmctl(mSegmentId, IPC_RMID, 0);
		}
		else{
			shmdt(mMemory);
		}
		mSemaphore->post();
	}
	delete mSemaphore;
}

int SHMemory::getAttachCount(){
	struct shmid_ds stat;
	if (shmctl(mSegmentId, IPC_STAT, &stat) == 0){
		return stat.shm_nattch;
	}
	return -1;
}

int SHMemory::getSize(){
	struct shmid_ds info;
	if (shmctl(mSegmentId, IPC_STAT, &info) != -1){
		return info.shm_segsz;
	}
	return 0;
}

int SHMemory::write(int offset, const char* data, int len){
	if (mMemory != 0){
		int size = getSize();
		if (len < size){
			size = len;
		}
		for (int i = 0; i < size; i++){
			mMemory[i] = data[i];
		}
		return size;
	}
	return 0;
}

int SHMemory::read(int offset, char* buffer, int len){
	if (mMemory != 0){
		int size = getSize();
		if (len < size){
			size = len;
		}
		for (int i = 0; i < size; i++){
			buffer[i] = mMemory[i];
		}
		return size;
	}
	return 0;
}

int SHMemory::syncRead(int offset, char* buffer, int len){
	mSemaphore->wait();
	int aux = read(offset, buffer, len);
	mSemaphore->post();
	return aux;
}

int SHMemory::syncWrite(int offset, const char* data, int len){
	mSemaphore->wait();
	int aux = write(offset, data, len);
	mSemaphore->post();
	return aux;
}

SHMemory::operator char *(){
	return mMemory;
}
char& SHMemory::operator [](const int index){
	return mMemory[index];
}

int SHMemory::getKey(){
	return mKey;
}

bool SHMemory::lock(){
	if (mLocked){
		return false;
	}
	mLocked = true;
	return mSemaphore->wait();
}

bool SHMemory::unlock(){
	if (mLocked){
		mLocked = false;
		return mSemaphore->post();
	}
	return false;
}

