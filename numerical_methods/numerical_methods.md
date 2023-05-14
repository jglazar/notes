# Numerical Methods in Python

## Recursion

Divide and conquer is especially useful.
  * Towers of Hanoi: call f(n-1, from, alt, to) then 
  f(n-1, alt, to, from) for f(n, from, to, alt) fct.
  * Quicksort: get lists of smaller, equal, and greater elements 
  then result = f(smaller) + equal + f(bigger)
  * nCk = n-1Ck + n-1Ck-1
  * gcd(a, b) = gcd(a, b-a) because a = cx and b = dx

## Object-oriented programming

Inheritance -- create new classes from existing classes. 
Encapsulation -- hide private details. 
Polymorphism -- use common operation in different ways for different 
inputs.

Use PascalCase. Must include `self` in arguments list to include 
object's other attributes and methods. `self` not needed when calling 
specific object's method.

`class MyClass(SuperClass): def __init__(self, args)`

Can have static variables that belong to class, not object. 
  * e.g., numinstances defined as 0 in class and gets incremented 
  during init with Class.numinstances += 1 statement.
  * can reference from object using Class.variable

Child methods override parent methods with same name (polymorphism).

Use `super().__init__(self, args)` to use parent class's init function, 
then optionally add more things later in your init function.

Single underscore for private variable (by convention), double 
underscore forces private variable via name mangling which replaces 
name with `_classname__var` to ensure no overlap
  * Use getters and setters for private variables

## Runtime

Use `%time function(args)` to get single estimate of runtime. 
Use `%timeit function(args)` to get average and std dev of many runs. 
Use `%%time` or `%%timeit` at beginning of Jupyter cell.

Use `%prun function(args)` to get profiler. 
Use `!conda install line_profiler` then `%load_ext line_profiler` 
then `lprun -f function function(args)` to get line-by-line profile.

## Number representations

Floats are IEEE754 doubles with 64 total bits. 
  * 1 bit is sign with 0 positive and 1 negative
  * 11 bits are exponent, with 1023 (bias) subtracted to allow 
  decimals between 0 and 1.
  * 52 bits are fraction (coefficient of exponent), with implied 
  leading 1 because it's always between 1 and 2.
  * `n = (-1)^s 2^(e - 1023) * (1 + f)`
  * e.g., 15 is 0 sign, 1026 exponent, and 1/2 + 1/4 + 1/8 = 
  1110000...000 fraction.

`import sys; sys.float_info` gives max and min values

All numbers in finite precision gap are mapped to median. Gap grows 
as number grows. Use `numpy.spacing(num)` to get gap.

Biggest number is infinity and has exponent = 2047 and fraction = 0. 
Smallest number is 2^-1075.
  * Numbers cap out at infinity and -infinity.
  * Numbers smaller than 2^-1075 are mapped to zero.

Use `round(x, n)` to round floats to some precision n in order to 
meaningfully compare two floats with `==`

Round-off errors accumulate with more operations.

## Errors

Can have multiple except checks: `try: fct except TypeError: message 
except ValueError: message...`

Program only catches exception if exception is of correct type, or 
no type is specified (naked try).

Can raise custom exception with `raise( Exception('custom') )`

Type check function args with `if isinstance(a, float) and ...: pass 
else: raise( TypeError('message') )`
  * Can have multiple possible types with `isinstance(a, (float, int, 
  complex))`

Use `%debug` in notebook to open `ipdb` interactive debugger.
  * `n` runs line and goes to next, `c` continues until breakpoint, 
  `p` prints variables, `q` quits.
  * activate before running code with `%pdb on`. Deactivate with 
  `%pdb off`
  * set breakpoint with `pdb.set_trace()`

## Files

CSV and JSON are cross-platform. Pickle is binary file for sequential 
data like dicts and is Python-specific. 

HDF5 (heirarchical data format) has binary format with no file size 
limit, with parallel IO and many optimizations.
  * Datasets are array-like, groups are folder-like and hold datasets.

