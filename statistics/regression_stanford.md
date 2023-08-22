# Modern Regression

https://www.stat.cmu.edu/~larry/=stat401/

See this lecture for a nice review:
  * https://www.stat.cmu.edu/~larry/=stat401/lecture-22.pdf

## Lecture notes

MSE = E[(Y - yhat)^2] = Var[Y - yhat] + (E[y - yhat])^2 = variance + bias^2
  * Minimize w.r.t. yhat -- dMSE/dyhat = -2 (E[Y] - yhat) = 0 --> yhat = E[y]

Predicting one variable from another -- E[E[(Y-yhat)^2 | X]]. Set mu(x) = E[Y |
X=x] is the true population regression function

Best slope estimate = Cov[X,Y] / Var[X] doesn't depend on E[X] or E[Y]

Consistent estimator has ahat -> a as n -> infinity. Unbiased estimator has
E[ahat] = a. Consistent estimator must have Var[ahat] -> 0 as n -> infinity

Shrinkage estimators reduce Var[ahat] by shrinking E[ahat] lower than E[a].
Causes bias but still consistent

Assume E[r | X=x] = 0 and Var[r | X=x] = s^2

Unconditional expectation leverages nested expectation
  * E[B1] = E[E[B1|X1...Xn]] = B1
  * Var[B1] = E[Var[B1|X1...Xn]] + Var[E[B1|X1...Xn]] = s^2/n E[1/sx^2]

Estimators
  * B0hat = ymean - B1hat xmean
  * B0hat = B0 + 1/n sum(1 - xmean (xi - xmean)/sx^2)ei
  * Var[B0hat] = s^2/n (1 + xmean^2 / sx^2)
  * B1hat = cov[x,y] / sx^2, where we use data estimates
  * B1hat = B1 + sum((xi - xmean)/(n sx^2))ei
  * Var[B1hat] = s^2/(n sx^2)
  * ypredmean = B0 + B1x + 1/n sum(1 + (x - xmean) (xi-xmean)/sx^2)ei
  * Var[ypredmean] = s^2/n (1 + (x - meanx)^2/sx^2)

Residuals and error terms are not the same!
  * Guaranteed residuals sum(ei) = 0, indicating linear dependence
  * E[ei^2] = s^2 (1 - 1/n - (Xi - Xmean)^2 / sum(xi^2)) but E[noise^2] = s^2

Error propagation -- use 1st-order Taylor expansion
  * Var[ahat] = 1^T Var[b] 1, where a = f(b1, b2...) and Var matrix has
    Cov[bi,bj] * f'(bi) f'(bj)

Assuming Gaussian noise implies Gaussian coefficients Bi, predictions ypredi.
Chi-sq w n-p params n MLE[s^2]/s^2
  * Distribution assumption allows for MLE
  * MLE is always asymptotically efficient -- Var[MLE] -> 0 quickest
  * Can assume t-dist instead of Gaussian (bigger tails), but math gets messy
  * Use Gaussian B0hat, B1hat, s^2hat to construct CIs for B0, B1, s^2
    * We don't know s^2 --> Bhats follow t-dists. Small difference for large n
  * Non-significant p-value could arise from large CI (trivial)
  * Actual predictions Y|X=x have form Normal(ymean(x), s^2) = Normal(E[ypredmean],
    Var[ypredmean]) + Normal(0, s^2)
    * Prediction CI tends to s^2, not 0, as n -> infinity

Residuals are weighted sum of noise ei = (B0 - Bhat0) + (B1 - Bhat1)xi + ni
  * ei = sumj(dij + 1/n + (xi - xmean)(xj - xmean)/(n sx^2))nj. dij is delta fn
  * Var[ei|X] = s^2 sumj(cij^2). Var[ei] = (n-p)/n s^2
  * Residuals have sum(ei) = 0 and sum((xi - xmean)ei) = 0, but not noise
  * Correlation between residuals is weak and tends to zero
  * E[e^2|X] = Var[e|X] = MSE for all X
  * Can plot current residual vs prior residual to see shape

Can perform transformations of X, nonlinear least sq, smoothing, and
transforming y s.t. f(Y) = XB + noise. Box-Cox can be successful. Use MLE to
estimate params
  * Transforming y: g(Y) = Xb --> E[g(Y)|X=x] = XB -/-> E[Y|X=x] = inv(g)(XB)
  * P(l <= g(Y) <= u | X=x) --> apply inverses if g is increasing and one-to-one
  * Adding polynomial features: use Legendre polynomials to get same answer with
    lower variance
  * Categorical variables enforce parallel prediction surfaces for each value

