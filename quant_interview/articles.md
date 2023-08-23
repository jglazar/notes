# Articles

## Catalan numbers

Many equivalent forms 
  * `Cn = 1/(n+1) C(2n, n)`
  * `Cn = Product from k=2 to k=n of (n+k)/k`
  * `Cn = 1/(2n+1) C(2n+1, n)`
  * `Cn = C(2n, n) - C(2n, n-1) = C(2n, n) - C(2n, n+1)`
  * Sequence starting from `n = 0` is 1,1,2,5,14,42,132,429...

Satisfies recurrence relation `C0 = 1`, `Cn+1 = Sum from k=0 to k=n of Ck Cn-k`
  * Or, `Cn+1 = 2(2n+1)/(n+2) Cn`

Recurrence relation is most easily seen for diagonal grid paths
  * Set first point hitting x-axis at k = 1, 2, ..., n. Total paths to the
    right is just C(n-k). For the total paths to the left, raise the path on
    stilts (go up at move 1, down at move k), which is C(k) paths. Total is
    sum(Ck Cn-k) from k = 0 to k = n-1

Grows as `Cn ~ 4^n / (sqrt(pi) * n^(3/2))`

The only odd Catalan numbers are where `n = 2^a - 1`

It's the answer to popular problems asking for the number of...
  * Dyck words with `n` As and `n` Bs, where no substring starting from the
    beginning has more Bs than As
  * Valid open/close parentheses strings with `n` pairs of parens
  * Ways to parenthesize `n` factors
  * Non-isomorphic ordered trees
  * Lattice paths from `(0,0)` to `(n,n)` not passing above the diagonal
  * Ways to form `n` triangles from a polygon without intersecting lines
  * Permutations of `1...n` without a 3-unit increasing run 

Typical problem has structure like:
  * Every Dyck word can be written as `XaYb`, where `a` and `b` are Dyck words.
    This has recurrence relation above.

Nice solution from reflection principle, using lattice path interpretation:
  * Easier to see on diagonal grid with only (even, even) or (odd, odd) points
  * Consider paths ending at -2 height. Flip those paths across
    horizontal line at -1. Now those paths end at 0 height with at least one
    point touching horizontal line at -1. Reflection Principle states that those
    paths comprise all the bad paths.
  * Total bad paths = `C(2n, n-1)`

## Bertrand's ballot problem

Given `n` total votes with `a = n(1-p)` for A and `b = np` for B, with `0 < p <=
0.5`, what is the probability B is never ahead of A as the ballots are counted?

Same as Catalan, but with A != B
  * Total ways = `C(n, b)`
  * Bad ways = `C(n, b-1)` by reflection about -1 line
  * Good probability is `(a+1 - b) / (a+1) = (n(1-p)+1 - np) / (n(1-p)+1) =
    (n-2np+1) / (n-np+1)`

If no ties allowed, give A 1 vote then proceed with `n-1`, `a-1`, `b`
  * Good probability is `a/n * (a-b)/a = (a-b)/n = (n(1-p) - np) / n = 1 - 2p`
    * `a/n` is probability of getting first vote as A

## 10 important papers

Optimal execution of portfolio transactions, Almgren and Chriss, 2000
  * Formal algorithm for executing and measuring execution performance
  * Share prices vary by:
    * Exogenous forces -- random market vol independent of our order
    * Endogenous forces -- impact from our order. magnitude is inverse of
      liquidity. can be temporary or normalized (permanent)
  * Algorithm minimizes transaction cost and endogenous volatility risk

Long-run evolution of energy prices, Pindyck, 1999
  * Raw material prices have quadratic trend from 1916 to 1996, with minimum
    around 1920
  * Price is tied to marginal cost of extraction and estimated reserves

Closed-form GARCH option valuation model, Heston and Nandi, 1997
  * Values spot assets with GARCH model for its variance
  * GARCH is a time-series model, which makes sense for both mean and variance

Portfolio selection, Markovitz, 1952
  * Introduced diversification
  * For given expected return, there's an optimal portfolio minimizing risk (and
    vice versa)
  * Want to reduce correlation (diversify) to lower risk

