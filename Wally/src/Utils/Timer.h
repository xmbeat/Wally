/*
 * Timer.h
 *
 *  Created on: 24/02/2014
 *      Author: xmbeat
 */

#ifndef TIMER_H_
#define TIMER_H_
typedef void (*TimerCallback)();
class Timer {
public:
	Timer(TimerCallback callback);
	//Timer();
	virtual bool setTime(int seconds, int miliseconds);
	virtual void getTime(int *seconds, int* miliseconds);
	virtual void setCallback(TimerCallback callback);
	virtual ~Timer();
private:
	int mSeconds;
	int mMiliseconds;
	void* mTimerId;
	bool mRunning;
	TimerCallback mCallback;
};

#endif /* TIMER_H_ */
