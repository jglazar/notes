# Numerical Recipes in C

## 1. Precision

Floats are represented as `s * M * B^(e - E)`
  * `s` is sign bit
  * `M` is (23-bit) mantissa
  * `B` is base (typically 2, sometimes 16)
  * `e` is (8-bit) exponent
  * `E` is bias

Normalized bit patterns have highest-order bit = 1 (with base 2), since you can
always left-shift mantissa and right-shift exponent to get better precision.

Operations only happen after left-shifting smaller number's exponent (and
right-shifting its mantissa) to match larger number's exponent
  * This loses low-order bits in smaller number 

Machine accuracy epsilon is smallest number s.t. `1.0 + x != 1.0`
  * Typically around `3 * 10^-8`
  * Depends on number of bits in mantissa
  * Represents fractional accuracy (when two numbers of same exponent are added)
  * NOT the same as the smallest representable float number (which depends on
    number of bits in exponent, not mantissa)!

Aggregate error is like random walk, so `sqrt(n) * eps` expected error magnitude
  * Correlated calculations lead to `n * eps` expected error magnitude
  * Can have catastrophic cancellation when similar numbers are subtracted

Roundoff error (above) != truncation error, which is due to truncating series or
integral for numerical evaluation

Unstable algorithms magnify roundoff errors, but not truncation errors

## 2. Linear algebra

Degenerate matrix is "singular"
  * Condition number = biggest singular value / smallest
  * Square matrix: row degeneracy implies column degeneracy
  * Can cause method failure or catastrophic roundoff errors (verify by plugging
    solution vector back into original problem)
  * Use SVD to solve

`N < 50` can be solved with single-precision if not singular. Can solve systems
up to `N ~ few hundred`, or sparse systems with `N ~ few thousand`

`M < N` --> fewer equations than unknowns, no solution or infinite solutions
(add on any vector in N-M dim. nullspace)
  * Range is found with SVD

`M > N` --> more equations than unknowns, no solution, find best compromise
(linear least squares)

Use iterative methods when significance is an issue, like with large N or
singular matrix

### Gauss-Jordan elimination

* (-) Requires all individual `b` vectors to be manipulated simultaneously
* (-) 3x slower to solve single problem than LU decomp or Gaussian elimination
  (`N^3` vs `N^3 / 3`). Can halve work by not computing inverse, though.
* (+) Stable, esp. with full pivoting
* (+) Easy and solid

3 moves:
  1. Take linear combination of rows within matrix `A` (mimic in `b`)
  2. Interchange rows within matrix `A` (mimic in `b`)
  3. Interchange columns within `A` and exchange rows in `x`
    * Requires unscrambling variable order in the end

Divide by `a00`, then manipulate other rows to zero-out their `0`-column.

Using just move 1 is unstable (could div by zero), 1+2 ("partial pivoting") is
stable enough, 1+2+3 ("full pivoting") is stable.

Want to put large element on diagonal. Use "implicit pivoting" to scale rows to
prevent one row from dominating

Solution can be done in-place

Don't interchange columns, just re-label with helper arrays

### Gaussian elimination

Same as Gauss-Jordan, but only subtract rows below pivot and only use partial
pivoting. This yields upper-triangular matrix which is easy to backsubstitute.

`N^3 / 3` to reduce matrix, `N^2 / 2` for each `b` vector to backsubstitute,
`N^3 / 6` right-hand side manipulations (accounting for mostly-zero operations).
Yields `N^3` total to invert matrix, same as Gauss-Jordan.

All `b` vectors must be known in advance

### LU decomposition

`Ax = b` --> `LUx = b` --> `Ly = b` and `Ux = y`, which are both easy to solve
via forward and back-substitution (each `1/2 N^2` operations).

Don't need to know all `b` vectors in advance

Crout's algorithm -- write `N^2` equations for `N^2 + N` unknowns, then set all
`lii = 1`. 
  * Works in-place!
  * Uses partial pivoting for stability. Can also implement implicit pivoting.

Still `N^3` work to invert. Generally done by solving `N` problems, each being
one column of the identity matrix

Determinant is product of diagonal elements (since L's diagonal is all 1s and
`det(A) = det(L) * det(U)`)
  * Prevent over/underflow by tracking scale separately or taking sum of logs
    and tracking sign

