# WorldQuant alphas

## Terms

Sharpe -- Average measure of risk-adjusted returns
  * Sharpe = Avg. Annualized Returns / Annualized Std. Dev. of Returns

Turnover -- Average measure of daily trading activity
  * Turnover = Value Traded / Value Held

Fitness -- Hybrid metric for overall performance. Higher is better.
  * Fitness = Sharpe * Sqrt( Abs( Returns ) / Max( Turnover, 0.125 ) )

Returns -- Annualized average gain or loss as a fraction of the invested amount.
  * Invested amount is equal to half the book size

Drawdown -- Largest reduction in PnL during a given period, as a percentage.

Margin -- Average gain or loss per dollar traded
  * PnL divided by total dollars traded in a given time period

## Alphas

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	3	1	0.05	None	On	Off	Verify
Sharpe
1.39
Turnover
17.15%
Fitness
1.11
Returns
10.87%
Drawdown
8.14%
Margin
12.67‱
```
lookback = 10;
avg_ret = power(ts_product(returns+1, lookback), 1/lookback);
comp_avg = power(ts_product(rel_ret_comp+1, lookback), 1/lookback);
a = zscore(comp_avg / avg_ret);
when = ts_rank(ts_std_dev(returns, 60), 126) > 0.55; 
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	5	1	0.1	Subindustry	On	Off	Verify
Sharpe
1.94
Turnover
44.52%
Fitness
1.35
Returns
21.66%
Drawdown
11.37%
Margin
9.73‱
```
buzz = ts_backfill(-vec_sum(scl12_alltype_buzzvec), 20);
ts_av_diff(buzz, 60)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	CHN	TOP3000	Fast Expression	3	0	0.005	Market	On	Off	Verify
Sharpe
5.03
Turnover
13.02%
Fitness
7.52
Returns
29.08%
Drawdown
7.09%
Margin
44.68‱
```
gp = subindustry;
a = rank(-mdl175_volatility * log(volume)) * (1 + group_rank(mdl175_revenuettm,gp));
#vector_neut(a, ts_mean(mdl175_02amvt, 240))
group_vector_neut(a, ts_mean(mdl175_02amvt, 50), gp)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	5	1	0.01	Subindustry	On	Off	Verify

Sharpe
1.55
Turnover
3.71%
Fitness
1.18
Returns
7.28%
Drawdown
7.11%
Margin
39.28‱
```
-ts_rank(retained_earnings,500)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP200	Fast Expression	10	1	0.01	Subindustry	On	Off	Verify

Sharpe
1.62
Turnover
2.21%
Fitness
1.52
Returns
11.06%
Drawdown
11.65%
Margin
100.21‱
```
-rank(ebit/capex)
```


Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP1000	Fast Expression	10	1	0.01	Market	On	Off	Verify

Sharpe
1.38
Turnover
2.00%
Fitness
1.35
Returns
12.04%
Drawdown
13.20%
Margin
120.20‱
```
group_rank(fam_est_eps_rank, sector)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	1	1	0.05	Market	On	Off	Verify

Sharpe
1.59
Turnover
2.79%
Fitness
1.70
Returns
14.33%
Drawdown
7.53%
Margin
102.66‱
```
a = ts_av_diff(mdf_eg3, 50);
b = ts_corr(mdf_eg3, mdf_sg3, 50);
-a * b
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP500	Fast Expression	1	1	0.01	Subindustry	On	Off	Verify
Sharpe
1.28
Turnover
1.91%
Fitness
1.15
Returns
10.17%
Drawdown
8.18%
Margin
106.23‱
```
rank(mdf_rds)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP500	Fast Expression	20	1	0.01	Sector	On	Off	Verify

Sharpe
1.42
Turnover
8.15%
Fitness
1.06
Returns
6.94%
Drawdown
4.22%
Margin
17.03‱
```
oey_growth = ts_rank(mdf_oey, 63);
oey_growth - group_mean(oey_growth, 1, subindustry)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP1000	Fast Expression	9	0	0.1	Subindustry	On	Off	Verify

Sharpe
2.03
Turnover
14.25%
Fitness
1.58
Returns
8.67%
Drawdown
3.96%
Margin
12.17‱
```
rank( ts_rank( fnd6_epsfx /close, 40) )
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP1000	Fast Expression	10	1	0.1	Subindustry	On	Off	Verify

Sharpe
1.80
Turnover
13.89%
Fitness
1.42
Returns
8.64%
Drawdown
4.48%
Margin
12.44‱
```
rank(ts_rank( ebit/sharesout /close, 40))
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP200	Fast Expression	0	1	0.01	Subindustry	On	Off	Verify

