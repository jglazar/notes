# Alpha ideas

## 101 Formulaic Alphas

Price Volume seminar on 30 March 2023 recommended that 6-8 of these 
alphas, once improved, are submissible.

The 101 alphas are held from 0.6 - 6.4 days and tested between 4 January 2010 
and 31 December 2013 (1006 observations).

Found to have pairwise correlation of 15.9% and have returns correlated with 
volatility s.t. `returns ~ volatility ^ 0.76`.

Combining many alphas results in too many variables with too few observations, 
yielding near-singular covariance matrices.

Most of the list are price-volume. Some are fundamental. Some use industry 
neutralization.

### Definitions

"delay-d" alpha is executed d days after the relevant data.

P = average daily PnL, V = daily volatility, Q = average daily shares traded, 
D = average daily dollar volume traded, I = total dollar investment 

Sharpe ratio = `sqrt(252) * P / V`

Turnover = `D / I`

Cents-per-share = `100 * P / Q`

Yij = covariance matrix of daily returns for alphas i and j.

### Results

Sharpe ratio: 1.2 (min) - 1.9 (Q1) - 2.2 (median) - 2.5 (Q3) - 4.2 (max)

Turnover: 0.16 (min) - 0.34 (Q1) - 0.48 (median) - 0.65 (Q3) - 1.6 (max)

Cents-per-share: 0.13 (min) - 0.31 (Q1) - 0.40 (median) - 0.51 (Q3) - 2.0 (max)

### Alpha list

