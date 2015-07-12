#include "RWLock.h"

RWLock :: RWLock() {
	readers = 0;
	writers = 0;
	pthread_mutex_init(&mu,NULL);
	pthread_mutex_init(&barra, NULL);//Para bloquear a los readers quedar en el cond_wait si ya hay un writer esperando (evitar inanición)..
	pthread_cond_init(&vacio,NULL);
}

void RWLock :: rlock() {
	pthread_mutex_lock(&barra);
	pthread_mutex_unlock(&barra);

	pthread_mutex_lock(&mu);
	while(!(writers == 0)) pthread_cond_wait(&vacio, &mu);
	readers++;
	pthread_mutex_unlock(&mu);
}

void RWLock :: wlock() {
	pthread_mutex_lock(&barra);
	pthread_mutex_lock(&mu);
	while(!(readers == 0) && !(writers == 0)) pthread_cond_wait(&vacio, &mu);
	writers++;
	pthread_mutex_unlock(&mu);
	pthread_mutex_unlock(&barra);
}

void RWLock :: runlock() {
	pthread_mutex_lock(&mu);
	readers--;
	if (readers == 0) pthread_cond_signal(&vacio);
	pthread_mutex_unlock(&mu);
}

void RWLock :: wunlock() {
	pthread_mutex_lock(&mu);
	writers--;
	pthread_cond_broadcast(&vacio);
	pthread_mutex_unlock(&mu);
}
