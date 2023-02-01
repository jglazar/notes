# Financial calculus by Baxter and Rennie

## Expectation vs. markets and arbitrage

Bookmaker figures odds are 75-25 on bet, so he sets 3:1 odds. 
Bettors place 66-33 instead (10k on A, 5k on B). 
Expected bookie profit = 1/4 * -5000 + 3/4 * 1667 = 0. 

Bookie can guarantee zero profit or loss if he sets odds 2:1 to match 
bettors, ignoring his 75-25 odds.

Same pattern emerges in real bet (with guaranteed bookie profit from vig)

Price of good should equal expected value in long run, but short run 
(few plays of game, e.g.) has other factors (liquidity, e.g.)

Must discount future payoff with interest `exp(-rt)`
  * E.g., Forward contract has discounted value `(St - K) * exp(-rt)`, 
  where St is the stock price at expiry. By fairness, `E[ (St - K) * 
  exp(-rt) ] = 0` --> `K = E[St]`. 
  * St is log-normal distributed and E[ S0 exp(X) ] over Gaussian X 
  is `S0 exp( mu + 1/2 sigma^2 )`. 
  * Market price may deviate due to short-term effects.
  * Actual retail price is `S0 exp(-rt)` by arbitrage argument! Nothing 
  to do with expected price at all.

## Discrete processes

Can synthesize any derivative as a combo of the stock and a bond.
  * Basically, what are a and b s.t. a portfolio of a units of stock and 
  b units of bond have same outcomes as a derivative?
  * The value of the derivative is the cost of constructing the portfolio.
  * ❗️ This is not necessarily equal to the expected value of the 
  derivative!

Consider two prices after a timestep starting at price s1: s2 (stock goes 
up) and s3 (stock goes down). 
  * Cost of initial portfolio is `a * s1 + b * B0`
  * We want `a * s3 + b * B0 exp(rt) = f(s3)` and `a * s2 + b * 
  B0 exp(rt) = f(s2)`, where f is the function that maps stock prices to 
  derivative prices. 
  * This requires `a = (f(s3) - f(s2)) / (s3 - s2)` and `b = 1/( B0 
  exp(rt) ) * ( f(s3) - ( f(s3) - f(s2) ) / (s3 - s2) * s3 )`.
  * Thus, value of derivative = `V = a * s1 + b * B0 = s1 * ( f(s3) - 
  f(s2) ) / (s3 - s2) + exp(-rt) ( f(s3) - ( f(s3) - f(s2) ) / (s3 - s2) * 
  s3)`.

The above portfolio "enforces" the market price for the derivative. Any 
deviation allows arbitrage, regardless of underlying movement.

The value of the derivative can be rearranged to be `V = exp(-rt) ( (1-q) 
f(s2) + q f(s3) )`, where `q = ( s1 exp(rt) - s2 ) / (s3 - s2)`
  * So the value is the time-discounted expectation of the derivative 
  values w.r.t. some probability q.

Binomial tree builds up branches with transitions from j down to 2j or 
up to 2j+1. Can represent 2^n stock price outcomes, where n is the 
depth of the tree. 

The bond can also have random nature, where r is a string of random ri.

Model relies on backwards induction from end time back to start time. 
Use transition probabilities qj for state j to state 2j and (1-qj) for 
state j to state 2j+1. Then use qj and V as defined above to solve 
backwards from known endpoint values.
  * Can instead consider all 2^n paths, which involve 2^n - 1 qj 
  probabilities. Construct overall probabilities with product of 
  small path probabilities. Thus, a 2-step tree is just 2^2 - 1 = 3 
  branches, e.g.
  * Backwards induction enforces single branch arbitrage-style (a,b) 
  portfolio for each j --> 2j or 2j+1 branch combo.
  * Recalculate a and b and rebalance portfolio at each realized 
  branch move.

Formalization:
  * Process S = possible stock values = binomial tree of values
  * Measure P or Q = set of transition probabilities
  * Filtration F = history of price = path on tree = specific node (since 
  each node has a unique path from root to it, bc it's a tree)
  * Claim X = function of nodes at time T = function of filtration
    * Claim only defined on nodes at time T, whereas process is defined 
	on all nodes up to and including T
  * Conditional expectation operator `E_Q(X | F_i)` = expectation of X 
  with paths initiating at Fi (new root)
    * Allows you to convert a claim X into a process S given a measure Q
	* This happens to be a Q-martingale.
  * Previsible process phi = process whose values depend only on history 
  up to one timestep earlier. That is, it's known one node ahead of 
  reference process S. E.g., bond prices, or phi = `S_(i-1)`. 
    * Don't need to define previsible process at time zero (since 
	there's no -1 time).
  * Martingale = process w.r.t. measure P and filtration Fi with 
  `E_P ( S_j | F_i ) = S_i` for all i <= j.
    * The expected future value given the transition probabilities and 
	possible states is just the current value, just like a fair game. 
	No drift.
	* Turns out stock process S is not a P-martingale ( with P = 
	transition probabilities ), but is a Q-martingale ( with Q = 
	arbitrage probabilities ). Compare expectation tree with actual 
	price tree.

Conditional expectation process of claim -- `E_P ( E_P(X|Fj) | Fi ) = 
E_P(X|Fi)` for i <= j

Binomial representation theorem: Let S be a Q-martingale. If N is another 
Q-martingale, then there exists a previsible process phi s.t. 
`Ni = N0 + sum from k=1 to i of phi_k * deltaS_k` where deltaSk is 
change in S from t-1 to t.
  * We can go from N0 to Ni using known steps.
  * Construct N from S by scaling to match step widths and shifting to 
  match offsets. Use `phi_k = deltaN_k / deltaS_k` for scaling. Shift 
  must be zero due to martingale property.

Binomial representation theorem lets you construct a portfolio N that 
is a Q-martingale alongside S. Phi lets you construct N from S.

Bond process Bi is previsible and positive. Inverse (discount process) is 
also previsible. Inv(Bi) Si is discounted stock process. Inv(BT) X is 
discounted claim.