A new interpretation of information rate, Kelly, 1956
  * Introduced the Kelly Criterion for bet sizing to maximize geometric growth

Capital asset prices: a theory of mkt. eq. under cond. of risk, Sharpe, 1964
  * Introduced beta and CAPM to calculate return from risk
  * The only efficient portfolio is the market portfolio, assuming all
    information is known equally and is instantly processed
  * Only reasonable portfolio is mix of market and risk-free asset like T-bills

Incorporating signals into optimal trading, Lehalle, 2017
  * Markov signal for optimal trading of assets with O-U drift process
  * Order book imbalance predicts future price movements and is mean-reverting

Efficient capital markets: a review of theory and empirical work, Fama, 1970
  * Introduces EMH
  * 3 types of efficiency:
    * Weak -- prices contain info from historical prices. technical analysis is
      useless
    * Semi-strong -- prices also contain other public info. fundamental analysis
      is useless. this is most realistic
    * Strong -- prices also contain private info. note: practically impossible. 

Pricing of options and corporate liabilities, Black and Scholes, 1973
  * Introduced Black-Scholes model for options using heat-transfer physics

Does the stock market overreact?, Bondt and Thaler, 1985
  * Statistically significant evidence of non-efficient markets
  * Historical prices aren't correctly priced-in

## Markov Processes

Check out [Random Services](randomservices.org/random/markov/index.html) for a
great course

## Number sequences

Useful for recognizing solutions, then backsolving recurrence relations

### Famous sequences

1. Harmonic numbers -- Hn = 1, 3/2, 11/6, 25/12, 137/60, 49/20
  * Z = sum(Xi), E[Z] = sum(E[Xi]) = sum(1/i) or E[N] = 1/N + E[N-1]
2. Coupon collector -- n * Hn = 1, 3, 11/2, 25/3, 137/12, 147/10
  * Z = sum(Xi), E[Z] = sum(E[Xi]) = sum(((n-i)/n)^-1)
3. Fibonacci numbers -- 1, 1, 2, 3, 5, 8, 13, 21
  * E[N] = E[N-1] + E[N-2]
  * Ratio of Fn and F(n-1) approaches golden ratio = (1 + sqrt(5))/2 ~= 1.61
  * Tribonacci numbers -- 0, 1, 1, 2, 4, 7, 13, 24, 44, 81
4. Catalan numbers -- 1, 1, 2, 5, 14, 42, 132
  * Cn = sum(Ci C(n-1-i)) from i=0 to i=n-1, 2nCn - 2nC(n-1) =
    1/(n+1) 2nCn. Appears after using reflection principle to count paths
  * Partial sums from 0 slot -- 1, 2, 4, 9, 23, 65, 197, 626, 2056
  * Partial sums from 1 slot -- 0, 1, 3, 8, 22, 64, 196, 625
5. Lazy caterer seq. -- 1, 2, 4, 7, 11, 16
  * Max slices of cake with n cuts: Ln = n (new regions, at most) + L(n-1) =
    1 + n(n+1)/2
6. Magic square sums -- 15, 34, 65, 111, 175
  * Square of n^2 numbers s.t. all rows/cols/diags sum to same
    constant. Contains integers from 1 to n^2. 
7. Trees -- 0, 1, 1, 2, 4, 9, 20, 48, 115, 286, 719
  * Arrangements of n-1 nonoverlapping circles, unique functions w parentheses
    and exponentiation ((x^x)(x), e.g.)
  * `f(n): return n if n <= 1 else sum(sum(d*f(d) for d in
    divisor_tuple(k))*f(n-k) for k in range(1, n))//(n-1)`
8. Partitions -- 1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42
  * Ways to partition number n. Use Leetcode Coin Change 2 solution
9. Central binomial powers -- 1, 2, 6, 20, 70, 252, 924
  * Appear in middle of even rows in Pascal's triangle. Number of n-digit
    binary numbers with seen 1s <= 0s as number is read. 2nCn
10. Bell numbers -- 1, 1, 2, 5, 15, 52, 203, 877
  * Ways to partition set = Bn = sum((n-1)Ci Bi) from i=0 to i=n-1
  * Also, ways to factorize squarefree number, rhyme schemes (ABAA, e.g.),
    moments of Poisson distribution with mean 1

