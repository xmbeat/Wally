/*
 * BinarySemaphore.h
 *
 *  Created on: 23/02/2014
 *      Author: xmbeat
 */

#ifndef BINARYSEMAPHORE_H_
#define BINARYSEMAPHORE_H_




class BinarySemaphore {
public:
	BinarySemaphore(int key);
	virtual ~BinarySemaphore();
	virtual bool wait(bool canUndo = true);
	virtual bool post(bool canUndo = true);
private:
	int mSemId;
};

#endif /* BINARYSEMAPHORE_H_ */
