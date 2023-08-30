# Elements of Statistical Learning

## Introduction 

Linear classifier trains linear model on 0/1 data and sets 1 if pred>=0.5 else 0
  * Good if generating distribution is a few Gaussians with uncorrelated
    components and different means
  * Basis expansions and locally-weighted least sq yields flexible boundaries
  * Assumes function is globally linear

K nearest neighbors averages over k nearest neighbors
  * Good if generating distribution is many low-variance Gaussians with means
    distributed as a Gaussian
  * k = 1 leads to Voronoi tesselation with zero training error
  * Kernels use weights that smoothly decrease and can emphasize some variables
  * Universal approximator due to averaging/conditioning over neighborhood, but
    high variance and slow convergence w.r.t. n
  * Assumes function is locally constant

Bayesian classifier picks max probability class given X
  * Define loss matrix L and set to 0 on diagonal and 1 off-diag
  * Minimize expected error = Ex[sumk(L(y, ypred(X) * P(yk|X)))]

f(x) = E[Y|X=x] yields least squared error E[(Y - f(X))^2]. f(x) = Median(Y|X=x)
yields least absolute error E[|Y - f(X)|]. L1 loss is more robust than L2

Curse of dimensionality
  * Edge length containing fraction f of unit volume = f^(1/d). Capturing 10% of
    data in cube requires covering 80% of each input variable's dimension in 10D
  * Most data are near boundaries, making training harder
  * Data is sparsely strewn about the space. Density ~ N^(1/d)

MSE = E[(ypred - y)^2] = E[(ypred - E[ypred])^2] + E[(E[ypred] - y)^2] =
variance + bias^2. Expectations are taken over all possible training data
  * Expected prediction error for linear reg = Var[y0|x0] + Var[ypred0] +
    Bias^2(ypred0) = s^2 + x0^T inv(X^T X) x0 s^2 + 0^2 = s^2 p/N + s^2
    * Avoided curse of dimensionality if s^2 is small and/or N is large!
  * KNN generalization error = E[(Y - fpred(x)^2)|X=x] = s^2 + (f(x) - 1/k
    sum(f(xi)))^2 + s^2/k = irredicible + bias^2 + variance
    * Bias down and variance up with increasing complexity (k down)

Additive error model rolls up measurement error/missing variables into noise
  * Can have noise term also depend on x, e.g. via Binomial p(x)(1 - p(x))

Linear basis expansion -- f(x) = sum(hi(x) Bi) where the h(x) are basis fcts
  * Can apply least squares to find best Bhat. Analytic answer if h(x) have no
    hidden params, o/w use iterative/numerical optimization
  * More generally, can use MLE if P(y|B) is assumed
  * M polynomial splines of degree K connect up at M-K knots in K-1 dimensions

Statistical learning can find many predictor fcts. Need to induce constraints
  * Constraint strength is dictated by how big you define a neighborhood
  * Locally-varying fcts in small isotropic neighborhoods struggle w high dim
  * All methods that overcome curse of dim have a metric for measuring
    neighborhoods, preventing isotropy

Roughness penalties represent log-priors. Minimization yields posterior mode
  * E.g., cubic smoothing loss = sum(y - f(x))^2 + lambda integral(f''(x)^2)

Kernel methods specify local neighborhood
  * Popular choice is Gaussian kernel K(x0,x) = 1/l exp(-1/2 |x-x0|^2 / l)
  * SSR = sum(K(x0,xi) (y - f(xi))^2)
    * f(x) = constant -> Nadaraya-Watson f(x0) = sum(K(x0,xi)yi)/sum(K(x0,xi))
    * f(x) = constant + XB -> local linear regression
  * Indicator kernel I(|x-x0| <= |xk-x0|) -> k-nearest neighbors
  * Radial basis functions use f(x) = sum(K(mui,x) Bi)
  * Neural networks use f(x) = sum(s(ai^T x + bi) Bi) where s(x) is sigmoid

## Linear methods
 
