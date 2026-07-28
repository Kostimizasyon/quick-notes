# Welcome Rustacean, this is rust! A "statically" typed, borrow checking language with a really friendly compiler!
 
## WEIRD RUST SYNTAX & FEATURES

```rust

// NO () FOR BOOLEAN EXPRESSIONS
if a == 5 {}

// TYPE AFTER
let a : i32 = 0;

// CONSTRUCTING TYPES & CALLING CONSTRUCTOR
let b = String::new();

```

## CLI Tools
 
### Rustc
Rustc is our compiler for rust
```bash
rustc <file-name> # compile and build exe for given rust file
```
 
### Rustup
Our rust toolchan manager, allowing us to update rust view docs etc
```bash
rustup update
rustup default nightly
```
 
### Cargo
Cargo is our package / project manager in rust.
```bash
cargo new <project-name> # creates new project
cargo init # create cargo.toml 
cargo check # compile without creating binary exe
cargo build # compile and build exe
cargo run   # compile, build and run 
cargo add <crate-name> # add a crate to project:
```
 
And to use a crate / import stuff from rust
```rust
use std::collections::HashMap; // now hashmap is declared in this scope
use std::collections::* // not recommeneded
use std::collections::HasMap as HP // refer to it as HP
```
 
## Types
Unlike other programming languages, variables are const by default ( our compiler is good enough for us to never mention our types)
```rust
let a = 5;
a = 7; // THIS WOULDNT COMPILE
let mut a = 7; // shadowing!
a = 9; // works
const MAX_NUM = 85 * 85 * 90; // FULLY const, compile time calculated
static GREETING : &str = "hello"; // static lifetime, lives througout program
```
### Data Types
 
#### Primatives

i8, i16, i32, i64, i128 & u8, u16, u32, u64, u128 || Unsigned and signed ints
isize & usize || Unsigned and signed ints for architecture size
f32, f64 || Floating point ints, (f64 is actually more optimized for CPU's so its defautl)
chars (which are fucking 4 bytes cuz unicode, why.)

**&str** ===> string_view from c++, used for literals and such as a readonly value, NOT EQUAL TO STINRG
CANT BE CONVERTED TO STRING EXPLICITY.
 
#### Compound Types

##### tuples => can hold different data types together in a cluster but they have fixed size
```rust
let a = (1,2,5,"hello");
```
 
##### arrays => can only holde one data type, fixed size (unless vec)
```rust
let a = [1,2,3,4,6];
let a = [3;5];
```
 
##### vectors => dynamic arrays 
```rust
let vec = vec![3;5]; // vec of 5 3s
let vec = Vec::with_capacity(5); 
vec.extend([1,1,1]);
vec[4];
vec.get(4); // returns option
let item = vec.pop(); // returns option
vec.push(item);
```
 
##### slices => a slice into a memory block via a pointer and a range
```rust
let vec = vec![3;5];
let str = String::from("Hello");
let slice_vec = &vec[1..=2]; // slice into vec starting from 1 including 2
let slice_str = &str[0..2];  // slice of str starting from 0 until 2
let str_slice: &[&str] = &["one", "two", "three"]; // coercing an array to a slice
for s in str_slice {} // they are iterable
```

#### Pointers

##### Boxes => std::unique_ptr
 
Usefull for things that we dont really know the size of and shouldnt live on the stack

```rust
let a = 5;
let boxed_a = Box::new(a);

// move a value by dereferncing
let b = *boxed_a;
```
##### RC => std::shared_ptr     (Read only data than can be owned by multiple people, and dropped when last one stops being used)
```rust


```

###### Weak

#### Cells & RefCells

##### Cells

##### RefCells

#### Exception Handling
In rust we exception handle via types

##### Option std::optional<T>

Either return Some value or None

```rust

let a = "59".parse();

// a is an option type

let b = match a {
 Some(s) => s,
 None => false // fallback
}

a.unwrap();    // panic if no val
a.unwrap_or(); // fallback

```

##### Result<Ok, Err>  std::expected<T, E>

Either return Ok or Err

```rust
fn read_file() -> Result<String, std::Error> {
  let data = std::fs::read_to_string("f.txt");

 let mut file = match data {
  Ok(f) => f,
  Err(e) => return Err(e),
 }
}
// equivelent to
let mut file = data?;


a.unwrap();    // panic if err
a.unwrap_or(); // fallback
```

## Move Semantics

In rust, primative data types like i32, &T (and some non primatives as long as they implement the copy trait) are moved via copy,
but other types such as: Vec<T>, &mut T are moved via move!
```rust
let intval : i32 = 5;
let new_val : i32 = intval;
println!(intval); // still works!
let mut strval : String = String::from("");
let mut new_val : String = &strval;
println!(strval) // FIX: THIS WOULDNT COMPILE, as strval's reference has been moved to new_val,and the og has been destroyed
// to copy these types:
let strval = String::from("shdjqeıojwqojdjwq");
let new_val = strval.clone(); // copied!
```
 
## Lifetimes

## "OOP"

### Structs

Structs in rust are just data definitions, we can define functions on them.
```rust
pub struct Test {
 b : i32,
}
```

### Impl

How we implement functons for structs

```rust
impl Test {
 pub fn new(b : i32) -> Self {
  Self{ b: b}
 }
}

```

#### Self Param

```rust
impl Point {
    fn show(&self) { }        // borrow immutably — just reading
    fn mutate(&mut self) { }  // borrow mutably — modifying fields
    fn consume(self) { }      // takes ownership — transforms/destroys it
}
```

#### Traits (blueprints)

```rust
trait Drawable {
 fn draw(&self)
}

impl Drawable for Circle {
 //code...
}
```

## Pattern Matching

Rust doesnt have switch, instead it has match it is a lil magical

```rust
// match is an expression not a statement.
let match_type = match x {
    1 => println!("one"),
    2 | 3 => println!("two or three"),   // OR pattern
    4..=6 => println!("four to six"),    // inclusive range
    n if n > 100 => println!("big: {n}"), // conditional
    _ => println!("other"),               // default, MUST be exhaustive
}

match shape {
    Shape::Rectangle { w, h } => w * h,          // pulls fields out directly
    Shape::Circle(r) => 3.14 * r * r,             // pulls tuple-variant data out
}

match point {
    (0, 0) => println!("origin"),
    (x, 0) => println!("on x-axis at {x}"),
    (x, y) => println!("at {x},{y}"),
	}
```

## Functions

### Lambda Functions

```rust

// parameters => |a, b| // we actually can get away with not giving types
let add = |a, b| a + b;

// by default params gets borrowed
let destroy = move |a| a;
// move makes them move and take ownership

```

### Optional Params

For optional params, we use Option

```rust
fn test(hello : Option<bool>) {

 let hello = hello.unwrap_or(false);

}
```