1. `(rank(Ts_ArgMax(SignedPower(((returns < 0) ? stddev(returns, 20) : close), 2.), 5)) - 0.5`
2. `(-1 * correlation(rank(delta(log(volume), 2)), rank(((close - open) / open)), 6))`
3. `(-1 * correlation(rank(open), rank(volume), 10))`
4. `(-1 * Ts_Rank(rank(low), 9))`
5. `(rank((open - (sum(vwap, 10) / 10))) * (-1 * abs(rank((close - vwap)))))`
6. `-1 * correlation(open, volume, 10))`
7. `(adv20 < volume) ? ((-1 * ts_rank(abs(delta(close, 7)), 60)) * sign(delta(close, 7))) : (-1 * 1))`
8. `(-1 * rank(((sum(open, 5) * sum(returns, 5)) - delay((sum(open, 5) * sum(returns, 5)), 10))))`
9. `((0 < ts_min(delta(close, 1), 5)) ? delta(close, 1) : ((ts_max(delta(close, 1), 5) < 0) ? delta(close, 1) : (-1 * delta(close, 1))))`
10. `rank(((0 < ts_min(delta(close, 1), 4)) ? delta(close, 1) : ((ts_max(delta(close, 1), 4) < 0) ? delta(close, 1) : (-1 * delta(close, 1)))))`
11. `((rank(ts_max((vwap - close), 3)) + rank(ts_min((vwap - close), 3))) * rank(delta(volume, 3)))`
12. `(sign(delta(volume, 1)) * (-1 * delta(close, 1)))`
13. `(-1 * rank(covariance(rank(close), rank(volume), 5)))`
14. `((-1 * rank(delta(returns, 3))) * correlation(open, volume, 10))`
15. `(-1 * sum(rank(correlation(rank(high), rank(volume), 3)), 3))`
16. `(-1 * rank(covariance(rank(high), rank(volume), 5)))`
17. `(((-1 * rank(ts_rank(close, 10))) * rank(delta(delta(close, 1), 1))) * rank(ts_rank((volume / adv20), 5)))`
18. `(-1 * rank(((stddev(abs((close - open)), 5) + (close - open)) + correlation(close, open,10))))`
19. `((-1 * sign(((close - delay(close, 7)) + delta(close, 7)))) * (1 + rank((1 + sum(returns,250)))))`
20. `(((-1 * rank((open - delay(high, 1)))) * rank((open - delay(close, 1)))) * rank((open -delay(low, 1))))`
21. `((((sum(close, 8) / 8) + stddev(close, 8)) < (sum(close, 2) / 2)) ? (-1 * 1) : (((sum(close,2) / 2) < ((sum(close, 8) / 8) - stddev(close, 8))) ? 1 : (((1 < (volume / adv20)) || ((volume / adv20) == 1)) ? 1 : (-1 * 1))))`
22. `(-1 * (delta(correlation(high, volume, 5), 5) * rank(stddev(close, 20))))`
23. `(((sum(high, 20) / 20) < high) ? (-1 * delta(high, 2)) : 0)`
24. `(((delta((sum(close, 100) / 100), 100) / delay(close, 100)) < 0.05) || ((delta((sum(close, 100) / 100), 100) / delay(close, 100)) == 0.05)) ? (-1 * (close - ts_min(close,100))) : (-1 * delta(close, 3)))`
25. `rank(((((-1 * returns) * adv20) * vwap) * (high - close)))`
26. `(-1 * ts_max(correlation(ts_rank(volume, 5), ts_rank(high, 5), 5), 3))`
27. `((0.5 < rank((sum(correlation(rank(volume), rank(vwap), 6), 2) / 2.0))) ? (-1 * 1) : 1)`
28. `scale(((correlation(adv20, low, 5) + ((high + low) / 2)) - close))`
29. `(min(product(rank(rank(scale(log(sum(ts_min(rank(rank((-1 * rank(delta((close - 1),5))))), 2), 1))))), 1), 5) + ts_rank(delay((-1 * returns), 6), 5))`
30. `(((1.0 - rank(((sign((close - delay(close, 1))) + sign((delay(close, 1) - delay(close, 2)))) +sign((delay(close, 2) - delay(close, 3)))))) * sum(volume, 5)) / sum(volume, 20))`
31. `((rank(rank(rank(decay_linear((-1 * rank(rank(delta(close, 10)))), 10)))) + rank((-1 *delta(close, 3)))) + sign(scale(correlation(adv20, low, 12))))`
32. `(scale(((sum(close, 7) / 7) - close)) + (20 * scale(correlation(vwap, delay(close, 5),230))))` 
33. `rank((-1 * ((1 - (open / close))^1)))`
34. `rank(((1 - rank((stddev(returns, 2) / stddev(returns, 5)))) + (1 - rank(delta(close, 1)))))`
35. `((Ts_Rank(volume, 32) * (1 - Ts_Rank(((close + high) - low), 16))) * (1 -Ts_Rank(returns, 32)))`
36. `(((((2.21 * rank(correlation((close - open), delay(volume, 1), 15))) + (0.7 * rank((open- close)))) + (0.73 * rank(Ts_Rank(delay((-1 * returns), 6), 5)))) + rank(abs(correlation(vwap,adv20, 6)))) + (0.6 * rank((((sum(close, 200) / 200) - open) * (close - open)))))`
37. `(rank(correlation(delay((open - close), 1), close, 200)) + rank((open - close)))`
38. `((-1 * rank(Ts_Rank(close, 10))) * rank((close / open)))`
39. `((-1 * rank((delta(close, 7) * (1 - rank(decay_linear((volume / adv20), 9)))))) * (1 +rank(sum(returns, 250))))` 
40. `((-1 * rank(stddev(high, 10))) * correlation(high, volume, 10))`
41. `(((high * low)^0.5) - vwap)`
42. `rank((vwap - close)) / rank((vwap + close)))`
43. `(ts_rank((volume / adv20), 20) * ts_rank((-1 * delta(close, 7)), 8))`
44. `(-1 * correlation(high, rank(volume), 5))`
45. `(-1 * ((rank((sum(delay(close, 5), 20) / 20)) * correlation(close, volume, 2)) *rank(correlation(sum(close, 5), sum(close, 20), 2))))`
46. `((0.25 < (((delay(close, 20) - delay(close, 10)) / 10) - ((delay(close, 10) - close) / 10))) ?(-1 * 1) : (((((delay(close, 20) - delay(close, 10)) / 10) - ((delay(close, 10) - close) / 10)) < 0) ? 1 :((-1 * 1) * (close - delay(close, 1)))))`
47. `((((rank((1 / close)) * volume) / adv20) * ((high * rank((high - close))) / (sum(high, 5) /5))) - rank((vwap - delay(vwap, 5))))`
48. `(indneutralize(((correlation(delta(close, 1), delta(delay(close, 1), 1), 250) *delta(close, 1)) / close), IndClass.subindustry) / sum(((delta(close, 1) / delay(close, 1))^2), 250))`
49. `(((((delay(close, 20) - delay(close, 10)) / 10) - ((delay(close, 10) - close) / 10)) < (-1 *0.1)) ? 1 : ((-1 * 1) * (close - delay(close, 1))))`
50. `(-1 * ts_max(rank(correlation(rank(volume), rank(vwap), 5)), 5))`
51. `(((((delay(close, 20) - delay(close, 10)) / 10) - ((delay(close, 10) - close) / 10)) < (-1 *0.05)) ? 1 : ((-1 * 1) * (close - delay(close, 1))))`
52. `((((-1 * ts_min(low, 5)) + delay(ts_min(low, 5), 5)) * rank(((sum(returns, 240) -sum(returns, 20)) / 220))) * ts_rank(volume, 5))`
53. `(-1 * delta((((close - low) - (high - close)) / (close - low)), 9))`
54. `((-1 * ((low - close) * (open^5))) / ((low - high) * (close^5)))`
55. `(-1 * correlation(rank(((close - ts_min(low, 12)) / (ts_max(high, 12) - ts_min(low,12)))), rank(volume), 6))`
56. `(0 - (1 * (rank((sum(returns, 10) / sum(sum(returns, 2), 3))) * rank((returns * cap)))))`
57. `(0 - (1 * ((close - vwap) / decay_linear(rank(ts_argmax(close, 30)), 2))))`
58. `(-1 * Ts_Rank(decay_linear(correlation(IndNeutralize(vwap, IndClass.sector), volume,3.92795), 7.89291), 5.50322))`
59. `(-1 * Ts_Rank(decay_linear(correlation(IndNeutralize(((vwap * 0.728317) + (vwap *(1 - 0.728317))), IndClass.industry), volume, 4.25197), 16.2289), 8.19648))`
60. `(0 - (1 * ((2 * scale(rank(((((close - low) - (high - close)) / (high - low)) * volume)))) -scale(rank(ts_argmax(close, 10))))))`
61. `(rank((vwap - ts_min(vwap, 16.1219))) < rank(correlation(vwap, adv180, 17.9282)))`
62. `((rank(correlation(vwap, sum(adv20, 22.4101), 9.91009)) < rank(((rank(open) +rank(open)) < (rank(((high + low) / 2)) + rank(high))))) * -1)`
63. `((rank(decay_linear(delta(IndNeutralize(close, IndClass.industry), 2.25164), 8.22237))- rank(decay_linear(correlation(((vwap * 0.318108) + (open * (1 - 0.318108))), sum(adv180,37.2467), 13.557), 12.2883))) * -1)`
64. `((rank(correlation(sum(((open * 0.178404) + (low * (1 - 0.178404))), 12.7054),sum(adv120, 12.7054), 16.6208)) < rank(delta(((((high + low) / 2) * 0.178404) + (vwap * (1 -0.178404))), 3.69741))) * -1)`
65. `((rank(correlation(((open * 0.00817205) + (vwap * (1 - 0.00817205))), sum(adv60,8.6911), 6.40374)) < rank((open - ts_min(open, 13.635)))) * -1)` 
66. `((rank(decay_linear(delta(vwap, 3.51013), 7.23052)) + Ts_Rank(decay_linear(((((low* 0.96633) + (low * (1 - 0.96633))) - vwap) / (open - ((high + low) / 2))), 11.4157), 6.72611)) * -1)`
67. `((rank((high - ts_min(high, 2.14593)))^rank(correlation(IndNeutralize(vwap,IndClass.sector), IndNeutralize(adv20, IndClass.subindustry), 6.02936))) * -1)`
68. `((Ts_Rank(correlation(rank(high), rank(adv15), 8.91644), 13.9333) <rank(delta(((close * 0.518371) + (low * (1 - 0.518371))), 1.06157))) * -1)`
69. `: ((rank(ts_max(delta(IndNeutralize(vwap, IndClass.industry), 2.72412),4.79344))^Ts_Rank(correlation(((close * 0.490655) + (vwap * (1 - 0.490655))), adv20, 4.92416),9.0615)) * -1)`
70. `((rank(delta(vwap, 1.29456))^Ts_Rank(correlation(IndNeutralize(close,IndClass.industry), adv50, 17.8256), 17.9171)) * -1)`
71. `max(Ts_Rank(decay_linear(correlation(Ts_Rank(close, 3.43976), Ts_Rank(adv180,12.0647), 18.0175), 4.20501), 15.6948), Ts_Rank(decay_linear((rank(((low + open) - (vwap +vwap)))^2), 16.4662), 4.4388))`
72. `(rank(decay_linear(correlation(((high + low) / 2), adv40, 8.93345), 10.1519)) /rank(decay_linear(correlation(Ts_Rank(vwap, 3.72469), Ts_Rank(volume, 18.5188), 6.86671),2.95011)))`
73. `(max(rank(decay_linear(delta(vwap, 4.72775), 2.91864)),Ts_Rank(decay_linear(((delta(((open * 0.147155) + (low * (1 - 0.147155))), 2.03608) / ((open *0.147155) + (low * (1 - 0.147155)))) * -1), 3.33829), 16.7411)) * -1)`
74. `((rank(correlation(close, sum(adv30, 37.4843), 15.1365)) <rank(correlation(rank(((high * 0.0261661) + (vwap * (1 - 0.0261661)))), rank(volume), 11.4791)))* -1)`
75. `(rank(correlation(vwap, volume, 4.24304)) < rank(correlation(rank(low), rank(adv50),12.4413)))`
76. `(max(rank(decay_linear(delta(vwap, 1.24383), 11.8259)),Ts_Rank(decay_linear(Ts_Rank(correlation(IndNeutralize(low, IndClass.sector), adv81,8.14941), 19.569), 17.1543), 19.383)) * -1)`
77. `min(rank(decay_linear(((((high + low) / 2) + high) - (vwap + high)), 20.0451)),rank(decay_linear(correlation(((high + low) / 2), adv40, 3.1614), 5.64125)))`
78. `(rank(correlation(sum(((low * 0.352233) + (vwap * (1 - 0.352233))), 19.7428),sum(adv40, 19.7428), 6.83313))^rank(correlation(rank(vwap), rank(volume), 5.77492)))`
79. `(rank(delta(IndNeutralize(((close * 0.60733) + (open * (1 - 0.60733))),IndClass.sector), 1.23438)) < rank(correlation(Ts_Rank(vwap, 3.60973), Ts_Rank(adv150,9.18637), 14.6644)))`
80. `((rank(Sign(delta(IndNeutralize(((open * 0.868128) + (high * (1 - 0.868128))),IndClass.industry), 4.04545)))^Ts_Rank(correlation(high, adv10, 5.11456), 5.53756)) * -1)`
81. `((rank(Log(product(rank((rank(correlation(vwap, sum(adv10, 49.6054),8.47743))^4)), 14.9655))) < rank(correlation(rank(vwap), rank(volume), 5.07914))) * -1)`
82. `(min(rank(decay_linear(delta(open, 1.46063), 14.8717)),Ts_Rank(decay_linear(correlation(IndNeutralize(volume, IndClass.sector), ((open * 0.634196) +(open * (1 - 0.634196))), 17.4842), 6.92131), 13.4283)) * -1)`
83. `((rank(delay(((high - low) / (sum(close, 5) / 5)), 2)) * rank(rank(volume))) / (((high -low) / (sum(close, 5) / 5)) / (vwap - close)))`
84. `SignedPower(Ts_Rank((vwap - ts_max(vwap, 15.3217)), 20.7127), delta(close,4.96796))`
85. `(rank(correlation(((high * 0.876703) + (close * (1 - 0.876703))), adv30,9.61331))^rank(correlation(Ts_Rank(((high + low) / 2), 3.70596), Ts_Rank(volume,7.11408)))`
86. `((Ts_Rank(correlation(close, sum(adv20, 14.7444), 6.00049), 20.4195) < rank(((open+ close) - (vwap + open)))) * -1)`
87. `(max(rank(decay_linear(delta(((close * 0.369701) + (vwap * (1 - 0.369701))),1.91233), 2.65461)), Ts_Rank(decay_linear(abs(correlation(IndNeutralize(adv81,IndClass.industry), close, 13.4132)), 4.89768), 14.4535)) * -1)`
88. `min(rank(decay_linear(((rank(open) + rank(low)) - (rank(high) + rank(close))),8.06882)), Ts_Rank(decay_linear(correlation(Ts_Rank(close, 8.44728), Ts_Rank(adv60,20.6966), 8.01266), 6.65053), 2.61957))`
89. `(Ts_Rank(decay_linear(correlation(((low * 0.967285) + (low * (1 - 0.967285))), adv10,6.94279), 5.51607), 3.79744) - Ts_Rank(decay_linear(delta(IndNeutralize(vwap,IndClass.industry), 3.48158), 10.1466), 15.3012))` 
90. `((rank((close - ts_max(close, 4.66719)))^Ts_Rank(correlation(IndNeutralize(adv40,IndClass.subindustry), low, 5.38375), 3.21856)) * -1)`
91. `((Ts_Rank(decay_linear(decay_linear(correlation(IndNeutralize(close,IndClass.industry), volume, 9.74928), 16.398), 3.83219), 4.8667) -rank(decay_linear(correlation(vwap, adv30, 4.01303), 2.6809))) * -1)`
92. `min(Ts_Rank(decay_linear(((((high + low) / 2) + close) < (low + open)), 14.7221),18.8683), Ts_Rank(decay_linear(correlation(rank(low), rank(adv30), 7.58555), 6.94024),6.80584))`
93. `(Ts_Rank(decay_linear(correlation(IndNeutralize(vwap, IndClass.industry), adv81,17.4193), 19.848), 7.54455) / rank(decay_linear(delta(((close * 0.524434) + (vwap * (1 -0.524434))), 2.77377), 16.2664)))`
94. `((rank((vwap - ts_min(vwap, 11.5783)))^Ts_Rank(correlation(Ts_Rank(vwap,19.6462), Ts_Rank(adv60, 4.02992), 18.0926), 2.70756)) * -1)`
95. `(rank((open - ts_min(open, 12.4105))) < Ts_Rank((rank(correlation(sum(((high + low)/ 2), 19.1351), sum(adv40, 19.1351), 12.8742))^5), 11.7584))`
96. `(max(Ts_Rank(decay_linear(correlation(rank(vwap), rank(volume), 3.83878),4.16783), 8.38151), Ts_Rank(decay_linear(Ts_ArgMax(correlation(Ts_Rank(close, 7.45404),Ts_Rank(adv60, 4.13242), 3.65459), 12.6556), 14.0365), 13.4143)) * -1)`
97. `((rank(decay_linear(delta(IndNeutralize(((low * 0.721001) + (vwap * (1 - 0.721001))),IndClass.industry), 3.3705), 20.4523)) - Ts_Rank(decay_linear(Ts_Rank(correlation(Ts_Rank(low,7.87871), Ts_Rank(adv60, 17.255), 4.97547), 18.5925), 15.7152), 6.71659)) * -1)`
98. `(rank(decay_linear(correlation(vwap, sum(adv5, 26.4719), 4.58418), 7.18088)) - rank(decay_linear(Ts_Rank(Ts_ArgMin(correlation(rank(open), rank(adv15), 20.8187), 8.62571),6.95668), 8.07206)))`
99. `((rank(correlation(sum(((high + low) / 2), 19.8975), sum(adv60, 19.8975), 8.8136)) <rank(correlation(low, volume, 6.28259))) * -1)`
100. `(0 - (1 * (((1.5 * scale(indneutralize(indneutralize(rank(((((close - low) - (high -close)) / (high - low)) * volume)), IndClass.subindustry), IndClass.subindustry))) - scale(indneutralize((correlation(close, rank(adv20), 5) - rank(ts_argmin(close, 30))), IndClass.subindustry))) * (volume / adv20))))`
101. `((close - open) / ((high - low) + .001))`
     
