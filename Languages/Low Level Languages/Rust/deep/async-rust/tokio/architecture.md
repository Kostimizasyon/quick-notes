# Tokio Architecture

[referencevid](https://www.youtube.com/watch?v=FUg1y-yv6cs)

Tokio uses Tasks which are up to ~64kb's, theya are Lazy and are scheduled and executed via the Scheduler and Executor

Tokio's arcitechure is quite simple, it consists of 4 main parts:

## The Runtime

The parent to all, handles how the Tasks execute and are planned.

### Scheduler & Executor

Schedules and executes tasks. Scheduler pickes them, executor executes them.

#### Global Task Queue / Injection Queue

Where tasks lay globaly before they are locally assigned to threads local queues

#### Local Task Queue

Task queue's that are spesific to certain threads, one per thread.

256 slot ring buffer. ( small to fit inside a cpu cache )
Lock free

#### Work Stealing

One of the biggest reasons as to why tokio is really fucking fast. Tokio wont let a core sit idle, it will firstly check the global
queue for tasks, if it cannot find any, it will steal work from other threads local queues and give that thread a task.

### Threads

Cpu threads duh.

### IO Driver / Reactor

Bridges the tasks between OS, parks the tasks frees workers / threads.

Built on mio

### OS

OS
