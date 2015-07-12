#ifndef RWLock_h
#define RWLock_h
#include <iostream>

class RWLock {
    public:
        RWLock();
        void rlock();
        void wlock();
        void runlock();
        void wunlock();

    private:
//        pthread_rwlock_t rwlock;
	int readers;
	int writers;
	pthread_mutex_t mu;
	pthread_mutex_t barra;
	pthread_cond_t vacio;
};

#endif
