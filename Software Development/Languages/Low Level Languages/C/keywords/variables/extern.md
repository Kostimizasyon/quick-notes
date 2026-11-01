# extern

    Externing is basically the process of telling the compiler
    to skip over a variable check, dont alloc memory and tell it
    that the linker will find it.

    It allows us to declare a variable once and use it everywhere
    such as global variables, header variables etc

```c

// header declaration

    // count.h
        extern int count;

    // count.c
        int count = 0;
    
    // main.c
        #include "count.h"

        // we can now uise the count variable

// global variables for functions

int count;

// since count is never used before this extern call, it is redundant
int main() {

    extern int count; // now it uses the global variable

}


```