### Iterative improvement

`A * deltax = A * (x + deltax) - b`

Fast (`N^2`) if LU decomp already calculated. Need to store A and b separately
too.

### Special matrices

Tridiagonal
  * LU decomp and forward/backsubstitution only take `O(N)`. 
  * Can store matrix as 3 vectors
  * No pivoting needed
  * Diagonal dominance (`abs(mid_i) > abs(lo_i) + abs(hi_i)`) guarantees no
    zero-pivot.

Vandermonde -- each row is `1, xi, xi^2, xi^3, ...`
  * Comes up in fitting polynomial to N coordinates and reconstructing
    discrete distributions from moments and data points
  * `N^2` work. Use double-precision!

Toeplitz -- `2N - 1` numbers with mirror symmetry about diagonal
  * Comes up in deconvolution and signal processing
  * Bordering method is recursive solution for perfect symmetry
  * Levinson's method is useful for imperfect symmetry
    * Works in-place
    * No pivoting, so fails if any diagonal principal minor is zero

Hilbert -- `aij = 1/(i + j - 1)`
  * Ill-conditioned, but have exact integer algorithm

Sparse -- many forms
  * Block tridiagonal looks like Hi-C map!
  * Check out Yale Sparse Matrix Package
  * Methods can be unstable
  * Sherman-Morrison: `A` --> `A + u @ v` can have inverse updated with 2 matrix
    multiplications and a vector dot product (`3N^2` multiplications)
    * No pivoting allowed
    * Useful for building solution to matrix related to sparse matrix (with
      efficient inversion algorithm)
  * Conjugate gradients: minimize `f(x) = 1/2 (Ax - b)^2`
    * Only requires multiplications of matrix/transpose with vector (which is <<
      `O(N^2)` due to sparsity)  
    * Iterative, typically needing `N` iterations with 3 matrix multiplies each
    * Condition number is square of original. Not an issue for positive-definite
      matrix

### Singular value decomposition

`A = U W V^T`, where `U` is orthogonal (orthonormal), `W` is diagonal-only
singular values, and `V` is orthogonal (orthonormal)
  * `inv(A) = V 1/W U^T`, where `1/W` is just inverse of diagonals
  * Singular if some `wi = 0`. Replace `1/wi` by zero to get solution vector of
    smallest length (zeroed out vectors in nullspace)
  * Should set threshold for `wi` and acceptable residual (error)

Very stable!

Constructs orthonormal bases for nullspace (rows of `V^T` corresponding to `wi =
0`) and range (cols of `U` corresponding to `wi != 0`). Recall `rank + nullity =
N`

* `M < N` case: augment with rows of zeros 
* `M > N` case: rows of `V^T` corresponding to small `wi` are linear
  combinations of `x` that are insensitive to data

Useful for compressing matrix, since we can throw out rows/cols with small `wi`

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

## 11. Eigensystems

`Ax = lambda x` only holds if `det(A - lambda I) = 0`, which expands to Nth
degree polynoomial
  * Root searching performs poorly for solving the polynomial

Can shift eigenvalues by adding `tau I` to original matrix `A`

Symmetric = Hermitian, orthogonal = unitary, both of which are normal (matrix
commutes with conjugate transpose)
  * Eigenvalues of Hermitian matrix are real
  * Eigenvectors of normal matrix with unique eigenvalues are complete and
    orthogonal
    * Eigenvectors of degenerate eigenvalues can be swapped in linear
      combinations. Can use Gram-Schmidt orthogonalization to find complete and
      orthogonal set
  * Non-normal matrices are defective, and its eigenvectors may not span space

Left eigenvectors are right eigenvectors of the transpose of the matrix.
  * Their eigenvalues are identical
  * If matrix is symmetric, then left and right eigenvectors are just transposes
  * Even for non-normal matrices, left and right eigenvectors are orthogonal
    s.t. `Xr = inv(Xl)` upon proper normalization

Similarity transform of A gives `inv(Xr) A Xr = diag(lambda)`
  * Most diagonalization techiques nudge the system via similarity transforms
  * Jacobi transformations zero-out an off-diagonal element. Householder
    transformations and the elimination method zero-out rows or columns.
  * Note: Gaussian elimination is not a similarity transform