### Other sequences

1. Look-and-say seq. -- 1, 11, 21, 1211, 111221, 312211, 13112221
2. Primes -- 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
3. Sylvester numbers -- 2, 3, 7, 43, 1807, 3263443
  * Sn = 1 + product(Si) from i=0 to i=n-1 
4. Factorials -- 1, 1, 2, 6, 24, 120, 720, 5040
5. Derangements -- 1, 0, 1, 2, 9, 44, 265, 1854
  * Incl-excl gets n! - n (n-1)! + nC2 (n-2)! - ... = n! sum((-1)^i/i!), i=0-n
  * Dn / n! goes to 1/e as n goes to infinity, since exp(-1) = sum((-1)^i / i!)
6. Woodall numbers -- 1, 7, 23, 63, 159, 383
  * Formula is Wn = n 2^n - 1
7. Cullen numbers -- 1, 3, 9, 25, 65, 161, 385
  * Formula is Cn = n 2^n + 1
8. Jacobsthal numbers -- 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683
  * Formula is Jn = J(n-1) + 2 J(n-2)
9. Pell numbers -- 0, 1, 2, 5, 12, 29, 70, 169, 408
  * Formula is Pn = 2 P(n-1) + P(n-2)
  * Ratio of consecutive elements approximates sqrt(2)

### Figurate sequences

1. Triangular -- 0, 1, 3, 6, 10, 15, 21, 28, 36, 45
  * Number of dots used to create equilateral triangle = 1+2+...+n = n(n+1)/2,
    or Tn = n + T(n-1) with T1 = 1. Also, number of handshakes needed for n ppl
2. Tetrahedral -- 0, 1, 4, 10, 20, 35, 56, 84
  * Sum of first n Triangular numbers = sum(Tn) from n=1 to n=n = n(n+1)(n+2)/6
3. Square pyramidal -- 0, 1, 5, 14, 30, 55, 91, 140
  * Stacks of smaller squares = sum(i^2) from i=1 to i=n = n(n+1)(2n+1)/6
4. Star -- 1, 13, 37, 73, 121, 181
  * Places in Chinese checkers board = Sn = 6n(n-1) + 1

In general, the sum of p'th powers of the first n integers is given by
Faulhaber's formula
  * sum(i^p) from i=1 to n =  1/(p+1) sum((p+1)Ci Bi n^(p-i+1)) from i=0 to i=p
    where Bi is the i'th Bell number

## Wikipedia - Modern Portfolio Theory

Returns expectation = w^T r, variance = w^T C w where r is expected return of
stocks and C is covariance of stock returns

Minimize w^T C w - q r^T w for w s.t. sum(w) = 1 and q >= 0
  * q is risk tolerance factor

Optimization can be performed with Markowitz critical line algorithm for
quadratic programming with linear constraints and asset bounds

Capital allocation line is tangent to efficient frontier and has y-intercept at
risk-free rate in plot of returns vs. risk 
  * Tangency point is portfolio with highest Sharpe ratio
  * This line allows for better portfolios since it's above efficient frontier

Idiosyncratic risk is mitigated via diversification (reducing overall variance
by leveraging negative covariances). Systematic risk is mitigated via long-short
strategies to maintain market-neutral portfolio
  * Conditional asset pricing models consider impact of asset on portfolio, and
    therefore rely on covariance 

CAPM yields E[Ri] = Rf + Bi (E[Rm] - Rf), where Rf is risk-free returns, Rm is
market returns, and Bi is OLS estimate of asset vs. market (proxy for risk)
  * Assume weight wa is small compared to wm. Assume any money (weight) placed
    into asset is as good as money put into market portfolio
  * wa(E[Ra] - Rf) / (2 wa wm Cov[a,m]) = wa(E[Rm] - Rf) / (2 wa wm Cov[m,m])
  * Bi = Cov[a,m] / Cov[m,m], which is just OLS estimate!
  * New variance / market variance ~= 1 + 2 wa (Bi - 1)

Criticisms
  * Variance is symmetric, but people are loss-averse
  * No model structure, just probabilistic fitting
  * Relies on assumption of elliptical joint returns pdf

## Derivations of my own

