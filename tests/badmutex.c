#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void good(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    while( a == 0)
	pthread_cond_wait(& c, &m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}

void badMutexInWait(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    while( a == 0)
	pthread_cond_wait(& c, &m2);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}

void badMutexPairing(int a) {
    pthread_mutex_lock(& m);
    pthread_mutex_unlock(& m2);
}