Factorization methods like QR use `A = Al Ar` --> `Ar Al = inv(Al) A Al`

Easiest to get just eigenvalues, then get desired eigenvectors by inv. iteration

### Jacobi transformations

Foolproof for real symmetric matrices, but slower than QR if N >= 10

Accumulates `A = ... inv(P3) inv(P2) inv(P1) A P1 P2 P3 ...`, where right side
stores `Xr` (where cols are eigenvectors) and matrix has eigenvalues on diagonal

Pick angle and calculate cosine `c` and sine `s`, then construct matrix `I + T`
where T has `c` placed in 2 spots on diagonal and `s` on 2 off-diagonal spaces.
This generates a plane rotation after `A' = (I+T)^T A (I+T)`

For symmetric matrix, zeroing out corresponding element happens if angle = `(aqq
- app) / 2apq`. Can avoid expensive trig with further approximations.

Use cyclic Jacobi transformations across each element in matrix for overall
`O(N^3)` time to converge

### Householder reduction

Givens reduction reduces matrix to tridiagonal form in known number of steps.
Just don't annihilate inner corners of box

Householder reduces to tridiagonal form with orthogonal transformations that
annihilate entire row/column
  * Uses matrix `P = I - 2 w x w^T` (outer product). P is its own inverse and
    transpose. `w` uses matrix elements to enable zeroing

### Tridiagonal matrices

Recursion relation exists for solving characteristic polynomial to get
eigenvalues. Can then apply typical root-finding method to polish root.
  * Use inverse iteration to find corresponding eigenvectors

QL decomp is achievable for any real matrix. Apply Householder transformations
to eliminate values below diagonal
  * Q is orthogonal, L is lower-triangular (can instead have upper-triangular R)
  * Preserves symmetry, tridiagonal form, and Hessenberg form

QL algorithm finds `Ai = Qi Li` then `Ai+I = Li Qi = Qi^T Ai Qi`
  * Takes `O(N^3)` time per iteration in general. Tridiagonal only needs `O(N)`
    and Hessenberg only needs `O(N^2)` per iteration.

Can apply shifts `Ai - ki I = Qi Li` s.t. `Ai+I = Li Qi + ki I = Qi^T Ai Qi`
  * Convergence is then determined by `(lambdaa - ki)/(lambdab - ki)` for
    element `a_ab`
  * Can apply implicit shifting for increased stability for small eigenvalues

### Other special matrices and tips

Complex: `(A + iB) (u + iv) = lambda (u + iv)` can be rewritten as stacked real
matrix `[[A, -B], [B, A]] * [u, v] = lambda [u, v]`
  * Hermitian matrix has `A^T = A` and `B^T = -B`
  * 2n eigenvectors are pairs `(u + iv)` and `i(u + iv)`
  * Complex conjugate pair eigenvalue pairs manifest as blocks along diagonal

Balancing makes rows'/cols' norms approximately equivalent. Takes `O(N^2)` time.
Uses similarity transforms.

Element along diagonal with all-zeros in col/row is already an eigenvalue.
Typically worthwhile to remove corresponding row and col from matrix

Reduction to Hessenberg form can happen via Householder reflections or (more
efficiently) an altered form of Gaussian elimination with pivoting

### Improving eigenvalues and inverse iteration

1. Set up `(A - tau I) y = b`, where `b` is a random vector. 
2. Solve for `y`
3. Replace `b` with normalized `y` and iteratively solve. 

Eventually gets `tau` as eigenvalue and `y` as its eigenvector, with `b ~= 0`

Works bc `lambdai+1 = lambdai + |bi|^2 / |bi y|`

Want change in eigenvector to be large and change in eigenvalue to be small

For degenerate/close eigenvalues, perturb eigenvalue and redo iteration

## 7. Random numbers

See `rng.md` notes file

## 8. Sorting

In order from bad to good:
  1. Bubble sort sucks
  2. Insertion sort is best when `N < 50`
    * (+) Best case is `O(N)`
  3. Shell's method optimizes insertion sort -- good when `50 < N < 1000`
  4. Heapsort works in-place and is simple -- authors' favorite!
    * (+) Consistent +/- 20% of average performance
    * (+) No extra memory (truly in-place). Simple and elegant
    * (-) Best case is `O(N log N)` bc always need to create heap
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

