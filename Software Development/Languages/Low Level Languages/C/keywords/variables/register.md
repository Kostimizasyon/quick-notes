# register

Register is us telling the compiler store this in the register as I will use 
this a lot, most of the time compilers do ignore this in more modern times and
they optimize it better than we ever can.

Best use case is something like:

```c
register int i;

for (i = 0 ; i < 10000000 ; i++) {
    // some operation
}
```

Where i will be used a LOT so its better optimization to keep it in the 
register for fast acess.

But registers do not have a memory adress so:
```c
register int i;

&i // error
```
