# consteval C++20

Consteval is essentially just constexp, but unlike constexpr we FORCE the compiler to always do the calculation
at compile time and throw if it cannot be done at compile time.

```cpp

consteval int calculate_area(int a, int b) {
    return a *b;
}

auto a = calculate_area(4, 5); // calculated at compile time

int x = cin.get();

auto b = calculate_area(x, x); // throws

```

## if consteval C++23

Can only be used within a consteval/constexpr function, behaves like std::is_constant_evaluated()
but instead its just a branching instead of a bool returning func call

```cpp

constexpr auto get_result(int param) {
    if consteval {
        return param * 2; // compile time path
    }
    if !consteval { 
        return param;    // runtime path
    }         
}


```
