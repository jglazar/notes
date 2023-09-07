# Time Series Analysis by Shumway and Stoffer

## Introduction 

Time series violate iid assumptions

Moving averages and autocorrelation are common smoothing models

Autocovariance measures linear dependence on previous data
  * Pure white noise has 0 autocorrelation for time i != time j, Var[noise] else
  * Smoothing operations introduce decreasing covariance with separation
  * Cov of linear combos sum(ai Xi) and sum(bj Yj) is sumpairs(ai bj Cov[Xi,Yj])
  * Normalize to autocorrelation by dividing Cov[s,t] by sqrt(Cov[s,s] * Cov[t,t])

Strict stationarity requires joint CDF at time t is same as time t+h for any h
  * Implies that autocorrelation only depends on lag, not absolute times
    * Therefore, autocorr = autocov(h,0) / autocov(0,0)
  * Weak stationarity only requires constant mean and autocorrelation only
    depends on lag
  * Weak implies strong only if distribution is Gaussian (like independence)

Random walk isn't stationary bc ACov[s,t] = min(s,t) s^2 depends on time

Two time series are jointly stationary if they're each stationary and
cross-covariance only depends on lag
  * CCov[X(t+h),Yt] = E[(X(t+h) - mux(t+h))(Yt - muyt)]
  * If yt = a x(t-h) + wt, then CCov[yt,xt] = CCov[a x(t-h) + wt, xt] = a
    ACov[x(t-h),xt]

Gaussian process has joint Normal at all times, where variables are Xt
  * Marginal Normal isn't enough -- if X and Z iid Normal, set Y = Z if XZ > 0
    and Y = −Z if XZ ≤ 0. Y|X,Z is Normal but X,Y,Z not joint Normal

Estimating means and autocov at each Xt isn't possible with one time series
  * Use stationarity property -- mut = mu = 1/n sum(xi), autocovt = autocov =
    1/n sum((x(t+h) - mu)(xt - mu))

Autocorrelation = ACov[h,0] / ACov[0,0] are Normal(0, 1/sqrt(n)) if at least one
of the processes (in CCov) is Gaussian white noise
  * These are typically shown as dashed lines +/- 2/sqrt(n) for 95% interval.
    Only applies if white noise though!

Prewhitening removes trends first, leaving (hopefully) just the noise

Generalizations are straightforward to vector time series (10 stocks, e.g.) and
multidimensional time series (ground temperatures over time, e.g.)
  * Vector time series has CCov matrix at lag h, estimated by 1/n sum((xi(t+h) -
    mui)(xjt - muj))
    * For zero mean, same as X X^T but first X has values shifted by h

### Exercises

Use MGF to get expectation value of yt = exp(xt) where Xt ~ Normal with mean mux
and ACov C(h). ACov of yt can use E[xt yt] - mux muy

## EDA

Can perform linear regression as normal. Model is now yt = B0 + sum(Bi xit) +
wt. Assume wt are iid Gaussians
  * Can include lagged variables if desired
  * Can include time as variable
  * Should check model assumptions of uncorrelated Gaussian residuals

Stationarity is required when estimating ACorr
  * De-trend data first
  * Can de-trend generic a cos(f t + p) = b cos(ft) + c sin(f t) with trig iden
  * Differencing works if xt = trend + stationary = ut + zt and trend = drift +
    autoreg + noise = dt + u(t-1) + wt --> xt - x(t-1) = d + wt + zt - z(t-1)
    which is stationary
  * Differencing requires no parameter fitting, but doesn't get underlying zt
  * First-order differencing removes linear trend, 2nd-order kills quadratic...
    * Order-d difference is (1-B)^d, where B is linear backshift operator

Good practice to use smooth method like local linear reg or splines to check
linearity of response vs. variable scatterplots at different lags
  * CCorr may not pick up nonlinear trends
  * Can use piecewise regression to emulate nonlinearity/kinks
    * Set up dummy variable for condition (D = (Xk < 0), e.g.) and include it
      individually and multiplied by each other variable

## Autoregression

Autoregression has xt = sum(Bi xi) + wt. Requires stationary xt and white noise
  * AR(1) model can collect terms to get xt = B^k x(t-k) + sum(B^i w(t-i))
    * Thus, mean = 0 (of course), ACov(h,0) = s^2 / (1-B^2) B^h, ACorr = B^h
    * Require |B| < 1. B = 1 gives random walk, which isn't stationary. |B| > 1
      gives stationary but future-dependent process
    * Can transform explosive (|B|>1) into causal. E.g., xt = 2x(t-1) + wt -->
      yt = 1/2 y(t-1) + vt, where Var[wt] = 1 and Var[vt] = 1/4
  * In general, Acorr is sum(Bi^h fi(h)), where fi(h) is some polynomial

Moving average has xt = sum(Bi wi) + wt
  * MA(1) model has ACov = (1+B^2)s^2 if h=0, B s^2 if h=1, 0 else and ACorr =
    B/(1+B^2) if h=1, 0 else. Only correlated with lag-1!
    * Cannot distinguish (s^2, B) and (s^2 B, 1/B). Invertible MA models on xt are
      AR models on wt with negated coefficient, requiring |B| < 1
  * In general, ACorr is zero beyond max lag

ARMA models have parameter redundancy if xt = wt, possible future dependence if
AR param is > 1, and non-unique MA models
  * Order can be reduced if parameters factorize nicely -- see pg 95, e.g.
  * ACorr is inferred from recurrence relation and parameterized polynomials

Partial ACorr removes dependencies on variables between xt and x(t-h)
  * Consider X,Y,Z. Regress X on Z and Y on Z. PCorr = Corr[X',Y']
    * Use X' = X - Xpred and Y' = Y - Ypred, where predictions are lin reg est
  * For joint Normal, PCorr[X,Y|Z] = Corr[X,Y|Z]

