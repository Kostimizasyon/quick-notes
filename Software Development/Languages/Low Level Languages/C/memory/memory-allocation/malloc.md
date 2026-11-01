# malloc

Malloc is the act of allocating memory on the heap on a set
lenght. The memory is **uninitilzed**.

```c
void* malloc(size_t size);

// usage 

char* string = malloc(50);

  // use of string

free(string);

```
## depth

If the malloc cant find a big enough memory chunk for the allocation then
it will ask the kernel for more memory via (brk/sbrk) or mmap reducing
performance further.

Malloc is essentially packeged with a syscall so it is not the most
efficient thing ever
