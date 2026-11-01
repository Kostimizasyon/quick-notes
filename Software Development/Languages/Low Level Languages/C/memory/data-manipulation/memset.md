# memset

Fills the given area's n poitns with the const val c, returns a pointer to area.
DOES IT ONE BYTE AT A TIME.

```c

void * memset(void* a, int c, size_t n);

int* arr = malloc(10 * ( sizeof int ));

memset(arr, 67, 10 * ( sizeof int ));

```
