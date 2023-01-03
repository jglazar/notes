# FAQ in Quantitative Finance

## History

1827 -- Brownian motion for small particles in liquid. Note: Log-normal 
random walk is classical model of stocks

1900 -- Bachelier develops math for random walks

1900s -- Higgins and Nelson start discussing put-call parity and 
delta hedging

1905 -- Einstein investigates diffusion and thermodynamics

1908 -- Bronzin writes book on options and risk neutrality

1911 -- Richardson solves diffusion eqns using finite differences. 
Investigates fractals

1915 and 1926/7 -- High peak and fat tails in price data discovered

1923 -- Wiener develops rigorous theory for Brownian motion

1950s -- Samuelson develops derivative pricing through expectations

1951 -- Ito shows relationship between stochastic variables and 
functions of them. E.g., log-normal SDE for asset -> SDE for option
  * `dF = dF/dX dX + 1/2 d2F/dX2 dt` where X is Wiener process

1952 -- Markowitz develops portfolio selection methods. Efficient 
portfolios maximize expected return at a given level of risk

1962 -- Mandelbrot finds fat tails in cotton price returns

1963 -- Sharpe, Lintner, and Mossin price risky assets with Capital 
Asset Pricing Model

1966 -- Fama posits market efficiency

1968 -- Thorp discovers Blackjack strategy, build wearable computer, 
and develops option pricing model

1973 -- Black, Scholes, and Merton derive B-S equation using geometric 
Brownian motion
  * `dS = mu S dt + sigma S dX` where S is asset price
  * `dV/dt + 1/2 sigma^2 S^2 d2V/dS2 + rSdV/dS - rV = 0` where V is 
  option value

1974 -- Merton models company value using calls, predicting risk of 
default.

1977 -- Boyle relates option price to asset path MC simulations

1977 -- Vasicek derives bond pricing equation

1979 -- Cox, Ross, and Rubinstein develop simple algorithm for B-S eqn

1980 -- Harrison, Kreps, and Pliska bring more rigorous math

1986 -- Ho and Lee develop yield-curve fitting for bond option pricing

1992 -- Heath, Jarrow, and Morton model yield curve evolution

1990s -- Multi-asset options valuation using MC sims

1994 -- Calculate option coefficients by working backwards from stats

1996 -- Avellaneda and Paras create nonlinear uncertain volatility model

1997 -- Brace, Gatarek, and Musiela create model with few input rates

2000 -- Li uses copulas to model collateralized debt obligations

2002 -- SABR interest rate model calculates forward rate and volatility

2007/8 -- Financial crisis, largely from simple quant models

## FAQs

Probabilistic models take growth rate and volatility, and return expected 
asset paths

Deterministic models like dynamical system and chaos theory haven't 
worked as well

Discrete and Continuous models are similar. E.g., binomial model and B-S eqn.

Sims are useful for evaluating many asset price paths. Discretization 
can be used to solve continuous models like B-S. Asymptotic analysis 
is useful for big or small parameters (e.g. close to expiration). 
Series solutions for linear equations and Green's functions for 
special cases are helpful too.


## Problems

1. Spin barrel on 6-chamber gun, then shoot. I survive. Should I spin 
again or shoot next chamber?
2. Probability of birthday match in room with n people.
3. Find best spot in line if you get prize for being first to match 
someone's bday in front of you.



