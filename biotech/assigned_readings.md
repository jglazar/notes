# Assigned readings for PBG competition

## Valuation methods in early-stage biotech

Considering private biotech in seed stage or 1/2 round of funding.

Terminal value: a company's worth when the investor can finally sell.
  * Must discount back 5-7 years, plus add risk.

Must predict capital needs for use in scientific/clinical/commercial 
developments.

Capital structure: who owns what and via what securities/instruments

Dilution: impact of new capital infusions on ownership pct

### Problem setup

Assume $100M is spent in the following way:
  * $10M for financing of preclinical/IP/core mgmt team 
  * $10M for Phase 1, $10M for Phase 2A, $20M for Phase 2B, $50M for 
  phase 3A

Company is then acquired for $250M.
  * In real world, company would likely go public or enter strategic 
  alliance before this step.

Assume:
  * Expected rate of return = 50% per year. 
    * Realistically, use lower rate in later rounds or when risk is lower.
  * Sell shares at year 5.
  * There are 4 additional rounds of financing prior to exit, each with 
  dilutive impact of 20% over prior round.
  * Current ownership is 2M shares.

**How much ownership (as pct or shares) is needed to meet return 
expectations at exit time?**

### Solution

1. Determine terminal value
  * Assumed $250M
2. Calculate discounted terminal value (DTV)
  * $250M / (1.50)^5 = $32.925M
3. Required ownership at exit (RFP), assuming no additional financing
  * Investment / DTV = $10M / $32.925M = 30.4%
4. Determine new shares, allowing for additional rounds
  * Shares at end = current shares / (1-RFP) = 2.873M, so additional shares 
  = 873k
  * Allowing additional rounds: retention ratio = % retained after 4 rounds 
  with 20% dilution each = 1.2^-4 = 0.482
  * Current ownership = RFP / RR = 63.1%, or 2M / (1-0.631) = 5.42M shares 
  total or 3.42M additional shares issued.
5. Share price
  * No dilution: investment / new shares = $10M / 873k = $11.45 per share
  * With dilution: investment / new shares = $10M / 3.42M = $2.95 per share
6. Pre-money (before capital infusion) and post-money (after capital 
infusion) values of company. Pre = Post - new capital
  * No dilution: Total shares * price per share = 2M * $11.45 = $22.9M, 
  plus $10M = $32.9M
  * With dilution: Total shares * price per share = 2M * $2.95 = $5.9M, 
  plus $10M = $15.9M

So dilution degrades pre-money value from ~$23M to ~$6M, a ~4-fold drop!


