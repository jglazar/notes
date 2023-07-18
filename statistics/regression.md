# Linear regression

## Quant primer

Assumptions
  * Weak exogeneity -- X has no error (it's not a random variable)
    * Avoids requiring more complex errors-in-variables models
    * Test w bootstrap. Use MCMC to estimate params with heirarchical model
  * Linearity -- E[Y|X] is linear function of X and parameters
    * Not that bad bc X are constants. Just requires linearity in parameters
    * Can have x1^2, e.g.
  * Homoskedasticity of residuals
    * Heterosk. causes imprecise (but unbiased) parameter estimates + biased std
      errors, leading to bad tests/CIs. Many low + some high --> overestimate
      avg. sq. residual leading to high CIs. Vice versa for many high + some low
    * Fix with transformation. GLMs (weighted least squares) can assign residual
      variance prop. to mean. Bayesian linear reg. can handle heterosk.
  * Independent errors -- no correlations in residuals
    * Correlations emerge during crises
    * Fix with multivariate reg., correlation structure, or generalized least sq
  * No multicollinearity in X
    * Technically, only requires no perfect multicollinearity
    * Messes with linear algebra solver. Cannot trust t-tests. Must include all
      variables regardless of test results. Sensitive to small changes in data
  * (Optional) Residuals follow a given distribution. Useful for theoretical
    interpretations
    * Heavier tails mess with parameter estimates/conf. intervals. Fix with
      robust regression. Can model specific distribution.

Test for parameters uses statistic `(s - s0)/stddev(S)`, where s is estimated
value, s0 is reference value (typically 0), and S is true variable
  * Normal + homoskedastic errors --> statistic is t-distributed with n-p d.o.f.
  * Multicollinearity leads to high stddev(S) and correlations b/t params

Least squares gives `b = inv(X^T X) X^T y`
  * `SSE = e^T e = (Y-Xb)^T (Y-Xb) = Y^T T - b^T X^T Y - Y^T X b + b^T x^T X b =
    Y^T Y - 2 Y^T X b + b^T X^T X b`
  * Derivative w.r.t. b = `-2 X^T Y + 2 X^T X b` = 0
  * 2nd derivative = `2 X^T X` = positive, indicating minimum

Can use MLE (frequentist) or estimation (Bayesian) when assuming distribution
(prior).
  * Assume Normal -- Y ~ Normal(0, s^2 I) with nice likelihood, yielding `dL/db
    = 1/2s^2 (2 X^T Y - 2 X^T X b)` and `dL/ds = -n/s + 1/s^3 (Y-Xb)^T (Y-Xb)`
    * Thus, `b = inv(X^T X) X^T Y` and `s^2 = 1/n e^T e`
  * Most GLMs don't have MLE match least-squares or have analytic solution

Simple linear regression has neat form
  * `SSE = sum((yi - a + bxi)^2)`
  * `a = y_mean - bx_mean` and `b = sum((yi - y_mean)(xi - x_mean))/sum((xi -
    x_mean)^2) = Cov[x,y]/Var[x] = Corr[x,y] sqrt(Var[y] / Var[x])`
    * So slope = correlation when Var[y] = Var[x]
  * SLR has R^2 = Corr[x,y]^2

Linear regression for T/F values
  * Logistic regression assumes y ~ Bernoulli(p), logit(p) = Xb, p =
    logistic(Xb)
  * Probit regression assumes y ~ Bernoulli(p), probit(p) = Xb, p = CDF(Xb),
    where CDF is the std. Normal CDF and probit is inverse cdf (quantile fct.)
  * R^2 doesn't exist anymore -- use pseudo-R^2 instead
  * No analytic solution -- use iterative method or MLE/posterior estimation
  * Use Wald statistic for testing -- `(b - b0)^2 / stddev(B)` w chi-sq. dist.


## Wikipedia

### Simple linear regression

OLS minimizes sum of squared residuals. Can minimize sum of absolute errors or
use more exotic estimators like Theil-San (estimate slope as avg. of pairwise
slopes) 

As shown above, `a = y_mean - b x_mean` and `b = Corr[x,y] sy/sx`, so `(y_pred -
u_mean)/sy = corr[x,y] (x - x_mean)/sx` is centered, stddev-weighted line
through origin
  * This implies regression toward the mean bc -1 < Corr < +1. The outlier-ness
    for yi will be less than the outlier-ness for xi
  * Also, `b = sum(wi (yi - y_mean)/(xi - x_mean))`, where `wi = (x_i -
    x_mean)^2 / sum((xi - x_mean)^2)`. This implies that extreme xi have high
    influence on the slope
  * Line will go through `(x_mean, y_mean)` due to intercept estimate

Corr[x,y] is estimator of Pearson correlation only if we interpret xi as samples
from some distribution with non-zero variance. OLS assumes X isn't a random var.

Sum of residuals must be identically zero. 

Residuals and x-values are uncorrelated, forcing `sum(xi ei) = 0`.

`se^2 = (1 - rho_xy^2) sy^2`

Conf. intervals and unbiasedness are only valid under specific distribution
assumptions
  * Standard method for CI construction assumes Normal residuals or many
    samples, in which case the parameter's statistic is approximately Normal

Assuming e ~ Normal(0, s^2) and xi are constants (not random variables)
  * Thus, y, a, and b are all Normal
  * `b ~ Normal(b_hat, s^2 / sum((xi - x_mean)^2))`
  * SSE ~ chi-sq. with n-2 d.o.f.
  * Thus, `(b_hat - b0)/(sb_hat)` is t-distributed with n-2 d.o.f.
  * `sb_hat = sqrt(1/(n-2) sum(e_i^2) / sum((xi - x_mean)^2))` is "standard error
    of the estimator b"
  * a has std error `sb_hat sqrt(1/n sum(xi^2))`

Confidence band around prediction means (not predictions themselves) is smallest
around `x_mean` and expands in either direction

No intercept -- `b = E[XY]/E[X^2]`
  * std error of b = `sqrt(1/(n-1) sum(ei^2) / sum(xi^2))`

If not assuming Normal residuals but have large sample size:
  * Replace t-dist with std. Normal
  * Can replace 1/(n-2) with 1/n, but it won't make a big difference bc n is big
  * ? May still have CI issues from large residuals?

### Linear regression

Used for predicting new values or quantifying strength of relationship bt
response and explanatory variables
  * Can find subsets of variables with no or redundant relationships to target

Can use least-squares, least sum of absolute deviations, ridge regression
(penalize L2 norm of parameters), LASSO (L1 norm)

Dependent variable is assumed to be caused/influenced by independent variables

Must include intercept for some statistical inference procedures

X is sometimes assumed to be constant, other times assumed to be random variable

Parameters are partial derivatives of dependent w.r.t. independent. Called
"unique effect of xi on y"
  * "Marginal effect of xi on y" is total derivative. Found w simple lin. reg.
  * Total deriv = `Dy/Dx1 = dy/dx1 + dy/dx2 Dx2/Dxi + ...`

Tricky intepretation -- can't vary intercept or dummy terms. Can't hold x fixed
and change x^2 if both are in model
  * Can also have high unique effect but low marginal effect and vice versa

General linear models have vector yi and matrix of parameters B

Generalized linear models have bounded/discrete yi
  * E[Y|X] = inv(g)(XB), where g links (-inf,inf) to proper bounds

Ridge regression introduces bias to lower variance. Lowers MSE if
multicollinearity or overfitting is an issue. Bad for inference

Least absolute deviation (LAD) is robust. Same as MLE when e ~ Laplace 

Parameters are assumed to be `Normal(b_hat, stdvar(b))` where `stdvar(b)
= inv(X^T X) s^2` and s^2 is estimated residual variance
  * Emerges because parameter estimates are n weighted sums of (yi - ymean)
  * Parameters are t-dist. if residuals are Normal or Normal if CLT is invoked

### Other techniques

Other estimation techniques
  * Bayesian -- assume prior for parameters and get posterior
  * Quantile -- model median of Y|X rather than mean
  * Least-angle for m < n
  * Theil-San is robust, gets median of pairwise slope

Weighted least squares has `b = inv(X^T W X) X^T W y`
  * `wii = 1/sii^2`, where `si` is like error bar
  * Can make wij = Cov[yi,yj]
  * Generalized least squares assumes Cov[e|X] = W
    * Cov[b|X] = inv(X^T inv(W) X)
    * Allows off-diagonal terms

Errors-in-variables accounts for measurement error in x
  * `x = x' + n --> bhat = Cov[x,y]/Var[x] = b sx'^2/(sx'^2 + sn^2) = b /
    (1+sn^2/sx'^2)`
  * Deming reg assumes known constant ratio of y noise to x noise se^2/sn^2

### Multicollinearity

An independent variable can be predicted from a linear combination of the others

Still get good predictions, but poor estimates for individual effects

Red flags:
  * Big changes in parameter estimates when variable is added/deleted
  * Big changes in parameter estimates when data is perturbed
  * Big changes in parameter estimates across cross-validation sets
  * Previously-significant parameters (from an F-test) are now insignificant
  * Previously-significant parameters (from individual simple linear reg.) are
    now insignificant
  * High VIF = 1/tolerance with tolerance = 1 - Ri^2, where Ri^2 is reg. of your
    variable on all others
  * High condition number = sqrt(max / min eigenvalue) for design matrix
    * Helps highlight which variables are correlated
  * High correlation between 2 variables
    * Only catches 2-var collinearity, not higher order linear combinations

Effects:
  * High standard errors of parameters, leading to lower statistical power
  * Wacky parameters cause poor generalization to out-of-sample data
  * Terrible predictions if new data has different multicollinearity pattern

Remedies:
  * Fix overspecified dummy variables (fall, winter, spring, summer, intercept)
  * Fix synthetic multicollinearity by mean-centering data. E.g., x and x^2
  * Use cross-validation to create many models, then report each one
  * Do nothing bc predictions are still unbiased and accurate
  * Drop a variable. This loses information and causes a bias for any remaining
    correlated variables, however.
  * Get more data
  * Standardize independent variables
  * Ridge regression
  * Principal component regression

Special methods below (regularization, logistic, Poisson) require numerical
optimization of MLE or least squares to estimate parameters

Note that generalized linear regression has link(E[yi|xi]) = xi b. Don't simply
regress link(yi) onto x! Link is applied to expectation, not raw data, and needs
special MLE to fit.

### LASSO and ridge regression

Not scale-invariant! Be sure to standardize independent variables 

Does not regularize intercept term!

Find hyperparameters with cross-validation or AIC/BIC

LASSO = least absolute shrinkage and selection operator
  * Better than stepwise selection bc that method increases prediction error if
    there's no small set of indep. variables with strong relationship to target
    * Min. sum((yi-a-Xb)^2) / n + lambda norm0(b), or force norm0(b) <= cutoff
  * Minimize sum((yi-a-Xb)^2) / n + lambda norm1(b), or force norm1(b) <= cutoff

Ridge
  * Min. sum((yi-a-Xb)^2) / n + lambda norm2(b)^2, or force norm2(b) <= cutoff
  * Leads to `b_hat = inv(X^T X + lamdba I) X^T y`, where lambda I improves 
    condition number

Elastic net
  * Minimize sum((yi-a-Xb)^2) / n + lambda1 norm1(b) + lambda2 norm2(b)^2
  * Selects strongly correlated subsets and improves overall prediction
    accuracy. LASSO only selects 1 variable per correlated subgroup
  * Works well if n < m, when LASSO can only select n variables

For orthonormal independent variables
  * LASSO translates all parameters towards zero by factor n lambda, setting to
    zero if needed
  * Ridge shrinks all parameters by uniform 1/(1 + n lambda)
  * Best subset only keep parameters with |b| >= sqrt(n lambda)

Geometrical picture
  * LASSO has hypercube in diamond formation around origin. Constant-SSE surface
    is likely to have 1st intersection at corner
  * Ridge has hypersphere around origin. Constant-SSE surface can intersect
    anywhere with equal likelihood

Bayesian interpretation
  * LASSO assumes parameters have Laplace prior
  * Ridge assumes parameters have Normal prior

### Logistic regression

Log-odds is linear combination of independent variables
  * `ln(p/(1-p)) = b0 + b1 x`
  * Link function is logit -- `E[yi|xi] = pi = 1/(1 + exp(-(b0 + b1 x)))` -->
    `logit(E[yi|xi]) = ln(pi/(1-pi)) = xi b`
    * mu = -b0/b1 is crossover point where p = 0.5
  * Logit link assumes logistic errors, probit link assumes std Normal errors
    * Probit was historically preferred until 1960s

Linear increases in an independent variable multiplicitavely scales odds
  * Odds ratio increases by factor exp(b1) for each unit increase in x1

Likelihood = product(pi^yi (1-pi)^(1-yi))
  * Assumes yi ~ Bernoulli(pi)
  * Define loss = negative log likelihood and find that we're minimizing
    cross-entropy between the predicted and actual distributions
  * Logistic regression is only case where MLE is max entropy bc of exp. family

Can become a classifier if a cutoff probability is specified
  * Vary cutoff to create receiver-operator curve

Multiple (m) categories can be captures with m-1 unique regressions
  * First category has probability p0(x) = 1 - sum(pi(x))
  * Others have pi(x) = exp(x bi) / (1 + sum(exp(x bj)))

No analytic optimum -- use Newton method for MLE, MCMC for Bayesian estimation w
prior, variational Bayes.
  * Luckily, derivative is simply d(log(L))/dbi = sum((y-pj)xji)

Fit testing done via deviance, which is chi-sq dist. when we have much data
  * D = ln(L^2 / Lnull^2) = 2(ln(L) - ln(Lnull))
  * Compare SSE random permuted regression - SSE dummy (always guess ymean)
  * p-value has interpretation of proportion of random datasets with better fit
  * D = -2 ln(L / Ls), where Ls is perfect (saturated) model's likelihood
    (usually estimated as 1)

Parameter testing
  * Likelihood ratio test -- stepwise include new variable and check for
    likelihood ratio significance with chi-sq.
  * Wald test -- Wi = bi^2/stdvar(bi) is approx. chi-sq.

Can correct for oversampling rare case with `b0' = b0 + log(p/(1-p)) +
log(p'/(1-p'))` where p is true prevalence and p' is sample prevalence

### Poisson regression

Models count data and contingency tables. Also called log-linear model

Logarithm of E[Y|X] is linear in parameters, or E[Y|X] = exp(Xb)
  * Link function is log -- `E[yi|xi] = lambda_i = exp(xi b)` --> `ln(E[yi|xi])
    = xi b`
  * But don't simply take logarithm of yi and perform linear regression! Ignores
    Poisson discreteness. Also has issues with zero-counts

Negative binomial regression is similar, but doesn't require variance = mean

Likelihood = product(lambda^y exp(-lambda) / y!), where lambda = exp(Xb)
  * Log likelihood = sum(yi xi b - exp(xi b))

## Time series on Kaggle

Autocorrelation plot shows correlations at lags

Partial autocorrelation plot shows regression of current on lag

`sm.tsa.seasonal_decompose` splits signal into trend, seasonal, and residual
  * Residual should be stationary 

Augmented Dickey-Fuller test sees if time series is random walk

Models 
  * Autoregression with lag -- Yt = mu + b Y(t-1) + et
    * b = 1 is random walk. b = 0 is white noise. -1 < b < +1 is stationary. b =
      -c e is mean reversion. b = +c e is momentum.
    * If adding Y(t-k), include all further times too
  * Moving average with lag -- Yt = mu + et + b e(t-1)
  * ARMA combines AR + MA -- Yt = mu + b1 Y(t-1) + et + b2 e(t-1)
  * ARIMA handles nonstationary time series -- dYt = b1 dY(t-1) + et + b2 e(t-1)
  * VAR (vector autoreg.) handles many time series
  * State space specifies covariance and noise structures
  * SARIMA handles seasonal nonstationary time series
  * Unobserved component handles trend + seasonality + cycles + predictors
  * Dynamic factor handles multiple VAR for many targets

