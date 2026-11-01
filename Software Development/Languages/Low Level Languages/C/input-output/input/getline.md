# ssize_t getline(char **lineptr, size_t *n, FILE *stream)

Get a whole line of input from the user, sources any FILE *, it mallocs and
reallocs on its own uses a buffer to store the input. (cant overflow)

## Parameters

### lineptr

Adress for the buffer for the input to be stored, we can make it a nullptr as
getline will alloc by itself anyways

### *n

Adress for the size of the active buffer being used
Getline updates it as the buffer grows

### *stream

Where to read the input from, a file or just stdin (input from cmd)

```c

char *line = NULL;
size_t cap = 0;
getline(&line, &cap, stdin);
free(line);

```

## Return

Returns the chars read or EOF