Unbiased estimator with higher variance -- inv(X^T X) X^T y + (ypred - y)
  * Below, call A = inv(X^T X) X^T and H = XA = hat matrix
  * E[Bhat] = (A + H - I)(XB) = AXB + HXB - XB = B
  * Var[Bhat] = s^2 (A + H - I)(A^T + H - I) = s^2(inv(X^T X) + (I-H)). Note
    that diagonal elements of (I-H) are 0 <= x <= 1 bc so is Hii
  * Note: need to chop off ypred - y at length p to match dimension

Orthogonal bases lead to lower Var[Bhat]
  * Consider X^T X = [[A,C^T],[C,D]] so inv(X^T X) has top-left element inv(A -
    C^T inv(D) C) by Schur complement
  * A and D are both mini-X^T X matrices and are symmetric + positive semidef.
    Therefore so is inv(D) bc D = V S V^T --> invert positive eigenvalues
  * So C^T inv(D) C >= 0 and A - C^T inv(D) C is smaller than A, meaning inverse
    is bigger. Thus, variance is bigger

Flipping Y and X simple linear regression changes B but not significance
  * B = CorrXY sy/sx, B' = CorrXY sx/xy, B/(1/B') = r^2 <= 1
  * Overall R^2 of fit doesn't change, so neither does F-statistics =
    R^2/(1-R^2) (n-2)
  * Test stat for slope = Cov[X,Y]/s sqrt(Var[X]) ?= Cov[Y,X]/s' sqrt(Var[Y])
    --> Y^T(I-H)Y X^T X ?= X^T(I-H')X Y^T Y --> true
  * Results don't change at all if variables are standardized first

## Quantopian python notebooks

We should keep outliers that capture info, but not ones from pure noise

Regime changes happen in time, which cause new distributions. This breaks homosk
  * E.g., Exxon Mobil stock after 2014
  * Check for breakpoints with `stats.diagnostic.breaks_cusumolsresid`

Beta hedging takes short on SP500 to remove dependency on market
  * E[Y] = alpha + B E[market] --> E[Y] = alpha
  * Var[Y] = B^2 Var[Market] --> Var[Y] = 0
  * Estimated Bhat will not perfectly match in future time periods
  * Can leverage strategy to get desired returns while keeping 0 variance

Long-short equity removes need for beta hedging by being market-neutral. Long
top-ranked stocks and short bottom-ranked stocks
  * This is probably what CrunchDAO is doing

Fama-French adds market cap, book/price, momentum to market risk (CAPM) model
  * Accounts for hot small caps outperforming CAPM prediction
  * R = a + B1 F1 + ...
  * Can preprocess factors by normalizing across assets
    * Winsorization sets top x% to least extreme value -- tames outliers

Trading cost = leverage turnover tradingdays transactioncost. Can have 2%
increase in costs from 0.01% increase in transaction costs

PCA gives ad-hoc factors, which can then be used to group alike assets or value
portfolio/beta-hedge

IR = Sharpe = (info coef) sqrt(breadth) --> max with many good uncorrelated bets
  * Hedge out common factors like market/sector exposure
  * Sector/market risk is naturally hedged in pairs trade
  * Cross-sectional strategy: de-mean alpha vector by sector avg
  * Event-driven strategy: add offsetting alphas in same sector or hedge w ETF

Get stationary time series by taking differences (many times if needed)
  * Order of integration checks if i'th cumulative sum has sum(|bj|^2) = 0 where
    corresponding time series Xt = sum(bj innov(t-j) + signal(t))
  * Returns (pct change) are typically more stationary than prices
  * A set of I(1) time series is cointegrated if a linear combination is I(0)
    * Some linear combo cancel autocorrelation/trends. Useful for pairs trading

Correlation and cointegration are different
  * High corr, low coint -- X1 and X2 are roughly straight lines w diff slopes
  * Low corr, high coint -- X1 is noise, X2 is square wave, so X1 + 0 X2 is I(0)
  * Perform (rolling) CV to ensure cointegration holds over time

Covariance matrix is best estimated with shrinkage -- C = (1-d)S + (d)I, where S
is sample covariance matrix. Ledoit-Wolf method finds optimal d
