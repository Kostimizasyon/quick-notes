# Raw String Literals

In cpp we can use raw string literals to express our strings in multiple lines and provide special
characters without using escapes

```cpp
std::cout << R"tag(Hello""World)tag";
```

Only thing it requires is a tag opening namely: R"anything()anything", one of the most useful ways to use it:

```cpp
auto lua_debug = R"lua(
local debug = function()
    print("Debuging!")
end
)lua"
```