Many of the mean-reversion ones work especially well in 2020 and 2021. 
33 and 101 are simple and work great. I even edited 57 to create a 
submittable alpha.

Short `ts_decay_linear`, `rank`, and only using relative values (pcts) 
help performance

## WorldQuant website

### Rules

Daily score is capped at 2000, which can be achieved with 1 or 2 alphas.
  * Score depends on quantity (more alphas submitted is better) and avg. alpha quality
  * Smaller universe, lower self-correlation, higher fitness, longer delay (d1 vs. d0), 
  * Score is normalized across all users with >= 1 alpha submitted that day. 

IQC uses Merged PnL from all team members and all alphas
  * Equal weighting across submitted alphas
  * Considers Sharpe, returns/drawdown, and turnover
  * ❗️ Check before/after score in Performance Comparison tab before 
  submitting
  * Stage 1 only considers in-sample. Stage 2 considers out-of-sample.
  * Delay 0 alpha contributions are divided by 3 in final score

Bronze over 1000, Silver over 5000, Gold over 10000
  * Silver and Gold get access to special training and videos
  * Scores over 10000 are eligible for interview invite

Reported turnover = average daily turnover. 
  * Daily turnover = percentage of portfolio bought/sold b/t today and yesterday, 
  by dollar value 

Self-correlation is calculated by PnL graph, not alpha weights
  * Self correlation uses a 2-year window. Inner correlation uses the intersect 
  of the alpha's PnL time periods.
  * Alphas with high self-correlation can still be submitted if Sharpe is improved 
  by at least 10%

