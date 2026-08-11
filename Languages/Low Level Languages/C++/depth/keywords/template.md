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

// also

template<typenamei... Types)
void print(Types... args) {

}

```

Templates are macros that write code in runtime/compiletime essentially, they will only create a function as its used, if a 
string call is never made for Print it wont be made. Essentially rust macros derive kinda.

In c++20 we can also use the requires keyword to implicitly require the type given to have spesific attributes
We can group these with the concept keyword to define speesific requirements aswell

```cpp

template<typename T>
concept SupportsLessThan = requires (T x) { x < x; }

template<typename T>
requires std::copyable<T> && SupportsLessThan<T>
T mymax(T a, T b) {
    return b < a ? b : a;
}

// we can also use the require infront of auto OR as a bool value

concept HasPushBack = rqeuires (Coll c, Coll::value_type v) {c.push_back(v);}; 

void push_back(HasPushBack auto const& a, const auto& val) {

    auto b = // some value
    if constexpr ( requires { b.push_back(val) }) {}

    
} 

```


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
