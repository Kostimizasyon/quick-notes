# constexpr C++17

Constant expressions are expressions that are calculated at compile time, works on only certain types.
Mostly primative.

```cpp

// Constexpr functions are ran at compile time if the compiler can know the params
// at compile time otherwise it behaves just like a regular function call

// we tell the compiler, this function CAN BE calculated at compile time.
// doesnt mean it always is calculated at compile time. We just tell the
// compiler you can do it.
constexpr int calculate_area(int a, int b) {
    return a *b;
}

auto a = calculate_area(4, 5); // calculated at compile time

int x = cin.get();

auto b = calculate_area(x, x); // calculated at run time

```

## If constexpr:

```cpp

// without constexpr, the branch wont know what route to
// go for and it will get confused and throw an error

templatre<typename Param>
auto do_work(Param param) {
    if constexpr ( param / 2 != 0 ) {
        return 2
    }
    else {
        return 1.2
    }
}

std::is_constant_evaluated() // True if the given expression is evaluated constantly

constexpr auto do_work() {
    // this is technically a runtime check
    if (std::is_constant_evaluated()) {
        return 42;
    }
    else {
        return 43;
    }
}

auto c = do_work();           // returns 43
const auto a = do_work();     // returns 42
constexpr auto a = do_work(); // returns 42

```