Sub-universe Sharpe threshold scales with sub-universe size

In-sample is 7 years ago to 2 years ago, updated daily. The past year is used 
for scoring and testing.

### Settings and data

Groups include market, sector, industry, and subindustry

Simulation settings
  * Decay takes weighted sum of last n days: 
  `(n x0 + (n-1) x1 + ... + x(n-1)) / (n + n-1 + ... + 1)`
    * Decay reduces turnover but attenuates signal
  * Truncation sets max weight for portfolio. 0 = no restriction.
    * Recommended 0.05 - 0.10
  * Neutralization sets total long = total short within group  
  by reassigning `alpha <- alpha - mean(alpha)`
  * NaN handling: 0 for time-series data, group mean/median/count for 
  group data
  * Unit handling raises a warning if wrong units are combined. E.g, 
  price + volume.

Data can be in vector form, with different vector lengths for each stock
  * e.g., `scl15_d1_sentiment`
  * Need to aggregate vector into single number, then apply normal operations
    * `vec_avg`, `vec_choose`, `vec_count`, `vec_ir`, `vec_kurtosis`, 
    `vec_max`, `vec_min`, `vec_norm`, `vec_percentage`, `vec_powersum`, 
    `vec_range`, `vec_skewness`, `vec_stddev`, `vec_sum`
  * `nws12_afterhsz_1_minute` gives pct change within 1 minute after news 
  release. Predict momentum for high-intensity (high count) and reversion for 
  low-intensity (low-count). 
  * `scl15_d1_sentiment` gives sentiment score for each event in a day. Predict 
  momentum for good sentiment (high mean or median). 
  * Both above alphas have high turnover -- use `ts_rank` or `ts_decay` to smooth.

