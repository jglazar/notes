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

### Avoiding excessive copying

When passing objects:
  * Pass big objects (like vectors) by reference
  * Pass small objects (like int/double/char/ptrs) by value

Declare and assign objects at once
  * `Type a = b` or `Type a(b)` uses copy constructor once
  * `Type a; a = b` uses default constructor and assignment operator

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

Use initialization lists in constructors to avoid extra assignment operation

Define a move constructor for big objects
  * `Type(Type&& other) noexcept {...}`
    * `noexcept` allows compiler to select it instead of copy constructor
  * Don't accidentally deallocate nullptr in destructor!
  * Move assignment is used automatically whenever you assign to an rvalue
    * Must define separately from move constructor
    * `Type c = foo(a)` or `Type c = std::move(a)`

Avoid generic constructor `Type(std::initializer_list ls) {}`
  * Creates temporary to perform implicit conversions
    * E.g., `Type c = val; c *= {3}` converts 3 into `Type`, then performs `*`
  * Preface all constructors with `explicit` to let compiler complain about 
  implicit conversions

Don't return big types by value
  * Chaining together many operations creates tons of temporaries
  * This also occurs when using `+, -, *, &`, etc.
  * Modify in-place instead, using `+=, -=, *=`, etc. e.g.

Help the compiler perform return value optimization
  * Constructs result in-place, avoiding extra copy: `Type c = foo(a, b)`
  * Return one unnamed variable at end of `foo(a, b)`: `return Type(c, d)`
    * Don't return one of several objects of type `Type`

Prefer prefix increment over postfix increment to avoid extra copy

Reserve space ahead of time for collections

Use references in range-based for loops -- `for (auto& x : vec) {...}`

Use `emplace` to move items into container
  * `push` copies instead
  * `push` with `std::move` is better, but still not as good as `emplace`

## Peter Isensee C++ Optimization

Inlining can run slower by pushing existing variables out of the cache

Virtual functions have high relative overhead for small objects

Default to returning by value, unless you call function a lot

Define custom allocators by overloading `new` and `delete`
  * Pool memory allocation to get contiguous objects
  * Customize container allocators

Template metaprogramming may fail if compiler doesn't want to do pre-work
  * Check out Blitz++ for good TMP

## IT Hare Parallelization

`std::reduce` actually has 4 functions under the hood
  * `operator()(Accumulator acc, double item) {...}`
  * `operator()(double item, Accumulator acc) {...}`
  * `operator()(double item1, double item2) {...}`
  * `operator()(Accumulator acc1, Accumulator acc2) {...}`
  * !! Need to define all 4 if non-commutative function, like sum of squares!

Try to cram all operations into 1 pass over data
  * Create custom `Accumulator` struct with necessary data members
  * Acts in same spirit as single for-loop with multiple accumulations

## Cornell Virtual Workshop Vectorization

Ways to enable vectorization, easy to hard
  * Link to already vectorized code
  * Let the compiler vectorize (FORTRAN does a great job)
    * Need to avoid data dependencies
  * Program directly in vector intrinsics
  * Program in assembly

Vectorization is basically loop unrolling
  * Fused multiply-add expedites multiply with addition 

AVX has 256-bit vector registers, which hold 4 64-bit doubles or 8 floats
  * New processors are generally backwards-compatible, except KNC

Data must be packed into and unpacked from the vector registers
  * Easiest if data is already contiguous

Vector processing units -- typically 2 per core
  * Old VPUs had 1 for multiply and the other for add/subtract
  * New VPUs have both do fused multiply-add

Intel compilers
  * Vectorize at `-O2`
  * Generate SSEs instructions, which only uses 128 bits!
  * Specify target architecture with `-xCORE-AVX512`, e.g.
    * Specify multiple with `-axCORE-...,CORE-...` to produce fat binary
  * Skylake CPUs have 512-bit ZMM math registers, which are activated with
    `-qopt-zmm-usage=high`
  * Allow vectorization across source files with `-ipo`
  * Get optimization report with `-qopt-report=n`, where `n` is verbosity code
    * `-qopt-report-phase=vec` just reports vectorization

GCC
  * Vectorizes at `-O2 -ftree-vectorize` or `-O3`
    * Turn off with `-fno-tree-vectorize` after `-O3`
  * Specify target architecture with `-march=...` or `-march=native`
    * Beware of compiling on login node and computing on compute node!
  * Use AVX-512 with `-mprefer-vector-width=512`
  * Allow vectorization across source files with `-flto`
  * Get optimization report with `-fopt-info`
    * `-fopt-info-vec` or `-fopt-info-vec-all` just reports vectorization

To enable vectorization:
  * Loop length must be known at runtime -- no early breaks
  * No if-then within loop, unless compiler does masked assignments
  * No function calls within loop, unless compiler inlined function or functions
    are vectorized library functions (`libmvec` library in `glibc` version 2.22+, 
    check with `ldd --version`)
    * The only allowed operations are special vectorized intrinsics
  * Direct indexing only -- no `a[b[i]]`
  * Only the innermost loop is optimized, though compiler may reorder loops

Data dependencies
  * No -- Read-after-write (like prefix sum `a[i] = a[i-1] + b[i]`),
    write-after-write (like `a[i%2] = b[i] + c[i]`)
  * OK -- Write-after-read (like postfix sum `a[i] = a[i+1] + b[i]`),
    read-after-read (like `a[i] = b[i%2] + c[i]`)

Aliasing technically allows 2+ pointers to point to same memory
  * Compiler has to prove there's no overlap like prefix sum
    * Compilers will employ simple arithmetic and may push decision to runtime
  * Mark each pointer like `double * restrict ptr_a` to indicate no overlap
    * Must use `-restrict` flag for Intel compilers and use >= C99 standard

Compiler hints
  * `#pragma GCC ivdep` ignores apparent data dependencies
  * `#pragma vector always` always vectorizes, even if compiler doesn't want to
  * `#pragma simd` always vectorizes and complains if it cannot
  * `#pragma novector` disables vectorization
  * `#pragma omp simd` is used with OpenMP 4.0+ and compiler flags `-fopenmp` 
  and `-fopenmp-simd`
    * May also need `#pragma omp for simd` to vectorize multithreaded code

Alignment
  * Add `alignas(64)` or `__attribute__((aligned(64)))` for static arrays
  * Add `memalign(64, size)` or `aligned_alloc(64, size)` for dynamic arrays
  * `__assume_aligned(a, 64)` or `#pragma vector aligned` assumes function 
  arguments are aligned
