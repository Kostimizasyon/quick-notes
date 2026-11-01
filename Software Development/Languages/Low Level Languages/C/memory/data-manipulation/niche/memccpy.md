# memccpy

 The  memccpy() function copies no more than n bytes from memory area src to memory
 area dest, stopping when the character c is found (c is copied).
 If the memory areas overlap, the results are undefined.

 The memccpy() function returns a pointer to the next character in dest after
 c or NULL if c was not found in the first n characters of src


```c
    void* memccpy(void* dest, const void* src, int c, size_t n);

    char* keyval = "key=val";

    char* res = malloc(20);

    char* end = memccpy(res, keyval, '=', sizeof(keyval));

    if (end) {
        *(end - 1) = '\0'; // replace the '=' with null
    }

```
