# realloc

Realloc allows us to resize an already alloced memory, however if there
is fragmentation in the memory  it is more than likely for us to not
have enought space to have a continous memory, resulting in a copy and
mallocing memeory elsewhere (slow asf)

```c

void* realloc(void *ptr, size_t new_size);

char* string = malloc(50);

// usage 

char* temp = realloc(string, 100);

if (!temp) { free(string); return -1; }

arr = temp;

```
