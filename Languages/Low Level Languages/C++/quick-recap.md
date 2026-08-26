# C++ BREAKDOWN

## Const

Const is your best friend, it optimizes compiler. Const any value u can.
```cpp
// returns const int, param is a non-reassignable local copy, const-qualified method (no member mutation, usable on const objects)
const int function(const int param) const {} 
// a constant pointer to a constant intiger
const* const int a; 
```

### Constexpr

Constexpr are just const values that are calculated at compile time.
```cpp
constexpr int LENGTH = 500;
constexpr int HEIGHT = 500;
constexpr int AREA = HEIGHT * LENGTH; // the variables it uses HAS TO also be constexpr
```

Values that are calculated in compile time if given constexpr params, but can still be executed at runtime. 
These functions can only call other constexpr functions, they should always return

```cpp
constexpr int a() { return 5 * 5; } // guarenteed run
constexpr int a(int b) { return b * b } // only runs on compile time if b is constexpr
```

### Consteval

ONLY FUNCTIONS
Consteval => ONLY use these at compile time, error if used in runetime (c++20)

```cpp
consteval square(int x) { return x * x; }

square_ce(5);      // OK
square_ce(y);      // error — y isn't known at compile time
```

## HEADER SETUP

Create a header for the class, write the class fields then do function declerations with params + return types
just not the function block essentially, instead a ";"
```cpp
class test {
    int a = 5;

    Test(int a );
    void fuck(int param);
}
```
Then create a c++ file, and implement there while importing header, use namespaces
```cpp
#include "test.h"

Test::Test(int a) : a(a) {}

void Test::fuck(int param) { std::cout << "fuck"; }

```
Then just import the header anywhere and use the classes with a namespace

### Forward Declaration
Two headers importing eachother, fix:
```cpp
// in the header do:
class ImportedType; // init so we can actually use it

void a(ImportedType b);

// then in the c++ file
include "ImportedType.h"
// import here instead
```
