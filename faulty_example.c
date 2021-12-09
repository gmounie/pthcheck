#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void f() {
  pthread_mutex_lock(&m);
  // do something
  pthread_mutex_lock(&m);
}
