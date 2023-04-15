# Notes from YouTube

## The Cherno -- smart pointers

Can assign `std::unique_ptr<T> (new T)` or use `make_unique<T>`
  * Cannot be copied, so `std::unique_ptr<T> = new T` disallowed


Don't use `new` to make `std::shared_ptr<T>`, since that invokes 2 constructors
due to the ref tracking behavior of shared pointers.

`std::weak_ptr` acts like `std::shared_ptr`, but does not increase ref count or
keep an object alive
  * Useful for seeing if object is alive or dead

## The Cherno -- move semantics and std::move

Before C++11 you copied even if not needed
  * Pass object into function that takes ownership
  * Return object from function (though RVO/copy elision could help)

Move constructor should be marked `noexcept`

Example move constructor -- `A(B&& b) : my_b(std::move(b)) {}`

This calls the copy constructor when building `c` -- `B b = "test"; B c = b;`

This calls the move constructor when building `c` -- `B b = "test"; 
B c(std::move(b));` or `B c = std::move(b);` 

`std::move(x)` is like `(B&&)x` cast, but figures out type automatically at
compile time

`c = std::move(b)` calls move assignment if c already initialized
  * Assignment is called when variable is assigned into existing variable
    * Think of `y = x` as `y.assign(x)`, where y already exists

## The Cherno -- singletons

⚠️ C++ Core Guidelines recommends against using singletons! Just use global data
instead (ideally const)

Singleton is class with only 1 instance -- basically just global data with
associated functions
  * Basically just a namespace (kinda like `utils` in Chrom3D)

Classes are meant to be instantiated many times in many ways (polymorphism). So
why even have singletons?
  * Keeps things more organized, allows for private variables, and allows
    assignment of singleton object to flexible variable name

Good candidates for singletons: RNG, renderer (just functions), logging

How to implement
  * Don't want a public constructor -- make private
  * Want static function `get` that returns ref to single instantiation
    * Can bypass with `return this->get().member;` from class methods
  * Have private static member that is the instatiation (self-referential)

Access singleton elements or methods with `Singleton::get().method()`

Easy to accidentally create 2nd instance with `Singleton i2 = Singleton::get();`
rather than `Singleton& i2 = Singleton::get();`
  * Delete copy constructor and assign operator!

## The Cherno -- global variables

Could create `globals.cpp` and place variable definitions there, then declare
appearances in other files as `extern`

Including header in many files creates many copies (preprocessor trivially
copy-pastes code)

Global `static` implies internal linkage -- only visible within current `.cpp`
file. Then when `#include` copies over code, each `.cpp` has its own version!

`inline static` variable inside a class in `.h` file correctly creates only 
one instance

`inline` for global variable works best. Acts as if variable was included in one
`.cpp` file.

## Flipcode -- reduce header dependencies

Don't include header if only used to define type for a pointer
  * Generally, use pointers instead of raw member variables

Use nested datatypes if only used privately by one class (e.g. my `Axis` struct)

Avoid preprocessor `#DEFINE` -- use `static const` as private member instead

If unable to hide type defn, use namespace

Use friends to access data/services from singletons
