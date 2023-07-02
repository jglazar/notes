# Data description and modeling

## Chapter 13 from Numerical Recipes -- Describing data

See blue notebook for notes on STAT415 from Penn State

### General advice

Can't prove (null) hypothesis, only disprove (alternative) hypothesis

Fat tails -- sample mean converges poorly (try median/mode). Variance and higher
moments don't converge at all (try MAD).
  * Splitting `Var[X] = E[X^2] - E[X]^2` is bad for computation speed/roundoff

Skewness (3rd moment) and kurtosis (4th moment) are suspicious, as they may not
converge
  * Skewness has its own std dev of `sqrt(6/N)` for Normal dist, e.g.
  * Kurtosis has its own std dev of `sqrt(24/N)` for Normal dist, e.g.

Estimate mode not by binning, but by estimating the rate of an inhomogenous
Poission process by Jth waiting times (?)
  * Sort, then pass through with window of size J and calculate `p((xi +
    xi+J)/2) = J / N(xi+J - xi)`. Largest value is mode
  * Std dev of estimator is `sqrt(J) / N(xi+J - xi)`
  * Pick J >= 3 and as large as tolerable. Bigger J smears data

Be suspicious of 2-group t-tests with different variances. Dists may be
different shapes.

Covariance can artificially increase apparent variance and decrease significance
  * Approximate std dev with `Var[Xa] + Var[Xb] - 2 Cov[Xa, Xb]`

### Tests between distributions

Test if 2 dists are different or if model fits certain dist

Chi-sq for categorical data
  * Use dof = number of bins. Decrement 1 for each fitted parameter
  * Chi-sq = sum of (squared normals / variance) = `sum((obs - exp)^2/exp)` =
    `sum((a - b)^2/(a + b))`

Kolmogorov for continuous data
  * Max absolute difference between cdfs. 
  * Approximation of dist -- `Q(sqrt(N) D)` or `Q(sqrt(N1 N2 / (N1 + N2)) D)`
    where `Q(x) = 2 * sum((-1)^(j-1) exp(-2 j^2 x^2))`. Works well for N >= 20

### Contingency table analysis

Test for dependence b/t nominal (unordered categorical) variables 

Chi-sq characterizes significance, entropy characterizes strength

