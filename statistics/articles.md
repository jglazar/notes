# Articles

## Wikipedia - Covariance

Note that Cov takes 2 variables and Var takes only 1

Cov[X,Y] = E[(X - E[X])(Y - E[Y])] = E[XY] - E[X]E[Y]
  * Latter form can have catastrophic cancellation
  * Discrete form, pi equal: 1/n^2 sumi(sumj(1/2 (xi - xj) (yi - yj)))

Rules
  * Cov[X,a] = 0
  * Cov[X,X] = Var[X]
  * Cov[X,Y] = Cov[Y,X]
  * Cov[aX,bY] = ab Cov[X,Y]
  * Cov[X+a,Y+b] = Cov[X,Y]
  * Cov[aX+bY,cW+dV] = ac Cov[X,W] + ad Cov[X,V] + bc Cov[Y,W] + bd Cov[Y,V]
    * Cov is bilinear (distributes)!
  * Var[a^T x] = Var[sum(ai Xi)] = sumi(sumj(ai aj Cov[Xi,Xj]))
  * Hoeffding -- Cov[X,Y] = integral over x,y of (Fxy - Fx Fy) where F is cdf

Classic counterexample to independence = 0 cov is Y = X^2
  * Joint Normals actually do have independence = 0 cov

Cov is an inner product bc it is bilinear, symmetric, and positive
semi-definite. Thus, |Cov[X,Y]| <= sqrt(Var[X] Var[Y]) is Cauchy-Schwartz ineq.
  * Let Z = X - Cov[X,Y]/Var[Y] Y (like Gram-Schmidt orthog.), then 0 <= Var[Z]
    = Cov[Z,Z] = Var[X] - Cov[X,Y]^2 / Var[Y]

Rules for vector X
  * Cov[X,X] = E[(X-E[X])(X-E[X])^T] = E[X X^T] - E[X]E[X]^T
  * Cov[AX,AX] = E[(AX)(AX)^T]- E[AX] E[X^T A^T] = A Cov[X,X] A^T
  * Cov[X,Y] = Cov[Y,X]^T

## Matrix calculus

https://tminka.github.io/papers/matrix/minka-matrix.pdf

Derivatives are elementwise, but can be cleverly computed using matrices

S (scalar), V (vector), M (matrix) -- dS/dS, dV/dS, dM/dS, dS/dV, dV/dV, dS/dM
  * Partials w.r.t. numerator (denom) take numerator's (demom transpose's) shape
  * Thus, dV/dS is column vector and dS/dV is row vector

Define y(x + dx) = y(x) + A dx + O(small). Then A is Jacobian and A^T is grad(y)

