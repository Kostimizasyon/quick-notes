# friend

Friend is a keyword that lets another class acess its private fields as a friend.

friends have access to non-public, non-static and static (possibly inline) members
    

```cpp



class A
{
 int a = 0; // protected

 void funct() {}

 friend class X; // define the class x as a friend (ellaborated as a class)
 friend X;       // c++11

};

class X {

    friend void A::funct();
    
};

```

Template Friends


