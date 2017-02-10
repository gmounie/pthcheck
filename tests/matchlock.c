#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void good(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}

void bad(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_unlock(& m2);
    return;
}

