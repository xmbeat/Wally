/*
 Copyright (c) <2012> <Xmbeat::Juan Hebert Chable Covarrubias>

Permission is hereby granted, free of charge, to any
person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the
Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice
shall be included in all copies or substantial portions of
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <unistd.h>
#include "String.h"
class Thread
{
    public:
		static const int MAX_PRIORITY;
		static const int MIN_PRIORITY;
        Thread():requestJoin(false), mIsRunning(false) {}
        virtual ~Thread() {}
        virtual void run() {}
        void start();
        
        virtual void setName(String name){
        	_name = name;
        	//pthread_setname_np(*this, _name);
        };
        virtual String getName(){
        	char buf[256];
        	pthread_getname_np(*this, buf, 256);
        	//return buf;
        	return _name;
        }
        virtual operator pthread_t();

        void setPriority(int);
        int getPriority();
        void join()
        {
        	requestJoin = true;
			if (mIsRunning){
        		pthread_join(*this, NULL);//no nos interesa el return
			}
        }
		void stop()
		{
			if (mIsRunning){
				pthread_detach(*this);
				pthread_cancel(*this);
			}
		}
        static void yield();
		static void sleep(int m);
		void setDeleteReference(bool val){
			deleteReference = val;
		}
		bool isDeleteReference(){
			return deleteReference;
		}
    private:
        bool requestJoin;
        bool deleteReference;//Solo para poder eliminar la referencia al final de la ejecucion
        String _name;
        pthread_t _hilo;
        int mPriority;
		bool mIsRunning;
        static void *threadStarter(void* pThread)
        {
        	Thread *hilo = (Thread*)pThread;
			hilo->mIsRunning = true;//WARNING: INSEGURO PARA EL PROPOSITO DE LA VARIABLE!
            hilo->run();//Como no puedo obtener la direccion de run,
            //entonces uso un puntero, para llamar al "main" del hilo(run)
            if (!hilo->requestJoin)
            {
            	pthread_detach(hilo->_hilo);//no son joinables
            }
            //pthread_exit(NULL);
			hilo->requestJoin = false;
			hilo->mIsRunning = false;
			if (hilo->isDeleteReference()){
				delete hilo;
			}
            return NULL;
        }

};
const int Thread::MAX_PRIORITY = sched_get_priority_max(SCHED_RR);
const int Thread::MIN_PRIORITY =  sched_get_priority_min(SCHED_RR);

void Thread::yield()
{
#ifdef __USE_GNU
	pthread_yield();
#else
	sched_yield();
#endif
}
void Thread::sleep(int m)
{
	usleep(m*1000);
}
Thread::operator pthread_t()
{
    return _hilo;
}

int Thread::getPriority()
{
	sched_param param;
	int policy;
	if (pthread_getschedparam(*this, &policy, &param)==0)
	{
		return param.__sched_priority;
	}
	return mPriority;
}
void Thread::setPriority(int priority)
{
	//pthread_setschedprio(*this, priority);
	sched_param param;
	param.__sched_priority = priority;
	pthread_setschedparam(*this, 0, &param);
	mPriority = priority;
}
void Thread::start()
{//Preferentemente Sincronizado!!!
	if (mIsRunning){
		//Lanzar Excepcion al tratar de lanzar el hilo 2 veces
	}
	else{
		pthread_create(&_hilo, NULL, &threadStarter, (void*)this);
	}
}

//====PARA HACER UN METODO ATOMICO ENTRE HILOS, ADEMAS PARA WAIT Y NOTIFY===
class Synchronizable
{
private:
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;//realmente esta dentro de la estructura.
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t *curLock;
public:
	Synchronizable():
		curLock(NULL)
	{}
	operator pthread_mutex_t*(){
		return &lock;
	}
	void synchronizeOn(pthread_mutex_t*mutex = NULL)
	{
		if (mutex!=NULL)
			curLock = mutex;
		else
			curLock = &lock;
		pthread_mutex_lock(curLock);
	}
	void synchronizeOff()
	{
		pthread_mutex_unlock(curLock);
	}

	void wait()
	{	//esperamos por la notificacion
		 pthread_cond_wait(&cond,  &lock );
	}
	void notify()
	{
		pthread_cond_signal(&cond);
	}
	void notifyAll()
	{
		pthread_cond_broadcast(&cond);
	}
};
#endif // THREAD_H
