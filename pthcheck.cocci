@nounlock@
pthread_mutex_t M;
@@
* pthread_mutex_lock(& M);
... when != pthread_mutex_unlock(& M)

@nolock@
pthread_mutex_t M;
@@
... when != pthread_mutex_lock(& M)
* pthread_mutex_unlock(& M);

@badmatch@
pthread_mutex_t M;
pthread_mutex_t M2;
@@
* pthread_mutex_lock(& M);
...  when != M2 = M
* pthread_mutex_unlock(& M2);

@noif@
pthread_mutex_t M;
pthread_cond_t C;
expression E;
@@
pthread_mutex_lock(& M);
...
(
* if (E) pthread_cond_wait(& C, & M);
|
* if (E) { ... pthread_cond_wait(& C, & M); ... }
)
...
pthread_mutex_unlock(& M);
