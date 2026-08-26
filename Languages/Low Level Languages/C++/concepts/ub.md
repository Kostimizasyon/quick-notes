# Undefined Behavior

C++ code where the std is unclear about what it should do. Dangerous stuff, anything can happen.
Compilers wont really care about undefined behavior, and wont optimize with them in mind.

The compiler will always choose optimization over fixing undefined behavior.

```cpp
int n1, n2 = 0;

int should_optimize(int n) {

    for (size_t j = 0 ; j != n ; j++) n1++
    for (size_t j = 0 ; j != n ; j++) n2++

    // compiler will actually just optimize this away to
    // for (size_t j = 0 ; j != n ; j++) n1++ n2++
    // which actually can caused undefined behavior, as if n is odd
    // the first loop never ends, and n2 is never incremented
    // but in the standard a loop is considered terminatable, so the compiler doesnt care.
}

// another example: 

bool g(int l)  {

    if ( l == INT_MAX) return false; // the compiler will actually optimize this away, because it doesnt really care if ur program is undefined or not
    // this is because the compiler only cares about the stuff std enforces on it, it doesnt care when the issue isnt handled clearly by the std

    return l + 1 > l; // this here is also optimzied to just be true, for an int +1 is always greater.
    // we can see from the example below that the compielr only does tihs because int overflow is strictly ub

}

bool f(unsigned int a)  {

    return a + 1 > a; // here the compielr actually wont optimize this away
    // because an overflow of an unsigned int is perfectly defined behaviour, the compiler
    // will actually check to see if it overflowed or not

}

```

One of the main dangers behind an ub is the fact that a compilers upgrade might introduce some new ub:

```cpp

// big old example:

struct MyAwesomeType {
    int get_val() {
        if (this) {
            return value;
        }
        else {
            return 0;
        }
    }
};

// this code used to be almost a standard thing every dev did, if the given thing is a nullptr return 0
// however around 2016 compilers actually updated to force "if (this)" to be a tautology, causing ub all around
// the place

// another example

int i = 1;

int main() {
    std::cout << "Before";
    while (i) {}
    std::cout << "After";
}

// GCC pre 10 actually just hung after Before, then the std declared on some spesific cases of infinite loops
// a new behavior, where then the compilers optimized away the infinite loop causing After to fire right after and exit

```
