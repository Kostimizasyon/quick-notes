# Welcome Rustacean, this is rust! A "statically" typed, borrow checking language with a really friendly compiler!

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

bools, chars (which are fucking 4 bytes for some reason)

tuples => can hold different data types together in a cluster but they have fixed size
```rust
let a = (1,2,5,"hello");
```

arrays => can only holde one data type, fixed size (unless vec)
```rust
let a = [1,2,3,4,6];
let vec = vec![3;5]; // vec of 5 3s
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


