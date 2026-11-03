# perror

```c
void perror(const char *s);
```

Perror produces a message on standard error describing the last errror
encountered during a call to a system or a lib func.

If s is not NULL and *s IS NOT `\0`, the argument is printed follow by a 
colon and a blank, then the corresponding value to the current value of
errorno and a newline.

The global error list `sys_errlist[]`, which can be indexed by errno.
The largest number provided in the table is `sys_nerr`-1

It essentially just add `strerror(errorno)` after the thing you give it.
