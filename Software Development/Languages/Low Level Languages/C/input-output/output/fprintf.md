# fprintf

Output a string to the given stream. Streams:

- `stdin` (fd 0): standard input. Input only (keyboard or piped data), so you read from it, you don't `fprintf` to it.
- `stdout` (fd 1): standard output. Normal program output, goes to the terminal unless redirected.
- `stderr` (fd 2): standard error. Errors and diagnostics, unbuffered, and separate from `stdout`.
- `actual text file` (fd 3 or higher): a stream you open with `fopen`, gets the next free fd.

```c
int fprintf(FILE *stream, const char *format, ...);

fprintf(stderr, "Hello here is error: %s", strerror(errno));
```