Works well for few training points or low signal-to-noise. Can use basis fcts

Least squares is reasonable if data is independent, or at least if yi are
conditionally independent given xi

Assumptions
  * Uncorrelated yi with const variance s^2 with xi nonrandom yields Var[Bhat]
  * Inferences require E[Y|X] is linear, noise is additive and Gaussian, Bhat
    and s^2hat are independent
    * Bhat is Normal(B, inv(X^T X) s^2) and (n-p)s^2hat / s^2 is chisq(n-p) so
      Bhat / (sqrt(s^2hat inv(X^T X)ii)) is t-dist with n-p d.o.f.
    * Use F-test on F = (SSR0 - SSR1)(p1-p0) / SSR1/(n-p1)
    * T-stats are same as F-test with one coef dropped
    * Conf set is (Bhat - B)^T X^T X (Bhat - B) <= s^2hat chisq(p, 1-a)

Gauss-Markov guarantees that least sq est. has least variance among unbiased est
  * Uses triangle inequality (Cauchy-Schwartz)
  * Implies least sq est has smallest MSE of all unbiased linear ests
  * Expected prediction error for new point = E[(y - ypred(x0))^2] = s^2 + MSE

Multiple regression is like sequential regressions on residuals (Gram-Schmidt)
  * Regress x on 1 to produce res x - xmean^T 1. Regress y on z to get Bhat
  * Regress xi on each orthogonal residual vector so far, then remove new
    residual (weighted by regression param) from xi to get zi
  * Bhati = regress y on residual zi
  * Var[Bhati] = s^2 / ||zi||^2
  * This is the QR decomp -- X = Z inv(D) D G = QR
    * R Bhat = Q^T y, yhat = Q Q^T y (orthogonal projection)
  * Orthogonal inputs --> multiple reg is like many simple regs

Multiple outputs -- extend Y and B into matrices. Bhat = inv(X^T X) X^T Y still
  * For correlated noise, minimize (Y-XB)^T inv(C) (Y-XB) where C is kxk
    noise covariance matrix. B solution decouples if C same for each sample

Subset selection and coefficient shrinkage induce bias to reduce variance,
increasing overall prediction accuracy and yielding more interpretable model
  * Subset selection has high variance due to discrete yes/no process

Ridge regression imposes continuous penalty on L2 norm of Bhat
  * Prevents large variance bt correlated vars, where large cancellations occur
  * Requires standardizing inputs
  * Don't penalize intercept term! That depends on Y origin. Center all
    variables first, then disregard intercept term
  * Min (y - XB)^T (y - XB) + l B^T B --> Bhat' = inv(X^T X + lI) X^T y. Makes
    problem nonsingular!
  * Orthogonal X --> Bhat' are just uniformly rescaled Bhat / (1 + l)
  * Same as assuming Normal(0,s^2/l^2) B prior and finding posterior mode/mean
  * Take SVD -- XBhat' = U D inv(D + lI) D U^T y = sum(ui + di^2/(dj+l) ui^T y)
    * More shrinkage for dimensions with smaller sq singular values di^2
    * X = U D V^T --> X^T X = V D^2 V^T is eigendecomp. U spans col space and V
      spans row space. Eigenvectors point out linear combos of X cols with
      biggest variance. Each variance = di^2 / n
  * The hope is that y varies most along directions with most variance
  * Consider effective d.o.f. = tr(X inv(X^T X + lI) X^T) = sum(di^2 / (di^2+l))

LASSO is same as ridge, but L1 norm penalty 
  * Still need to standardize X and center y and discard intercept
  * If l > L1(Bhat), nothing changes. If l = L1(Bhat)/2, shrinkage ~ 50%

Principal components reg is like ridge, but discards smallest p-M components

Partial least sq selects directions with high variance * sq correlation with y
  * Calculate vector z = sum(xi^T y xi), then regress y on z. Orthogonalize all
    xi against z and recurse. Stop after reaching M zi vectors and their regs
  * Solution is nonlinear fct of y
  * Variance typically dominates, so it acts like ridge/principal comp reg
  * Does nothing if X already orthogonal
  * Actually same as conjugate gradients algo for least sq!

