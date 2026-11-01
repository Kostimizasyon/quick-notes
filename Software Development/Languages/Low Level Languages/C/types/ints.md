# INTS

```c

// strlen, sizeof...
size_t      // used for a coutner of bytes, unsigned int capable of [0, SIZE_MAX]

// read, write...
ssize_t     // used for a counter of bytes AND error indication,
            // signed int capable of [-1, SSIZE_MAX]

int8_t      // described as *SIGN*int*TYPE*_t, can be unsigned (u), signed(nothign)
            // and 8-16-32-64 for size
            // TYPE can be normal(blank)

ptrdiff_t   // used for a counter of elements or an arr index. Result of 
            // subtracting two pointers, signed int of [PTRDIFF_MIN, PTRDIFF_MAX]

int_fast8_t // described as *SIGN*int_*TYPE**SIZE*_t 
            // *SIGN* can be unsigned (u), signed(nothign)
            // *TYPE* can be:
            // fast -> whatever is the quickest for *SIZE* match (ATLEAST N *SIZE* BYTES)
            // least-> smallest type that holds *SIZE* (ATLEAST N *SIZE* BYTES)
            // *SIZE* can be 8,16,32,64

```