Use `matplotlib.animation` to write movies with metadata.

## Parallelization

Process = instance of program created by OS, has own memory block.

Thread = sub-process within process, sharing memory w other threads.

Python has Global Interpreter Lock which allows only 1 native thread 
to run at a time. This is due to the old age of Python.

In `multiprocessing` package, use `Pool(processes=n)` class methods. 
  * `map(fct, iter)` applies function to each element and collects result 
  * `apply` accepts more arguments
  * both above methods lock main program until completion. Can use 
  `map_async` or `apply_async` if don't need results in order.

Typical log-log runtime graph 
  * serial -- linear 
  * parallelized -- flat, then linear. Downshift compared to serial 
  should have size = number of processors

In `joblib` package, use `Parallel(n_jobs=n)(delayed(fct)(i) for i 
in range(x))`. Don't instantiate `Parallel` object! `n_jobs=-1` uses 
all cpus available.

## Linear algebra

Ln norm is root base n of ( sum of v^n ). L1 is sum of absolute values, 
L2 is Euclidean distance, Linfinity = maximum absolute value.
  * `np.linalg.norm(vec, n)`

Numpy is row-major.

Inverse of 2x2 matrix A = a, b, c, d is 1/det(A) * d, -b, -c, a
  * Singular matrices have zero determinant and no inverse.
  * Matrices with near-zero determinant are ill-conditioned. Can 
  quantify with condition number `np.linalg.cond` = ||A|| * ||A^-1||.

Rank = number of independent columns = number of independent rows. 
  * If rank(A) = min(m,n), then matrix is full-rank. 
  * If rank( [A,y] ) = rank(A) + 1, then y lies outside of A's range 
  and there is no solution to Ax = y.

Rank(A) = n indicates possible solutions.
  * Impossible if m < n, since max rank is m
  * If m > n, there could be a solution if remaining m-n equations 
  are redundant.
  * If rank(A) < n then there are infinite solutions because we can 
  add scaled vectors in the nullspace to solution vectors.

### Solution algorithms

LU decomposition is useful if solving Ax = y for many y's, since one 
can easily solve Lb = y then Ux = b using simple substitutions.
  * Gaussian elimination is actually LU decomposition under the hood. 
  The L has 1s on the diagonal and the row multipliers under the 
  diagonal. 

Iterative methods use `x_i = 1/a_ii ( y_i - sum for j!=i  ( a_ij x_j 
) )` to converge to solution. Same as A = L + U --> Lx = y - Ux
  * Guaranteed convergence if A is diagonally dominant -- abs val of 
  diagonal is greater than sum of off-diagonal abs vals for each row.
  * Also guaranteed convergence if A is symmetric and positive definite.
  * Gauss-Seidel guesses x2...xn and calculates x1, then uses new 
  x1 and x3...xn to calculate x2, ...

Numpy solver uses LU decomposition. Scipy LU decomposition also 
gives the permutation matrix P which reorders A to proceed with 
Gaussian elimination.

Gaussian elimination on A augmented with identity matrix gives 
inverse. LU decomposition works -- LUX = I --> LB = I, UX = B. 
Can find inverse with easy-mode Gaussian elimination on L|I or do 
elimination column-by-column by solving Lb1 = [1,0,0]^T then 
Lb2 = [0,1,0]^T ...

### Exercises

Problem: select linearly independent columns from m x n matrix A.
  * Solution 1: add column to new matrix, then check if new matrix is 
  full-rank with `np.linalg.matrix_rank`. Pass if column is 0 vector. 
  O(n) to go through columns, but rank check actually does 
  O(n * m^2 + n^3) SVD each time.
  * Solution 2: if A is square, just get columns corresponding to 
  eigenvectors with nonzero eigenvalues. In the eigenbasis, the 
  action of A collapses vector components along eigenvectors with 
  zero eigenvalue. These eigenvectors span the nullspace, just like 
  the corresponding columns in A.
  * Solution 3: Use Gaussian elimination to find dependent rows?