## 9. Root finding

(Almost) always used bracketed search!
  * Ensure that the function switches sign within the bracket
  * If not, bump out lesser-valued point by `factor * (x2 - x1)`
  * Or, divide section into `n` subsections and check 1-2, 1-3, ..., 1-n

* No derivative -- Brent's method or Ridder's method
* Can compute derivative -- Newton-Raphson with bounds
* Can compute second derivative -- Halley's method
* Polynomial -- Laguerre's method
* Multidimensional -- Newton-Raphson, with great 1st guess

Bisection is easy, guaranteed to converge, has linear convergence (sig figs are
earned linearly -- `eps_n+1 = c * eps_n^1`)
  * Uncertainty is halved every iteration, so every `log2(10)` iterations earns
    another sig fig (about 3 iterations, since that divides interval by 8)
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
  * Quadratic convergence -- constant # function calls = 2 sig figs
  * Useful for polishing up known roots 
  * Using numerical derivative (rather than analytical) requires 2 function
    calls, reducing convergence to sqrt(2) power. Also tough to pick `dx`. Can
    get only linear speedup if `dx` too big (s.t. `f'(x)` doesn't change). Use
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

## 10. Optimization

Want short time and low memory use. Function/derivative evaluations are
typically most expensive step.

Can get global min by taking smallest of many local min, or checking if
perturbations of local min land in better spot. Annealing works well!

Linear programming (simplex algo, e.g.) works well for linear function and
linear constraint optimization 

Recommendations:
  * Always bracket the minimum
  * 1D, use no deriv, continuous 2nd deriv -- use Brent's method
  * 1D, use no deriv, discontinuous 2nd deriv -- use Golden Section search
  * 1D, use deriv -- use modified Brent's method without high-order polynomials
  * ND, `N^2` space, use no deriv -- downhill simplex. Simple but slow
  * ND, `N^2` space, use no deriv -- direction set method. Needs 1D method too
  * ND, `N` space, use deriv -- conjugate gradient. Needs 1D method too
  * ND, `N^2` space, use deriv -- quasi-Newton/variable-metric. Needs 1D method

Minimum is bracketed when `a < b < c` and `f(a) > f(b) < f(c)`
  * Take successively larger steps downhill (by golden ratio, e.g.), with
    optional parabolic fit. Keep only 3 most recent points. Stop when newest
    point goes uphill.

Golden Section search: 
  * Select new point `x` between `b` and `c`. 
  * If `f(x) > f(b)` then new bracket is `a,b,x`
  * If `f(x) < f(b)` then new bracket is `b,x,c`
  * Note that Taylor expansion around min gives precision bound on bracket = 
    `sqrt(eps)`, where `eps` is the machine precision (`10^-4` for float,
    `10^-8` for double)
  * Self-similarity of sections yields ratio of `(3 - sqrt(5))/2 = 0.38`. Pick
    position that is `0.38 * larger interval width` beyond point `b`. This gives
    total bracket reduction factor of 0.62, compared to 0.5 from bisection
    search. Gives linear convergence.

Downhill simplex sets up N-dimensional simplex, then executes moves to slowly
ooze the simplex toward a min. E.g., pull one vertex through opposite plane

Naive multi-dimensional minimization loops along x, then y, then z...
  * Requires tons of tiny steps to get anywhere if slope is tilted (curvature is
    bigger along some directions more than others)

Steepest descent (with maximal step sizes) makes 90-degree zig-zag pattern,
since next gradient is orthogonal to prior step.
  * Gradients give `N` information per evaluation. Need at least `N^2` info to
    find min

Conjugate gradients take smart non-interfering steps
  * Conjugate set of vectors have all pairs `u A v = 0`. In our case, `A` is
    Hessian matrix.
    * Next step doesn't correct prior step at all
  * This allows a single pass minimizing through all vectors
  * Can perform type of Gram-Schmidt orthogonalization to get sequence of
    orthogonal vectors `g` and conjugate vectors `h`. No Hessian needed!

Variable metric methods build iterative approximation for inverse of Hessian
  * DFP and BFGS are popular
  * Want `x2 - x1 = inv(H) * -grad(x1)`
  * Trick: approximate Cholesky decomposition matrix of Hessian

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