Sharpe
1.37
Turnover
2.50%
Fitness
1.09
Returns
7.89%
Drawdown
7.61%
Margin
63.22‱
```
ts_av_diff(mdf_eg3, 600)*ts_corr(mdf_eg3, mdf_sg3, 600)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP200	Fast Expression	0	1	0.01	Sector	On	Off	Verify

Sharpe
1.27
Turnover
5.99%
Fitness
1.29
Returns
12.90%
Drawdown
13.40%
Margin
43.07‱
```
zscore(cash_st/debt_st)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP500	Fast Expression	0	0	0.1	Subindustry	On	Off	Verify

Sharpe
2.02
Turnover
2.36%
Fitness
2.30
Returns
16.15%
Drawdown
6.95%
Margin
136.98‱
```
-rank(ebit/capex)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP1000	Fast Expression	0	1	0.01	Sector	On	Off	Verify

Sharpe
1.62
Turnover
1.50%
Fitness
1.70
Returns
13.72%
Drawdown
6.95%
Margin
183.03‱
```
-rank(ebit/capex)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	0	1	0.01	Market	On	Off	Verify

Sharpe
1.45
Turnover
1.42%
Fitness
1.18
Returns
8.31%
Drawdown
4.89%
Margin
116.89‱
```
fam_roe_rank*rank(sales/assets)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	0	0	0.1	Subindustry	On	Off	Verify

Sharpe
2.58
Turnover
26.63%
Fitness
1.70
Returns
11.62%
Drawdown
2.99%
Margin
8.73‱

```
-ts_zscore(enterprise_value/ebitda,63)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	30	1	0.01	Subindustry	On	Off	Verify

Sharpe
1.84
Turnover
8.99%
Fitness
1.08
Returns
4.29%
Drawdown
1.93%
Margin
9.55‱
```
avg_news = vec_avg(nws12_afterhsz_sl);
rank(ts_sum(avg_news, 60)) > 0.5 
    ? 1
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	0	1	0.08	Subindustry	On	Off	Verify

Sharpe
1.35
Turnover
2.17%
Fitness
1.57
Returns
16.83%
Drawdown
17.79%
Margin
154.75‱
```
ts_av_diff(mdf_nps,500)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	8	1	0.01	Sector	On	Off	Verify
Sharpe
1.75
Turnover
24.34%
Fitness
1.19
Returns
11.26%
Drawdown
5.04%
Margin
9.26‱
```
group_zscore( ts_zscore(mdf_gry, 20), sector )
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	0	1	0.1	Subindustry	On	Off	Verify

Sharpe
1.79
Turnover
14.71%
Fitness
1.24
Returns
7.10%
Drawdown
6.82%
Margin
9.65‱
```
ts_zscore(mdf_oey, 250)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	1	1	0.01	Industry	On	Off	Verify

Sharpe
2.00
Turnover
25.32%
Fitness
1.26
Returns
10.10%
Drawdown
3.77%
Margin
7.98‱
```
-ts_zscore(enterprise_value/ebitda,63)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP500	Fast Expression	0	1	0.01	Market	On	Off	Verify

Sharpe
1.44
Turnover
1.52%
Fitness
1.36
Returns
11.10%
Drawdown
12.14%
Margin
145.75‱
```
-Last_Diff_Value(sales, lookback=125) * rank(vwap)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	20	1	0.01	Market	On	Off	Verify

Sharpe
1.25
Turnover
18.36%
Fitness
1.10
Returns
14.27%
Drawdown
11.55%
Margin
15.54‱
```
-delta(close, 5)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	10	1	0.01	Market	On	Off	Verify

Sharpe
1.80
Turnover
51.95%
Fitness
1.03
Returns
17.13%
Drawdown
8.75%
Margin
6.60‱
```
(high + low)/2 - close
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP200	Fast Expression	10	1	0.05	Market	On	Off	Verify

Sharpe
1.58
Turnover
49.64%
Fitness
1.09
Returns
23.76%
Drawdown
10.30%
Margin
9.57‱

```
decay_days = 1;
rel_days_since_max = rank(ts_arg_max(close, 30));
decline_pct = (vwap - close) / close;
decline_pct / min( ts_decay_linear(rel_days_since_max, decay_days), 0.15)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	10	1	0.01	None	On	Off	Verify

Sharpe
1.40
Turnover
9.68%
Fitness
2.86
Returns
52.02%
Drawdown
55.18%
Margin
107.45‱
```
change_day = (vwap - close) / close;
ts_decay_exp_window(rank(change_day), 4)
```

Instrument Type	Region	Universe	Language	Decay	Delay	Truncation	Neutralization	Pasteurization	NaN Handling	Unit Handling
Equity	USA	TOP3000	Fast Expression	10	1	0.01	Subindustry	On	Off	Verify

Sharpe
1.92
Turnover
48.92%
Fitness
0.99
Returns
13.01%
Drawdown
8.25%
Margin
5.32‱
```
decay_days = 2;
rel_days_since_max = rank(ts_arg_max(close, 30));
decline_pct = (vwap - close) / close;
decline_pct / min( ts_decay_linear(rel_days_since_max, decay_days), 0.20)
```