ANOVA F-test tests if linear model assumptions hold and B1 = 0. Just sees if new
model is better than old (typically intercept-only) model.
  * Multiple F-test takes (s^2null - s^2full)/(pnull - pfull) / (s^2full /
    (n-p)) ~ F(pnull-pfull,n-p)
  * Full F-test considers all slopes. Tests if MSE reduction beats random noise
  * Can use for deleting variables
    * Should only remove variables if CI is tight around zero
    * Stepwise regression like this can have many insig changes cause sig change

p-values can be misleading
  * Bi which is not exactly zero can be made arbitrarily significant by
    increasing n and/or the sample variance of X
  * Bi could be insignificant for low data, high variance, low uncorrelated
    variance
  * If X2 isn't in model: Bhat1 = Cov[X1, B0 + B1X1 + B2X2 + noise] / Var[X1] =
    B1 + B2 Cov[X1,X2]/Var[X1] --> Bhat1 != 0 if B1 = 0 and B2 != 0

R^2 = SSEreg / SSEtot 
  * Tends to Var[ypredmean(X)]/Var[Y] = B1^2 Var[X] / (B1^2 Var[X] + s^2) as n
    -> infinity, since all our parameter estimates are consistent
    * Can make R^2 ~= 0 if small Var[X] or big s^2, even if model is correct
  * MSE and out-of-sample error are much better prediction error indicators
  * Says nothing about CIs, can't compare against transformed Y

Matrix rules
  * E[AX] = A E[X]
    * Note that expectation of a vector takes a vertical sum
  * Var[X] = E[X X^T] - E[X] E[X]^T
  * Var[a + bX] = b^2 Var[X]
  * Var[AX] = A Var[X] A^T
  * E[X^T A X] = E[X]^T A E[X] + tr(A Var[X])
    * X^T A X = tr(X^T A X) = tr(A X X^T) = tr(A Var[X] + E[X] E[X]^T)...
    * For Normals: Var[X^T A X] = 2 tr(A C A C) + 4 mu^T A C A mu

Normal dist: f(X) = 1/(2 pi)^(p/2) sqrt(|C|) exp(-1/2 (X-mu)^T inv(C) (X-mu))

Least squares with matrices
  * Call H = X inv(X^T X) X^T and G = inv(X^T X) X^T
  * Hat matrix gives influence dypredi / dyj = Hij. Symmetric and idempotent
  * Residuals e = Y - Ypred = (I - H) Y projects onto space orthogonal to cols.
    Gives influence dei/dyj = (I - H)ij
    * This implies X^T e = 0, a source of p constraints
  * Var[Ypred] = Var[H noise] = H Var[noise] H^T = s^2 H
  * Var[resid] = Var[(I-H)Y] = Var[(I-H)(XB + noise)] = s^2(I-H)
  * E[s^2hat] = s^2/n tr(I - H) = s^2/n (n - p), since tr(H) = p
  * Bhat = G (XB + noise) = B + G noise --> Normal(B, s^2 inv(X^T X))

Matrix calculus
  * Taking derivative of B^T X^T X B w.r.t. B gives 2 X^T X B
  * grad(x^T a) = a, grad(b^T x) = b, grad(x^T C x) = (C + C^T)x
    * Proven by breaking into sums with indices

Multicollinearity
  * Look at correlation matrix. Obscures multicollinearity w many variables
  * Look at VIF. Rarely used, though.
  * Find eigenvalues of X^T X -- look for eigenvalues near zero
  * Calculate det(X^T X) or condition number (= smax/smin, s = singular value)

Ridge regression minimizes (Y - XB)^T (Y - XB) + lambda ||B||^2
  * Gives single answer (estimate stability) to multicollinear reg problem
  * Gradient = 0 --> B = inv(X^T X + lambda I) X^T Y
  * Induces downward bias but reduces variance
  * Same as min (Y - XB)^T (Y - XB) s.t. ||B||^2 <= c -- use Lagrange mult
  * Need to standardize variables first!
  * Regularization or dimension reduction needed if n << p

Confidence ellipsoid created by (Bhat - B)^T inv(Var[B]) (Bhat - B) ~ chi-sq(p)
  * Var[C^-1/2 (Bhat - B)] = V U^-1/2 V^T V U V = I --> C^-1/2 (Bhat-B) ~ N(0,I)
  * Above expression = (C^-1/2 (Bhat - B))^T (C^-1/2 (Bhat - B)) ~ sum of p
    squared Normals ~ chi-sq(p)

