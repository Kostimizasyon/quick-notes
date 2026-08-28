# OOP

C++ has structs and classes for oop, which are almost the exact samething, except for the fact that structs are public by default and classes are
private by default. In practice structs are mostly used for small less complex little datatypes and stuff, where as classes are used for more complex
types.

```cpp

struct Point {

    int x = 0;
    int y = 0;

};

class Printer {};
```

Now a few things they share / oop princples

```cpp

// Constructors & Destructors
struct Point {

    // default constructor
    Point() {}
    // value constructor
    Point (int) {}
    // copy constructor
    Point(const Point &) {}
    // move  constructor
    Point(Point &&) {}
    // desctructor
    ~Point() {}
};

// Inheritance & polymorphism, override
struct Point {
    virtual void get_area() {}
};

struct circle : public point {
    void get_area() override {}
};

```