Rules
  * dA = 0
  * d(aX) = a dX
  * d(X+Y) = dX + dY
  * d(tr(X)) = tr(dX)
  * d(XY) = (dX)Y + X(dY)
  * d(X x Y) = (dX) x Y + X x (dY), where x is Kronecker/Hadamard product
  * d(inv(X)) = -inv(X) dX inv(x)
    * Derived from 0 = dI = d(inv(X) X)
  * d|X| = |X| tr(inv(X) dX)
  * d log|X| = tr(inv(X) dX)
  * d(X') = (dX)' where ' rearranges elements (like transpose, vec, vec-trans)

Make into canonical form -- dS = S dS, dV = V dS, dM = M dS, dS = V dV, dV = M
dV, dS = tr(M dM)

Trace is typically dropped and 1/dX should cancel to leave answer

Recall that trace is invariant under cyclic permutation. 
  * Trace is basis-indep: A --> B A inv(B) yields tr(A) = tr(inv(B) B A) = tr(A)

Easier than Lagrange multiplier for symmetry constraint is baked-in:
  * dS(M) = tr(MdM) --> dS(M)/dM = (M + M^T) - diag(M)
  * If diagonal-only: dS(M) = tr(MdM) --> dS(M)/dM = diag(M)
    * If X is diagonal then so is dX.

E.g., PCA -- with E[X]=0, minimize E[(X-aV)^T (X-aV)] w.r.t. V with a = V^T X
  * E[...] = E[X^T X - a V^T X - X^T a V + a^2 V^T V] = Cov[X,X] - 2 a X^T V +
    a^2 V^T V --> maximize V^T C V - lambda(V^T V - 1) 
  * Taking derivative yields 2CV - 2 lambda V = 0, which occurs if V is eigenvec
  * This is maximized when v points in direction of eigenvector w largest val

E.g., Consider X = inv(A) U and ui ~ fi(wi). Observe X and W. Infer A to find U
  * p(U|W) = prod(fi(ui|wi)) and p(X|A,W) = |A| prod(fi(ui|wi))
  * log p(X|A,W) = log |A| + sum(log fi(ui|wi))
  * gradA log p(X|A,W) = inv(A)^T + (gradui fi(ui|wi) / fi(ui|wi)) X^T
    * I guess the intuition is d/dA = d/dU x where x is constant?
  * gradwi log p(X|A,W) = gradwi fi(ui|wi) / fi(ui|wi)
   
E.g., Infer cov matrix of zero-mean joint Normal pdf by max log-likelihood
  * log-lik = sum of -d/2 log(2pi) - 1/2 log|C| - 1/2 xi^T inv(C) xi
  * dS/dC gives M = sum of -1/2 inv(C) + 1/2 inv(C) xi xi^T inv(C)
    * Then apply symmetrization trick and set to zero. Yields C = sum(xi xi^T)/n
  * Answer is same as estimating each covariance. Note MLE uses n, not n-1

Kronecker product, vec, and vec-transpose allow for expression of multilinear
models that account for separate linear effects

Hadamard product is elementwise matrix mult.
  * If Z = X x Y, then CovZ = CovA x CovB

Partitioned matrix inversion uses A = Schur(D) = A - B inv(D) C
  * For block matrix M = [[A,B],[C,D]], inverse of Schur(D) = A - B inv(D) C
    gives top-left element in inv(M)
    * Can be useful for solving systems of linear equations
  * For multivariate Normal, Cov[X|Y] = Schur(D) where C = B^T (by symmetry) and
    E[X|Y] = E[X] + B inv(D) (Y - E[Y])
  * Sample covariance has Wishart distribution

Polar decomposition of A = PU, where P is positive-def and U is unitary (orthog)
  * This finds the closest unitary matrix to A, minimizing (A - U)
  * Same as taking complex decomposition of number, with magnitude and angle
  * Find most likely rotation matrix of identity matrix rotated plus white noise
    * Minimize tr((A-U)^T (A-U)) = tr(A^T A) - 2 tr(A^T U)
    * Maximize tr(A^T U) = tr(U A^T)
    * Find SVD of A^T = V S W^T --> tr(U A^T) = tr(W^T U V S) = tr(X S)
    * Now maximize tr(XS) = sum(Xii Sii) which is max when Xii = 1 and X = I.
      Thus, U = W V^T
  * Can change starting point to known B... just take SVD of B A^T

Hessian matrices are dS/(dV dV^T)
  * Take derivative of derivative. Note that d(dX) = 0
  * S(V + dV) = S(V) + A^T dVA + 1/2 dV^T H dV
  * Canonical forms -- d^2S = h(dS)^2, d^2S = dV^T H dV, d^2S = d vec(M^T) H d
    vec(M)
  * H must be symmetric

## Kalman filters -- Berkeley EECS 126

https://inst.eecs.berkeley.edu/~ee126/sp18/

Assume Xn = aX(n-1) + Vn and Yn = cXn + Wn. Observe Y, want E(Xn | Y1,2,...,n)
  * Assume for simplicity |a| < 1 (could introduce control term o/w) and c = 1
    (could rescale Y and W o/w)

Lemma: E(X|Y,Z) = E(X|Y) + E(X|Z - E(Z|Y)) 
  * E(Xn|Y1,...,Yn) = E(Xn-1|Y1,...,Yn-1) + E[Xn|Yn - E[Y|Y1,...,Yn-1]]
  * Conditional in second term is called innovation = In
  * Thus, Xn|n = Xn|n-1 + kn In and In = Yn - E[Xn + Wn | Y1,...,Yn-1] = Yn -
    Xn|n-1. Just determine kn = Kalman gain!

Geometric picture comes from constraints -- see article
  * Xn|n-1 is orthogonal to (Xn - Xn|n-1)
  * Innovation vector is orthogonal to original estimate E[Y|...] --> In is
    orthogonal to Xn|n-1
  * Yn = In + Xn|n-1 is now fixed
  * Project Xn onto In to get kn In. Project Xn - Xn|n-1 onto Yn - Xn|n-1 = Xn|n
  * Finally, use similar triangles to find kn = sn|n-1^2 / (sn|n-1^2 + sw^2)
  * Further, sn|n-1^2 = a^2 sn-1|n-1^2 + sv^2
  * Pythagorean theorem gives sn|n^2 = sn|n-1^2 (1 - kn)

Vector equations are simple generalizations of these equations

## Linear regression intuition

Mainly from StackExchange answers

X^T X maps from alpha to beta
  * Consider prediction as vector in column space given by sum(Bi xi). These
    coordinates are in a non-orthogonal basis (cols of X)
  * Consider direct orthogonal projection onto each xi -- X^T v
  * So XB gives skew-coodinates, then X^T projects onto each axis to get alphas
  * a = X^T X B --> B = inv(X^T X) a
  * E.g., B = inv(X^T X) X^T y, where X^T y is orthogonal projection of y onto
    each xi

For skew vs. orthogonal coordinates: P = SC , where P is n x p perpendicular
axis coords, S is n x p skew coords, and C is p x p symmetric matrix of cosines
  * SB = a has S convert from skew-coords (B) to orthogonal coords (a). inv(S)a
    = B has S convert from orthogonal coords (a) to skew-coords (B)

R^2 = 1/n y^T X B = 1/n sum(Corr[y,Xi] Bi) for centered + normalized y and X
  * R^2 = ESS/TSS = yhat^T yhat / y^T y = 1/n (yH)^T Hy = 1/n Y X^T B
    * Hat matrix is symmetric and idempotent: H^T H = H H = H
  * Geometrically, R^2 = yhat^T yhat = B^T C B, which gives diagonal of
    parallelogram as function of sides

Can have significance in X2 simple reg but non-sig in X1, X2 multiple reg
  * Typical case -- X1, X2, y all correlate. yhat is B1 X1 + B2 X2
  * This case -- y falls along X1 and still correlates with X2. Multiple reg
    drops y onto X1 perfectly, leaving B2 = 0
  * Suppressor case -- y and X2 are orthogonal, so simple reg gives B2 = 0. y
    and X1 correlate, then residual has negative corr with X2 leading to B2 < 0
  * Consider 

Great trick -- draw 3D picture with n = 3, p = 2. Set up X1 and X2 skewed
spanning a plane, then draw y and it's projection onto that plane yhat
  * Can consider Gram-Schmidt style regression

## Feature selection

See StackExchange and https://www.stat.cmu.edu/~larry/=stat401/

Stepwise regression is often taught in textbooks, but tends to overfit data and
prevents use of p-values/significance tests/conf intervals

Using p-values in general is bad because it is easy to get significance for
large data

LASSO is most common. Use CV to pick regularizer strength value.

Multicollinearity can be hard to detect if many variables X1 = X2 + X3 + ... 
  * Assume Xi ~ Normal(0, s^2) and set Xa = 1/k (X1 + X2 + X3 + ... + Xk).
    Then Corr[Xi,Xa] = Cov[Xi,1/k(sum)] / sqrt(Var[Xi]Var[Xa]) = 1/k s^2 /
    sqrt(s^2 1/k^2 k s^2) = 1/sqrt(k)
  * Causes singular X^T X -- dependent col is linear sum of indep cols
    * At least one zero-eigenval, causing 0 determinant
    * Near-singular --> det(X^T X) small --> det(inv(X^T X)) = 1/det(X^T X) huge
    * Cov goes from positive definite to semi-definite: v X^T X v can yield zero
      when v is eigenvector with zero eigenvalue

Cov is positive definite when X is full rank:
  * C = 1/n times a sum of xi^T xi, so vCv is a sum of squares which can't be
    negative, indicating positive semi-definiteness 
  * vCv = 0 for v orthogonal to all xi. C is pos-definite if X is full-rank

Variance inflation factor = ratio of variance from simple reg vs. multiple reg
  * Happens to be same as 1/(1-R^2), with R^2 from regressing X1 on all other
    Xi. This pops out of Schur complement representation of Var[B1]
  * Set up block matrix of X^T X = [[X1/1, X1/-1],[X-1/1, Xwith-1/-1]]
  * Schur complement of 1/1 element is Schur(D) = A - B inv(D) C. The inverse of
    this is the 1/1 element in inv(X^T X)
  * Finally, Var[B1] = s^2 * (x1^T x1 - inverse 1/1 element). Inv element = a
    C-1/-1 a where a = X-1^T x1 is orthogonal projection of x1 onto each X-1.
  * This simplifies to s^2 / SSR = s^2 / ((n-1) Var[X1] [1 - R^2])
  * Typical cutoff is 1/(1-R^2) >= 10 

## Kalman filter

https://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/

Notation -- next step is k. Prime (') decrements to step k-1, our current step

At time k-1, we have state vector xk' and variance Pk'. Then apply kinematics to
get next state vector xk = Fk xk' and next variance Pk = Fk Pk' Fk^T

External controls are modeled with interaction matrix Bk and inputs uk. This
gives xk = Fk xk' + Bk uk

Extra noise adds variance Qk, yielding total covariance Pk = Fk Pk' Fk^T + Qk

Now we have a full state prediction with uncertainty. These are fed through a
measurement matrix Hk to get observations. We also have newly measured values zk
with uncertainty Rk

When multiplying Gaussians:
  * Mean = mu0 + K (mu1 - mu0)
  * Variance = C0 - K C0
  * Kalman gain = K = C0 inv(C0 + C1)

Gaussian 1 is prediction with mean = Hk xk and variance = Hk Pk Hk^T. Gaussian 2
is observation with mean = zk and variance = Rk. Final answer after
simplification is Gaussian with mean = xk + K1 (zk - Hk xk) and variance = Pk -
K' Hk Pk, where K1 = Pk Hk^T inv(Hk Pk Hk^T + Rk), xk and Pk as above

So we use xk' and Pk' along with Fk, Bk, uk, and Qk to predict xk and Pk. Then
update prediction with measurement zk and Hk and Rk to get final answer

Simple 1D case:
  * xk = xk' + (sp^2 + sq^2) / (sp^2 + sq^2 + sr^2) (zk - xk') -- conservatively
    weighted update
  * pk = pk' - (sp^2 + sq^2) / (sp^2 + sq^2 + sr^2) (sp^2 + sq^2) -- lowered
    variance due to measured info

Notes from online Jupyter notebook course:
  * Need good estimates for variances, o/w too much reliance on data (noisy) or
    matrix model (biased, ignores shifts in data)
  * Kalman is type of g-h filter: xpred = xprev + v dt, r = z - xpred, v += h
    r/dt, xpred += g r -- g gives position response, h gives velocity response
  * Filters often "ring" (oscillate) before converging on nice smooth line
  * Discrete filters predict by convolving state pdf with transition kernel
    (motion noise), then update w likelihood fct. Called "predictor-corrector".
    This is just repeated Bayes rule
  * Univariate Kalman filter (no velocity) can't account for changes in
    velocity (always under/overshoots) unless control uk = vk

## Regime modeling -- Two Sigma

https://www.twosigma.com/articles/a-machine-learning-approach-to-regime-modeling/

Fit 4-dist 17-dim Gaussian mixture model to 17 pre-computed factors
  * Use CV and evaluate log-likelihood to tune number of dists

Interpretations and frequencies of each state
  1. Crisis, 17%: high volatility, negative equity and credit returns, worse
     emerging markets performance, positive interest/low-risk returns, great
     trend-following and large-cap returns, highest factor-factor correlation
  2. Steady-state, 47%: equity/credit/style factors perform well, local equity
     and emerging markets returns are flat
  3. Inflation, 20%: US local inflation has huge returns, global equity and
     interest rates underperform, high foreign currency
  4. Danger, 16%: global equity does well but high volatility, higher overall
     volatility, style factors except momentum perform well 

## Kaggle competition winners

### Optiver realized volatility prediction

Most people reverse engineered the time ID to get real prices

1st place
  * New features with nearest neighbor aggregation
  * Blend LightGBM, MLP, 1D-CNN
    * CNN: 584 -dense- 1024 -reshape- 128x8 -conv- 384x8 -avgpool- 384x4 -conv-
      384x4 -maxpool- 384x2 -reshape- 768 -dense- 1
  * ❌ Didn't work: domain-specific features, TabNet, training on residual,
    dimensional reduction

4th place
  * Predict target / realized volatility of 0-600 seconds
  * Predict average volatility of all stocks in given time

7th place
  * LGBM + FFNN ensemble
  * Get mean, slope, and error of linear regression on ftrs in 100-sec periods
  * BorutaSHAP with XGBRegressor for feature selection. Kept ~60
    * Domain-specific ftrs were unimportant

18th place
  * If CV improves with new feature, try on leaderboard. Keep if LB score up
  * Use RNN to extract features for each stock at each time
    * RNN is too slow
    * More practically, use handmade features instead of RNN
  * Use transformer to capture inter-stock relationships
    * Blend with TabNet and NN with different feature sets
  * Use nearest neighbors to find top-N closest times, then average ftrs for
    each stock from neighbors as new ftrs

25th place
  * Tried defining alternate weighted average price fct, but no improvement
    * WAP minimizes function
  * Alternate WAP fct evaluated at current price gives liquidity 
  * Trade volume / liquidity has correlation of 0.88 with log-volatility
  * LGBM selects features
  * Ensemble 2 NN on 4 folds. One takes all 190 ftrs, other takes 40 best ftrs
  * Multi-input multi-output rather than individual models for each stock

### Two sigma financial modeling challenge

7th place
  * XGB was efficient and fast
  * Reverse engineering prices via rolling stddev or cross-sectional normaliz.
    didn't work
  * Features: 1st and 2nd order differences 
  * Switch between trending and mean-reversion depending on return dispersion
  * Auxiliary strategy bets on inflection points from market extremes (like
    getting cheap options)

12th place
  * Blend 7 models: Ridge A,B,C with selected features, 222 trees, XGB, Ridge
    online rolling fit trained every 100 timesteps, Variance by timestep

### JPX Tokyo stock exchange predictoin

4th place
  * Rank `return_1day` descending, and if `expecteddividend > 0`, rank it lowest
  * `return_1day = ftrs['adjustedclose'].pct_change(1)`

7th place
  * Group stocks by sector and train LGBM on each sector
    * Optuna tuned `num_leaves, max_depth, learning_rate, n_estimators`
  * Rank by predicted change ratio

8th place
  * Create ftrs: open-close returns, close-close returns, amplitude, volatility,
    moving avgs
    * Set sensible defaults
  * Walk-forward CV for LGBM

### Jane Street market prediction

1st place
  * Blend Autoencoder+MLP and XGBoost
    * Bottleneck + MLP + Keras Tuner 8601c5. Adjust CV to prevent leakage
    * Autoencoder+MLP alone still earns 1st place
  * 5-fold 31-gap purged time-series CV. Remove first 85 days due to different
    feature variance, forward-fill missing vals, use mean of abs vals of
    targets as sample weights
  * Autoencoder makes new ftrs, which are added to originals for downstream MLP
  * Add target info to autoencoder to create more relevant ftrs, add Gaussian
    noise layer before encoder to prevent overfitting, use swish activation
    instead of ReLU to prevent dead neurons and smooth gradient
  * Batch normalization and dropout for MLP, early stopping with BCE loss
  * Average over 3 random seeds to reduce variance
  * Hyperopt for hyperparamter tuning

3rd place
  * Ensemble of 15 49-layer MLPs
  * Input batchnorm + log ftrs extension - 1x - 3 dense layers w 100 units,
    batchnorm, dropout 0.35, mish activation - 23x - 2 dense layers same as
    above - skip connection sbt blocks 0 and 1-23 - output dense layer with 5
    resps, sigmoid activation
  * Threshold at 0.5
  * Remove first 85 days, include rows with zero weight, NaN fill with median
    conditioned on f0
  * Train: batch 30k, Adam with lr=1e-3, 200 epochs, loss mixes BCE and utility
    * Train on 85-300, validate on 350-500. Rerun with 8 rng seeds
  * Inference by converting to tf-lite (greatly improves speed)

10th place
  * Geometric Brownian motion w drift fitting gives returns of each time horizon
    * Uses returns to predict drift
  * Mixture density network with neg-log-lik loss fct estimates same thing
    * Predict lower-triangular sqrt of cov matrix and mean vector. Very finicky
    * Uses features and drift to predict returns

23rd place
  * Classification labels from sigmoid(a * returns)
  * Log-transform weights for CV
  * Ensemble 20 MLPs, 5 densenets, 5 resnets on large-weight data; 1 MLP on rest
  * Submit 1 final model with threshold 0.49 and another with 0.51 (bull, bear)

39th place
  * Mean OOF utility scores, basic GroupKFold split with 50 dates as groups
  * Rolling lag features for ftr0, before/after lunch time, slope of ftr64
  * Multi-label output, skip resp4 target, predict mean of all other resps
  * 3-layer MLP with batch normalization and dropout. Optimize using LAMB w
    lookahead. 50 models total (5 folds, 10 seeds each)
  * Bet if 66% of models vote for it. Higher threshold for bigger bets (lowers
    variance). Each model has 1 vote per target
  * ❌ AdaHessian optimizer, TabNet, and knowledge distillation performed worse

44th place
  * 5-fold purged time series CV with 20 gap, early stopping with valid-auc
  * Fill NaN with 0 and FeatureNeutralization(p=0.25), fill NaN with mean,
    denoising autoencoder
  * Ensemble of NN, CNN, and DenseNet. Weights determined by CV

## G-Research crypto forecasting

2nd place
  * LightGBM GBDT with squared loss. No ensembling, regularizatoin,
    augmentation, neutralization. Only tune number of estimators, number of
    leaves, and learning rate
  * CPython and Numba for feature generation (not shared with public)
  * 6-fold walk-forward grouped CV, 40-week groups, gap 1 week, 20 week skips

3rd place
  * 7-fold embargo CV for single LightGMB
  * Only use close, use difference bt change of each currency and change of all
    currencies, ignore times with too few cryptos, forward fill, use log of
    ratio of current value to prior value, use diff bt price and avg crypto

7th place
  * Nx90x14x9 time, minute, asset, ftrs input - Nx90x14x64 MLP - add 2D
    positional embedding - axial transformer encoder - pooling for time series
    Nx14x64 - transformer encoder - MLP - output Nx14

9th place
  * Use Hull moving avg, lag feature with Fibonacci sizes 55,210,340,890,3750
  * 3 LightGBM: one each trained on up, down, neutral markets. Default params

13th place
  * 17 ftrs w lagged and timestamp avgs, target engineering, pred switching
    * EMAs, historical returns, historical vols over various lookbacks
    * Avg above ftrs over timestamps to produce more ftrs
    * Binning to 500-1000 unique values worked well
    * Split target into forward 15 min return and beta of future on past
  * Ensemble LGBM and Keras NN
  * Download and train on additional data from Binance helped a little
  * ❌ Didn't work: classification, hyperparam tuning, PCA features, using all
    14 assets features

14th place
  * Ensemble 2 LGBM: one learning each asset individually with 20 technical
    indicators and 2 time features; one learning all asset data
  * SMA diff, Bollinger bands, RSI, ATR, log returns, upper/lower shadow

23rd place
  * Add features asset return, portfolio return, difference, asset return for
    moving avg. All for past 1,2,3,5,10,15,20,30,40,50,60 min.
  * Ensemble of 12 * 5 LGBM models
  * Add Gaussian noise to all ftrs and target to smooth tree predictions and
    augment dataset

37th place
  * Ensemble of default XGB, low tuned XGB, and 2 LGBMs, each w different seed

### Ubiquant market prediction

1st place
  * Ensemble average of (LGBM x 5 folds) and (TabNet x 5 folds)
    * Custom MLPs were unstable in CV
  * Add avg value at each time for top 100 ftrs after sorting correlation of 300
    features with target
  * Purged group time series CV

2nd place
  * Ensemble 5 LightGBM with early stopping based on CV correlation
  * Add 300+100 ftrs as above and mean/std/1st/5th/9th deciles for each ftr
  * Purged group time series CV k-fold with embargo
  * ❌ Didn't work: Autoencoder MLP, feature neutralization, PCA

3rd place
  * 5 seeds ensemble of 6-layer transformer, maxseqlength = 3500 investments, PCCLoss
  * 10 epochs on training and 3 on supplemental data
  * Original 300 ftrs, random zero on ftr level and random mask on seq level
  * Last 100/200/300 CV
  * ❌ Didn't work: feature clipping, avg ftr groups by time id, ftr selection
    by corr, sample selection/weighting, target norm./clipping, LGB, MLP, 1DCNN

5th place
  * NN with 4 dense layers, Adam optimizer, MSE loss, RMSE and WCorr metrics
    * 300,256,128,32 MLP. Ensemble 20 models, each trained on 20% of data and
      validated on 5%
  * Target log transformation, remove 127 outliers
  * Transform ftrs with QuantileTransformer
  * Custom CV with 20 folds and 10 purged timesteps

7th place
  * Single LGB with hand-tuned params, extratrees=True
  * Custom (secret) feature engineering
    * Basic version with only original 300 ftrs scores outside of medal range
  * Standard TimeSeriesSplit CV

8th place
  * Weighted ensemble of 0.92(1/2 (10 LGBM) + 1/2 (30 NN)) + 0.08(custom model)
  * Split dataset in 2 to save memory
  * Add avg of each ftr per timestep and diff b/t current value and rolling avg
    of hand-selected ftrs
    * Check if ftr correlates with target's sign when significantly different
      from rolling avg
  * Custom model based off rare events of informative ftrs scores poorly
  * CV on last 25% of data. Final submission used entire dataset
  * Form bull/bear model by multiplying/dividing positive/negative preds by 1.4

17th place
  * NN with hidden layers of size 1000 and 512
  * Train for 21 epochs, go through entire train set twice per epoch, L2 with
    128 batch and decaying learning rate for 1st run and L1 + variance with 1000
    batch and small constant learning rate for 2nd run.
  * Average predictions from 11th, 16th, and 21st epochs
  * Remove ftrs using permutation importance
  * Add missing ftr to check if stock is present in previous timestep. Common in
    Chinese market to suspend trading
  * Batch normalize all ftrs except missing ftr
  * Only use stocks after 850th timestep, weight new timesteps higher
  * Scale target using mean and std within each timestep
  * ✅ Tips: blend NN with LightGBM (but beware memory issues), don't run many
    hyperparam experiments (low signal-noise)
