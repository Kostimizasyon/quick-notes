# memset_explicit 

C23, it makes it so memset CANNOT be overwritten / overoptimized by the compiler.

```c
void* memset_explicit(size_t n, void* a, int c, size_t n);
```
