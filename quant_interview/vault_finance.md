# Vault Guide to Quant Finance

## Bonds

Bond = contract to provide scheduled payments 
  * bonds are > 1 year, bills are < 1 year

Yield curve gives sensitivity to interest rates

Bonds converge to "par value" at maturity, so volatility decreases w.r.t. 
time
  * risks include default, basis, credit, interest rate, and yield curve

Credit rating negatively correlates with cost of credit
  * issued by Moody's, S+P, or Fitch
  * downgrades can drop rating below investor cutoff, leading to selloff

Pn = P0 * ( 1+r/n )^n tends to P0 * exp(rn). Working backwards gives 
P0 = Pn * ( 1+r/n )^-n which tends to Pn * exp(-rn)

### Coupon payments

Bonds give consistent "coupon payment" of some percentage of principal 
per year until expiration. They give back the principal at the end.

P0 = 8 * (1+r)^-1 + 8 * (1+r)^-2 + ... + 108 * (1+r)^-10 = 87.7. 
So this bond in total is worth 87.7 dollars today.

General formula is `PV = sum from 1 to n ( CFi / (1+r)^i ) + P/(1+r)^n`
  * CFi is the cash flow (payment) at year i and r is the discount rate 
  (interest rate for money in savings acct, high-yield treasuries, etc.)
  * Technically, interest rate can change too, so r --> ri (prevailing 
  discount rate).
  * If `CF = CF0 * (1+g)^n`, then PV tends to CF0 / (r-g)

Shortcut -- Subtract (final term * infinite series) from infinite series, 
then add in principal repayment.
  * `PV = C/r - C/r * 1/(1+r)^n + P/(1+r)^n`

Annuity has constant CFi, as above. Perpetuity takes n to infinity, 
so sum converges to CF / r

Can model perpetual debt or constant dividends (r = "hurdle rate")

### Yield curve

Discount/par/premium bonds are worth less/equal/more than principal 
because coupon interest rate is lower/same/higher than discount rate

Yield curve gives discount rate ri as a function of time-to-maturity 
("tenor"). Just plug in these values as ri in PV calculation.

Yield of the bond = average r needed to match PV of yield-curve-calculated 
bond to PV of constant-r bond
  * Gives fair comparison between bonds with different coupon rates AND 
  maturities
  * Inversely related to bond price. 
  * Yield converges to par at maturity, or ri -> 0 at t = 0

Yield curve normally increases w.r.t. time because long-term interest rates 
are better than short-term ones, and locking up money in bond is risky due 
to possible interest rate hikes (good for savings account, bad for bond) 
or negative event happening to bond provider.

### Taylor Series

Useful for bond pricing w.r.t. yield if we know value of pricing function 
and its derivatives at one (yield) point and want to estimate the 
function's value at another (yield) point.

Multivariate case: df = df/dx dx + df/dy dy + 1/2!( d2f/dx2 dx^2 + 
d2f/dy2 dy^2 + 2d2f/dxdy dxdy ) + ... use Pascals Triangle to get combos

