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

## Creating submittable alphas

Added 19 alpha examples to Documentation page

Upload profile pic so that leaderboard looks more engaging

Same idea, different data field -- try all possible combos
  * `ts_rank(operating_income/cap, 252)` and 
  `ts_rank(mdf_oey, 252)` on TOP3000 with neutralization 
  subindustry, 0 decay, 0.08 truncation, 1 delay
  * Search through all data sets

Same idea, different operator
  * `ts_rank(mdf_oey, 252)` and `ts_quantile(mdf_oey, 252)`
  * Could tack on cross-sectional groupwise rank before 
  taking time-series rank, e.g.

Toggle settings, esp. decay and neutralization
  * `ts_av_diff(mdf_nps, 500)` with neutralization market or 
  subindustry, TOP3000, decay 0, truncation 0.08, delay 1
  * Subindustry generally performs well

News data -- financial reports, analyst recommendations, 
company products, legal events
  * Impact can range days to quarters
  * Combine with stock price data
  * Must take `vec_avg` or similar
  * 3 trading sessions -- pre-trading (4-9:30), main trading 
  (9:30-4), post-trading (4-8)
    * News normally released pre- or post-trading, which causes 
    jumps during main trading
    * Delay is a significant factor for news data -- try 0
  * `rank( ts_sum( vec_avg(nws12_afterhsz_sl), 60 ) ) > 0.5 ? 
  1 : rank( -ts_delta(close, 2) )*1` on TOP3000 with 
  neutralization subindustry, decay 3, and truncation 0.01
  * Turnover is usually high

Sentiment data -- aggregated buzz/mood from news sites, 
social media, and forums
  * Helps businesses understand consumer views
  * Must take `vec_avg` or similar
  * `-ts_regression(returns, ts_delay(snt_buzz_ret, 1), 120)` 
  on TOP3000 with neutralization subindustry, decay 15, 
  max weight 0.1. `snt_buzz_ret` uses magnitude of buzz to 
  predict returns.

## Q and A

Check out articles on the forum
  * Seven Tips for Creating Delay 0 Alphas
  * 6 ways to evaluate a dataset

Hired 6 interns and 5 full-time from last tournament

Getting started with China region -- price limit system prevents negating as a
strategy
  * CHN has high in-sample performance

Only a subset of alphas work well for delay-1 and delay-0

Use high-frequency data like price/volume, news, sentiment, and option data for
delay-0 alphas. Trade on liquid universe.

`zscore(vwap / close) * (1 - rank(high / low))`
  * Neutralization market, truncation 0.01, decay 15, TOP1000, delay 0
  * Improve with more liquid universe 

`zscore(implied_volatility_call_720 - implied_volatility_put_720)`
  * Neutralization market, truncation 0.01, decay 3, TOP3000, delay 0
  * Improve with historical volatility, trading volume, and open interest

`-ts_corr(ts_rank(volume, 10), ts_rank(vwap, 10), 20)`
  * Neutralization subindustry, truncation 0.1, decay 3, TOP3000 China, delay 0
  * Improve by reducing noise when correlation is below threshold
  * China price reversion is typical in short-term trending markets

`when = ts_arg_max(volume, 5) == 0; trade_when(when, -rank(ts_delta(close, 3)),
-1)`
  * Neutralization subindustry, truncation 0.1, decay 3, TOP3000 China, delay 1
  * Improve by exiting when stock hits Chinese price limit (10%)

`rank(ts_delta(retained_earnings / sharesout, 90))`
  * Neutralization subindustry, truncation 0.01, decay 5, TOP3000 China, delay 1
  * Improve by lowering number of days in `ts_delta`

Truncation 0.01 for TOP3000
  * Use `rank` to prevent overweighting

## Consultant/Researcher Q and A

Hosted by Nicole Goldstein

You-Lin Wu was finance undergrad in Taiwan. Now researcher
  * Used Brain to do free research and apply theories learned in practice
  * Won Taiwan regional round to compete in Singapore
  * Day-to-day: similar to IQC, but with more tools and data
  * Tips: important to review alphas and think about improvements
  * Advice: submit many alphas

Yash Zanwar was undergrad in India. Now researcher
  * Learned Brain over time, then competed in IQC with friends
  * Won India regional round to compete in Singapore (with You-Lin!)
  * Day-to-day: research, platform improvements, community engagement
  * Tips: Ideas can come from anywhere, like news. Try different topics
  * Advice: attention to detail. Show good performance for many settings

Jayden Lee started as consultant, then intern, now researcher
  * Only made it to Round 2, not into next rounds
  * Tips: avoid overfitting. Use few parameters. Diversify alpha pool
  * Alpha idea: long low-beta, short high-beta (overrated). Calculate beta with
    CAPM model -- check Data Explorer for more
  * Advice: avoid overfitting bc you invest in future, not past 

