# Optimization Tips

## Johnny's SW Lab

### Dangerous features

Some features were fast, but haven't evolved with CPU architectures

Vectors of pointers `std::vector<Object*>`
  * Promotes indirection, leading to 10x slowdowns
  * Causes many small allocations, fragmenting memory
  * Required for polymorphism in containers
  * ✅ Use `std::vector<std::variant<...>>` instead
  * ✅ Use `std::vector<std::unique_ptr<...>>` with custom allocator
  * ✅ Use polymorphic arrays or multivectors

Avoid large classes that promote data non-locality
  * Should have frequently-accessed data listed together in class definition
  * Typically, 64 bytes of data are fetched into cache at once

Avoid large virtual functions in unsorted containers, since it'll load cold code

Avoid explicit `for`-loop integer indices
  * Prevents compiler optimizations due to possible out-of-order evaluation
  * ✅ Use range-based for loops, `std::transform`, and `std::reduce`

### Excessive copying

Passing objects
  * Pass big objects (like vectors) by reference
  * Pass small objects (like int/double/char/ptrs) by value

Declare and assign objects at once
  * `Type a = b` or `Type a(b)` uses copy constructor once
  * `Type a; a = b` uses default constuctor and assignment operator

Reuse old variables to avoid reallocations 
  * Write assignment operator to only reallocate if new size > old size
  * ❗️ Very important within hot loops! Initialize one temp variable outside
    loop and overwrite as-needed

Use `+=, -=, *=, /=, &=, |=` to avoid temporary objects
  * ❗️ Applies to compound operations
    * `Type res = (a1 + a2 + a3) / b` is equivalent to `Type tmp1(a1 + a2); Type
      tmp2(tmp1 + a3); Type res(tmp2 / b);` -- 2 temporaries!
    * ✅ Break up operations to avoid temporaries -- `Type res(a1 + a2); res +=
      a3; res /= b;`