### Pasteurization and neutralization

All data is auto-pasteurized s.t. non-universe stocks are NaN.
  * Manually pasteurize data in group-wise comparisons to only consider group 
  stocks inside the universe. 
  * Pasteurize doesn't affect single-stock operators like +,-,ts,max,min,etc. Only 
  affects group operators like `group_rank`, `group_mean`, `group_max`, etc.
  * Pasteurize only makes big difference if universe is small (USATOP200, e.g.)
  * Check the following:
  * `group_rank(pasteurize((close - ts_delay(close, 5)) / close) , sector)`
  * `group_rank( (close - ts_delay(close, 5)) / close , sector)`
  * `group_rank(pasteurize(sales_growth),sector) - group_rank(sales_growth,sector)`

All alphas should be neutralized s.t. longs and shorts balance out in each 
subindustry/industry/sector/market
  * Neutralizing by market favors some sectors over others 
  * Neutralizing simple price reversion alpha by market instead of by subindustry 
  can reduce Sharpe but greatly increases fitness! 
  * Turns out, no neutralization is insanely good for price reversion 
  (so you can long or short the whole market)
  * Can use `group_neutralize` to apply granular neutralization 
  * Use big groups for small liquid universes, small groups for big illiquid universes

### Tips

Neutralization 
  * Fundamentals affect price differently in different industries -- neutralize by industry 
  * Analyst data estimates future fundamental data -- neutralize by industry 
  * Model datasets vary wildly with subcategory -- try different neutralization groups
  * News impacts companies differently based on subindustry --  neutralize by subindustry
  * Options have consistent impact across industries -- neutralize by market or sector
  * Price volume ideas work for all instruments -- don't neutralize by industry or subindustry!
  * Social media impact is company-dependent -- neutralize by subindustry or industry 
  * Institution data depends on type and provider -- neutralize by sector or industry
  * Short interest -- neutralize by industry and experiment with other groups
  * Insider news is company-dependent -- neutralize by industry or subindustry
  * Sentiment is company-dependent -- neutralize by industry or subindustry
  * Earnings is like fundamentals -- neutralize by industry
  * Sector/Market/Industry are macroeconomic -- neutralize macro groups (not subindustries) 