Comparison
  * Discrete methods perform worse than continuous
  * Ridge shrinks all directions, imposing no prior and discovering corr in X
  * PCR's prior places more weight on high-variance directions. Can be unstable
  * For orthonormal X -- ridge scales, lasso shifts+truncates at zero, subset
    keeps M largest

L0 norm is subset selection, L1 norm is lasso, L2 norm is ridge
  * Lasso corresponds to Laplace prior
  * Lasso and subset selection have prior mode != mean. Typically want mean
  * Fractional norms concentrate mass around coord axes and are not convex
  * CV for norm order not worth extra variance
  * Norm > L1 is differentiable at 0, so cannot zero-out coefs
  * Elastic net averages lasso and ridge. Selects variables and shrinks together
    coefs for correlated vars. Also computationally efficient compared to
    fractional norms

Multiple output regression shrinkage
  * Can estimate separate shrinkage params l or use common one
  * Canonical correlation analysis maximizes sq correlation between orthogonal
    vectors in X and separate orthogonal vectors in Y. Similar to PCA reg
    * Uses generalized SVD of sample cross-covariance matrix Y^T X / n
  * Reduced rank reg minimizes (Y - XB)^T inv(C) (Y - XB), where C is estimated
    with Y^T Y / n. Bhat' = Bhat Um inv(Um) where Um is submatrix from SVD
    * Bhat' is interpreted as OLS on pooled response y Um, mapped back w inv(Um)
    * Ypred = X Bhat' = H Y Pm, where H is OLS hat and Pm is CCA projector
    * Better estimate of C is (Y - XB)^T (Y - XB) / (n - pk). Same answer though
  * Breiman and Friedman have smooth reduced rank regression

Cholesky on X^T X requires p^3 + N p^2 / 2 flops, QR on X requires N p^2 flops

### Exercises

Prove Gauss-Markov
  * Call A = inv(X^T X) X^T
  * New estimator Bhat' = Ay + Cy, with E[Ay] = B and E[Cy] = CXB --> CX = 0
  * Var[Bhat'] = s^2 (A+C) (A+C)^T = s^2 (A A^T + C A^T + A C^T + C C^T) =
    Var[Bhat] + s^2 C C^T with 2nd term positive semi-def 
    * v^T C C^T v = (C^T v)^T (C^T v) >= 0

T-test statistic is same as F-test statistic for model without 1 param
  * Set up constrained opt s.t. v^T B = 0, where v = (0,0,...,1,...0,0). Find
    optimum of Lagrangian at Bhatnew = Bhat - lhat/2 inv(X^T X) vj. Then SSR0 =
    (y - Bhatnew X)^T (y - Bhatnew)

Given QR decomp of X and current residual e, find best feature in X2 to include
  * Orthogonalize a feature into Q, then regress e onto new q. Repeat for each
    feature and pick biggest match (smallest remaining residual)

Given regression parameter z-scores, pick feature to remove
  * Select smallest absolute z-score. Z-score is same as F-score for removing
    single variable, and F-score captures SSR increase/decrease

Given C = Cov[noise] for multiple output reg, find Bhat
  * MLE on multivariate Gaussian gives min (y - XB)^T inv(C) (y - XB) --> Bhat =
    inv(X^T inv(C) X) X^T inv(C) y. Take Cholesky of C to get inv(C) = S S^T and
    multiply in redundant terms to constructively cancel, leaving OLS Bhat
  * Only works if C same for each observation. O/w need quadratic optimization

Constraints can be implemented via hint data satisfying them
  * Ridge = OLS on X augmented with sqrt(l) I with corresponding y-values of 0
  * Break summation form of SSR = sum((y - XB)^2) and break into top and bottom

PCR and OLS Bhat are same
  * X = U D V^T --> Bhat = inv(X^T X) X^T y = V inv(D) U^T y
  * Z = X V, T = y^T z / z^T z, Bhat' = V T = V inv(D) U^T y

For orthonormal X
  * Ridge -- Bhat' = inv(X^T X + lI) X^T y = 1/(1+l) X^T y = 1/(1+l) Bhat
  * Lasso -- Bhati' = sign(Bhati) (|Bhati| - l). Expand (y - XB)^T (y - XB), use
    orthonormal X, then declare individual optimization 1/2 Bi^2 + (l - Bhati)Bi

## Linear classification

If monotone transformation of P(G=i|X=x) is linear in x, then decision boundary
is also linear (hyperplanar)
  * E.g., logit transformation, wherein decision boundary has log-odds = 0

Linear regression of raw conditional probs P(G=k|X=x) = E[Y|X=x] can work
  * Set up indicator variables in matrix Y and fit multiple output linear reg
  * num classes > 2 has issue of masking -- one group's response can be
    symmetric about origin s.t. it's never selected
    * Try expanding basis with polynomials

Linear discriminant analysis assumes Gaussians for each class, with unique means
and common covariance matrix
  * P(G=k|X=x) = fi(x) pi / sum(fi(x) pi)
  * Ratio of log-odds = log(pi/pj) - 1/2 (mui + muj)^T inv(C) (mui - muj) + x^T
    inv(C) (mui - muj) -- linear in x, implying linear decision boundary)
  * Use MLE estimates of pi, mui, and C (or use unbiased estimate)
  * The "discriminant function" is x^T inv(C) mui - 1/2 mui^T inv(C) mui + log(pi)
    * Same regardless of basis. Matrices pull out and cancel
  * Quadratic discriminant analysis estimates separate Ci for each class
  * Works well due to low variance. Estimates are stable
  * Can add regularization to covariance matrix C = a s^2I + (1-a)Cest

