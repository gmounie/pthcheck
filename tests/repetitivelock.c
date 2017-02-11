#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void good(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}

void badRepetitiveLock(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}



