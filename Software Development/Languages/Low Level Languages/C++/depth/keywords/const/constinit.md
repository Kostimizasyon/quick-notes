# constinit C++20

Initilize the value at compile time, doesnt work for local values. They are NOT const. They are mutable.
If you want a const constinit, you just want a constexpr.

Initilization of global statics happen before main.

Of course their values should be given as constexpr otherwise UB? im not sure.

```cpp

const int &get_value() {

    constinit static std::mutex my_mutex;

    std::scoped_lock l{my_mutex};

    constinit static auto value = 4;

    ++value;

    return value;

}
```

