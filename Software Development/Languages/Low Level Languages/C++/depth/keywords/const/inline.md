# inline c++17

Inline functions, suggest to the compiler, hey you could inline this instead of calling it, you can just copy over its content.

```cpp

inline int square(int x) {
    return x * x;
}

int main() {

    // here constexpr is better, just humor it.
    int val = square(5); 
    // the compiler will treat this as int val = 5 * 5; (which it would do by default at higher optimizations regardless of the inline flag)
    // the inline flag actually can deoptimize code use it carefully, the C++ Weekly episode explains this pretty well.
    // the cost of the inlining wont change, but the threshold will increase just by adding inline, so in most cases its pretty fine just not adding inline

    // o1 actually wont inline any function ever regardless of the flag
}

```

Inline variables

```cpp
// in our header:
int counter = 0; // error if included in multiple cpp files, multiple definitions
inline int counter = 0; // fix

// common usage:
class Foo {
    inline static int x = 0;
}


```