Problem: Complexity of determinant calculation
  * Solution: nxn yields n * det(n-1) = n * (n-1) * ...  = n!

## Eigenvectors and eigenvalues

Power method is iterative way to get largest eigenvalue and its 
eigenvector. Repeated application of A on x will eventually select 
only the eigenvector with max eigenvalue. 
  * In eigenbasis, `Ax0 = c1 A v1 + c2 A v2 + ... = 
  c1 l1 v1 + c2 l2 v2 + ... = c1 l1 x1` where `x1 = v1 + c2/c1 
  l2/l1 v2 + ...`. Then apply Ax1 ...
  * Tends to `Akx = l1 v1`
  * Apply normalization to xk after each round. Linfinity norm (div 
  vector by max value) is easiest and yields l1 factor.
  * Can set eigenvalue difference cutoff, eigenvector angle difference 
  cutoff, or residual vector norm cutoff
  * `x = np.dot(A,x); l1, x = l_infinity_normalize(x)`

Inverse power method uses fact that eigenvalues of inv(A) are 
reciprocals of eigenvalues of A. Thus, power method using inv(A) 
yields smallest eigenvalue of A. Eigenvectors are the same.

Shifted power method requires knowing max eigenvalue of A, then 
setting `B = A - l1 I`, then finding max eigenvalue of B which  
will be some `lk - l1`. Then repeat rank(A) times to get 
all eigenvalues.
  * Unsure if this gets eigenvectors too

QR decomposition gets A = QR where Q is orthogonal (orthonormal) and 
R is upper triangular. Orthogonal matrices have inv(Q) = Q^T
  * Repeat `A(k+1) = inv(Qk) Ak Qk = Rk Qk`, thus making Ak and A(k+1) 
  similar ( both only differ in basis ) with the same 
  eigenvalues (and eigenvectors? I think not.)
  * Must compute QR decomposition at each stage
  * This converges to A = RQ = eigenvalues on diagonal = Householder matrix

## Linear Regression

Y = Xb, where rows in X are f(x), the (linearly independent) basis 
functions.

Geometric interpretation: 
  * X is n x p matrix, b is p x 1 vector. 
  * X lifts vector b to column space of X. 
  * We seek the vector b that minimizes the distance from the vector 
  Xb (in the column space) to y, which generally lives outside the 
  column space. 
  * The smallest Euclidean distance from y to the column space is 
  given by a perpendicular vector between Xb and y (orthogonal 
  projection of y onto column space of X). 
  * Therefore, y - Xb and Xb are perpendicular. `Xb dot ( y - Xb ) = 0` --> 
  `b^T X^T y = b^T X^T X b^T` --> `b = inv(X^T X) X^T y`
  * Hat matrix `inv(X^T X) X^T` is also called pseudo-inverse and 
  only exists if A has linearly independent columns and n > p

Analytic solution:
  * Minimize sum of squared errors (Xb - y)^T (Xb - y) w.r.t. b
  * d/db b^T X^T X b - 2 b^T X^T y + y^T y = 0
  * 2 X^T X b - 2 X^T y = 0
  * b = inv(X^T X) X^T y

Deal with nonlinearity: 
  * take appropriate logarithms
  * use `np.polyfit` to fit nth-order polynomial
  * use generic `curve_fit` from scipy library to fit an arbitrary fct.

## Interpolation

Guarantee that fit goes through every given data point.

❗️ Don't use results outside of interpolation range!

Linear interpolation just plots straight line between adjacent points.

Cubic spline uses n - 1 cubic fcts to fit n points -- 4(n - 1) unknowns.
  * Connect each pair of adjacent points with its own cubic fct -- 
  2(n - 1) equations.
  * Match first and second derivatives of neighboring fcts -- 2(n - 2) 
  equations.
  * Pick 2 more equations, e.g., second derivatives are 0 at ends 
  * Set up and solve Xb = y style equation, where b is all 4(n - 1) 
  parameters. Be sure to write down 1st and 2nd derivative eqns too.