Chi-sq tests if `nij / N.j = Ni / N`, or equivalently `exp_ij = Ni. N.j / N`
  * Dof = `total cells in table - constraints = rows*cols - rows - cols + 1`,
    since we need to calculate `Ni.` and `N.j`
  * Map chi-sq to (0, 1) interval with Cramer's `V = sqrt(chi-sq / (N
    min(rows-1, cols-1)))` or contingency coefficient `C = sqrt(chi-sq /
    (chi-sq + N))`. No absolute interpretation, though

Entropy = `sum(p * -ln(p))`
  * Consider 20-questions, and `p` is fraction of remaining answer space after
    answering a question. This formula gives value of a question.
  * Given 2 question possibilities, calculate uncertainty coefficient `U(b|a)
    = (H(b) - H(b|a)) / H(b)`. Gives fraction of entropy lost if `a` already
    known before asking `b`
  * Can combine to get `U(a,b) = 2 (H(a) + H(b) - H(a,b) / (H(a) + H(b)))`.
    Numerator is zero if independent

### Correlation

Pearson's r summarizes strength of correlation, not whether it exists
  * `r = Cov[x,y] / sqrt(Var[x] * Var[y])`
  * `r = -Sx / sqrt(S * Sxx)`. Positive/negative --> errors in slope and
    intercept are correlated/anti-correlated

If x and y distributions are sufficiently Normal (no fat tails):
  * r is distributed as Normal(0, 1/sqrt(N))
  * If N is small, use `t = r * sqrt((N - 2)/(1 - r^2))` with N-2 dof
  * If N is moderate (>= 10), can compare difference between r from different
    experiments / see if control variable affects our correlation.
    * Fisher's z-transformation is `z = 1/2 ln((1 + r)/(1 - r))`. This is
      distributed as `Normal(1/2(ln((1+r)/(1-r) + r/(N-1))), 1/sqrt(N-3))`

Rank correlation -- replace number with its relative rank
  * Replace repeats with mean rank if they were all different
  * Ranks are drawn from Uniform(0, 1) dist and sum is guaranteed `= N*(N+1)/2`
  * Spearman rho: linear correlation of ranks. Test significance with `t = rho
    sqrt((N - 2)/(1 - rho^2))`
    * Related to `D = sum(xi - yi)^2` where `rho = 1 - 6D/(N^3 - N)`
    * D is distributed as `Normal((N^3 - N)/6, N^2(N-1)(N+1)^2 / 36)`
  * Kendall's tau: enumerate all pairs of `(xi, yi), (xj, yj)`, then calculate
    `tau = (a-d) / (sqrt(a+d+ex) * sqrt(a+d+ey))`, where `a` is number of
    concordant pairs (x up and y up), `d` is number of discordant pairs, `ex(y)`
    is tie in y(x) rank
    * tau has distribution `Normal(0, (4N + 10)/(9N * (N - 1)))`
    * More robust, but less powerful (more likely to accept null hypothesis)
  * Kendall works better than Spearman for ordinal variables (few values)

### Smoothing

Best to fit data to parametric model or filter a noisy signal (Fourier method)

Simple method: remove linear trend, low-pass filter with FFT, then add back
linear trend

Good for fat tails: replace each data point by the median in window
  * Invariant under rescaling/reparameterizing x or y

## Chapter 14 from Numerical Recipes -- Modeling data

Want to minimize merit function and calculate goodness of fit and parameter
error bars
  * Merit function may have multiple minima

### Maximum likelihood estimation

Minimizing square error is same as minimizing `-log(L)` when `yi ~ Normal(f(xi),
s^2)`
  * `s` is same std dev for all data
  * All data are independent s.t. likelihood is simple product
  * Note: Normal dist is bad for counts (Poisson has fatter tails) and outliers

Chi-sq statistic changes `s` to `si`, a given uncertainty for each observation.
  * This prevents factoring out common `s`, leading to `-log(L) ~ sum((yi -
    yhat) / si)^2`
  * This statistic is drawn from the chi-sq dist with `N - m` d.o.f.
  * Non-normal residuals lead to low statistics, so `p > 0.001` is actually fine
  * Aim for `chi-sq ~ v`, where v is d.o.f. Large `v` --> chi-sq ~ Normal(`v`,
    `2v`)

Can estimate single error bar for all data `s` by minimizing SSE, then taking
`s^2 = 1/N * sum((yi - yhat)^2)` (MSE)
  * Cannot use chi-sq statistic for goodness of fit anymore

### Fitting to y = a + bx

Minimize `sum((yi - a - b xi)^2 / si^2)` for a and b, then collect:
  * `S = sum(1 / si^2)`
  * `Sx = sum(xi / si^2)`
  * `Sy = sum(yi / si^2)`
  * `Sxx = sum(xi^2 / si^2)`
  * `Sxy = sum(xi yi / si^2)`
  * `Delta = S Sxx - (Sx)^2`
  * Can rearrange sums to avoid roundoff -- see text

This yields expressions for `a` and `b`. 
  * Use error propagation `sf^2 = sum((df/dxi)^2 si^2)` to get `sa^2 = Sxx /
    Delta` and `sb^2 = S / Delta`
  * `Cov(a,b) = -Sx / Delta`, `Corr(a,b) = -Sx / sqrt(S Sxx)`
  * Goodness of fit is given by traditional chi-sq

`chi-sq = (1 - r^2) sum((yi - ybar)^2 / si^2)`, where `r` is linear correlation
coefficient

No `si` given? Set `si = 1` and multiply `sa^2` and `sb^2` by `chi-sq / (N-2)`
where `chi-sq` is calculated from model fit to get new parameter uncertainties 

### General linear least squares

`y = sum(ai Xi(x))`, where `Xi(x)` are basis functions
  * Can be any form, like Fourier, polynomials, etc.

Create design matrix `A` with elements `aij = Xj(xi) / si` and target vector `b`
with elements `bi = yi / si`. 
  * `A m = b`, where `m` is model weights vector. Generally, rows > cols.
  * `(A^T A) m = A^T b` gives nice N x N equation to solve
  * `C = inv(A^T A)` is covariance matrix of parameters, s.t. diagonal elements
    are squared parameter uncertainties `smi^2` 
    * Error propagation: `smi^2 = s^2 * (C A^T * 1/s)^2 = C A^T A C^T = inv(A^T
      A) A^T A C = C`

Solving above `(A^T A) m = A^T b` with LU decomp has roundoff error issues
  * Use QR decomp of A or SVD instead

Can freeze parameters, remove from problem by incorporating into `b` vector,
then re-fill in final answer and zero out their variances/covariances

(Near)-singularity in normal equations leads to zero pivots or sensitive
parameters
  * Happens when >=2 `m` vectors are equally valid -- some basis functions
    capture no information
  * SVD pushes down null vectors and provides least squares estimates for
    remaining vectors

After SVD:
  * Parameter estimates are `sum(Ui * b / wi) * Vi`
  * Sq uncertainties for `mi` are `sum(1/wj^2 Vij^2)`, where `wi` is the singular value
    and `Vi` is the corresponding column of `V` -- each uncertainty is
    independent of the others!
    * `Vi` vectors are principal axes of uncertainty ellipsoid of `m` params
  * Covariance matrix for parameters has elements `Cij = sum(Vik Vjk / wk^2)`
  * If zero-pivot encountered, just zero-out its inverse
    * Good cutoff for small values is `N * eps * w_max`

Only downside to SVD is extra `N * M` space to store design matrix, and slow
speed

### Nonlinear models

Minimize chi-sq merit function iteratively

We know the Hessian! Simply apply `delta_ai = c * sum(1/2 Hij delta_aj)`

Levenberg-Marquardt method switches between inverse-Hessian and steepest descent
  * Also dynamically sets the constant `c` above

### Confidence intervals

Ol' reliable: generate random synthetic datasets (with replacement), fit
parameters to each, and report original fit +/- std dev across fits

Generate confidence region in parameter space. You pick confidence level and
region shape
  * Good shape: region containing all parameter vectors s.t.
    they are within constant-chi-sq difference from original fit. Pick
    constant-chi-sq s.t. 95% of parameter vectors lie within region.

Confidence region for parameter subset is simply projection of full region onto
subspace. Never use raw intersection instead of projection!

If residuals have Normal distribution:
  * You can use `C = inv(X^T X)` to estimate parameter covariance matrix 

If (1) residuals are Normal and (2a) it's a linear model or (2b) you have enough
samples s.t. parameter uncertainties lie within linearized model's region:
  1. Pick v = number of parameters of interest and p = confidence level
  2. Calculate chi-sq cutoff for v dof and p confidence level
  3. Grab corresponding rows and columns from chi-sq covariance matrix =
     `inv(curvature)`
  4. Invert the matrix
  5. Equation for CI is `dav inv(matrix) dav`, where `dav` is vector of your
     parameters of interest

Better still -- use SVD! Columns of V are principal axes of constant-chi-sq
ellipsoids, with lengths inversely proportional to singular values
  * Equation for CI is `sum(wi^2 (Vi * da)^2)`
  * Formula for covariance matrix is `sum(1/wi^2 Vi x Vi) = sum(1/wi^2 Vji Vki)`

### Robust estimators

L-estimates are linear combinations of order statistics (like median and Tukey's
trimean = Q1/4 + Q2/2 + Q3/4). 

R-estimates are estimates from rank tests (like Wilcoxon mean rank test,
Kolmogorov-Smirnov test, and Spearman correlation coefficient)

M-estimates are maximum likelihood. 

Generally, max-likelihood involves `0 = sum(1/sigma_i * f'((yi -
y_pred)/sigma_i) * dy_pred/dak)` for parameter `ak`
  * For Normal distributed predictions -- `f'(x) = x`
    * Same as minimizing MSE
    * Points weighted by deviation
  * For double-exponential distributed predictions -- `f'(x) = sign(x)`
    * Same as minimizing MAE
    * Points weighted evenly
    * Discontinuity causes issues for minimizers/solvers -- use downhill simplex
  * For Cauchy distributed predictions -- `f'(x) = x / (1 + 1/2 x^2)`
    * Points weighted by deviation, then de-weighted by deviation!
    * Sensitivity causes issues for minimizers/solvers -- use downhill simplex
  * Andrew's sine -- `f'(x) = sin(x/c) if abs(x) < c pi, else 0`
  * Tukey's biweight -- `f'(x) = x(1 - x^2/c^2) if abs(x) < c, else 0`

### Markov Chain Monte Carlo

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