Interaction terms yield more flexibility
  * Different slopes and intercepts for different categories
  * Same noise variance, though

Outliers and influential points aren't the same
  * Jackknife residual = (Yi - Ypredi')/s = ei / (si' sqrt(1 - hii)), where
    prime denotes case where we deleted that point from the fit
  * Cook's distance = (Y - Y')^T (Y - Y')/(p s^2) = ri^2/p hii/(1-hii), where ri
    = ei / (s^2 sqrt(1-hii)) = studentized residual
  * Coefficients change as Bhat' = Bhat - inv(X^T X) ei / (1 - hii)
  * Find outliers with Cook's distance, leverage (= hii), or student resid
  * Delete points, change model, or change estimation procedure if outliers
    * Data could be erroneous or come from different population
    * Model may need quadratic term or nonlinear form
    * Robust regression uses |Y - XB| or Huber function for loss

Predictions for new data has bigger MSE than for training data
  * For same X values: E[sum(Yi' - Ypredi)^2] = E[sum(Yi - Ypredi)^2] + 2 s^2 p
  * Note that Yi and Yi' are iid and Cov[Yi, Ypredi] = Hii s^2 --> sum(Cov) =
    tr(H) s^2 = p s^2.
    * tr(H) = tr(X inv(X^T X) X^T) = tr(x^T X inv(X^T X)) = tr(Ip) where Ip is
      pxp identity matrix
  * Perform E[sum(A - B)^2] = Var[(A-B)] + (E[(A-B)])^2
  * Multiply everything by 1/n to get optimism = 2/n s^2 p
  * Best estimate of generalization error is avg. over cross-validation trials
    * LOOCV = 1/n sum((Yi - Ypredi')^2) = 1/n sum((Yi - Ypredi)/(1-Hii)^2)
    * Taylor exp and using avg Hii = p/n yields LOOCV = training MSE + optimism

Model selection 
  * Pick model with best generalization error via CV
  * Mallow's Cp = 1/n sum((Yi - Ypredi)^2) + optimism -- penalizes more params
    * Use largest model's estimate of s^2
  * Adjusted R^2 = 1 - MSE/sy^2 n/(n-p) -- incorporates unbiased estimate of s^2
  * Akaike Info Criterion = log-likelihood - dimension = -n/2(1 + log(2pi)) - n/2
    log(MSE) - p+1 for Gaussian case (p counts intercept, +1 for noise estimate)
    * Max AIC yields same model as max Cp if correct model is a candidate
  * Bayesian Info Criterion = log-likelihood - log(n)/2 dim -- stronger penalty

Data splitting solves issue of doing inference w same data as used for model
selection. Use 1/2 for models training + selection, then retrain on other 1/2

Weighted least squares allows focusing on important regions or y error bars
  * Minimize (Y - XB)^T W (Y - XB) --> Bhat = inv(X^T W X) X^T W y
  * Set K = inv(X^T W X) X^T W. Then Bhat = Ky = B + Knoise, E[Bhat] = B,
    Var[Bhat] = K C K^T where C is Var[noise] (which isn't s^2 I anymore)
    * Var[Bhat] = inv(X^T inv(C) X) if W = inv(C)
  * Useful if:
    * Yi are averaged over ni measurements, s.t. wi ~ ni
    * Yi ~ Binom(ni, pi) s.t. Var[Yi] = ni pi (1 - pi)
    * Yi ~ Poisson(li) s.t. Var[Yi] = li. Useful if Yi can be infinite

Gauss-Markov shows that above Bhat estimator has least var among unbiased est.
  * Bhat = (K+R)C. Var[Bhat'] = inv(X^T inv(C) X)+R^T C R = Var[Bhat] + R^T C R

WLS yields unbiased Bhat with lower variance than OLS
  * Var[Bhat] = 1/sum(xi^2 / si^2) = sum(xi^2 si^2) / (sum(xi/si)^2 sum(xi
    si)^2) <= sum(xi^2 si^2) / sum(xi^2)^2 (by Cauchy-Schwartz) = Var[BhatOLS]

Estimating noise structure. E[noise|X] = 0, but Var[noise|X] can be any matrix
  * Off-diagonal terms imply correlation between noise 
  * Get ypredmean(x). Then calculate sq residuals or log sq residuals. Then
    predict conditional means. Now you're done or apply sx^2 = exp(pred)
    * Exponential method guarantees positive variances
  * If C is somehow known: Take Cholesky decomp and premultiply y and X by
    inv(R) then do OLS. Or, do weighted least sq with W = inv(C)
    * C = R R^T --> Var[inv(R) noise] = inv(R) R R^T inv(R)^T = I

Variable selection reduces variance but increases bias
  * E[(Y - ypredmean(X))^2] = E[(Y - mean(X))^2] + E[(E[ypredmean(X)] -
    mean(X))^2] + E[(ypredmean(X) - E[ypredmean(X)])^2] = unavoidable error +
    bias^2 + variance
  * p-values are sensitive to Bhat size, noise reduction, sample size, Var[Xi],
    and non-correlation (low VIF) -- but none of these indicates "importance"
    * p = Bhati / (sqrt(VIF) s / sqrt(n Var[Xi]))
    * p-values answers question "can we reliably detect non-zero coefficient?"
  * AIC and Cp approximate cross-validation. Just use CV!

Can perform stepwise regression or LASSO for variable selection
  * Be sure to standardize variables first. Can center Y to obviate intercept
  * Forward stepwise regression adds single variable at a time based on best CV
    score, AIC, SSR, etc. Stop after next improvement doesn't pass threshold
  * LASSO just needs CV to pick lambda
  * Only do inference (CIs, hypothesis tests) on new data. Split data in half

Nonparametric regression is flexible
  * Regressogram: ypredmean(x) = sum(ymeanj I(X in Bj)) predicts average y value
    in k total buckets each of width h
  * Kernel smoothing replaces indicator with kernel: ypredmean(x) =
    sum(Ky)/sum(K) = sum(li Yi), where K = K(z) = K((x - xi)/h)
    * Smoothing kernel has integral = 1, E[z] = 0, Var[z] > 0
    * Common choice is exp(-1/2 z^2)
  * Kernel is linear -- yhat = L y. tr(L) is effective d.o.f. L isn't projector
  * Choose h via CV. LOOCV has MSE 1/n sum((Yi - ypredmean(xi)) / (1 - Lii))^2.
    Can even replace 1/(1-Lii)^2 with 1/(1 - dof/n)^2 for generalized CV
  * Nonparametric MSE reduces as n^(-4/5) rather than n^-1

Produce variability bands for ypredmean(x) via bootstrapping
  * Technically doesn't produce CI, but good enough

Multidimensional nonparametric regression has curse of dimensionality --
neighborhoods are sparse. MSE has form n^(-4/(4+d))

Causal inference gives prediction after intervening and setting X=x
  * Requires stronger assumptions
  * Causal inference estimates the parameter characterizing causation. Causal
    discovery in a set of variables is statistically impossible
  * Best method is randomized controlled trial. Observational inference is worse

Confounding variables account for dependence bt X and Y (e.g., some ppl choose
to take vitamins and are healthy)
  * We desire X indep Y, but settle on (X indep Y) | Z. Parameter = E[Y1] -
    E[Y0] = integral over pz dz (E[Y|X=1,Z=z] - E[Y|X=0,Z=z])
  * Parameter = B1 if linear model is correct and all confounding factors are
    included in model

### Exercises

Cov[X,e] = E[Xe] - E[X]E[e] = E[E[Xe|X=x]] = E[X]E[e|X=x]. 2nd term is usually 0

Consider biased s^2 estimator 1/n e^t e. E[est] = 1/n E[sum((yi - ypred)^2)] =
1/n E[Var[y - ypred] + (E[y - ypred])^2] = 1/n (n-p)s^2 due to p constraints

p-values are uniformly distributed over [0,1] 
  * Ff(f0) = P(F(X) <= f0) = P(X <= inv(F)(f0)) = F(inv(F)(f0)) = f0 --> F(X) ~
    U(0,1)
  * p = 1 - F|t|(|t|) = 1 - U(0,1) = U(0,1)

### Homework

For discrete X in {1,2,...,inf}, E[X] = sum(P(X>=xi)). Write matrix of terms
(P1+P2+P3+...)+(P2+P3+...)+... and notice 1 P1, 2 P2, 3 P3,... = sum(xi P(Xi))

Sum(residuals) = 1 dot e = 0, since the 1 vector is always in our column space
  * Fitting Y on [1,e] design matrix yields zero slope and thus Ymean intercept

Using OLS estimator for B when we observe W = X + d instead yields downward bias
  * Consider no intercept: Bhat = w y / w w --> E[Bhat] = B1 E[xx / (xx + dd)]

E[MLE for s^2] = E[e^T e / n] = (n-p)/n E[e^T e / (n-p)] = (n-p)/n, by chi-sq

0 <= Hii <= 1 because hii = hii^2 + sum(hii hij) -- hii is positive and bigger
than hii^2