Lagrange polynomial is linear combination of basis functions `P_i(x) = 
product for j != i of ( (x - xj)/(xi - xj) )` with coefficients `yi`
  * `P_i( xj )` is orthonormal for i, j. This ensures interpolation.

Newton polynomial is linear combination of basis functions `n_i(x) = 
product to i-1 of ( (x - xj) )` with coefficients `a0 + a1 (x - x0) + 
a2 (x - x0) (x - x1) + ...`.
  * Divided differences gets coefficients: `f(x0) = a0`, `f(x1) = a0 + 
  a1(x1 - x0)`, ... continue recursively.
  * `f(x1, x0) = (y1 - y0) / (x1 - x0)`
  * `f(x2, x1, x0) = ( f(x2, x1) - f(x1, x0) ) / (x2 - x1)`
  * `f(xk,...x0) = (f(xk,...,x1) - f(xk-1, ..., x0)) / (xk - x0)`
  * Keep 1, 2, ... k-1 divided differences of k, k-1k, ..., 2 
  consecutive variables each in table.
  * Adding new data only requires higher differences -- no recalculation!

Nearest neighbor interpolation looks like step function, where values 
between points take on y-value of nearest point

## Series

Taylor series expand function around point. Taylor series of polynomial 
around any point is just the original polynomial.

exp(x) = sum( x^n / n! ). exp(ix) = cos(x) + i sin(x). cos(x) gets 
even power terms, sin(x) gets odd power terms.

Round-off errors are due to computer imprecision, while truncation 
errors are due to mathematical approximations.
  * Round-off errors often happen when large numbers need to perfectly 
  cancel, as in `exp(-30)` approximation.
  * Taylor remainder estimation theorem bounds truncation error around 
  point x: `abs(error for nth order approximation) <= M * 
  abs(x - a)^(n + 1) / (n + 1)!`, where M is the maximum of abs( 
  (n + 1)th derivative of f ) on interval between a and x.
  * Proof uses integration by parts to convert `integral from a to x of 
  (n + 1)th derivative of f / n! * (x - t)^n` into `f(x) - sum from 0 
  to n of ( kth derivative of f evaluated at a ) / k! * (x - a)^k` which 
  is the error. Then, abs( error ) = abs( original integral ) <= 
  integral of abs( integrand ) = result as desired.

## Root finding

`scipy.optimize.fsolve( fct, starting_guess )` gets root, starting from 
guess.

Can define error metric for tolerance calculation in many ways. 
E.g., abs( f(x) ) or abs( x(i+1) - xi ) for root finding

Bisection method looks for roots between positive f(a) and negative 
f(b) using binary search.
  * Typical cutoff is `abs( f( (a+b)/2 ) ) < tol`
  * E.g., sqrt(2) is root of `f(x) = x^2 - 2`

Newton-Raphson approximates function as `f(x) = f(x0) + f'(x0) * 
(x - x0)` then solves for zero of approximated function. 
  * Solution is `x1 = x0 - f(x0) / f'(x0)`
  * Much faster convergence than bisection
  * Issues if derivative is near zero, e.g., can jump to root far from 
  initial guess.

## Numerical differentiation

Create 1D grids using `linspace`

Assume in the following that xi, xj, xk separated by h each.

1st derivatives estimated using finite difference. 
Errors for concave up include:
  * Forward -- use xj and xk, under- then overestimates slope
  * Backward -- xi and xj, over- then underestimates slope 
  * Central -- use xi and xk, consistently overestimates slope

Taylor expand f(x) around xj, then consider f(xk) and solve for f'(xj)
  * `f'(xj) = ( f(xk) - f(xj) ) / h + -f''(xj) h / 2! - 
  f'''(xj) h^2 / 3! + ...`, so first-order approximation has error O(h)
  * Central approximation takes f(xk) - f(xi) which cancels even 
  derivative terms in expansions, leaving O(h^2) accuracy!
  * Can combine 4 terms around xj with `f'(xj) = ( f(xa) - 8 f(xb) + 
  8 f(xc) - f(xd) ) / 12h` has accuracy O(h^4)

