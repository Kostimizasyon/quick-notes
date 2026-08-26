# Templates

```cpp

template<typename T> // after <, it takes in template params
void Print(T val) { // since these are actually not even real, a syntax error or something like that, if the function isnt called is fine for compilation (clang gives an error)
    std::cout << val << "\n";
}

int main() {
    Print("Hello world!"); // only now, a string print is made. Otherwise it is essentially non existant
    Print<float>(5.5f);    // we can also specify our template arg

    return 0;
}

```

Templates are macros that write code in runtime/compiletime essentially, they will only create a function as its used, if a 
string call is never made for Print it wont be made. Essentially rust macros derive kinda.

They aint just generics, they can be used on classes and functions too.

```cpp
template<typename T, int N>
class Array { // for a C style array, we need to alloc memory, which should be known at compile time, thankfully templates are calcualted at compile time!
        T Array[N];
}

int main() {

    Array<int, 5> five_len_array;

    return 0;
}

```
