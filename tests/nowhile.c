#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void good(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    while( a == 0)
	pthread_cond_wait(& c, &m);
    a = a + 1;
    while( a == 0) {
	a++;
	pthread_cond_wait(& c, &m);
	a--;
    }
    pthread_mutex_unlock(& m);
    return;
}

void badNoWhileAroundWait(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_cond_wait(& c, &m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}



