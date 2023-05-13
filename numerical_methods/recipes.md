# Numerical Recipes in C

## Linear algebra

### QR decomposition

Q is orthogonal and R is upper-triangular s.t. `QRx = b --> Rx = Q^T b` is easy
to solve via backsubstitution

Build using successive Householder reflections 
  * Requires 2x number of ops as LU decomp

* (+) Useful for constructing orthogonal bases and solving least-squares
* (-) But SVD is better at those anyway
* (+) `O(N^2)` matrix factorization update when solving closely related systems
  * Uses Jacobi rotations

### Lower than `O(N^3)` inversion

Partition matrix into 2x2 supermatrix, then note trick to reduce 8
multiplications down to 7 by introducing many more adds/subs.

Recursive Strassen method gives `O(N^log2(7))` time complexity. Pays off after
`N > 100`

## Sorting

In order from bad to good:
  1. Bubble sort sucks
  2. Insertion sort is best when `N < 50`
  3. Shell's method optimizes insertion sort -- good when `50 < N < 1000`
  4. Heapsort works in-place and is simple -- authors' favorite!
    * (+) Consistent +/- 20% of average performance
    * (+) Best case is `O(N)`
    * (-) Cache thrashing due to large jumps to heap children
  5. Quicksort is faster than heapsort by about 2x when `N > 1000`
    * (+) Much better cache coherency
    * (-) Requires some extra `2 log2 N` stack memory
    * (-) Somewhat complicated, esp. with optimizations
    * (-) Worst case is `O(N^2)` if data is sorted -- can fix with random pivot
  6. Quicksort with insertion sort when subarrays have `N < 7`

Shell's method sorts groups of offset pairs, then offset quads, then offset
octets...
  * Helps pre-sort to prevent insertion sort from wandering far down on inner loop
  * Worst case `O(N^3/2)`, average case `O(N^1.27)`

## Root finding

(Almost) always used bracketed search!
  * Ensure that the function switches sign within the bracket

* No derivative -- Brent's method or Ridder's method
* Can compute derivative -- Newton-Raphson with bounds
* Can compute second derivative -- Halley's method
* Polynomial -- Laguerre's method
* Multidimensional -- Newton-Raphson, with great 1st guess

Bisection is easy, guaranteed to converge, has linear convergence (sig figs are
earned linearly -- one function call = 1 sig fig)
  * Bisection works better for discontinuous functions and continuous functions
    with sharp 2nd-deriv change near root.

Secant and False Position methods assume linearity to redraw boundaries
  * Secant moves left and right bounds in tandem, keeping most recent estimate
  * False position keeps bounds s.t. `f(a) * f(b) < 0`
  * Superlinear convergence

Ridder's method has quadratic convergence, but 2 function calls, so sqrt(2)
convergence. Works better overall if exponential factors used.

Brent's method mixes bisection with inverse quadratic interpolation

Newton-Raphson expands function as 1st-order Taylor approx., then takes next
guess as the zero-crossing
  * `f(x+d) = 0 = f(x) + f'(x)*d --> d = -f(x) / f'(x) --> x2 = x1 + d`
  * Terrible when 1st-deriv vanishes
  * Can enter cycles
  * Quadratic convergence -- 1 function call = 2 sig figs
  * Useful for polishing up known roots 
  * Using numerical derivative (rather than analytical) requires 2 function
    calls, reducing convergence to sqrt(2). Also tough to pick `dx`. Can get
    only linear speedup if `dx` too big (s.t. `f'(x)` doesn't change). Use
    Brent's method instead.
  * Best is to mix Newton-Raphson with bisection search -- do bisection step if
    NR goes out of bounds or doesn't reduce bracket size sufficiently

Halley's method uses `x2 = x1 + -f(x1) / (f'(x1) (1 - (f(x1)f''(x1)) / (2
f'(x1)^2) ))`
  * Converges cubically -- each function call triples sig figs
  * Can implement when near root by bracketing denominator b/t 0.8 and 1.2

Polynomial hack: use eigenvalue finder on companion matrix (see text)

Newton-Raphson is only real option for multidimensional
  * `F(x+d) = 0 = F(x) + J*d` then use LU decomp to solve for d. `x2 = x1 + d`.
    J is Jacobian matrix
  * Cannot apply minimization to `H = F1(x)^2 + F2(y)^2 + ...`. Will likely get
    stuck in local minimum

## Minimization

### Dynamic programming

Problem has stages each containing a set of states. Cost to traverse graph. 
Similar to backtracking but with costs.

Bellman/Dijkstra/Viterbi algorithm: one sweep, labeling each node with cost of
best path to that node.
  * Can read off optimal path at the end.

Main trick is minimizing number of states at each stage. Only want states with
finite cost. Can use hash memory.

Examples: Parenthesizing matrix multiplication, DNA sequence alignment

## Random numbers