`np.diff( array )` gives n - 1 forward differences, which can then be 
divided by h to get slope estimates

Plot max absolute error vs. step size in logscale to get O(h^p) scaling

Take Taylor expansions of f(x) around xj, then consider f(xi) and 
f(xk), then add the expressions to get f'(xj) cancellation and isolate 
f''(xj) to find O(h^2) estimate of second derivative = `f''(xj) = 
( f(xk) - 2 f(xj) + f(xi) ) / h^2`

Signal with small noise `cos(x) + a sin(fx)` has derivative `-sin(x) + 
af cos(fx)`, which can be abnormally high if f is high
  * Can smooth with moving window `y_new[i] = np.mean( y[i-n : i+n] )`

## Numerical integration

Integral estimated using finite sums.

Taylor expand f(x) around xj, then distribute integral.
  * Integral over 1 interval = `h f(xj) + O(h^2)`, summed n = (b - a) / 
  h times = O(h) accuracy
  * Midpoint rule uses x = (xj + xk) / 2. Taylor expand around midpoint 
  to find cancellation of odd-power integrals (due to symmetry), yielding 
  O(h^3) accuracy for one interval or O(h^2) accuracy overall.
  * Trapezoid rule uses area of `h ( f(xj) + f(xk) ) / 2`. Use 
  Taylor expansion of midpoint, evaluate at xj and xk, then solve 
  for f(mid). Next, consider integral of Taylor expansion, plugging 
  in f(mid) found before. Yield same O(h^3) accuracy as midpoint, 
  which becomes O(h^2) overall.
  * Avoid double-counting ends (extra computational work) by taking 
  `h/2 ( f(x0) + f(xn) + 2 * sum from 1 to n-1 of ( f(xi) ) )`

Simpson's rule fits quadratic to xi, xj, and xk then evaluates integral 
analytically.
  * Simplest to use Lagrange polynomials to interpolate 3 points.
  * Each approximation is over 2 intervals, so you need even number of 
  intervals and odd number of grid points
  * Integral from xi to xk is `h/3 ( f(xi) + 4 f(xj) + f(xk) )`
  * Grouping for efficiency yields `h/3 ( f(x0) + f(xn) + 4 * sum of 
  odd i from 1 to n-1 of ( f(xi) ) + 2 * sum of even i from 1 to n-1 of 
  ( f(xi) ) )`
  * Taylor expand around xj, then evaluate at xi and xk. Take `1/6 ( 
  f(xi) + 4 f(xj) + f(xk) )` to find odd terms cancel. Then solve for 
  f(xj). Next, take integral of original Taylor expansion and drop odd 
  power terms due to symmetry around xj. Evaluate square term's integral 
  and subsitute f(xj) found earlier to get cancellation. This yields 
  O(h^5) accuracy for interval, or O(h^4) accuracy overall.

`scipy.integrate` package has `trapz` for trapezoidal approximation, 
`cumtrapz` for cumulative integral up to point x, `quad` for 
Gaussian quadrature (very accurate).

Gaussian quadrature uses N points to get perfect performance on 
polynomial of order 2N - 1. Uses roots of set of orthogonal 
polynomials to find optimal evaluation points. Must shift interval 
from (-1,1) to (a,b).
  * Computational complexity is O(N^2) I think, compared to O(N) for 
  other methods (simple sums).