LDA is simply finding nearest centroid in centroid-space, reducing dimension
  * Desire subspace that maximally separates centroids -- a^T B a / a^T W a,
    where B is inter-class covariance and W is intra-class covariance s.t. C=B+W
  * Direction given by max eigenvalue of inv(W) B

Logistic regression models log-odds against 2 classes as linear function
  * Max log-likelihood of multinomial = sum(yi B^T xi + log(1 + exp(B^T xi)))
  * Use Newton-Raphson with first and second derivs to optimize

LDA assumes Gaussian P(X,G) whereas logistic focuses only on P(G|X) 
  * LDA assumes more structure and has lower variance. Similar performance too
  * LDA is most optimal if classes truly come from Gaussian dist

## Basis expansion

Splines partition each variable, then fit polynomial fcts to those regions
  * Must select partition spots manually/via CV
  * Constraints at borders enforce continuity in value/1st deriv/2nd deriv
  * Can capture nonlinear effects
  * X' = R^T B, where X are new features and R is n x p' translator matrix

Best spline minimizes SSR + l integral(f''(x))
  * Solution is spline with break points at each datum
  * Best Bhat minimizes (y - RX')^T (y - RX') + l B^T D B, where D is 2nd deriv
    matrix of basis fcts. Bhat = inv(R^T R + l D) R^T y, like ridge reg
  * Ridge version of hat matrix acts as smoother bc H^2 < H. Effective d.o.f. =
    tr(H) < N

Can take eigendecomposition of H to find eigenfunctions
  * Eigenfunctions don't change w.r.t. lambda parameter
  * Higher eigenfunctions are shrunk more due to high curvature (just like
    Fourier solution to heat eqn?)

Banded smoothing matrices are equivalent to local smoothing kernels

Radial basis functions arise in multidimensional splines
  * Gaussian process regression is Bayesian interpretation of reproducing kernel
    Hilbert spaces (which use the kernel trick)
  * These methods estimate eigendecomposition using data! Very physics-y

## Kernel methods

The model IS the training data, plus some neighborhood parameter lambda

Rolling window is discontinuous. Use Nadaraya kernel-weighted average instead

