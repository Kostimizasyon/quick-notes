# decltype

Decltype is a C++11 feature that gives us the ability to defer and use any type of an object
even a fucntions return type, this is all done in compile time with 0 runtime overhead.

```cpp

auto lambda = [](this auto& self) {
    self.update_values();
    return self.value;
}

using Base = decltype(lambda);

struct Derived : Base {
    void update_values() {
        value++;
    }
    int value = 0;
}

Derived d;

d.update_values();
d(); // calls the overloaded call operator of the lambda

```