ACorr = 0 for MA after appropriate lag. PACorr = 0 for AR after appropriate lag

Forecasting -- best linear predictor needs only 2nd-order moments and is MSE
predictor for Gaussian processes
  * Forecasting stationary process gives Normal(mu, s^2) at long times
  * Forecasting trending process gives Normal(mu t, t s^2) at long times --
    increasing prediction error!

Estimation uses method of moments for AR(p) models Xt = sum(xi Bi) + wt
  * Collect symmetric matrices V = ACov[i-j,0] and R = ACorr[i-j,0]. Collect
    vector C = ACorr[i,0]
  * We know RB = C for AR process. Invert R or use Durbin-Levinson to get B
  * Noise variance estimate s^2 = ACov[0,0] * (1 - C^T inv(R) C)
  * Covariance matrix of B = 1/n s^2 / ACov[0,0] inv(R)
  * These Yule-Walker estimations are nearly identical to OLS for AR models

Estimation in general uses specialized techniques like Yule-Walker or MLE. These
generally produce similar results to OLS

Bootstrapping is good for robust uncertainty bounds on parameter estimates
  * Xt = Xt' + It = mu + B(X(t-1)-mu) + It, where It is innovation (difference)
  * Fit mu and B via OLS (or other way), then sample innovations w replacement
  * Use innovations to build out new dataset. Fit params and repeat
  * Useful when errors aren't Gaussian but Laplacian

Model building
  * Transform or difference the data to get stationary process
    * Growth rate = diff(log(yt)) is often useful
    * Higher order differencing removes higher order polynomial trends --
      expand out (1-B)^d where B is backdiff operator and d is order
  * Plot ACorr and PACorr to get feel for model order
  * Many models may be valid. They can be equivalent (e.g., AR(1) and MA(2) with
    special parameters)
    * Beware of overfitting (order is too high). Yields high variance param ests
  * Standardized innovations (Xt - Xt')/sqrt(Var[pred]) should follow iid
    N(0,1). Check ACorr and PACorr to ensure no correlations
    * Correlated errors require weighted least squares with ACov matrix.
      Transform all variables with premultiplication by V^(-1/2)

Process for correlated residuals
  1. Run OLS of yt on zt1, .. ., ztr. Calculate residuals
  2. Identify ARMA model for residuals 
  3. Construct weight matrix from ARMA model ACorr 
  4. Inspect residuals for whiteness, and adjust the model if necessary

SARIMA captures seasonality by relying on x(t-12) and w(t-12), e.g.

## State space models

Linear Gaussian model has states xt = B x(t-1) + C ut + wt and obs. yt = At xt +
D ut + vt, where ut are fixed inputs (may be removed from model)
  * At is measurement matrix and may change with time
    * e.g. At = I if data exists and is unfiltered, At = 0 if data is missing
  * If xt is AR(1), yt would be ARMA(1,1) when At = I

Kalman predicts xt using y(1..s). Smooth: t < s, filter: t = s, forecast: t > s

MLE assumes Normal innovations and works via recursion and Newton-Raphson
  * Simplest way is to maximize likelihood from Kalman function w BFGS routine
  * Innovation = It = yt - At xt' - D ut, where xt' is prediction given x(1..t)
  * Innovations are Normal vectors with mean 0 and Cov = At Pt' At^T + R, where
    Pt' is Cov of (xt - x(t-1)) and R is Cov of (yt - y(t-1))
  * Another method is expectation-maximization. Tends to converge slowly
    1. Initialize mu0, C0, B, Q, R vectors/matrices and compute incomplete data
       log-likelihood. Now iterate:
    2. Calculate xt', Pt', Pt'' predictions given current data
    3. Maximize likelihood to get mu0, C0, B, Q, R and compute log-likelihood

Structured models can account for seasonality and trends
  * E.g., yt = Tt + St + vt, Tt = B1 T(t-1) + wt1, St = -S(t-1) - S(t-2) -
    S(t-3) + wt2 --> Observation is yt, state is Tt, St, S(t-1), S(t-2). Set up
    transition + measurement matrices and estimate r, q1, q2

Bootstrapping can be used to estimate confidence intervals, even though
theoretical ones for the Gaussian case exist
  * As above, reparameterize in terms of innovations, then randomly sample
    observed innovations and resimulate, then refit, and repeat
  * Bootstrap errors will be ~50% bigger than Normal std errors

Stochastic regression allows slope to change over time
  * yt = a + Bt zt + vt, (Bt - b) = B2(Bt - b) + wt
  * State space notation: xt=Bt, B2=B2, ut=1, Υ=(1−B2)b, Q=sw^2, At=zt, G=a,
    R=sv^2, S=0. 
  * If B2 = 0, then B1 = muB1 + wt. If sw^2 ~ 0, then B1 = muB1 is deterministic

HMM can capture serial correlation and marginal distributions together
  * Acts like Gaussian mixture model but w serial correlation (time structure)
  * Works great for count data. More interpretable than time series regression
  * 2 state Poisson -- E[yt] = p1 l1 + p2 l2, Var[yt] = E[Var[yt|xt]] +
    Var[E[yt|xt]] = E[yt] + p1 p2 (l2 - l1)^2, where yt is observation and xt is
    state. Also has exponentially decaying autocorrelation
  * Can get confidence intervals with parametric bootstrap

Baum-Welch is EM: assume transition/emission parameters and estimate state
probs, then use state probs and observations to estimate MLE (weighted averages)
for params

Switching regression is HMM where OLS parameters change with state
  * Can also have autoregression
