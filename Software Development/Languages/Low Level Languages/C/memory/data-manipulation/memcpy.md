# memcpy

Copy size n from src to dest, returns pointer to dst. **If overlapping
adresses then undefined**.

```c
void* memcpy(void* dst, void* src, size_t size);

// usage
    char* string = malloc(10);
    char* hello = "hello world";

    string = memcpy(string, hello, 10);
```
