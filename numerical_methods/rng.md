# Random number generation

## Chapter 7 from Numerical Recipes

Want generator with period `>= 2^64`

Period is at most `m`, the largest possible input
  * Pigeonhole principle: any state value must lead to one next value which
    leads to...
  * Beware of MC integration with `> m` rng draws -- duplicated points!

### Uniform distribution

Easiest RNG is linear congruential generator: `Xnew = (a * Xold + c) % m`
  * Can pick `m` as word size to avoid performing `%`
    * There's also a more complicated performance trick with `m = wordsize + 1`,
      which has benefit of avoiding major issues with low-order bits
  * (-) Fills `m^1/k` hyperplanes when pulling `k` numbers at a time
  * (-) Small bits are less random than big bits
    * If `m` is power of 2, then top bit has `2^(n-2)` period, next bit has
      `2^(n-3)`... last bits are constant or simply flip

Converting LCG to range
  * ❗️ Avoid `rand % range` bc low bits are trash! 
  * Simple solution: `(rand / m) * range` to use high bits
  * There's a bias of order `1/m` for large `range / m`, where lower numbers are
    more likely than higher numbers 
    * E.g., `m = 10, range = 3` --> `0: 4/10, 1: 3/10, 2: 3/10`
    * Simple solution: re-sample if `rand <= floor(m/range) * range`
    * Don't need re-sampling if `range % m == 0`
    * See [here](https://www.pcg-random.org/posts/bounded-rands.html) for more

LCG Tips
  * Pick `m` as computer's word size (`2^16`, `2^32`, or `2^64`) to avoid `%`
  * If `m` is power of 2, pick `a` s.t. `a % 8 == 5 or 3` to ensure all numbers
    are visited (maximal period)
  * If `m` is not a power of 2 (next lowest prime, usually) you need
    double-width registers to perform arithmetic. Must avoid overflow!
    * Can use [Schrage's method][SchrageMethod]
    * Provides much more randomness for low-order bits
    * Performance trick exists for `m = wordsize +/- 1`
  * Pick `a` between `0.01*m - 0.99*m` and have no bitwise pattern
  * Pick `c` to have no common factors with `m`. `c = 1` or `c = a` work well
  * Only generate `m / 1000` (or `sqrt(m)`) numbers before changing parameters
    (like `a`)
  * See 1st edition for recommended values of `a, c, m`

My favorite method -- fast and simple
  * Set `c = 0` (called "MLCG" or "Lehmer RNG") to avoid addition
  * Set `m = wordsize (2^64)` to avoid modulo -- enforce with `uint64_t`
  * Ensure max period (`= m/4`) is achieved by picking:
    * X0 is relatively prime to `m` -- any odd number
    * `a` is primitive element modulo `m` -- `a % 8 = 3 or 5`
  * Check out code/rng.c for implementation
  * Check out [Daniel Lemire][LemireRNG] and comparison [here][MinimalStandard]
  * Check out "Tables of LCGs of different sizes and good lattice structures"
    paper by L'Ecuyer for more constants

My favorite range converter
  * Biased, but large state (`2^128` or `2^64` depending on choice above) makes
    error microscopic
  * Fastest due to avoiding division/modulo -- see O'Neill bounds article
  * See code/rng.c for implementation 
  * Lemire's unbiased version is unbiased and also very fast

Float conversion
  * `(float)rand * 1.0f/(float)RAND_MAX` -- compile-time calculate factor
  * Trick: cast rng to signed int, then multiply, then add 0.5
    * See [this paper](https://www.doornik.com/research/randomdouble.pdf)

Longer period: keep array `rands`, then `x1 = rands[conv(x0)]`
  * `conv(n)` converts `n` to index of `rands`, like `(int)(float(n) / m *
    arrsize)` or (worse -- see above) `n % arrsize`
  * `rands[x0]` is replaced with new random number
  * `x1` becomes new index for grabbing `x2`...
  * Removes sequential correlation and provides nearly infinite period
  * Low-order bits are still suspicious

Portable, but slower: separate RNG for most significant portion, least
significant portion, and shuffling
  * Must avoid integer overflows, so `m` and `a` must be small

Subtractive method (Knuth's) also available (and quite fast)
  * Updates array using Fibonacci-style recurrence

64-bit XOR shift
  * `x = x XOR (x>>a1); x = x XOR (x<<a2); x = x XOR (x>>a3); `
  * Flipping << and >> produces opposite bit order
  * Period of `2^64 - 1` (avoid self-propagating 0)
  * XOR acts like matrix on vector of 0s and 1s. Matrix has 1s on main diagonal
    and another diagonal above (for <<) or below (for >>)
  * Require identity after period, no identity after number of steps = prime
    factor of period
  * See 3rd edition for recommended values of `a1, a2, a3`

New Xoroshiro methods are fast, lightweight, and pass tests
  * Here's [xoshiro256ss](https://prng.di.unimi.it/xoshiro256starstar.c)
  * Has 4 `uint64_t` numbers as state
  * Does XOR, rotation, and shift operations
  * (-) Requires special initialization to avoid zero state

[LemireRNG]: https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/ 
[SchrageMethod]: https://en.wikipedia.org/wiki/Lehmer_random_number_generator#Schrage's_method
[MinimalStandard]: https://www.pcg-random.org/posts/does-it-beat-the-minimal-standard.html

### Testing RNG

* Marsaglia's Diehard battery of tests (run in 15 seconds)
  * Considered outdated
* BigCrush battery of tests (run in 4 hours)
* Knuth's spectral test -- checks for hyperplane/lattice structure
* Check if distribution can be described by uniform dist
  * Look at the histogram
  * Kolmogorov test to check empirical cdf vs. uniform cdf
  * Chi-sq with k-1 d.o.f. for counts of each integer (or bin of integers).
    `sum((obsi - expi)^2 / expi)`

### Other distributions

Can approximately generate `N(0,1)` by taking sum of 12 `U(0,1)`, then
subtracting 6 (recall that variance of uniform is `(b-a)^2/12`)

Check 3rd ed. for multivariate Normal

### Monte Carlo integration

Check 3rd ed. for advanced methods

## Sampling

Fisher-Yates shuffle creates in-place random permutation in one pass
  * Note for below that `rng(a, b)` is inclusive 
  * `for i in range(0, n): r = rng(i, n-1); swap(i, r)`
    * Can stop early to get small shuffled subset
  * Or (simpler, IMO): `for i in range(0, n): r = rng(0, i); swap(i, r)`
  * This generates `n!` possible sequences, which is correct
  * Generating rng between 0 and `N` each time gets `N^N` sequences -- incorrect

Sattolo's algorithm gets random cyclic permutation
  * Generate `r = rng(i+1, n-1)` or `r = rng(0, i-1)` instead
  * Creates one of `(N-1)!` outcomes, which is the number of cyclic permutations

Reservoir sampling takes random sample of `k` elements in one pass 
  * Same as simpler Fisher-Yates, but:
    * Swap as normal if `rng` and `i` are both <= k-1 (can ignore if order
      doesn't matter)
    * Overwrite if `rng <= k-1` and `i >= k`
    * Ignore if `rng` and `i` >= k
  * Initialize reservoir with first `k` items in collection
  * For each new element `xi`, get random int between 0 and `i`
  * If `rng <= k-1`, then `reservoir[rng] = xi`
  * Proof by induction shows it works

There's a faster but more complex reservoir method with `O(k + k log(N/k))` time

Heap method: assign random numbers to each element and add to `k`-size heap
  * `O(N + k log k log (N/k))` time (worse than before)
  * Allows extension to items with weights -- use `pow(rng, 1/weights[i])`
