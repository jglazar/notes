# WorldQuant seminar 

## Price volume alphas

### Operators

Operators are building blocks
  * each one has a detailed explanation/math definition
  * add, subtract, mult, div -- be aware of units!
  * if/else, ternary
  * logical and, or, not
  * less/greater comparisons, eq/neq

Cross-sectional operators perform op across all stocks in universe 
at given point in time
  * rank, zscore, scale, sign

Time-series operators perform op on one stock across many points in time
  * tsdelta, tsdelay, tssum, tsmean, tsrank, tszscore, tsstddev, tsregression

Group operators are more powerful cross-sectional operators
  * Pick group like sector, industry, subindustry

Time-series regression
  * tsregression(y, x, window, lag, retval) -- y(t) = a + b * x(t-lag) for 
  t in past window days. Returns error, a, b, estimate. 

Cannot do cross-sectional correlation, only time-series correlation

Tradewhen operator activates between entry and exit conditions
  * Reduces turnover
  * Useful for trading during high-volatility times

Humpdecay -- return today's or yesterday's price, depending if change 
exceeds hump value
  * Reduces turnover

Good values
  * Truncation value = 0.01 for diversity
  * Reversion threshold = 0.55 because research show 50% time reversion, 10% momentum, 
  40% random 

### Data

Learn tab --> Datasets has all available datasets
  * Can create alphas for USA and China

Stock price increases with demand
  * Open, high, low, close
  * Total daily return -- close on day 1 to close on day 2

Volume (important!)
  * Daily
  * Average within timeframe, typically ~1 month which is 20 trading days
  * !!!Volume weighted average price = sum(price * shares traded at that price / 
  total shares traded that day)

Frequency -- how often data is updated, except sharesout, cap, split, dividend
  * Typically updated daily

Coverage -- how much stock data is available
  * 100% coverage -- data for all stocks in universe

### Technical indicators

Useful for identifying conditions, rather than as direct buy/sell signals 
  * E.g., overbought, oversold, trading, trending

RSI measures price magnitude changes -- indicates overbought/oversold
  * Check online for formula. Must implement by hand in Brain platform
  * Ranges from 0 (oversold) to 100 (overbought)

### Ideas

Momentum / trend-following
  * Buy upward stocks, short downward stocks

Trend reversion
  * Short overbought stocks, buy cheap stocks
  * Useful in long-short frameworks
  * Works well during extreme price movements (overreaction)
    * Consider stddev to measure extreme price movements
    * Trade during times of high volatility

Try alpha `-(close - ts_mean(close, 5))`
  * Revert to weekly price, compared cross-sectionally
  * Uses absolute difference, so high prices are unfairly up-weighted
  * Long-short neutralization is performed to balance long and short positions
  * Wrap alpha with `rank` operator to get percentile? Helps with weighting
    * Good trick to improve diversity and performance

Reduce turnover = percent of portfolio traded per day ~ transaction costs!
  * Increase alpha decay
  * Combine operators
    * Also reduces correlation

Try alpha `vwap / close`
  * Revert to vol-weighted average price, compared cross-sectionally
  * vwap represents "fair price", so following day should revert

Try alpha `group_zscore( -(close - open) / (high - low), subindustry )`
  * Simple candlestick-based alpha
  * Buy if closed below open, scaled by overall range

Try alpha `group_rank( ts_zscore(vwap/close, 250), subindustry )`
  * zscore is similar to rank, but Normal dist instead of Uniform dist
  * Pick stocks that are far from their time-average price, compared to 
  different stocks in subindustry

Try alpha `-tsregression( returns, ts_delay(returns,1), 252 )`
  * Use regression residuals as weights, so prices should revert to 
  regression prediction

Try alpha `trade_when( ts_rank( ts_std_dev(returns, 22), 252 ) > 0.55, 
                      -ts_regression(returns, ts_delay(returns,1), 252), -1
                    )`
  * Works really well!
  * Trade regression reversion idea when volatility is high
  * Otherwise, use previous day's value
  * Delay to prevent high turnover

Check research paper "101 Formulaic Alphas in Wilmott Magazine"
  * Improve implementations to find 6-8 submittable alphas!
  * Understand how they work in real markets

IncredibleCharts.com has indicators
  * Bollinger bands, etc

### Homework

Try simple moving average reversion
  * `signal = ts_mean(close, 20) / ts_mean(close, 5);`
  * `signed_power(ts_zscore(signal, 480), 2)`

Try Bollinger Bands
  * Check closing lower than low band / higher than high band
  * `window = 20; average = (high + low + close + open) / 4;`
  * `MA = ts_mean(average, window);`
  * `BOLU = MA + ts_std_dev(average, window);`
  * `BOLD = MA - ts_std_dev(average, window);`
  * `signal = ts_sum(close < BOLD, window) - ts_sum(close > BOLU, window);`
  * `ts_zscore(signal, 240)`

Try Stochastic Oscillator
  * `window = 10; lo = ts_min(low, window); hi = ts_max(high_window);`
  * `k = (close - lo) / (hi - lo); d = ts_decay_exp_window(k, 3, factor=0.5);`
  * `-d`

Come up with ideas by reading descriptions of datasets
  * E.g., Fundamental data might indicate value. Use ratios.

Reduce self-correlation by working with diverse datasets

## Fundamental datasets

Data comes from balance sheet, income statement, and cash flow statement
  * Income statement shows basic earnings and costs
  * Balance sheet shows stockholders' equity (book value)
  * CF statement shows reinvestments into company and liquidity
  * Updated quarterly, depending on exchange requirements
  * Helps understand business and future prospects

Creates financial portrait, identifies intrinsic value, helps recommendations
  * Insight into business decisions
  * Pay attention to key value drivers like CF and EPS
  * Cross-sectional comparisons and time-series analysis
    * Use financial ratios
  * Price-volume + fundamental is best
    * Combine based on financial or economic ideas

Use time-series ops and ratios using PV data to increase turnover

Use `keep` and `tradewhen` to reduce turnover

Examples
  * `ts_rank(equity / cap, 20)` -- like book/market ratio
    * TOP3000, neutralization industry, decay 5, truncation 0.1
    * 1.6 Sharpe, 25% turnover, 0.87 fitness, 7% returns
    * Try operators other than `ts_rank`, use groups
  * `-ts_zscore(enterprise_value / ebitda, 63)` -- short rising valuation
    * TOP3000, neutralization industry, decay 5, truncation 0.01
    * 1.7 Sharpe, 15% turnover, 1.08 fitness, 7% returns 

Model data has predicted fundamental, price, and ratio data from proprietary
datasets
  * Includes daily, quarterly, and annual frequency data

Examples
  * `ts_rank(mdf_oey, 250)` -- long increasing operating earnings yield
    * TOP3000, neutralization industry, decay 0, truncation 0.01
    * 1.9 Sharpe, 15% turnover, 1.14 fitness, 5.5% returns
  * `group_zscore( ts_zscore(mdf_gry, 20), sector )` -- long increasing growth
    rate and dividend yield
    * TOP3000, neutralization industry, decay 0, truncation 0.1
    * 1.9 Sharpe, 33% turnover, 0.86 fitness, 7% returns
    * Reduce turnover by increasing decay

Check out Financial Ratio video, "The Power of Firm Fundamentals in Explaining
Stock Returns" (abstract ID 3090626), "Earnings and Price Momentum" (abstract ID
342581)
