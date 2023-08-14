# Automated trading by Max Dama

## Introduction and history

Programming is fast method to turn ideas into cash

Top earners are traders

Trading pulls from comp sci, stats, math, psych, econ, business, operations
research, and history

Early markets were in-person. Then banks were formed and telecoms ruled.
Exchanges were formed and central venues were established. Now trading is done
via programming

Punnett square:
  * Front office, buy side: asset mgmt, HF, prop trading. Use MATLAB, Java
  * Back office, buy side: data, execution, servers. Bash, SQL, C++
  * Front office, sell side: S+T (executing orders, creating derivatives). Excel
  * Back office, sell side: tech, risk. C++

Ideally, start at front office sell side, specialize in a product, then jump to
front office buy side at VP level

Frequencies:
  * High -- intraday. Need great hardware
    * E.g., market making (bid-ask spread), arbitrage, momentum, reversion
  * Low -- montly. Need great models
    * E.g., relative value, tactical asset allocation (macroecon factors)
  * Specialty
    * E.g., emerging markets, behavioral, news

Apply to many companies
  * See page 6 of pdf for list

Focus on S+T on sell-side. Create derivatives (basically, swaps + options)
  * Derivatives shield taxes, repackage risk, and sidestep regulations

## Brainteasers

## Alpha

Alpha is additional return over a naive forecast
  * Comes from info, processing, modeling, and/or speed
  * Correct encoding of signal is often simple
    * Use rate of change, normalize values, smooth signal, use weighted least
      sq., handle numerical errors/edge cases

6 styles of alphas:
  * Market making -- profit off spread
  * Directional -- wait for price to increase
  * Arbitrage -- profit off difference across exchanges
  * Relative value -- wait for 2 stocks to diverge
  * Model based -- buy if price below model; sell at model price
  * Carry -- buy stock for cash flow, then sell later

Examples
  * Frontrunning with HFT
  * Traffic analysis -- don't analyze messages, but volume of messages
  * Options and correlation -- correlation is mean-reverting, and volatility of
    basket depends on correlation. So, buy calls on ETF if corr is low
  * StarMine analyst revisions
  * Inflows from funds on 1st of month -- buy on last day and sell next day
  * Stock market wizards tips
  * Weight price by bid and ask quantities

Regression
  * Use time series regression to see relationship b/t signal and returns
  * Normalize to get fair signals across stocks
  * Smooth to reduce turnover
  * Trim outliers
  * Check for errors like gaps, holidays, zero-prices, etc.
  * Always use sliding windows/online algorithms to avoid overfitting
    * Exponentially weighted algorithms are memoryless!
  * With no intercept, E[Y|X] = x * Cov / VarX, Var[Y|X] = VarY (1 - Cov Cov /
    VarX VarY)

ML is flexible, but can lead to chasing ghosts
  * Incorporate as much structure as possible
  * 3 types of nonlinearity -- time-series, variable interactions, and
    polynomials
  * Typically interested in 1st moment, not higher moments (useful for risk)

Research checklist -- see page 21/22 of pdf

## Simulations

Types
  * Backtests have long runtimes and setup, but good for everything
  * Event studies are easier to run and set up, but only good for news
    * Good for checking for information leakage
  * Correlations are fast to run and set up, but only good for prototyping
  * Paper trading has no setup, and is great for production testing
    * Great for HFT due to lots of data quickly

Pitfalls
  * Introducing information from the future
  * Survivorship bias of testing only best companies (in SP500, e.g.)
  * Transaction costs rise during high volatility

Optimization
  * Use grid search, hill climbing, sim. annealing, or genetic algo
  * Ideally, use few parameters and plot profit vs. params

Tips
  * Control all program state incl. random seed and clock
  * Backtesting, paper trading, and live trading should converge on same results
  * Use manual loops to prevent future sight
  * Focus on max/avg drawdown rather than Sharpe

Betting
  * Kelly criterion -- maximize prod((1+f)^np(1-f)^(n(1-p))) --> f = 2p - 1
    * Coincides with maximizing E[profits]/Var[profits] for Gaussian profits

Correlations
  * Weight different strats to minimize overall variance
  * Cov = Corr stdX stdY
  * Imagine sharing coins when creating 2 sums. More shared coins --> higher Cov
  * Need lots of backtest data to estimate N^2 strat correlations
    * Estimate with BARRA model, factor model, regularize by combining with
      identity matrix, bootstrap, use eigenvalues/eigenvectors to extract
      strongest covariances, give up and use equal weighting

## Execution

High participation rate (% of ADV) and big spreads lead to slippage

Slice up orders via TWAP or VWAP (better)
