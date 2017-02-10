#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void good(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}

void bad1(int a) {
    pthread_mutex_lock(& m);
    a = a + 1;
    return;
}

void bad2(int a) {
    a = a + 1;
    pthread_mutex_unlock(& m);
    return;
}