Favor diversity -- low correlation is more important than a minor 
increase in performance
  * Submit both delay-1 and delay-0 alphas
  * Explore both USA and China -- alphas are totally uncorrelated!
  * Try ideas on TOP3000 (can be illiquid) vs TOP1000 vs TOP200 (liquid)
    * Incorporate weighting (e.g. by market cap or volume) to trade 
    low liquidity stocks less frequently.
  * Consider short-term (price-volume, news) and long-term (fundamental, 
  analyst, news)
  * Use diverse operators
  * Overfitting can reduce OS score

Increase returns:
  * Increase turnover — more trading, potentially higher returns.
  * Use lower decay (in settings)
  * Work on smaller, more liquid universes (in settings)
  * Keeping returns and drawdown constant, increase the volatility 
  * Use news and analyst datasets
  * Use fundamental data rather than price data

Popular ideas
  * Mean reversion
  * Technical indicators
    * RSI, stochastic oscillator, MACD, money flow index, Bollinger Bands
  * Accruals and cashflow
    * High accrual (change in net operating assets) is bad
    * `-delta(assets_curr - (liabilities_curr - debt_st), 60)`
  * Growth of revenue, assets, or headcount
    * `- (assets / delay(assets, 250) – 1)`
  * Inventory turnover
    * `sales / inventory`
  * Price movement and technical indicators
  * Volatility measures -- historical, implied, intraday, vol index
  * Volume's interaction with price
  * Short-term and long-term trends