Boole's rule gets O(h^7) accuracy with `3h/90 * ( 7 f(xa) + 32 f(xb) + 
12 f(xc) + 32 f(xd) + 7 f(xe) )`

MC integration works well for high dimensions because its error drops 
as 1/sqrt(N), whereas Simpson's rule, e.g., drops as 1/N^(4/d)

Can use numerical integration to get Fourier coefficients `a_n = 1/pi * 
integral from -pi to pi of ( f(x) cos(nx) )` and `b_n = 1/pi * 
integral from -pi to pi of ( f(c) sin(nx) )`.
  * Fourier series is useful for approximating periodic functions.

## Ordinary differential equations -- initial value problems

Write derivative operator as matrix acting on state vector. State 
vector can comprise, e.g., two linked variables, or position and 
velocity. Idea is to reduce order of diff eqn by 1.
  * `r' = 4r - 2w; w' = r + 2` --> `D = [4, -2, 1, 1]` acting on 
  state vector `[r, w]`
  * `x'' = -w^2 x` --> `D = [0, 1, -w^2, 0]` acting on state vector 
  `[x, x']`. Can derive by performing derivative on each vector element.
  * In general, matrix looks like [0, 1] up to last row because each 
  lower derivative takes on value of next-highest derivative (derivative 
  of f is f', f' is f'', and so on.). The final row captures the info 
  from the diff eqn, writing the highest-order derivative as a function 
  of the lower order derivatives. 
  * Can add constant to top of state vector if needed, with 
  corresponding row [1, 0, 0...] bc it's constant. Could also set 
  D to be function of state with, e.g., [0, constant/x'] which cancels 
  out x' upon matrix multiplication

All derivatives are w.r.t. one variable (time, e.g.). Many derivative 
variables require PDE methods.

Assume a grid of ..., ti, tj, tk, ... values with spacing of h

Explicit Euler formula approximates `S(tk) = S(tj) + h dS(tj)/dt`, or 
`Sk = Sj + h D Sj`.
Use initial value S(t0) and dS/dt matrix to integrate up to tn.

Implicit Euler formula approximates `S(tk) = S(tj) + h dS(tk)/dt`, or 
`Sk = Sj + h D Sk` --> `Sk = inv(I - h D) * Sj`

Trapezoidal formula averages explicit and implicit with `S(tk) = S(tj) + 
h/2 ( dS(tk)/dt + dS(tj)/dt )`, or `Sk = Sj + h/2 D ( Sj + Sk )` --> 
`Sk =  inv( I - h/2 D ) ( I + h/2 D ) Sj`

Explicit and implicit methods can be unstable (error gets worse over 
calculation). Trapezoidal works a bit better due to averaging.

### Predictor-corrector methods

Query derivative at different locations to generate predictions, then 
use weighed average to correct the current state.

Midpoint method computes Sk using Sj and derivative at Sm, the 
midpoint between tj and tk ( = tj + h/2 ). `Sk = Sj + h D Sm` and 
`Sm = Sj + h/2 D Sj`

Runge-Kutta emulates higher-order Taylor expansion terms using 
weighted averages of midpoint terms. Notation below is a bit sloppy.
  * If D is a function of S and t, then `D(t + dt, S + dS) = D + dD/dt 
  dt + dD/dS D(S,t) dt` and `S(t + dt) = S(t) + c1 D(t, S) h + c2 
  D(t + dt, S + dS) h = S + (c1 + c2) D(t, S) h + c1 (dD/dt dt + dD/dS 
  D(t, S) dt) h^2` where dt is p * h or q * h
  * 2nd order -- `Sk = Sj + h/2 (k1 + k2)`, `k1 = Djj Sj`, 
  `k2 = Dm Sm` where Sm is predicted using k1.
  * 4th order -- `Sk = Sj + h/6 (k1 + 2k2 + 2k3 + k4)`, `k1 = Djj Sj`, 
  `k2 = Dmm Sm` (predicted from k1), `k3 = Dmm Sm` (predicted from k2), 
  `k4 = Dkk Sk` (Dkk predicted from k3). 
  * 4th order is similar to Simpson's rule. Has O(h^4) accuracy.

Solve initial value problems in Python with `scipy.integrate.solve_ivp()` 
method, which takes a function, interval, initial state, method, 
evaluation times, relative tolerance, and absolute tolerance. The 
function takes in the state and time and outputs the state after 
differentiating.

### Advanced methods

Multistep methods use info from many points, e.g., using polynomial 
interpolation to estimate values and derivatives. Adams-Bashforth, 
Adams-Moulton, and backwards differentiation belong to this category.

More advanced methods like Radau or backwards differentiation are needed 
for stiff ODEs, which require tight sampling. E.g., imagine slow 
pendulum with stiff spring -- need to capture high-frequency movements 
of spring AND long-time movements of pendulum. Two different timescales.

## Ordinary differential equations -- boundary value problems

Instead of specifying initial state with n constraints, we specify n 
boundary conditions. E.g., 2nd-order ODE needs f(a) and f(b), 
f'(a) and f'(b), or mixed.

Shooting method guesses state vector, then integrates to the other 
boundary and checks against known boundary condition. Use root-finding 
method to get guess - known = 0 solution.

Finite difference method replaces derivatives with finite approximations. 
E.g., `y' = (yk - yi) / 2h` and `y'' = (yk - 2 yj + yi) / h^2`. 
  * Set up huge matrix equation Dx = b where x has n elements, 
  where n is the number of sample points. The vector b 
  contains the boundary information and zeros/constants.
  * Convert boundary conditions for derivatives to boundary 
  conditions on raw values using finite difference eqns. 
  E.g., `y'(a) = 0` --> `(y_(n+1) - y_(n-1)) / 2h = 0` --> 
  `y_(n+1) = y_(n-1)`, so we know the value just past the final 
  sample point (which may or may not be useful).
  * Each row in Dx = b is the function expressing the highest-order 
  derivative. E.g., `y'' = -g = (yk - 2 yj + yi) / h^2` --> b is 
  -g * h^2. 

Can get values at indices outside of range by solving for them in 
finite difference eqn. E.g., `(y0 - 2y1 + y2) / h^2 = -g` --> 
solve for y0. Can use this info to compute y'(0) using only raw values 
yi, e.g.

Solve boundary value problems in Python with `scipy.integrate.solve_bvp()`, 
which takes same arguments as `solve_ivp()`.

## Fourier transforms

Discrete transform -- `Xk = sum from 0 to N-1 of ( xj exp( -2 pi i k j/N ) )`
  * xj is the data point, assumed to be from equally-spaced sample?
  * Amplitude of signal = norm(Xk) / N
  * Phase of signal = arctan( Im(Xk) / Re(Xk) )
  * Same as multiplying matrix M and data vector x, where `M_kj = 
  exp( -2 pi i k j/N )`

Only need to consider up to Nyquist frequency = sampling frequency / 2

Inverse transform -- `xn = 1/N sum from 0 to N-1 of ( Xk exp( 2 pi i k j/N ) )`

Discrete transform has O(kn) runtime, where k is the number of frequencies 
considered ( = n, or really n/2 )

Fast Fourier transform takes advantage of duplicated work and uses 
divide-and-conquer recursion to achieve O(n log n) speed.
  * Breaks sum into sum over odds and evens, removing `exp( -2 pi i 
  k 1/N ) = 1` term to find shared exponential terms in odd and even sums. 
  * Recursively call FFT with FFT(even) and FFT(odd), defaulting to 
  slow discrete transform when problem reaches small enough size.
  * Pad out input vector with zeros until length is power of 2.

Numpy has `np.fft.fft` and inverse `np.fft.ifft` functions. 
Scipy has `scipy.fftpack.fftfreq`.

## Machine learning

Categorical and supervised -- neural network, logistic regression, random 
forest, naive bayes, support vector machine.

Quantitative and supervised -- neural network, ridge regression, random 
forest, lasso, support vector machine

Categorical and unsupervised -- k-means, gaussian mixture, DBSCAN, spectral 
clustering, heirarchical clustering

Quantitative and unsupervised -- PCA, LDA, isomap, autoencoder

Support vector machine finds hyperplane with maximal separation between 
classes and plane.

Neural network uses epochs of forward and backpropagation alongside 
gradient descent to train nodes.

Clustering finds patterns and internal structure in dataset to find groups. 

K-means initializes k centroids, then assigns points to nearest centroid, 
then places centroid at its group's calculated centroid, and iterates.
  * Can predict classification of new data
