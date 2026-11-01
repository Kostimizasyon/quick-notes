# int getchar(void) {}

getchar reads the input from the user in a line buffer, usually used like:

```c
int c;

while ( ( c = getchar()) != EOF ) {}
```
getchar triggers on each char read from the buffer.
