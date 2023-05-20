# Numerical Recipes in C

## Linear algebra

### Cholesky decomposition

2x faster than other methods for solving linear eqns involving symmetric
positive-definite matrix
  * Positive-definite: `v A v > 0` for all vectors `v`, or, all eigenvalues are
    positive

Similar to LU decomp, but finds `L L^T = A`. Like a square root.

`N^3 / 6` operations and `N` square roots.

* (+) No pivoting -- numerically stable
* (+) Failure simply indicates matrix was not positive definite

### QR decomposition

Q is orthogonal and R is upper-triangular s.t. `QRx = b --> Rx = Q^T b` is easy
to solve via backsubstitution

Build using successive Householder reflections 
  * Requires 2x number of ops as LU decomp

* (+) Faster than Jacobi method for diagonalizing real symmetric matrices
* (+) Useful for constructing orthogonal bases and solving least-squares
* (-) But SVD is better at those anyway
* (+) `O(N^2)` matrix factorization update when solving closely related systems
  * Uses Jacobi rotations

### Lower than `O(N^3)` multiplication and inversion

Partition matrix into 2x2 supermatrix, then note trick to reduce 8
multiplications down to 7 by introducing many more adds/subs.

Recursive Strassen method gives `O(N^log2(7))` time complexity. Pays off after
`N > 100`

## Random numbers

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

## Optimization

Interior point methods often beat simplex methods
  * Traverse interior of feasible region
  * Use primal-dual relationship and KKT condition
  * Quite complicated, but default algorithm works well

Simulated annealing is good general-purpose method, but authors aren't sure how
good

### Dynamic programming 

Problem is sequence of stages each containing a set of states. Cost to traverse 
graph. Similar to backtracking but with costs.
  * Directed graph: nodes are states, edges are allowable choices with 
  corresponding cost. Represent forbidden transitions as edge with infinite 
  cost.
  * ✅ Try to minimize number of states at each stage. Stages need not be 
  chronological. Consider hash memory to efficiently retrieve edges with 
  finite cost.

Bellman/Dijkstra/Viterbi algorithm: forward sweep and label each node with cost
of best way to reach that node, then (optionally) backtrack to read off set of
decisions made along the way.

Main trick is minimizing paths to small number of states which ignore their
history (Markov property). Can use hash memory.

E.g., Multiply ABCDE matrices to minimize operations
  * Each stage is the number of multiplications so far
  * Don't need to consider exact breakdown of how state was reached. E.g., 
  No need to consider A(B(CD)E) instead of A(BCDE).

E.g., Find best-scoring match between two DNA sequences
  * Allowed edits are deletion, insertion, and substitution. 
  * Traverse table with sequences along columns and rows

## Modeling data

MCMC is good when estimating/sampling posterior
  * Requires detailed balance and ergodicity (and aperiodicity)
  * Top eigenvalue of transition matrix is 1, 2nd eigenvalue determines
    convergence speed
  * Samples are complete -- can marginalize out unwanted data
  * Picking transition distribution (moves) can be tricky
    * E.g., 2 moves -- `k` fixed and `l` small, `k++` and `l` changed s.t. `l/k`
      constant
  * ✅ Use `log(p)` to prevent under/overflow during unnormalized probability
    density (like `exp(-delta_e/T)`) calculations

Gibbs sampler takes independent samples from each component variables'
conditional pdf.
  * (+) Yields big moves, unlike tiny moves from MCMC
  * (-) Must know/calculate normalize conditional pdfs
  * Works well for discrete variables, where normalization is quick. Numerical
    integration for continuous variables is slow -- better to use MCMC.
  * ❗️ Not the same as doing MCMC with moves one component at a time!

## Geometry

KD-trees hold points
  * Takes `O(N log N)` time and `O(N)` space to construct
  * Each box has 2 children, each partition uses 1 coord, coords are used
    cyclically, and cuts are made s.t. children have equal numbers of points
  * Children also have pointer to parent

Benefits of KD-trees
  * Find any point's nearest neighbor in `O(log N)` time 
    * Comes in handy when repeating for many points
  * Find `n` nearest neighbors in `O(log n log N)` time using heap

Triangle area calculated with `1/2 A x B`, where `A` and `B` are vectors

Random points on n-dimensional sphere
  * Get n independent Gaussians. These make an n-dimensional vector that is
    spherically symmetric bc multi-dim Gaussian factorizes to product of 
    Gaussians. Then take `x = v / |v|`.
    * Get point inside with uniform random radius 
  * For `n = 2`: Rejection-sample point inside circle, then scale out to land on
    perimeter with `x = v / |v|`
  * For `n = 3`: Rejection-sample point inside circle, then use Marsalgia
    formula
  * For `n = 4`: Rejection-sample 2 points inside circle, then use special
    formula

Random n-dimensional rotation matrix
  * Fill n x n matrix with random Gaussian samples, then apply QR-decomp to get
    rotation matrix `Q`. Can get `det(Q) = 1` (proper rotation matrix) by
    swapping any two rows
  * For `n = 2`: Pick random `theta`, then fill rotation matrix with
    `sin(theta)` and `cos(theta)`
  * For `n = 2`: Get random point on unit circle, then set `cos(theta) = x` and
    `sin(theta) = y`
    * ✅ Avoids trig function calls
  * For `n = 3`: Get random point on 4D hypersphere, then apply special formulas

Delaunay triangulation best avoids small angles and long sides 
  * Useful for 2D interpolations and convex hulls
  * Find triangle containing point in `O(log N)` time
  * Find all nearest neighbors in `O(N log N)` time
  * Solve largest empty circle problem with one pass through triangles
  * Minimum spanning tree is a subset of Delaunay edges -- use Kruksal's method
    which gives `O(N log N)` time (greedy method guaranteed to find optimum!)

Voronoi tesselation is dual graph of Delaunay triangulation
  * Get point-point vectors, then draw perpendicular bisectors
  * Voronoi vertices are circumcenters of Delaunay triangles
  * Solve path farthest from obstacles by following Voronoi edges

QO-trees partition the space into even 4ths (in 2D) or 8ths (in 3D)
  * Useful for collision detection -- only check current box and its neighbors
    * Only need to check current box and its ancestors when searching for
      element intersecting point
  * Generally gets time complexity of `O(N^1/2)` (in 2D) or `O(N^2/3)` (in 3D)
