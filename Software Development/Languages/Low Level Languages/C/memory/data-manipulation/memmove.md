# memmove

memcpy but worrks with overlap, is always safe but can be slwoer
due to compiler optimizations.

```c

void *memmove(void *dest,void *src, size_t n);

char *string = malloc(10);
memcpy(string, "hello", 6);              // "hello\0"

memmove(string + 2, string, 6);          // overlapping: src 0..5, dest 2..7
// string is now "hehello\0"
```
