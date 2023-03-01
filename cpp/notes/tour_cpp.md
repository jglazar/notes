# Tour of C++, 3rd edition

## Basics

### Compilation

Compiler produces object files, which are linked into executable.

All entities are statically-typed -- compiler must know type.

There is only one `main()` function. Don't need to return value 
(default is success).

Modules are useful in C++20, but aren't supported by CMake yet. 
Syntax is simply `import std`, e.g.

### Functions

Don't need variable name in declaration (just type). Name only 
needed for function definition.

Compiler throws error if picking correct function (out of all 
overloaded fcts with same name) is ambiguous. E.g., `print(0,0)` 
cannot choose between `print(int, double)` and `print(double, int)`.

### Types

Size is implementation-dependent. Check size with `sizeof` operator. 
Can specify with alias like `int32_t`.

Apostrophe is useful for separating digits (for human readability).

0b is binary prefix, 0x is hexadecimal prefix, and 0 is octal prefix.

Bitwise operators apply to each bit separately. Logical operators 
apply to entire variables and output just T/F. E.g., `&` and `|` are 
bitwise but `&&` and `||` are logical.

Compound expressions have unspecified evaluation order.

Can initialize variables with simple `=` or `{}` or `= {}`.
  * `=` converts to declared type, which could accidentally chop 
  off info. E.g., `int i = 7.8` chops down to 7. Compiler will 
  throw error if `{}` used instead.

`auto` figures out type from value. Useful for generic programming. 
Should use most of the time! Only specify type if there's a specific 
reason, like precision or non-obvious types.

### Scope

Variables can be local (between `{}` in fct or lamnda, e.g.), class, 
namespace, or global (none of the above).

Objects are constructed, used, then destroyed. Member objects are 
destroyed when the class object is destroyed. Namespace objects are 
destroyed at end of program. Objects made with `new` must be explicitly 
destroyed with `delete`

`const` = don't change during use. Useful for passing data to functions 
using pointers or references. May be evaluated at runtime.

`constexpr` = evaluate at compile time. Useful for setting constants. 
  * Can tag function to enable `constexpr` variables which use 
  function in definition. All fct args must be `constexpr` too in 
  that instance.
  * `constexpr` functions can also be called normally.
  * Array sizes are `constexpr`.

`consteval` = use function only at compile time. Like a stronger 
`constexpr`.

`constexpr` and `consteval` functions cannot have side effects and 
can only use arguments. They are pure functions.

### References

Use range-based loops: `for ( auto v : vec ){  }`, or pass-by-ref 
with `for ( auto& v : vec )`. 

References cannot refer to different objects after initialization, 
unlike pointers.

Apply `const` to pass-by-ref arg to avoid accidental changes while 
benefitting from not copying. This is quite common.

There is only one `nullptr`. There is no null reference.

Can advance pointer `p` to next element in array with `++p`.

Pointers can be reassigned without affecting underlying variables. 
References cannot be reassigned, so reassigning refs actually just 
changes the underlying variable.

Assignment requires that assigned-to object has a value. Initialization 
makes uninitialized memory into valid object.

### Control

`switch` statements use `break` to move past entire block once satisfied. 
Should set a `default` option at end.

Can introduce new variable in for-loop or if-statement sections. E.g., 
`if (auto n = vec.size(); n != 0){ ... }`. Variable remains in-scope 
for both branches of if-statement.

Leave out `== 0` or `== nullptr`. It's implied.

### Advice

Use the STL.

Keep functions short and focused. They should do one logical operation.

Overload functions to perform same task on different types.

Function may/must be evaluated at compile time -- `constexpr`/`consteval`.
  * No side effects? Mark either.

Use digit separators. Use the `{}` initializer. Use `auto`.

Minimize variable scope. Use short names for local vars and longer names 
for nonlocal vars. Avoid all caps.

Use the implicit if-statement check against 0 or nullptr.

Use range-for rather than explicit incrementor `i` var.

Only use `unsigned` for bit manip.

State intent, not code, using comments.

## Ranges

Ranges are a generalization of `{begin, end}` sequence definitions. 
They can be `{begin, end}` iterators, `{begin, size}`, or `{begin, 
predicate}`.

Views (range adaptors) grab slice of range. Can filter, take, 
transform, and more. 
  * Doesn't own elements, and cannot outlive underlying range. E.g., 
  cannot return view of range that only lives in function.
  * Cheap to copy, so pass by value.

Generators (factories) create range on-the-fly. Can create empty 
range, single-element range, iota (finite or infinite!), and stream.

Pipelines are useful for organizing. First element must be range.
  * Views and pipelines are implemented with template metaprogramming, 
  which can degrade performance. Be sure to measure against normal 
  for-loop!

Create custom parallel range algorithm with `void sort(auto policy, 
random_access_range auto& r){ sort(policy, r.begin(), r.end()); }`

## Pointers

Owning pointers like `unique_ptr` and `shared_ptr` are responsible 
for deleting the object. Non-owning pointers include `*` and `span`.

Avoid dangling pointers! Don't return a pointer to local object from 
function. 

Memory leaks cause poor performance and sometimes crashes.

RAII is implemented in constructor/destructor pairs.

`unique_ptr` destructor destroys object. Last `shared_ptr` destructor 
destroys object. Ensures object is destroyed if function is exited 
or exception is thrown!

Only use `shared_ptr` if needed. Incurs some cost.

Need to pass pointer into `unique_ptr` or `shared_ptr`. Use 
`make_unique` or `make_shared` in `<memory>` library to simplify.

Smart pointers are better than normal pointers, but worse than using 
pre-built containers. Data races can still happen.
  * Use smart pointers for sharing an object or referring to 
  polymorphic object (don't know exact type).
  * Don't use smart pointers for returning a collection of objects 
  from a function --> containers use copy elision and move semantics!

## Essential operations

* Constructor -- `X(arg)` or `X()`
* Destructor -- `~X()`
* Copy constructor -- `X( const X& )`
* Move constructor -- `X( X&& )`
* Copy assigner -- `X& operator=( const X& )`
* Move assigner -- `X& operator=( X&& )`

Compilers typically perform copy elision during assignment.

Compiler automatically creates default operations as-needed. If you 
specify `operation = default`, then compiler does NOT generate 
remaining default operations. 

Can specify `operation = delete` to avoid generating that operation. 
Useful for disallowing default memberwise copying in base class.

You should specify copy/move operations if object contains pointer 
member. 

Use `explicit` for constructors taking a single argument, since this 
prevents implicit conversion (like `Vector v = 7` reserving 7 spaces).

Simple types can use memberwise copy. Complicated types like `Vector` 
should not, since that'll just copy pointers to the same underlying 
data. Resource handles need custom operations.

Avoid using `std::copy()`. 

Use const reference arguments for large operands.

When operator overloading, specify all common operations.

Use initializer list in member functions to initialize member 
variables. Executes before function body. Useful for setting `const` 
member vars and references.

rvalue reference `&&` is ref to something nobody can assign to, 
allowing us to grab its value. E.g., variables returned from 
functions.

Use move semantics or smart pointers to move resources between scopes.
  * Return containers by value and rely on copy elision / move


