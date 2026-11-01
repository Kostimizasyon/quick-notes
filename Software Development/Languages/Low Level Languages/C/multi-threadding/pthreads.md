# pthreads

## info

C uses `Posix` threads where each thread can share the same memory (heap, globals)
but each has its own threads and registers, the scheduler either runs them concurrently
or interleaves them since memory is shared we need synching.

## usage & functions

These threads a handled via the `pthread_t` type. Then ran via the
`pthread_create` function. We can terminante these using the `pthread_exit`
Or it can be removed from memory after its done via the `pthread_join` function

```c

pthread_t t1;

// returns non 0 on error
// funcs passed HAS TO BE void*
// multiple args can be passed via structs
int pthread_create(pthread_t &t, const pthread_attrr_t attr, void* func, void* args);

// terminates the calling thread
// returns a val via ret_val if thread
// is joinable
void pthread_exit(void* ret_val);
// pthread_exit(NULL) waits till process exits
// using instead of return in main will lead to
// main terminating but the subprocesses keeping running

// waits untill threads job is done to terminate
// returns non 0 on failure
// if retval is not NULL then it will copy the exit
// status of the thread to where ret_val is pointing
int pthread_join(pthread_t &t, void** ret_val);

// returns the thread number of the current calling
// thread
pthread_t pthread_self();

// Marks the given thread as detached, when a detached
// thread terminatees its resaources are released back
// to the system without needing to join
// return non 0 on error
int detach(pthread_t thread);

```

```c
// example

typedef struct {
    int num;
    char[256] name;
} Arg;

void* worker(void* arg) {
    printf("%d) %s is working! \n",arg->name, arg->name);
    return NULL;
}

pthread_t t1;

struct Arg arguming = {
    .num = 24,
    .name = "Helloo"
} ;

int res = phtread_create(&t1, NULL, worker, (void*) arguming);

if (res != 0) {
    pthread_exit(&t1);
    return -1;
}

// we could actaully detatch this thread instead
// as we dont really care about what work it does
// so we dont need to waste resources tracing it
// but we would need to move return somewhere else as that
// would kill all processes runnig
pthread_join(&t1, NULL):
return 0;
```
