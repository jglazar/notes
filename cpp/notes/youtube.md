# Notes from YouTube

## The Cherno -- Smart pointers

Can assign `std::unique_ptr<T> (new T)` or use `make_unique<T>`
  * Cannot be copied, so `std::unique_ptr<T> = new T` disallowed


Don't use `new` to make `std::shared_ptr<T>`, since that invokes 2 constructors
due to the ref tracking behavior of shared pointers.

`std::weak_ptr` acts like `std::shared_ptr`, but does not increase ref count or
keep an object alive
  * Useful for seeing if object is alive or dead

## The Cherno -- Move semantics and std::move

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