Yu-Xiang (Simon) Mao was comp sci undergrad. Did internship and consultant, now
researcher
  * Placed 2nd in Taiwan regional round
  * See alpha creation as a game. Try anything
  * Advice: have an original alpha for the presentation

Ishan Shandilya found quant finance as undergrad major
  * Checked out Brain platform, then did internship.
  * Quant finance is secretive and uncollaborative. Brain enables interaction
  * Advice: quality through simplicity

Aditya Chaturvedi had bad grades, then found WorldQuant competition
  * Got internship, then consultant position. Now researcher
  * Background in materials science!
  * Advice: consistency in alpha submission. Try every day!

Data Explorer has tag for alpha generation -- can just use that data!

Re-use alphas from Round 1 in Round 2

## Options, Vector operators, and China markets

Vector data has multiple points per day (better called a tensor, IMO)

Stocks only specify direction and use current price. Options specify direction,
time, and price

Underlying property (call response)(put response)
  * Price+-, strike-+, expiry++, volatility++, risk-free rate+-, dividends-+

IV-vs-strike graph forms a smile

`ts_delay(call_breakeven_10, 7) / close`
  * Improve with other call or breakeven fields. Count frequency of close
    reaching breakeven
  * `a = above; trade_when(ts_arg_max(pcr_vol_10, 7) < 1, a, -1)`
  * Neutralization industry, truncation 0.03, decay 0, TOP3000

`ts_decay_linear(ts_delta(implied_volatility_call_60, 25) > 0, 20)`
  * Improve with `vector_neut()` operator
  * `a = above; vector_neut(a, (cap))`
  * Neutralization subindustry, truncation 0.03, decay 0, TOP3000
  * Check [paper](https://papers.ssrn.com/sol3/paper.cfm?abstract_id=2008902)
    * Big increase in call (put) IV over past month have high (low) returns

`vector_neut()` gets `a - (a*b)b` (orthogonal component to `b`) -- neutralizes
alpha vector over another risk factor

`-mdl175_volatility` -- new data field for China
  * Neutralization market, truncation 0.1, decay 3, TOP3000 China
  * Improve by reducing exposure to volatile stocks during high volumes
  * Can also upweigh stocks with high revenues for the past year
  * `rank(-mdl175_volatility * log(volume)) * (1 + group_rank(mdl175_revenuettm,
    sector))`
  * `vector_neut(above, ts_mean(mdl175_02amvt, 240))`
  * `group_vector_neut(above, ts_mean(mdl175_02amvt, 240), sector)`

`buzz = ts_backfill(-vec_sum(scl12_alltype_buzzvec), 20); ts_av_diff(buzz, 60)`
  * Neutralization industry/subindustry, truncation 0.08, decay 15, TOP3000

`ts_backfill(-vec_avg(nws12_afterhsz_maxupamt), 20)`
  * Neutralization industry, truncation 0.01, decay 10, TOP1000
  * Improve by neutralizing w.r.t. momentum. Set no neutralization and decay 0
  * `a = above; neut_a = vector_neut(a, ts_mean(returns, 250)); decay_a =
    ts_decay_exp_window(neut_a, 20, factor=0.4); group_neutralize(decay_a,
    densify((industry+1)*10 + exchange))`

`avg_ret = power(ts_product(returns+1, 5), 1/5); comp_avg =
power(ts_product(rel_ret_comp+1, 5), 1/5); a = zscore(comp_avg / avg_ret);
when = ts_rank(ts_std_dev(returns, 60), 126) > 0.55; trade_when(when, a, -1)`
  * Neutralization subindustry, truncation 0.01, decay 3, TOP3000
  * Geometric mean works much better than arithmetic mean for financial data
    * Can numerically stabilize with `exp(1/N sum(log(x)))`
  * Improve by neutralizing w.r.t. momentum
  * `vector_neut(above, ts_mean(returns, 120))`

`rank(-(mdf_pbk - ts_max(mdf_pbk, 10)))`
  * Neutralization subindustry, truncation 0.01, decay 3, TOP3000
  * Improve by reducing turnover
  * `rank(ts_sum(vec_avg(nws12_afterhsz_s1), 60)) > 0.5 ? 1 : above`
    * Moving negative sign outside the `rank()` operator is bad here
  * Improve further with `pv13` model groupings
  * `group_neutralize(above, densify(pv13_r2_min20_3000_sector))`

Check out Data Explorer for farming ideas -- simulate data field with high usage

China tips
  * Use `group_rank` instead of `rank`
  * Use our own risk factors for vector neutralization. Use `group_vector_neut`!

Low coverage is OK -- e.g., data on TOP1000 will only have 33% coverage

Translate math into alpha expressions -- change is `ts_delta` or `ts_zscore`,
dependence is `ts_corr` or `ts_regression`, prediction is `ts_regression(...
rettype=3)`
