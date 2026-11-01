# calloc

malloc some memory but also initilize the memory to 0.

```c

void* calloc(int n, size_t size);

// usage 

    int* arr = calloc(10, sizeof(int)); // get an array of length 10

    // use of arr

    free(arr);

```

## depth

It pre checks for overflow via count * size, if it overflows it will return
NULL, same as malloc for rest