Check resources like SSRN, Seeking Alpha, Wilmott, Epchan, 
AuTraSy. Read books like Active Portfolio Management by Grinold 
and Kahn.
  * Check Brain Tips series in Community forum

Need to check all alphas on USA D0, USA D1, CHN D0, CHN D1 -- free points!

### Listed alphas

1. `1/close`
2. `volume/adv20`
3. `ts_corr(close, open, 10)`
4. `open`
5. `(high + low)/2 - close`
6. `vwap < close ? high : low`
7. `Rank(adv20)`
8. `Min(0.5*(open+close), vwap)`
9. `Max(0.5*(high+low), vwap)`
10. `1/ts_stddev(returns, 22)`
11. `ts_sum(sharesout, 5)`
12. `ts_covariance(vwap, returns, 22)`
13. `1/Abs(0.5*(open+close) - vwap)	`
14. `ts_corr(vwap, ts_delay(close, 1), 5)`
15. `ts_delta(close, 5)`
16. `ts_decay_linear(sharesout*vwap, 5)`
17. `ts_decay_exp_window(close, 5, factor=0.25)`
18. `ts_product(volume/sharesout, 5)`
19. `Tail(close/vwap, lower=0.9, upper=1.1, newval=1.0)`
20. `Sign(close-vwap)`
21. `SignedPower(close-open, 0.5)`
22. `Pasteurize(1/(close-open))`
23. `Log(high/low)`
24. `group_neutralize(volume*vwap, market)`
25. `Scale(close^0.5)`
26. `Ts_Min(open, 22)`
27. `Ts_Max(close, 22)`
28. `Ts_Rank(volume, 22)`
29. `Ts_Skewness(returns, 11)`
30. `Ts_Kurtosis(returns, 11)`
31. `Ts_Moment(returns, 11, k=3)`
32. `ts_count_nans((close-open)^0.5, 22)`
33. `ts_corr(close, ts_step(1), 5)`
34. `Last_Diff_Value(sales, lookback=125)`
35. `group_rank(returns, industry)`
36. `group_mean(returns, volume, subindustry)`
37. `Ts_Regression(close, open, 20, lag =0, rettype= 2)`

5, 10 (negated), 15 (negated), 20 (negated), 32, and 34 (negated) are all good!

Other ideas from website / emails / videos 
  * `sales / assets` measures efficiency at generating revenue. Try 
  `rank(sales/assets)` with Subindustry neutralization in TOP3000.
  * Decreasing debt is good. `rank(-ts_delta(debt,90))` with Sector 
  neutralization for TOP3000 
  * Take difference in close prices between yesterday and today, hoping 
  for reversion. `-ts_delta(close, 1)`
  * Price reversion works well during high volatility or volume. 
  `-rank(ts_delta(close, 2)) * rank(volume / ts_sum(volume, 30) / 30)`

