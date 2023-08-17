# WorldQuant seminar 

## Rules

Submissions can take 30Gb RAM

5 hours of runtime per week

## Data

Given 276 dates (herein, days) of training data, with ~3000 stocks per day
  * Start with ~500 stocks per day, rises to ~4000 stocks per day
  * ❗️ Cannot use lagged time-series style features! Different number of rows
    per day
  * Use `from sklearn.model_selection import TimeSeriesSplit` to split across
    days. Taking contiguous chunks could accidentally mix days

Each stock has 460 features
  * All features are normalized to Normal(0, 1)

Output variable is uniform in (-1, 1)

Evaluated on Spearman rank correlation for new days

## Tips

Some features have correlations
  * Smallest is -0.49, biggest (non-self) is 0.53
  * Distribution is skewed negative
  * Test for significance with Bonferroni correction?

All features are Gaussian -- perhaps some models work well for this?

Could build new table with feature means over all rows for a given day. This
table has the same # rows (1) for each day, so can use lag
  * Could be useful for informing daily environmental conditions 
  * Incorporate into main predictions as constraints, neutralizations, or other
    conditions
  * Some features have significant mean-autocorrelation at lag-1

Rank points directly with techniques like RankNet, LambdaRank, or LambdaMART 

Differential features including:
  * Using models trained on previous dates of the samples in current date
  * Distance to the centroid point of data in past days to points today
  * Ranking points in current day among samples of previous days
  * Closest neighbors of samples of current date to samples in past dates

Feature importance/pruning 

Feature engineering like rolling windows (from which averages, medians, and
ranges of values can be extracted) of values for different dates

Further data exploration:
  * I'm curious about correlation matrix

Data preprocessing like clustering or outlier detection to de-bias predictions

Fine-tune the loss function to something other than MSE

## Strategies tried so far

All scores are Spearman correlation coefficient

"rx" means retrain every x days

Linear model with LASSO, alpha = 0.001
  * training: 3.538
  * testing: r0 - 2.784, r2 - 2.958, r4 - 3.000, r6 - 2.979, r8 - 2.991

Linear model with Elastic Net
  * alpha = 0 (LinearRegression)
    * training: 3.591
  * alpha = 0.000001
    * training: 3.608
  * alpha = 0.0001
    * training: 3.748
    * testing: r4 - 3.278
  * alpha = 0.001
    * training: 3.734
    * testing: r4 - 3.237
  * alpha = 0.01
    * training: 2.309

LightGBM with optimized params
  * training: 2.676
  * testing: r0 - 2.549, r2 - 2.844

XGBoost with basic params
  * training: 0.851
  * testing: r0 - 1.166

CatBoost with basic params
  * training: 2.579