First derivative of bond's PV(r) w.r.t. r is `( sum (i * CF / (1+r)^i) + 
n * P / (1+r)^n [principal payback]) * -1/(1+r)`. 
Stated another way, `1/P * dP/dr = -1/(1+r) * Dmac` where Dmac is the 
Macauley Duration, or 1/P * dP/dr = -Dmod where Dmod is the 
Modified Duration.
  * Positive duration means increasing yield causes decreasing price. 
  * Some special fixed income investments actually have negative duration!
  * Units of duration are time, with scale set by coupon payment interval
  * For zero-coupon bonds, Dmac = n which is typically higher than normal

Bond price vs. yield graph is actually convex up, so above linear 
approximation underestimates prices at higher or lower yields
  * Error tends to be worse at low yields

So deltaP = -P * Dmod * deltaR + 1/2 * C * deltaR^2 where C is dollar 
convexity = `sum( i * (i+1) * CF/(1+r)^(i+2) ) + 
n * (n+1) * P / (1+r)^(n+2)`

Can use finite differences to approximate 1st and 2nd derivatives of P(r) 
and calculate effective duration and effective convexity (for deltaP/P)
  * dP/dr = ( P(r+dr) - P(r-dr) )/2dr
  * d2P/dr2 = ( P(r+dr) - 2P(r) + P(r-dr) ) / dr^2

### Portfolio management

Bullet portfolio = bond maturities all concentrated around 1 point on 
yield curve

Barbell portfolio = bond maturities at short and long term only

Portfolio duration = linear weighted average of holdings

Duration measures interest rate risk, which applies to uniform curve shifts. 
Duration and convexity cannot model yield curve risk, which applies to 
non-uniform curve shifts.
  * Tracking key rate durations (price sensitivity to changes at specific 
  points on the yield curve) can help model non-uniform curve shifts

## Statistics

Lognormal distribution describes many financial variables. Its pdf is 
`1/sqrt(2pi sigma^2 x^2) * exp( -1/2 * (ln(x) - mu)^2/sigma^2 )` for x>0.

Equity prices/returns tend to be fat-tailed. Use truncated Levy dist 
or t-dist with few degrees of freedom instead of Normal dist.

Convert annual std dev to daily by dividing by sqrt(250) for 250 
trading days. Variances and expectation values scale linearly.

CAPM regresses return on std dev (volatility)

Fund performance regressed on market performance F = a + b * market 
typically yields insignificant a but significant b.

High autocorrelation --> use autoregression model Yt = a + b * Y(t-1) + 
error(t) or Yt - mu = b( Y(t-1) - mu) + error(t) where mu = a/(1-b)
  * Mean reversion if 0 < b < 1
  * Oscillation if -1 < b < 0
  * Random walk if b = 1 or b = -1
  * Explosive series if b > 1 or b < -1

Stock returns may be defined in relative terms: R = (Pi - P(i-1))/P(i-1) 
= Pi/P(i-1) - 1. 
  * R = log(Pi/P(i-1)) because Taylor expansion of log(x) around x=1 is  
  log(1) + (x-1) + ... so log(Pi/P(i-1)) = Pi/P(i-1) - 1 = R ✅

Q: Fund claims to beat market by 2% for 10 years while market has std 
dev = 20%. Evaluate this claim.
  * Test significance of f - m =/= 0. We know f - m = 2, Var(m) 
  = 400, and n=10. Assume Var(f) also = 400. So Var(f - m) = Var(f) + 
  Var(m) - 2 * corr * sqrt( Var(f) Var(m) ). Std error is 
  sqrt( Var(f - m) ) / sqrt(n). We need 2 * std error < 2 for significance. 
  This would require very high correlation = 0.9875 with the market. 
  * Need n > 10 for better significance. But over 20+ years, the fund's 
  claim likely neglects failed funds and changed objectives.

## Derivatives

Also called contingent claims. Can be bought on exchanges or tailored in 
over-the-counter transaction.

Can transfer risk (hedge), express view (speculate), or exploit profit 
opportunities (arbitrage)

### Forwards

Agreement to make trade at some future date. Traded over-the-counter only.

Seller wants to lock in price now to remove risk of price drop (price 
risk). Buyer speculates that price will be higher in the future.
  * Shifts price risk from seller to buyer.

Creditworthiness is big factor due to illiquidity and delayed payoff.

Examples 
  * buying/selling on eBay
  * shorting -- undercut Amazon bookseller because local 
  bookstore offers cheaper price. If someone purchases, you procure book 
  at cheaper price and sell at your price.

Use no-arbitrage argument to value forward price
  * Reverse cash and carry -- forward price is too low, so short the 
  underlying at the spot (current) price, then put proceeds into bank at 
  risk-free rate, then buy forward contract to cover short. Total cash 
  flow at maturity is (spot price) * exp(rt) [due to interest] - (forward 
  price). This must equal zero.
  * Cash and carry -- forward price is too high, so borrow money at 
  risk-free rate, then buy the underlying at the spot price, then sell 
  forward contract. Total cash flow at maturity is (forward price) - 
  (spot price) * exp(rt) 

Spot price and forward price must converge for vanishing maturity time

Profit as function of price at maturity is linear, with P = 0 at 
forward price

Cost of carry due to storage or insurance
  * Add carry cost to spot price in above arb-free formula.

Dividends can be invested in bank
  * One-time: add d * exp(T-tdiv) to cash and carry
  * Multi-time: add sum( d * exp(T-ti) ) to cash and carry
  * Continuous: reduce interest rate from r to (r - d)

Pros are custom tailoring and no up-front costs. Cons are illiquidity, 
unobservable price due to OTC trading, counterparty credit risk, and no 
clearinghouse to monitor/regulate trades.

### Futures

Fixes illiquity and credit risk issues of forwards using clearinghouse 
as middleman. Requires initial margin and maintenance margin.

Marking to market evaluates positions at end of each day and transfers 
cash into/out of accounts, like closing position and then establishing 
new one. Prevents defaults.

Clearinghouse can help you cancel a contract by buying/selling the 
opposite end with same underlying and maturity.

Interest rate parity requires balance between exchange rates and interest 
rates to avoid arb.
  * F * (1+rf)^t = P * (1 + rd)^t, where F = forward exchange rate, P = 
  present exchange rate, rf = foreign interest rate, rd = domestic interest 
  rate.
  * F * exp(rf t) = P * exp(rd t) for continuously compounding interest
  * Cash and carry: borrow domestic at spot * exp(-rf t) [discount to 
  present] to buy foreign at exp(-rf t), then invest foreign to gain 
  1 unit at maturity, then sell futures contract to remove that foreign 
  unit, then return borrowed money at spot * exp((rd - rf) t). Total 
  domestic cash flow is F - spot * exp( (rd - rf) t)
  * Good table design has transaction as rows and start-domestic, 
  start-foreign, end-domestic, end-foreign as columns. Sum of 
  end-domestic is profit and other columns should sum to zero.
  * Foreign interest rate acts like continuous dividend

Implied risk-free interest rate found by 1/t * log( F/(spot + carry) )

### Swaps

Agreement to exchange assets. Includes interest rates, currencies, equities, 
and commodities. 

Can transform liabilities to better match assets, borrow cheaply in 
different market, or gain exposure to a market.

E.g., financing companies (Ford, GE) borrow at low interest rate and sell 
loans at high interest rate.
  * Risk 1: mismatch between maturities, so sold loans may not consistently 
  bring in required revenues (loan rates could drop!) 
  * Risk 2: basis risk occurs when buying benchmark and selling benchmark 
  diverge over time, leading to inconsistency between revenue and debt
  * Benchmarks include LIBOR (London banks' interest rates)
  * Fixed-fixed interest rate swap trades revenue for fixed payment 
  with maturity matching debt's
  * Pay-fixed receive floating interest rate swap trades debt for floating 
  debt that tracks benchmark rate

Swaps help remove interest rate risks by providing guaranteed sources of 
revenue or debt

### Options basics

Derivative on underlying like stock, index, currency futures, commodity, 
or interest rate.

Buyer has right but not obligation (unlike forward/future), 
seller has obligation. Useful for speculation, hedging, and arbitrage.

Specify direction, time, and value of expected move.

Costs "premium" upfront. Provides leverage. Price depends on value of 
underlying and price's path over time.
  * Need model for dynamics of underlying, not just current price and 
  risk-free interest rate (like for forwards/futures)

Call profit is max( S-K-P, -P ) where S = spot price, K = strike price, 
P = premium
  * Premium raises effective strike price from K to K + P

Put profit is max( K-S-P, -P )
  * Premium lowers effective strike price from K to K - P

European options may only be exercised at expiry, but you can execute 
the reverse trade or sell the option to close the position any time.

American options can be exercised any time before expiry. Thus, American 
options are worth more than European. 

Euro options can be priced with Black-Scholes. American options must be priced numerically with MC, trees, 
or finite difference methods

Options have intrinsic value (if you sold now) and time value due to 
volatility of the underlying.
  * Out-of-the-money options purely have time value.
  * Time value decays exponentially w.r.t. time

Option price should correlate strongly with underlying price. Can cross-hedge 
if no perfect-correlation option found.

Put-call parity demands no-arb: S + p - c = K * exp(-rt) 
  * Borrow strike [discounted to present] to buy the underlying, 
  buy a put, and sell a call. Total at end = 0.
  * If K * exp(-rt) > S + p - c, then borrowing at strike gives you 
  extra money. Profit by trading this strategy. Can borrow (S+p-c) 
  then pay back (S+p-c) * exp(rt) and make K to profit.
  * If K * exp(-rt) < S + p - c, then borrowing at strike doesn't fully 
  cover expenses, so you'd lose money. Profit by reversing the trade. Sell 
  portfolio and put S + p - c into bank to collect (S+p-c) * exp(rt), then 
  take K loss at end to still profit.

Put-call parity allows you to create synthetic puts, calls, longs, and 
investments. Just solve eqn. to isolate desired product and trade 
corresponding products, with negative sign indicating selling and 
positive sign indicating buying.

### Options strategies

Naked puts/calls are selling puts/calls without owning the underlying. 
Profit chart is negative of puts/calls. Gain guaranteed premium, but 
exposed to unlimited (and leveraged) downside.

Straddles are simultaneous put + call. Profit chart looks like V. Can 
sell put + call to create naked straddle with unlimited downside for 
large positive or negative moves.

Spreads in time (calendar) or strike price (bull, bear, box, condor, 
butterfly, strangle). Buy at (k1, t1) but sell at (k2, t2) to help 
cover cost. Limits possible profits but decreases effective premium.

Cap/floor sets max/min interest rate set to track benchmark.

Collar is similar to bullish call spread, but buy put at k1 and sell call 
at k2. Max profit is k2 - S and max loss is S - k1. Useful if you own the 
underlying, as you create _ / - type price graph

Swaptions are options on swaps. E.g., option to swap for receiving fixed 
interest and paying floating interest. If interest rates rise, you can 
exercise to get higher fixed rate. Otherwise, you can let it expire.

### Options valuation -- Black-Scholes

Black-Scholes models price of derivative which depends only on underlying 
price and time-to-expiry. 
  * `dV/dt + 1/2 sigma^2 S^2 d2V/dS2 + r S dVcorresponding interest path - r V = 0`

Assume underlying has random walk `dS = a dt + b dz`, where dz is 
std normal (so b^2 is variance and b is std dev) and a gives drift. 
a and b can be a(x,t) and b(x,t), which yields generalized Ito process.

Change above to reflect random walk in **relative** return `dS/S = mu dt + 
sigma dz`. This comes from forward model S = S0 * exp(mu t). Recall 
logarithmic return Taylor expansion above.
  * Assumes constant sigma, so chance of realizing percentage return is 
  same for $1 per share as $100 per share (not super realistic) 
  * dS/S is normally distributed with mean mu and std dev sigma
  * This yields log-normal returns after time t. Can discretize and 
  simulate dS/S by sampling from normal distribution with mean mu and 
  std dev sigma / sqrt(12) [for 12 months per year, e.g.]. Then advance 
  to S + dS/S * S

Apply Taylor expansion for V(S, t) to get `dV = dV/dS dS + dV/dT dt + 
1/2( d2V/dS2 dS^2 + d2V/dt2 dt^2 + 2 dV/dS dV/dt dS dt )`
  * `dS^2 = mu^2 S^2 dt^2 + sigma^2 S^2 dz^2 + 2 S^2 mu sigma dt dz`
  * But dz ~ sqrt(t), so we ignore dt^2 and dt sqrt(dt) terms to simplify.
  * This yields `dV = ( mu S dV/dS + 1/2 sigma^2 S^2 d2V/dS2 + dV/dt ) 
  dt + sigma S dV/dS dz`. We can now simulate option prices with 
  discretization!
 
Create portfolio with V and -delta * S. This has dP = dV - delta dS, which 
contains dt term and dz term. Force dz term to zero if delta = dV/dS.
  * Next, invoke no-arb by investing P * exp(rt) in risk-free account, 
  so dP = P * r * dt. Equating dP = dP yields final Black-Scholes model.

Assumptions of Black-Scholes: can borrow/lend at risk-free rate r, may 
short-sell, sigma is constant, no friction/transaction costs, European 
options, no dividends.
  * Continuous dividend (index, e.g.) is modeled by reducing interest 
  rate to effective interest rate (r-d) for r S dV/dS term 
  (but not rV term!)
  * Foreign currency also acts as reduced interest rate (r-rf)

Two boundary conditions for S and one for t: Call at expiry is worth 
V = max(S-K, 0). This yields `V = S N(d1) - K exp(-rt) N(d2)` where N is 
std Normal cdf, `d1 = 1/(sigma sqrt(T - t)) * ( ln(S/K) + (r + 
1/2 sigma^2)(T-t) )`, `d2 = d1 - sigma sqrt(T-t)`
  * sigma and r are annual, T is expiry, t is current time
  * Solve for put with put-call parity relationship -- p = K exp(-rt) - 
  S + c
  * S changes to S^(-d t) for continuous dividend (but only for outermost 
  term, not in d1 or d2). d1 has r --> r - d

Can use Black-Scholes to value options or infer implied volatility sigma
  * Assume r = T-bill rate, sigma = historical volatility
  * Good for modeling at-the-money options. 
  * Volatility smile = graph of IV vs. K shows deep in- or out-of the 
  money options tend to be overvalued (high IV). This disproves 
  Black-Scholes assumption of log-normal returns and constant volatility. 
  Luckily, volatility tends to mean-revert.

### Options valuation -- trees

Construct Markov chain where option can increase or decrease (binomial), 
or increase/decrease/stay (trinomial). 
  * Stock price can increase to S * gain or decrease to S * loss. 
  * Tree resembles Pascal's Triangle where center node at odd-number 
  levels is constant stock price.
  * Symmetry due to constant sigma. Time-dependent sigma is appropriate 
  for fixed-income securities, which leads to drift/asymmetry.

Ensure mean and variance follow dS = mu S dt + sigma S dz by setting 
gain = exp(sigma sqrt(t)), loss = 1/gain, P(gain) = ( exp(rt) - 
loss )/(gain - loss), P(loss) = 1 - P(gain).

Asymmetric gain and loss amounts and probabilities lead to dynamic 
programming-style calculation

Construct underlying price probability tree moving forwards, then price 
option using max(S-K, 0) at each node, then work backwards using 
transition probabilities and discounting s.t. 
`Vij = exp(-r deltaT) * ( P(gain) * V(i+1)(j+1) + P(loss) * 
V(i-1)(j+1) )`. This finally yields present value of option.
  * Increase accuracy by decreasing deltaT timestep
  * Feels like backpropagation in neural networks

Can implement discrete dividends, path-dependent options, and American 
options
  * American -- at each backpropagation step, compare option value Vij 
  to intrinsic value alone. Just replace option value with max( European, 
  intrinsic ) at each i,j cell to get American option value!

### Options valuation -- finite differences

Discretize S - t space, plug in initial conditions, then step through 
PDE using finite difference equations.
  * Can discretize space to cluster points around interesting region, or 
  uniformly discretize.
  * Can change rij and sigmaij over time to model volatility shocks, e.g.

Implicit finite difference eqn is `ai V(i-1)j + bi V(i+1)j + ci Vi(j+1) 
= Vi(j+1)` where ai, bi, and ci are given in terms of sigma^2, deltaT, 
deltaS, r, Smin and S's position i.

Boundary conditions 
  * V(Smax) = S, V(Smin) = 0 for call
  * V(Smax) = 0, V(Smin) = K for put. 
  * No time value at expiry, only intrinsic value

Each step backwards from boundary conditions solves Ax = b where A is 
n * n tridiagonal with ai, bi, ci values. Can invert once and store 
for repeated application.
  * Special inversion methods exist, like LU factorization

Need to evaluate optimal strategy at each i,j point for American options. 
Compare European "option alive" value to immediately exercising "option 
dead" value and pick bigger value.

Can try explicit rather than implicit formulation if you assume derivatives 
are constant over interval deltaT. This gives `Vij = di V(i-1)j + 
ei Vi(j+1) + fi V(i-1)(j+1)` and may be quickly backsolved once di, ei, 
and fi are calculated.
  * Very sensitive to deltaT and deltaS -- can lead to negative probabilities. 
  * Can use ln(S) instead of S to improve numerical stability.

### Options valuation -- Monte Carlo

Generate random paths for asset using lognormal random walk. Evaluate 
option value at end of each path. Compute average value, then discount 
to present with exp(-rt).

Can implement path-dependency e.g. American options or barrier options

Take f = log(S), so df/dS = 1/S and d2f/dS2 = -1/S^2. Then Black-Scholes 
precursor gives `df = sigma S 1/S dz + ( mu S 1/S + 1/2 sigma^2 S^2 
(-1/S^2) ) dt = (mu - sigma^2 / 2) dt + sigma dz`.

Integrating above expression gives f(t) = S0 exp( (mu - sigma^2 / 2) t + 
integral from 0 to t of sigma dz ). For small time interval the mini-integral 
evaluates to sigma * sqrt(t) * N(z).

### Greeks

dV/dS = delta = N(d1), so graph of delta vs. S has sigmoid shape.
  * Delta is sensitive near the money, but not deep in or out.
  * Delta ~ 0.75 at the money
  * Put-call parity requires dV/dS = delta = N(d1) - 1. Just shift above 
  sigmoid shape down by 1.
  * Tack on exp(-d t) coefficient to account for continuous dividend
  * Actual derivation is quite ugly but works out simply!

d2V/dS2 = gamma = exp(-d t) N'(d1) / ( sigma S sqrt(t) ) 
  * N'(x) is just std normal pdf
  * Put gamma = call gamma.

dV/dr = rho = K t exp(-r t) N(d2)
  * Put rho negates K and d2

dV/dt = theta = ugly looking expression
  * Put theta negates two terms

dV/dsigma = vega = S sqrt(t) exp(-d t) N'(d1)
  * Put vega = call vega

### Exchange traded options

Options of futures given by Black's model: 
  * recall that future must have F = S exp(rt), and dS/S = mu dt + 
  sigma dz. 
  * Then sigma of future = 1/F sigma S dF/dS = 1/F sigma S exp(rt) = 
  sigma of underlying
  * Thus, `dF/F = muF dt + sigma dz`.

Options on futures are convenient bc they're never settled in physical 
delivery of the underlying, just cash.

Construct portfolio long a units of futures and short one option 
s.t. P = a - V and dP = -dV + a dF. Note that P = -V at startup because 
futures have no value at start.

Use dV Taylor expansion like Black-Scholes precursor then collect terms 
to eliminate dz term, requiring dV/dF = a.

Next, invoke no-arb to construct dP = P r dt and rearrange equality to get 
`dV/dt + 1/2 sigma^2 F^2 d2V/dF2 - rVdt = 0`. This is like dividend rate 
= interest rate.

Put-call parity gives F exp(-rt) + p - c = K exp(-rt), so put and call 
prices are identical if F = K.

Eurodollars (USD in foreign banks) future contract is 3-month LIBOR 
received over 3 months on $1MM deposit. Price constructed s.t. 
LIBOR3 + F = 100, so you can estimate implied expected LIBOR3 from price.
  * Contract value = 10,000 * (100 - 0.25 * LIBOR)
  * LIBOR down 1 basis point --> contract up $25
  * Contract prices correlate positively with bond prices, negatively with 
  interest rates

EDF call gives right to enter EDF contract with specified strike K and 
maturity T
  * EDF call = LIBOR put

Treasury bonds/notes also have futures and options on those futures

TED spread uses combo of EDF and Treasure futures. Spread provides measure 
of relative credit quality bt US Treasuries and intl banks.

### Exotic options

Difficult to price, and tend to be traded only OTC

Binary call/put profit graph looks like Heaviside step function. Cheaper 
than European option.

Compound options are options on options. Black-Scholes still applies, just 
break time into (0,T1) and (T1,T2) then evaluate max( V(S,T1) - K1, 0 ) 
to decide to exercise or not.

Barrier options are contingent upon underlyring breaking chosen price 
barrier at some point. Need path-dependent valuation calculation like 
Monte Carlo.

## Fixed Income

S and P has BBB, A, AA, AAA ratings = investment grade. BB, B, CCC, CC, C, 
R (regulatory supervision), SD, and D (default) are speculative. Ratings 
are updated quarterly.

Bonds are highly sensitive to interest rates

Treasury bills, notes, and bonds are sold at auction.
  * T-bills have < 270 days to maturity, converge to par at maturity, and 
  pay no interest (zero coupon). `Price = face value * (1 - ask/100 * 
  time/360)`. Weirdly, bid > ask.
  * Treasury notes/bonds are coupon-bearing, with maturities 2-10 years/
  10+ years

Agency bonds from Federal Home Loan Mortgage Corporation (Freddie Mac), 
Government National Mortgage Association (Ginnie Mae), Federal National 
Mortgage Association (Fannie Mae), Federal Farm Credit Bank, and Student 
Loan Marketing Association (Sallie Mae) help provide liquidity to certain 
markets.

Municipal bonds are issued by state/local governments. Exempt from federal 
and (maybe) state/local taxes. Equivalent yield = Muni yield / (1 - 
tax bracket), so higher tax brackets get better benefit.

General obligation bonds are issued based on taxes (real estate, cigarettes).

Revenue bonds are issued based off anticipated revenue from tolls, e.g.

Corporate bonds raise capital for company. Implied probability of default 
from (risk-free rate) = (risky rate) * p - 100 * (1-p)

Mortgages/auto loans are amortized, wherein customers pay on interest AND 
principal. These loans can be pooled into tranches and sold off.
  * Biggest risk is prepayment. If interest rates lower, then bond holders 
  need to invest during those low interest rates
  * Extension risk is opposite -- raising interest rates encourage borrowers 
  to extend their loan at lower rate.

Coupon reinvestment rate risk -- coupon payments need to be reinvested 
at lower interest rates if rates are dropping.

Zero-coupon bonds avoid coupon reinvestment rate risk but have higher price 
risk. Also can have tax disadvantages.

Floating rate bonds are pinned to a benchmark like LIBOR

Callable bonds may be called away from the investor if rates drop enough.
  * Similar embedded options cannot be priced simply with discounted 
  expected future cash flows
  * Generally grants higher coupon than non-callable bonds

Putable bonds may be put back to the company if rates jump high enough.
  * Insurance for investor causes higher price. 

Convertible bonds may be converted into equity.

Purchasing bond needs to factor in invoice price = accrued interest up to 
purchase day. E.g., 60/180 * $50 for buying bond 60 days into semi-annual 
coupon payment of $50.

### Bond pricing

Par means coupon = yield, discount means coupon < yield, premium means 
coupon > yield. Price is inversely proportional to yield.

Stated yield = coupon as percentage of principal =/= ultimate yield 

Current yield = coupon as percentage of price

Yield to maturity = single discount rate that reproduces yield-curve- 
calculated price

Duration given by 1/P dP/dr = -Dmod = Dmac * -1/(1+r)

Key rate durations help evaluate price changes due to non-uniform yield 
curve shifts

Use bootstrapping to evaluate forward rates, which are expected yields 
in the future
  * 6 month price = $99, 1 year price = $98. Coupon is 6% annually. 
  This implies 103/(1+x/2) = 99 --> x = 8.08% for 6-month spot rate. 
  Then 3/(1+0.0808/2) + 103/(1+x/2)^2 = 98 --> x = 8.12% for anticipated 
  6-month spot rate in 6 months.
  * Can repeat above process to go further out in 6-month increments.

Spot rate is yield of zero-coupon bond with certain maturity. 
  * Acts like yield curve from beginning of book (?)

Par yield is yield of bond selling at-par (yield = coupon)
  * Can use par yield to calculate spot yield using bootstrapping

Typically, par curve is below spot curve, which is below forward curve.

Market expects interest rates to rise --> yield curve slopes upwards.

### Derivatives

Bootstrapping routine above can be packaged into discount factors for 
each time period 6m, 1y, 1.5y, 2y, ...
  * dfn = P - C * sum from 1 to n-1 ( dfi ) / (100 + C)
  * df can be used to derive spot rate r, or vice versa
  * Spot rate ri = 2 * ( dfi^(-0.5/i)  - 1 ) 
  * Forward rate mFn (implied m-year rate in n years) is simply dfm/dfn

Use backward induction and binomial trees to value bonds with embedded 
options

Simplified Black-Derman-Toy assumes constant interest rate volatility. 
Estimate interest rate evolution using spot rates and interest rate 
volatility using current yield curve. Construct binomial tree ending 
at par, using backward induction to price back to present. Can edit nodes 
to max out at calling value, e.g.
  * Value of callable = value of normal - value of call option

Can similarly model interest rate caps and floors, swaps, swaptions...

### Mortgage backed securities

Mortgages are amortized (some payment goes to principal) and can be fixed 
or floating rate.

Interest rate risk (refinancing at lower rate) and prepayment risk (which 
negates lots of interest) are bad for bank

Prepayment can be quantified as constant prepayment rate (annual principal 
repayment) which is typically modeled by assuming a linear ramp to 6% then 
a constant 6%.

Mortgage payments are passed through to investor, minus some charges from 
bank.

Collateralized mortgage obligations prioritizes payback in tranches.
  * Help distribute prepayment risk, with more risk going to earlier tranches 
  * Residual tranche weirdly has negative convexity, because higher interest 
  rates will decrease prepayments

Interest-only strips only collect interest payments. Starts high and ends 
low. Principal-only strips only collect principal payments. Starts low and 
ends high.
  * Principal-only benefits from lower interest rates due to less 
  discounting (as with any bond) and increased chance of refinancing 
  which lowers the bond lifetime.

Valuation is difficult due to path dependency, no par value, and implicit 
call option. Use MC or non-recombining trees.

Non-recombining trees can model refinancing
1. Calculate fixed mortgage payment
  * Consider principal = price and payment = coupon to find payments
2. Develop interest rate paths
  * Binary tree due to non-recombination (up down =/= down up)
  * Apply function at each node 10 * ( max(y-rt, 0) + max(r(t-1)-rt, 0) )
3. Create prepayment tree based on model
  * If no refinancing, then normal payment applies
  * Refinancing requires cash flow of remaining principal * (1 + old rate)?
  * Remove these people from the mortgage pool at the end of the total time
4. Discount cash flows and calculate weighted average of present values
  * Discount along corresponding interest path 

## Equities

Price is the discounted cash flow of expected future earnings.

Efficient market hypothesis -- future prices are random
  * Weak -- prices include all publicly available data
  * Semi-strong -- prices include all trading and fundamental data
  * Strong -- prices include all public and private data. Only new data 
  (which is random) can impact the price

Dividend discount model discounts future flow of dividends by cost of 
equity capital to get the current price. P = D / r like a perpetuity.
  * Estimate cost of equity capital (r) using CAPM, or asking management 
  about their hurdle rate (minimum return)

Gordon growth model predicts that dividend will grow with rate g. P = 
D * (1 + g) / (r - g)

Two/Three-stage dividend discount model and H Model take account of slowing 
and finite company growth. Use multiples analysis to value companies that 
don't pay a dividend

### Multiples analysis

Price / earnings compares companies based on net income per dollar invested.
  * Gordon growth model can use payout ratio K (fraction of earnings given 
  as dividend) by subbing D --> K * earnings and rearranging to find 
  P/E = K * (1 + g)/(r - g)
  * P/E is unstable over time, and is only good as a quick estimate of 
  stock price.
  * Useful as comparison to similar companies or stock index, esp. to 
  figure out how much future income is implied by price.  

Dividend / price (dividend yield) is high when market is undervalued.

Price / sales is less subject to accounting manipulations than earnings.

Price / book value assumes company uses assets to generate earnings.
  * Some assets are recently prices, while older ones are historically 
  priced based on what company paid. This depresses book value.
  * Assets sometimes include intangibles like talent that don't appear 
  on balance sheet.

Price / cash flow measures cash after capital expenditures, interest 
payments, and preferred dividends.

Return is sum of price appreciation plus net cash flows r = ( P * (1 + g) + 
D - P ) / P = D / P + g. Then P * (1 + r) gives expected price in one year.
  * Growth rate tends to be dominant factor, rather than dividend

### CAPM

Capital asset pricing model assumes linear relationship between excess 
return vs. market, and all risk can be encapsulated in one parameter beta. 
Estimates required return on equity capital.
  * `r - rf = beta * ( rm - rf )`, where r is security's return, rf is 
  risk-free rate, rm is market return, and b is correlation between 
  security and market.
  * Security's excess return is multiple of market's excess return, and 
  that multiple is the volatility.
  * Beta ranges from 0 (risk-free) to 1 (market risk) to >1 (riskier than 
  market)
  * rf should have same maturity as investment period
  * rm should include all possible investments, but SP500 is good approx.

Company can grow by retaining earnings, buying back shares priced below 
book value, or sell stock above book value

Return on equity = (1 - K)g = net income / common equity = EPS / book 
value per share.

Dupont analysis -- ROE = asset turnover * profit margin * leverage ratio = 
sales/assets * net income/sales * assets/equity

Combining Dupont analysis and CAPM is sensitive and assumes mature, constant 
growth company

Consider return vs. risk graph. Efficient frontier looks like sqrt(x). 
Utility function is `U = E[x] - A/2 sigma^2 x` which looks like 
-1/(x+5) (sorta like right end of parabola). Investor has multiple 
indifference curves which are vertical translations of utility function. 
Select portfolio with indifference curve intersecting and tangent to 
efficient frontier.

Beta is just the regression coefficient (slope) of company excess returns 
vs. market excess returns. Beta = Cov[r, rm]/Var[m] = Corr * sigma / sigmam

CAPM assumes:
  * Investors only care about returns and std dev
  * Only correlation with market drives returns, so any 2 assets are 
  only correlated with one another through the market
  * Investors invest for one period
  * Investors borrow and lend at the risk-free rate
  * Taxes don't matter
  * Returns, std devs, and correlations are all estimated the same way 
  between investors

CAPM finds that the market portfolio is best possible solution.

Index model regresses with intercept and error (company-specific returns) 
and builds portfolio from n companies that tend to replicate market 
portfolio as n grows. This yields betap^2 sigmam^2 + Var[error]/n 
overall risk, which tends to market risk * beta with increasing n
  * `r - rf = sum ( weight * (ri - rf) ) = 1/n * sum( intercept + beta * 
  (rm - rf) - error )` for equal weights

### Hybrids

Combine equity, foreign exchange, commodities, and/or currencies using 
warrants, convertible preferred stock, convertible bonds, dual currency 
bonds, and PERCS

Warrant = right to buy stock at specified price and date. Similar to call, 
but not traded on exchanges, creates new shares (and thus dilution), and 
typically have long expirations

Convertible preferred stock can be switched to common stock. Preferred 
stock holders are paid dividends first.

Convertible bonds can be converted to shares. Pay normal coupons and par 
value at maturity. Typically have lower rates, and sometimes are callable. 
Offer company cheap way to onboard investors.

Convertible value = bond value + conversion value. Conversion value = 
a * stock value, and bond value has sqrt(x) behavior w.r.t. stock value.

Conversion price = par value / conversion ratio (shares per bond)

Parity means convertible bond price = value of converted shares

General valuation technique is to determine min value (compare raw bond 
value to converted stock value and pick max), then calculate investment 
premium, then premium payback period, then value embedded convertible 
option (using binomial trees, e.g.).

Conversion premium = implied price after conversion - current market price

Find premium payback period with (market price - conversion * stock price) / 
(coupon - conversion * dividend) to get number of years
  * Should be 3-5 years. Bad deal if >5 years.

Black-Scholes cannot estimate embedded option because:
  * Assumes constant volatility, which actually decreases over time 
  for bonds
  * Assumes constant interest rate, but bonds are very sensitive 
  to interest rate errors
  * Assumes lognormal dist for underlying, but bond value is capped. Thus, 
  B-S model overprices bond options

### Derivatives

Hedging portfolio with futures requires net-zero change in portfolio value 
during changes of underlying. beta = -DeltaP / DeltaF is the futures 
hedge ratio, which comes from regressing historical futures prices changes 
onto underlying price changes. Required number of contracts is -beta * 
portfolio long / (multiplier * contract size).
  * Basis risk still exists -- spread between spot and future =/= 0
  * Should rebalance daily due to fluctuations in beta

## Currencies and commodities

Currency swap exchanges interest payments + principals in two different 
currencies.
  * Lower effective international borrowing rates
  * Each company should borrow where they have comparative advantage 
  (lower interest rate in market, then pick remaining marketplace?)
  * Total net gains = big market spread - small market spread
  * Adjust payments to ensure swap value = zero at initiation

Commodity swap offers to pay flat rate X in return for value Y which is 
typically average of prior prices. Locks in price X.
  * Priced just like interest rate swap, with potential slight 
  complication if different currency used. 

Commodity futures need to price in physical delivery -- F = (S + s) * 
exp(r t)

Contango = future prices exceed future spot prices. Full carry = equal. 
Backwardation = below.
  * Backwardation happens if it's expected to lower demand or raise supply
  * Some markets just behave s.t. futures prices poorly estimate future 
  expected spot prices

## Risk management

Discount rate should capture all relevant sources of risk.
  * Forward rates matching bond maturity,  cost of equity capital, ...

Market risk includes price changes, interest rates, correlations, and 
chance that expected cash flows aren't realized.

Value at Risk = amount possibly lost, found via MC simulation or stats
  * Use covariance matrix to find overall portfolio VaR 
  * For normal dist., VaR = V0 * alpha * sigma where sigma is std. dev. 
  of returns (percentage). Can scale sigma with sqrt(t) as needed. Can 
  calculate sigma of portfolio and apply same formula.

Directional risk accounts for linear changes in underlying like beta, 
duration, and delta. Non-directional risk includes convexity, 
volatility, and gamma.

Credit risk is risk of default or ratings downgrades.

Counterparty risk is risk of counterparty walking away in OTC transaction. 
Important for interest rate/currency swaps.

Event risks include mergers, acquistions, credit downgrades, dividend 
reductions, leveraged buyouts, lawsuits, war, market crises.

Liquidity risk occurs when a company needs cash now, so it has to sell off 
assets at a discount.

Model risk is risk of using an inaccurate model.

Settlement risk is risk of settlement not occurring as anticipated. 
Especially important for foreign currency transactions like swaps. Can 
mitigate with netting, where no large sums but only net sums are exchanged. 

Specific risk is risk associated with specific issuer. Total price 
movement = beta * P * market return + P * specific error 

Currency risk includes devaluation and volatility. Transaction exposure 
happens when future business transactions include foreign currencies. 
  * Expected exchange rate = S * ( (1 + r)/(1 + rf) )^t
  * Interest rate parity may be violated in short-term, leading to arb

Translation exposure happens when financial statements are translated 
between currencies. Different exchange rates may be used, especially if 
country has rapid inflation.

Interest rate risk strongly affects fixed income through duration and 
convexity. Falling interest rates mean coupon payments cannot be invested 
at same rate. Holding period return comprises coupon interest, capital 
gains on price appreciation, and financing costs. 

Inflation modifies interest rates as (1 + r) --> (1 + r)(1 + i)

Credit spread risk is risk of widening spread, b/t Treasury bills and 
Eurodollar futures, e.g.. Can wipe out stat arb folks (like LTCM).

Prepayment risk is important for mortgage-backed securities and 
collateralized mortgage obligations. Prepayment is unpredictable. 
Burnout happens if many people already refinanced recently (path 
dependency).
  * Accelerates return of cash flows, which must be reinvested at lower rate

Default + credit rating risk can be calculated by creating interest rate 
tree on treasury bonds, then calibrating to price of corporate bond.

Equity risks include stock volatility, foreign exchange rate risk, interest 
rate risk (in swaps, e.g.), liquidity risk, and dividend assumption risk.
  * Can imagine equity as holding a call option with strike = liabilities
  * Dividends should be paid if there's no projects above hurdle rate. 
  * Cutting dividends indicates poor earnings expected. Compare 
  D * (1 + g)/(r - g) to sum( D/(1+r)^i ) 

Hedge with options, since futures/forwards don't exist for stocks. Must 
rebalance to maintain delta-neutral hedge. Position delta = option delta * 
number of contracts * contract size. Note that gamma is important, but 
still overestimates option price deep in/out of the money.