Basic kernel has bias at borders. Local linear reg makes 1st order correction
  * Each point has its own parameters ai and Bi
  * Minimize sum(K(xi,xj)(yi - ai - Bi xj)^2) --> ypred = b^T inv(B^T W B) B^T W
    y = sum(li yi), where li combines regression and kernel into one term
  * Therefore, li comprise hat matrix L which is a shrinkage matrix
  * Quadratic regression has marginal improvement with more variance and worse
    performance at boundaries. Stick to linear correction

Local regression is poor in high dimensions bc space is sparse and most points
are at boundary. Local polynomial regression helps w boundary
  * Local regression has poor interpretability beyond 2 or 3 dimensions. Use
    marginal linear regression instead at different marginal values

Can upweigh some features with matrix K(x,x0) = f((x-x0)^T A (x-x0)/d)

RBF method uses kernels as features, each with own Bi -- f(x) = sum(Ki(x,x0) Bi)
  * Need to estimate means and variances for each feature separately
  * Same as Gaussian mixture model when cov matrix = sp^2 I
    * f(x) = sum(ai Normal(mui, Ci)). Cov matrix needn't be diagonal
    * Use expectation-maximization to fit parameters

## Model selection

Use 60-20-20 split on training, validation, and test sets. Validation is used
for generalization error estimate to perform model selection.
  * Use AIC, BIC, MDL, or SRM to analytically estimate error. Bootstrap/CV
    resamples to estimate error

Optimism is the underestimation of out-of-sample error
  * Estimating optimism lets one estimate out-of-sample error = in-sample + opt
  * Optimism = 2/n sum(Cov[ypredi, yi]) for most loss functions
    * Equals 2/n tr(Cov(Hy,y)) = 2/n tr(H) s^2 = 2/n p s^2 for linear least-sq 
    * This yields out-of-sample error = Cp statistic
  * Optimism increases when each point has stronger influence on its prediction
    (hat matrix is strongly diagonal)

AIC = 2 p/n - 2 loglik / n, which reduces to Cp for Gaussian likelihood

BIC = log N d - 2 loglik is stricter, but will pick correct model as n -> inf

Cross-validation is easy, popular, and flexible. Folds+ --> bias- var+
  * Check learning curve (MSE vs. training size). Want to do CV where training
    curve is flat

Bootstrap evaluated on entire training set is too optimistic. Use out-of-bag
performance instead -- for each datum, average sq error over bootstrapped models
not trained on that datum
  * P(datum i in bootstrap b) = 1 - (1 - 1/n)^n ~ 1 - 1/e ~ 0.63

## Model inference and averaging

Nonparametric bootstrap trains on different random samples (w replacement) and
constructs empirical prediction confidence bounds. Parametric bootstrap adds
(Gaussian, e.g.) noise to data and refits
  * Parametric returns same prediction conf intervals as least squares

Information = -sum(second deriv of log-likelihood w.r.t. param). Fisher info =
E[info]. MLE ~ Normal(param, inv(Fisher info)). Estimate var of MLE with 2nd
deriv evaluated at MLE

Bayesian techniques account for uncertainty in estimating param
  * Pure Bayesian puts prior on all params, then integrates out irrelevant vars
  * Bootstrap approximates Bayesian posterior without needing to specify prior!

Expectation maximization gets best local solution for mixture models
  * Initialize params with guesses. Setting each variance = overall var is good
  * Compute responsibilities for each model i and point j rij = pi fi(yj) /
    sum(pi fi(yj))
  * Compute parameters (typically means and variances) weighted by
    responsibilities
  * Compute mixing probabilities pi = 1/n sum(rij)
  * Responsibilities are expected values E[pi|params,X]
  * Technically, the Dirac delta around a single point maximizes likelihood.
    Want more disperse solution

Gibbs sampler is like EM, but samples conditional dist rather than maximizes
  * Cycle through each parameter, sampling from its conditional dist keeping
    other params fixed. Gaussians are nice