New beginner alphas
1. `signal = abs(ts_mean(close,20)/ts_mean(close,60)-1); -signal*sign(returns)`
  * TOP3000, decay 5, neutralization Market
  * Try `trade_when` to reduce turnover
2. `rank(mdf_rds)`
  * TOP3000, decay 0, neutralization sector
  * Try different neutralization
3. `fam_roe_rank * rank(sales/assets)`
  * TOP3000, decay 0, neutralization industry
  * Try different neutralization
4. `-group_rank(ts_av_diff(mdf_pec,480),subindustry)`
  * TOP3000, decay 0, neutralization none
  * Try `vector_neut(x,y)` to neutralize to one-year Information ratio.
5. `sum_vol = ts_sum(vec_sum(scl12_alltype_buzzvec), 5);`, `significance = 
vec_norm (scl12_alltype_sentvec) / vec_count(scl12_alltype_sentvec);`, 
`sent_vol = -ts_rank(sum_vol, 60);`, `sent_sig = ts_max(significance, 10);`, 
`sent_vol * group_rank(sent_sig, sector)`
  * TOP200, decay 0, neutralization none
  * Try different simulation settings
6. `zscore(ts_ir(cashflow_op/debt_st,1250))`
  * TOP3000, decay 10, neutralization subindustry
  * Try comparing ratio only for companies with positive cashflow from ops
7. `ts_av_diff(mdf_nps,500)`
  * TOP3000, decay 5, neutralization market
  * Try different neutralization
8. `pcr_oi_all`
  * TOP200, decay 5, neutralization market
  * Try different universe, increase weight with high average volume 
9. `ts_av_diff(mdf_eg3, 250) * ts_corr(mdf_eg3, mdf_sg3, 250)`
  * TOP200, decay 0, neutralization subindustry
  * Try expanding lookback period
10. `market_ret = ts_product(1+group_mean(returns,1,market),250)-1;` 
`rfr = vec_avg(fnd6_newqeventv110_optrfrq);`, 
`expected_return = rfr + beta_last_360_days_spy * (market_ret-rfr);`
`actual_return = ts_product(returns+1,250)-1;`, 
`actual_return - expected_return`
  * TOP1000, decay 5, neutralization subindustry
  * Try different simulation settings
11. `group_rank(fam_est_eps_rank, sector)`
  * TOP3000, decay 0, neutralization subindustry
  * Try different group
12. `-group_rank(ts_av_diff(mdf_pbk, 5), subindustry)`
  * TOP3000, decay 20, neutralization market
  * Try creating custom subgroups of `rank(mdf_pbk)` using `bucket` operator
  * Try using `group_normalize()`
13. `trade_when(days_from_last_change(fam_earn_surp_pct)==0, fam_earn_surp_pct *
    -returns, -1)` 
  * TOP3000, decay 0, neutralization market
  * Try smoothing
14. `zscore(cash_st/debt_st)` 
  * TOP500, decay 0, neutralization subindustry
  * Try comparing against peers rather than whole market
15. `percent = ts_rank(vec_stddev(nws12_prez_result2),50);`, 
`-ts_rank(ts_decay_linear(percent, 150), 50)`
  * TOP3000, decay 20, neutralization market
  * Try `trade_when` to lower turnover
16. `-rank(ebit/capex)`
  * TOP3000, decay 0, neutralization sector
  * Try different neutralization
17. `-ts_rank(retained_earnings, 250)`
  * TOP3000, decay 10, neutralization sector
  * Try different neutralization 
18. `sent_vol = vec_sum(scl12_alltype_buzzvec);`, 
`trade_when(rank(sent_vol)>0.95, -zscore(scl12_buzz)*sent_vol, -1)`
  * TOP3000, decay 0, neutralization subindustry
  * Try smoothing
19. `a = ts_sum(open>close, 20) / ts_sum(open<close, 20);`, 
`b = ts_sum(open>close, 250) / ts_sum(open<close, 250);`
`rank(a/b)`
  * TOP3000, decay 20, neutralization subindustry
  * Try introducing price fluctuations
