# mutexes

## info

A mutex is a MUTual EXclusion device usefull for protecting shared data
by disallowing someone else to acess that data.

A mutex has two states, locked and unlocked. A mutex can never be owned
by more than one thread. A thread trying to lock a mutex wll have to wait
for the mutex.

A mutex has 3 types, `fast`, `recursive` or `error_checking`. The default
kind is fast. In glibc they are `normal`, `recursive` and `errorcheck`

| Behavior | NORMAL | ERRORCHECK | RECURSIVE |
|---|---|---|---|
| Owner locks again | **Deadlocks** | Returns `EDEADLK` | Allowed (count++) |
| Unlock when not owner | Undefined | Returns `EPERM` | Returns `EPERM` |
| Unlock when already unlocked | Undefined | Returns `EPERM` | Returns `EPERM` |
| Speed | Fastest | Slightly slower | Slightly slower |

| Attribute | Options | Purpose |
|---|---|---|
| `pshared` | `PTHREAD_PROCESS_PRIVATE` (default) / `SHARED` | Share the mutex across processes via shared memory |
| `robust` | `PTHREAD_MUTEX_ROBUST` | If the owner dies holding it, the next locker gets `EOWNERDEAD` and can repair state with `pthread_mutex_consistent` |
| `protocol` | `NONE` / `INHERIT` / `PROTECT` | Priority inheritance to avoid priority inversion (real-time) |

| C11 type | Same as |
|---|---|
| `mtx_plain` | NORMAL |
| `mtx_recursive` | RECURSIVE |
| `mtx_timed` | Allows `mtx_timedlock` |

A mutex can be initilized via the `pthread_mutex_init` function, or can be statically
initilized with `PTHREAD_MUTEX_INITILIZER`(fast),
`PTHREAD_RECURSIVE_MUTEX_INITILIZER_NP` (recursive)
and `PTHREAD_ERRORCHECK_MUTEX_INITILIZER_NP` (errorrcheck)

Mutexes can be locked and unlocked via the `pthread_mutex_lock` and the`pthread_mutex_unlock`
functions respectively. A mutex can also not frozen when lockign via the `pthread_trylock`func

An **UNLOCKED** mutex can be destroyed via the `pthread_mutex_destroy`func.

## usage & examples

```c
// init
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t errchkmutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

pthread_mutex_attr_t attr;
pthread_mutex_t mut;

int pthread_mutex_init(pthread_mutex_t &mut, pthread_mutex_attr_t attr*);

pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
pthread_mutex_init(&mutex, &attr);
pthread_mutexattr_destroy(&attr);   // safe once the mutex is initialized

// can also be done with 
pthread_mutex_init(&mutex, NULL); // defualt (fast)
```

```c

int pthread_mutexattr_init(pthread_mutexattr_t    *attr);

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);

//PTHREAD_MUTEX_NORMAL
//PTHREAD_MUTEX_ERRORCHECK
//PTHREAD_MUTEX_RECURSIVE
//PTHREAD_MUTEX_DEFUALT
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);

```

```c

int pthread_mutex_lock(pthread_mutex_t     *mutex);
int pthread_mutex_unlock(pthread_mutex_t   *mutex);
int pthread_mutex_trylock(pthread_mutex_t  *mutex);
int pthread_mutex_unlock(pthread_mutex_t   *mutex);
int pthread_mutex_destroy(pthread_mutex_t  *mutex);

```
