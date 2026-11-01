# memchr

Memchar scans the initial n bytes of the memory pointed to by s for the first
instance of c.

Returns a pointer to the matching byte or NULL if it doesnt exist.

```c

void* memchr(void* s, int c, size_t n);

    char* hello = "hello";

    char* found = memchr(hello, 'l', strlen(hello));

    if (!found) {
        printf("fuck\n");
        return;
    }

    ptrdiff_t ind = hello - found;

```
