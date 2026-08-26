# std::endl

The endline operator is essentially just:

```cpp

std::cout << "Hello world" << std::endl;

// is just equal to:

std::cout << "Hello world" << '\n' << std::flush; // flush the buffer
```

And almost 9 out of 10 times we should not flush the buffer, we have no reason to do so, so our
best practice is just essentially:

```cpp

for (int i = 0 ; i < 100000 ; i++) {
    std::cout << "hello world\n";
}

```

## New line operator

In our new line operator we should actually always use '\n' instead of "\n" even though there isnt
too big of a difference treating it as a char is better than a string as the compiler wont need to
iterate over the char since it knows its just one command.
