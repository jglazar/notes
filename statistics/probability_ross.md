# A first course in probability by Sheldon Ross

## Chapter 7 -- Expectation

Can construct `E[Y] = sum(E[Xi]) = n E[Xi]` for many cases
  * Y ~ binomial --> n total Xi ~ Bernoulli(p)
  * Y ~ neg binomial --> r total Xi ~ Geometric(p)
  * Y ~ hypergeometric --> n total Xi ~ Geometric(p)

Don't overthink it! First trial has success chance `m/N`. Other trials are
actually independent, so they also have success chance `m/N`. Can think of all
choices happening simultaneously rather than sequentially

### Problems

Set up Xi as indicator of success. Then `E[Xi] = 0*P(fail) + 1*P(success) =
P(success)`

Y is number of ppl selecting own hat --> n total Xi with `E[Xi] = 1/n`

Coupon collector: Y is number of trials to collect all coupons. Xi is time to
get i'th unique coupon. Xi is Geometric with `p = (n-i+1)/n`

Y is number of geese survived from n hunter shots with p0 chance each. Xi is
survival of i'th goose. Xi is Bernoulli with `p = (1 - p0/n)^n`

More problems

### Moments for number of events

notes on content

Example 3e

### Nested expectations

Mining problem

random number of random variables

Variance of geometric

5m, 5n conditioning in integrals

Conditional variance

### Problems

7.9

## Chapter 10 -- Simulation

### Variance reduction

Antithetic variates -- `Var[1/2 (Y1 + Y2)] = 1/4 Var[Y1] + 1/4 Var[Y2] + 1/2
Cov[Y1, Y2]`
  * Apply `Y1 = Y(U)` and `Y2 = Y(1-U)`, since `U` and `1-U` are both uniform
  * If `Y(U)` is monotonic, then `Cov[Y1, Y2]` will be negative

Conditioning -- use `E[Y|Z]` instead of `E[Y]`, since `E[E[Y|Z]] = E[Y]`
  * Uses fact that `Var[Y] = E[Var[Y|Z]] + Var[E[Y|Z]]`
  * E.g., instead of generating `(V1, V2)` pairs to estimate pi/4, just generate
    `V1` then use `E[I|V1] = sqrt(1 - V1^2)`
    * Can use antithetic variables too, since `sqrt(1-x^2)` is monotonic!

Control variates -- `W = g(X) + a*(f(X) - mu)`, where `E[f(X)] = mu` is known
  * `Var[W] = Var[g(X)] + a^2 Var[f(X)] + 2a Cov[g(X), f(X)]`
  * Select `a = -Cov[f, g] / Var[f]`
  * Hard to know `Var[f]` or `Cov[f, g]`. Can use data to estimate
