# pthcheck
Simple static checker rules for simple pthread monitor C code.

It uses coccinelle with some ad'hoc rules.

# Usage

```shell
	spatch --sp-file pthcheck.cocci FILE
```

The output patch matches the problematic lines. Empty patch means no
matching lines.

The matching rules (to find what is the problem) are exposed with the
debug option.

```
	spatch --debug --sp-file pthcheck.cocci FILE
```

# Example
## Faulty C code: two lock but no unlock in a fonction
A common typo.
```C
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void f() {
  pthread_mutex_lock(&m);
  // do something
  pthread_mutex_lock(&m);
}
```

## spatch output
spatch will give the following output:
```diff
init_defs_builtins: /usr/lib/coccinelle/standard.h
HANDLING: faulty_example.c
     (ONCE) already tagged but only removed, so safe
diff = 
--- faulty_example.c
+++ /tmp/cocci-output-46345-297cbf-faulty_example.c
@@ -5,5 +5,4 @@ pthread_mutex_t m = PTHREAD_MUTEX_INITIA
 void f() {
     pthread_mutex_lock(&m);
     // do something
-    pthread_mutex_lock(&m);
 }
```

## spatch output with debug
Spatch matches two rules
1. the unlock is missing in the function 
2. the function uses two times the same lock 

```
...
...
nounlock =
-----------------------------------------------------------------------
binding in = []
binding relevant in = []
               with rule_elem: *pthread_mutex_lock*(*&*M*)
               with binding: []
     binding out = []
...
...
...
repetitivelock =
-----------------------------------------------------------------------
binding in = []
binding relevant in = []
               with rule_elem: *pthread_mutex_lock*(*&*M*)
               with binding: []
     binding out = []
-----------------------------------------------------------------------
```

# Rules

The rules implemented target simple code. More advanced
synchronization scheme may trigger false positive matching.

It matches:
- mutex lock or trylock but no unlock
- mutex unlock but no lock or trylock
- mutex lock and unlock do not use the same mutex
- condition wait inside a if between a lock and unlock
- condition wait without lock on the same mutex before
- condition wait without unlock on the same mutex after
- signal without lock before
- signal without unlock after
- repetitive lock on the same mutex
- unlock lock around the wait with the same mutex

# TODO (merge request welcome)
- create do not get a thread_t
- return before unlock
- cancel after join
- cancel après create

# Rational

The rules come from the most common bugs of my students. 
