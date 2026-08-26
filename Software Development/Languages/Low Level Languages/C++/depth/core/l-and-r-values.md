# L and R Values

## L Values ( Locator Values, Left Values ...)

l values, are essentialyl vlaues that hold some space in memory

## R Values ( Right Values )

Temporary values that arent going to be stored unless asigned to an L value, literals, literal function returns etc.
ANYTHING on the right is an R value

```cpp

std::string a = "hello";
std::string b = "world";

std::string c = a + b; // everythingo nn the left is an L value, and everything on the right is an R value, EVEN a + b, but not a and b just a + b
```

```cpp

int main() {

    int i = 10; // i is an L value, where 10 is an R value


    auto r_return = [] () -> int { 
        return 10; // returns an R value
    };

    
    r_return() = 10; // compiler error, left side mush be a modifiable r value

    // so if we were to change the fn to return an L value

    auto l_return = [] () -> int& {
        static int val = 10;
        return val;
    }

    l_return() = 10; // defined behavior


    // If an L value param function is called via an R value, the value will be converted to an L value then ran

}

```

# References

## L Value References

** Can only be taken from an L value ** unless, you use a const ref.

```cpp
int& i = 10; // compiler error

const int& i = 10; // no problem
```

## R Value References, implemented C++11

Essnetially just temporary references

```cpp
    
void printName(const std::string& name) {} // accepts both l and r

void printName(std::string&& name) {}      // overloads other func for r values

```
