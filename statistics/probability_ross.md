# A first course in probability by Sheldon Ross

## Chapter 4 -- Random variables

Geometric distribution isn't covered with Chapter 7 methods
  * Use `x = (x - 1 + 1)` and expand
  * Mean: `E[X] = sum(x q^(x-1) p) = sum((x-1) q^(x-1) p) + 1 = q E[X] + 1`
  * Variance: `E[X^2] = sum(x^2 q^(x-1) p) = sum((x-1)^2 q^(x-1) p) + sum(2(x-1)
    q^(x-1) p) + 1`

## Chapter 6 -- Multiple variables

X and Y distributed uniformly in circle of radius R
  * Normalizing factor is 1/(pi R^2) = c
  * Marginal pdf: Integral x=-sqrt(R^2-y^2) to x=+sqrt() (c) = c sqrt(R^2-y^2)
  * cdf of distance: P(D <= d) = P(X^2 + Y^2 <= d^2) = Integral over region (c)
    = (pi d^2) c
  * Mean of distance: pdf is d(cdf)/dd = 2 pi d c, so mean = Integral from d=0
    to d=R (2 pi d c d) = 2R / 3

Buffon's needle -- prob of intersection?
  * Distance from line to needle midpoint is X ~ U(0, D/2). Angle is T ~ U(0,
    pi/2). Intersects if X < L/2 cos(T). Integral x=0 to x=D/2 Integral t=0 to
    t=pi/2 = D pi/4 (inv. normalizing factor). Integral x=0 to x=L/2 cos(t)
    Integral t=0 to t=pi/2 = 2L / (pi D)

3 people uniformly distributed along (0,1). Prob no 2 are <= d apart?
  * Assume WLOG X <= Y <= Z. Integral x=0 to x=1-2d Integral y=x+d to y=1-d
    Integral z=y+d to z=1 dz dy dx. Then multiply by 6 for orderings. `(1-2d)^3`

Distribution of X + Y is convolution of pdfs if X, Y independent
  * cdf = P(X+Y < z) = Integral(F(z-y) f(y)) (by independence)
  * pdf = d(cdf)/dz = Integral(f(z-y) f(y))

Distribution of X + Y for uniform
  * pdf = Integral y=-inf to y=+inf (fx(z-y) fy(y)) but consider z <= 1 and z >=
    1 separately, since each has separate bounds to keep fx(z-y) nonzero

Induction shows that cdf = `z^n / n!` if z <= 1
  * Expected number of uniforms needed to exceed 1: P(N > (n-1)) - P(N > n) =
    (n-1)/n!. Taking expectations gives e.

## Chapter 7 -- Expectation

Can construct `E[Y] = sum(E[Xi]) = n E[Xi]` for many cases
  * Y ~ binomial --> n total Xi ~ Bernoulli(p)
  * Y ~ neg binomial --> r total Xi ~ Geometric(p)
  * Y ~ hypergeometric --> n total Xi ~ Geometric(m/N)
    * or m total Xi ~ Geometric(n/N)

Don't overthink it! First trial has success chance `m/N`. Other trials are
actually independent, so they also have success chance `m/N`. Can think of all
choices happening simultaneously rather than sequentially

Set up Xi as indicator of success. Then `E[Xi] = 0*P(fail) + 1*P(success) =
P(success)`

Y is number of ppl selecting own hat
  * n total Xi with `E[Xi] = 1/n`

Coupon collector: Y is number of trials to collect all coupons
  * Xi is time to get your i'th unique coupon. Xi is Geometric(`p = (n-i+1)/n`)

Y is number of geese survived from n hunter shots with p0 chance each
  * Xi is survival of i'th goose. Xi is Bernoulli with `p = (1 - p0/n)^n`

Expected number of 0-runs in permutation of n 1s and m 0s, with N = n+m
  * Xi is start of 0-run in i'th position. Xi is Bernoulli with `p = n/N
    m/(N-1)` and X1 is m/N. E[Y] = sum(E[Xi]) = m/N + nm/N

Can use expected value to determine bounds

52 trees in a circle with 15 chipmunks. Prove there's 7 consecutive trees with
>= 3 chipmunks
  * Pigeonhole: 7 groups of 7, plus 3. Put 2 in each to get 14, but need 1 more
  * Probabilistic: Xi is indicator if i'th chipmunk is in your tree or next 6.
    Xi is Bernoulli with `p = 7/52`. So E[Y] = 15 * 7/52 > 2, meaning there must
    be a tree with >= 2 chipmunks

Can use incl-excl to calculate max(Xi)

Coupon collector with unique probabilities `pi`
  * Xi is number of coupons until getting the i'th coupon. Xi is Geometric(pi).
    E[max(Xi)] = sum(E[Xi]) - sum(E[min(Xi,Xj)]) + sum(E[min(Xi,Xj,Xk)])... and
    E[min(Xi,Xj)] = E[Xi or Xj] = 1/(pi + pj)

Can consider pairs of indicator events to calculate Var[X]
  * E[Xc2] = 1/2 E[X^2 - X] = sum pairs(E[Xi Xj]) = sum pairs(P(Xi,Xj)). So
    Var[Y] = 2 sum pairs(P(Xi,Xj)) + E[Y] - (E[Y])^2
  * Can generalize to E[Xck] to get k'th moment

Variance of Binomial(n,p)
  * Xi is i'th event succeeding. Bernoulli with prob p. Var[Y] = 2 * nC2 p^2 =
    n(n-1)p^2 + np - (np)^2 = np(1-p)

Variance of Hypergeometric(m,n)
  * Xi is i'th event succeeding. Bernoulli with prob m/N. Var[Y] = 2 * nC2
    (m/N)((m-1)/(N-1)) + mn/N - (mn/N)^2 = ...

Variance of hat problem
  * Xi is i'th man getting his hat. Bernoulli with prob 1/N. Var[Y] = 2 * nC2
    (1/N)(1/(N-1)) + 1 - (1)^2 = 1
  * Higher moments are also 1

Variance of coupon collector with unique probabilities `pi` within n picks
  * Xi is indicator of i'th coupon not appearing in n picks. Xi is
    Bernoulli((1-pi)^n). Var[Y] = 2 * sum pairs((1 - pi - pj)^n) + sum((1-pi)^n)
    - (sum((1-pi)^n))^2

Variance of negative hypergeometric
  * Ace problem xxAxxAxxAxxAxx is equivalent to considering orderings of AAAAx
    where x is some other specific card (7H, e.g.)
  * Mean: Xi is indicator of i'th regular ball picked before r'th special ball.
    Xi is Bernoulli(r/(m+1)), after finding `P(Xi) = r/(m+1)` is chance of
    getting x before r As. Total draws is Y = r + sum(Xi) so E[Y] = r + nr/(m+1)
  * Variance: find `P(Xi,Xj) = 2C2 * mC(r-1) / (m+2)C(r+1)` is chance of getting
    x and y before r As in AAAAxy. Var[Y] = Var[X] = ...

### Covariance

Useful identities
  * Cov[X, Y] = E[XY] - E[X]E[Y]
  * Cov[aX, Y] = a Cov[X, Y]
  * Cov[sum(Xi), sum(Yj)] = sum(sum(Cov[Xi, Yj]))
  * Var[sum(Xi)] = sum(Var[Xi]) + 2 sum pairs(Cov[Xi,Xj])
    * Cov term = 0 for independent variables

Don't compute Cov[X1,X2 | B]. Instead, expand into expectations, then condition

X - Y with X, Y Normal
  * Mean = mux - muy, Variance = sigmax^2 + sigmay^2 - 2 rho sigmax sigmay

Variance of binomial
  * Use fact that E[Xi^2] = E[Xi] for indicators
  * Var[Y] = sum(Var[Xi]) = n (E[Xi^2] - (E[Xi])^2) = n (p - p^2)

Variance of survey of size n from population of size N
  * Xi is indicator that i'th person from population is selected for survey.
    Their score is `vi`
  * Mean: E[Y] = E[sum(vi Xi)] = sum(vi n/N) = n vbar
  * Variance: E[Xi,Xj] = n/N (n-1)/(N-1). Var[Y] = sum(Var[vi Xi]) + 2 sum
    pairs(Cov[vi Xi, vj Xj]). Var[vi Xi] = vi^2 (n/N - (n/N)^2). Use
    expectations to calculate Cov term

Sample average and deviations from that average are uncorrelated, but not
independent. Independent if Normal, though.

### Nested expectations

E[Y] = sum(E[Y|Xi] P(Xi))

Guy has 3 doors. A leads to safety after 3 hours, B leads back after 5 hours, C
leads back after 7 hours. Expected hours until leaving?
  * E[Y] = E[Y|A] P(A) + ... = 3 1/3 + (5 + E[Y]) 1/3 + (7 + E[Y]) 1/3 = 15

Random number of customers (mean 50) spends random amounts of money (mean $8).
Assume independence. Expected revenue?
  * E[Y] = E[sum(Mi)] = E[E[sum(Mi) | N=n]] = E[nE[M]] = E[n] E[M] = 400

Variance of geometric
  * Mean: consider 1st event success, giving recursion `E[Y] = 1p + (E[Y]+1)p`,
    leading to E[Y] = 1/p
  * Variance: recursion `E[Y^2] = 1p + (E[(Y+1)^2])(1-p)`, then expand
    * Increment goes inside the expectation

Expected number of uniforms to add s.t. sum is greater than x
  * E[Y(x)] = integral from 0 to 1 (1 if y > x else E[Y(x-y)]) = 1 + integral
    from 0 to x of E[Y(x-y)]. Diff. + bounds yields f'(x) = f(x) so f(x) = e^x

Secretary problem -- maximize prob of picking best secretary
  * X is best sec's position. Our strategy is to discard first k then pick best
    so far. P(win) = sum(P(win|X=i) 1/n). No chance of winning for i <= k. Win
    requires that best one of first i-1 is in k rejected, which has prob k/(i-1)
    for i > k. Now sum to get 1/n sum from k+1 to n (k/(i-1)) and approximate
    with integral to get k/n ln(n/k). Max at k = n/e, with prob 1/e

P(X < Y) given fx(x) and fy(y) are independent
  * Integral (P(X < Y | Y=y) fy(y)) = Integral (Fx(y) fy(y))

P(X + Y = z) given fx(x) and fy(y) are independent
  * Find cdf instead of pdf, then take derivative w.r.t z
  * Integral (P(X < z - y | Y=y) fy(y)) = Integral (Fx(z-y) fy(y))

Useful identities
  * Var[X|Y] = E[(X - E[X|Y])^2 | Y]
  * Variance also follows independence: Var[X|Y] = Var[X] if X,Y indep
  * E[Var[X|Y]] = E[X^2] - E[(E[X|Y])^2]
  * Var(E[X|Y]) = E[(E[X|Y])^2] - (E[X])^2
  * Var[X] = E[Var(X|Y)] + Var[E[X|Y]]

People arrive with Poisson(lambda t). Train arrives with U(0,T). Y = # ppl board
  * Mean: `E[Y(T) | Y=t] = E[Y(t)] = lambda t`. `E[lambda t] = lambda T/2`
  * Variance: `Var[Y(T)] = E[Var(Y|T)] + Var[E[Y|T]] = E[lambda T] + Var[lambda
    T] = lambda T/2 + lambda^2 T^2 / 12`

Sum of random number N of random variables Xi
  * Mean: E[sum(Xi)] = E[E[sum(Xi) | N=n]] = E[n E[X]] = E[N] E[X]
  * Variance: Var[sum(Xi)] = E[Var[sum of n Xi]] + Var[n E[X]] = E[N] Var[X] +
    (E[X])^2 Var[N]

Pdf of binomial with p ~ U(0,1)
  * P(Y = y) = Integral (nCy p^y (1-p)^(n-y)) = nCy y!(n-y)!/(n+1)! = 1/(n+1)

### Moment generating functions

Common MGFs
  * Binomial -- `(p e^t + 1 - p)^n`
  * Poisson -- `exp(lambda (e^t - 1))`
  * Geometric -- `p e^t / (1 - (1-p) e^t)`
  * Neg Bin -- `(p e^t / (1 - (1-p) e^t))^r`
  * Uniform -- `(e^tb - e^ta) / (t(b-a))`
  * Exp -- `lambda / (lambda - t)`
  * Gamma -- `(lambda / (lambda - t))^r`
  * Normal -- `exp(mu t + (sigma^2 t^2 / 2))`
  * Chi-sq -- `(1 - 2t)^(-n/2)`

Negative binomial is just sum(Xi), where Xi is the time until the i'th failure
and is Geometric(p)

Sum of variables is multiplication of their MGFs

Sum of random number of random variables
  * E[mgf|N=n] = E[(mgf)^N], then take desired derivatives and set t=0

Pdf of binomial with p ~ U(0,1)
  * E[mgf] = Integral (mgf^n) dp = `1/(n+1) (exp(t(n+1)) - 1) / (exp(t) - 1) =
    1/(n+1) (1 + e^t + e^2t + ... + e^nt)`, which reveals pdf = 1/(n+1) for all
    i up to n

If joint MGF factorizes, then the two variables are independent

X+Y and X-Y for X, Y iid Normal are independent
  * Joint MGF = `E[exp(t(X+Y) + s(X-Y))] = E[e^(t+s)X] E[e^(t-s)Y] = exp(2 mu t
    + sigma^2 t^2) exp(sigma^2 s^2)`, which is mgf for Normal(2 mu, 2 sigma^2)
      and Normal(0, 2 sigma^2)
  * Can instead calculate joint pdf using transform method

### Problems

Gamble 1 unit on coin toss until win once, then stop
  * P(win money) = 1/2
  * P(lose money): P(win) + P(0) + P(lose) = 1. P(win) = 1/2 and P(0) = 1/4, so
    P(lose) = 1/4
  * E[profit] = 1/2 + 0 + -1/8 + -2/16 + -3/32 + ... = 1/2 - 1/4(sum(n/2^n)) = 0
  * Alternatively, W = 2 - N, where N is the number of trials and is
    Geometric(1/2). E[W] = 2 - E[N] = 0
  * Alternatively, E[W] = 1/2 * 1 + 1/2(-1 + E[W]) --> E[W] = 1/2 E[W] so E[W]=0

E[XY], E[X], and E[Y] just require plugging in relevant function and integrating
over whole joint pdf. Don't need to integrate out marginal then get expectation

Distance to hospital is |x| + |y|. Area is (-3/2,3/2) for X and Y. E[distance]?
  * Consider top-right quadrant. Integral from x=0 to x=3/2 Integral from y=0 to
    y=3/2 (x+y) = 3/2

A and B randomly pick 3 out of 10 objects. Can overlap
  * Expected number chosen by both: P(Xi) = 9/100 --> 9/10
  * Expected number chosen by neither: P(Xi) = 49/100 --> 4.9
  * Expected number chosen by one: P(Xi) = 21/100 --> 2.1 * 2 = 4.2

People walk into party and sit at new table if no table has a friend
  * Expected number of tables: Xi is i'th person has no friends. P(Xi) =
    (1-p)^(i-1), so sum(P(Xi)) = `((1-p)^n - 1)/((1-p) - 1) = (1 - (1-p)^n)/p`

n balls in n numbered urns s.t. ball i uniformly goes into urns 1...i
  * Expected number of empty urns: Xi is i'th urn empty. Start listing out Xi
    for P(X1), P(X2),... and note P(Xi) = (n-1)!/n! * (i-1) = (i-1)/n. Sum from
    2 to n = sum from 1 to n-1 of i/n = (n-1)n/2 / n = (n-1)/2
  * Prob that none is empty: P(none empty) = P(not X1 and not X2...). Can use
    incl-excl, but that'll take too long. Recursion from end shows that n'th
    ball must go to n'th urn, (n-1)th... so total prob = 1/n!

Expected number of changeovers in n flips of biased coin?
  * Xi is i'th and (i+1)th flips are different. P(Xi) = P(X) = 2p(1-p), so
    answer is 2p(n-1)(1-p)

Expected number of men next to women for random permutation of nM nW
  * Xi = i'th man is standing next to a woman. P(Xi) = P(2nd is woman | 1 slot)
    P(1 slot) + P(L or R is woman | mid) P(mid) + P((n-1)th is woman | n slot)
    P(n slot)... messy algebra

Expected number of trials to remove all black balls, when each one is replaced
with a white ball with prob (1-p)
  * Recursion: `E[N] = p(E[N] + 1) + (1-p)(E[N-1] + 1)`, then build from E[1] to
    find pattern E[N] = N/(1-p)
  * Identify neg. bin. with n trials and (1-p) success. Mean = n/(1-p)

Expected number of hat pairs in hat problem
  * nC2 total pairs, each having 1/n 1/(n-1) chance of swap. Answer = 1/2

Guess next card. Expected number correct when:
  * No info given: Xi is chance of 7H = 1/52 --> answer = 1
  * Card is flipped: Xi is chance of specific remaining card = 1/(52-i+1) = H52
    ~= log(52)
  * Told yes/no: Xi is chance you get your i'th card choice. X1 = 1, X2 = xxAxx
    chance it's in latter half = 1/2, X3 = xxAxxBxx chance you get A and B then
    it's in 3rd part = 1/6... --> answer = sum(1/i!) ~= e - 1

Expected number of matches for 1,14,27,40th card = A, 2,15... = 2, ...
  * Each place has 4/52 chance --> answer = 4

r types of coupons with individual probabilities of collecting
  * Expected number collected before type 1: Geometric(p1) --> answer = 1/p1 - 1
  * Expected number of types collected before type 1: Xi is getting type i
    before type 1. P(Xi) = `pi / (pi + p1)`, imagine setting up line segment
    with proportional probabilities and picking 1st variable. answer =
    sum(P(Xi)) = sum(pi / (pi + p1)). Has correct limiting behavior
    * Was easier for me to consider equal `pi`, leading to P(Xi) = 1/2. Just
      reweight this to account for unequal `pi`

Pick balls w/o replacement with unique weights
  * Expected number before ball 1: Xi is i'th ball is selected before ball 1.
    For equal weights, P(Xi) = 1/2. Just reweight to `pi/(pi+p1) = wi/(wi+w1)`

101 items in 10 boxes. At least 1 box must contain > 10 items.
  * Use Pigeonhole or probabilistic: E[X] = 10.1

Cov[X,Y] for n rolls where X = number of 1s and Y = number of 2s
  * Cov[sum(Xi), sum(Yi)] = sum over pairs(Cov[Xi, Yi]) = n * Cov[X, Y] bc rolls
    are independent. Cov[X, Y] = E[XY] - E[X]E[Y] = 0 - 1/36 (can't have both on
    same roll) --> answer = -n/36

In a group of 100 people:
  * Expected number of days that are 3 ppl's bday: Xi is 3 ppl have this bday.
    Xi is Binomial(100, 1/365) giving P(Xi) = `100C3 (1/365)^3 (364/365)^97`, so
    answer = `365 * 100C3 (1/365)^3 (364/365)^97`
  * Expected number of distinct bdays: Xi is someone has bday today. P(Xi) = `1
    - (364/365)^100`, so answer = `365 (1 - (364/365)^100)`

Urn 1 has 5W 6B. Urn 2 has 8W 10B. Two balls from Urn 1 are given to Urn 2, then
three balls are selected from Urn 2. Expected number of white balls?
  * Xi is i'th white ball in Urn 1 is selected. Yi is i'th white ball in Urn 2
    is selected. P(Xi) = 2/11 3/20 and P(Yi) = 3/20. Answer = `5P(Xi) + 8P(Yi)`

Bottle has m big and n small pills. If big is selected, it turns into small. If
small is selected, it is removed
  * Expected number of remaining pills after last big is taken: Xi is i'th
    original small remains. Yi is i'th new small remains, where i is i'th unique
    big pill. P(Xi) = 1/(m+1) [set up xxAxxAxxAxx]. P(Yi) = 1/(m-i+1) [set up
    xxAxx, xxAxxAxx,...] 
    * Can also solve with 2D recursion/DP in (m,n) grid. f(m,n) = m/(m+n) f(m-1,
      n+1) + n/(m+n) f(m,n-1)
  * Expected day of last pill: E[D] = 2m+n - E[p], given above

Whenever you see E[N] = e, it's likely `E[N] = 1 + 1/2! + 1/3! + ... + 1/n!`.
  * E.g., Xi is seeing your i'th card, given yes/no answers, and N is correct
    guesses (see above)

E[min] and E[max] of n U(0,1)
  * m'th order statistic: m nCm (F(a))^(m-1) f(a) (1-F(a))^(n-m)
  * max: n (F(a))^(n-1) f(a), min: n (1-F(a))^(n-1) f(a)... integrate for E[x]

A,B,C,D are iid with mean 0 and var 1
  * Corr[A+B,B+C] = (E[(A+B)(B+C)] - E[A+B]E[B+C])/sqrt(Var[A+B]Var[B+C]) = 1/2
  * Corr[A+B,C+D] = 0

Play dice game where P1 and P2 each try to beat dealer
  * Cov(X1, X2) > 0 because win likely means bad dealer roll
  * Cov(X1, X2) = E[X1 X2] - E[X1] E[X2], then condition on each individual E[X]

Roll dice with X = # rolls until 6 and Y = # rolls until 5
  * E[X|Y=5] constructs pdf 1/5 (4/5)^(x-1) for x < 5 and 1/6 (4/5)^4
    (5/6)^(x-1-4) for x > 5

Calculating integrals for E[X|Y=y] requires calculating f(x|y) = f(x,y)/f(y).
Cannot just directly integrate joint pdf

Roll 2 dice and win sum or re-roll. Sum = 7 ends game with 0 winnings
  * Best strategy: `E[X] = sum from 2 to c (Pi E[X]) + sum from c+1 to 12
    (Pi i)`, skipping 7 due to 0 EV. Best policy is re-rolling if <= 7 (or
    equivalently, <= 6 since 7 ends game). Expected winnings is 6.66

Flip coin until both H and T have shown up
  * Expected tosses: E[X] = P(1st is T) E[tosses until H] + P(1st is H) E[tosses
    until T] + 1 = (1-p)/p + p/(1-p) + 1
  * Prob last is H: same as P(1st is T) = 1-p

Urn has 10R, 8B, 12G balls. X is number of red and Y is number of blue
  * Cov[X,Y]: Set X = sum(Xi) and Y = sum(Yi). Cov[X,Y] = sum sum Cov[Xi,Yj] =
    80 Cov[Xa, Ya] = 80 (E[Xa Ya] - E[Xa] E[Ya]) = 80 (12/30 11/29 - 12/30
    12/30) = -0.66
  * Negative covariance makes sense due to occupation
  * Can also do E[XY] = sum(E[XY|X=x] P(X=x)), where X is hypergeometric with
    P(X=x) = 10Cx 20C(12-x) / 30C12. E[XY|X] = x 8 (12-x)/20, then applying
    expectation over that gives 2/5 (12 E[X] - E[X^2]), where E[X] and E[X^2]
    are for X's hypergeometric dist.

Urn with nW, mB balls. 
  * Expected number of white then black: Xi is i'th position has W then (i+1)th
    position has B. P(Xi) = n/N m/(N-1) --> answer = nm/N

10 married couples sit at 5 tables
  * Expected number of couples seated together: Xi is i'th husband is seated
    with wife. P(Xi) = 3/19 --> answer = 30/19 = 1.58
    * Don't sum over all people due to double-counting partnerships!
  * Expected number if each table has 2M 2W: Xi is i'th table's number of
    couples. Total ways is 10C2 10C2, ways with 0 is 10C2 8C2, ways with 1 is
    10C2 2C1 8C1, ways with 2 is 10C2 2C2. Then calculate expectation = 2
    * Alternatively, each husband now has P(Xi) = 2/10 --> answer = 2

Die is rolled until all numbers shown
  * Expected number of times 1 appears: expected number of rolls is coupon
    collector n Hn = 6 H6 = 14.7. Expected 1s = 1/6 * 14.7 = 2.45

Deck of nR nB is revealed. Each R revealed when #R > #B gets $1
  * Expected winnings: Xi is i'th red card satisfies condition. P(Xi) = 1/2 by
    symmetry --> answer = n/2

Have players 2C 3F 4B, making 3 teams of 3 each
  * Expected number of perfect teams: Xi is i'th team is perfect. P(Xi) = 2C1
    3C1 4C1 / 9C3 = 2/7 --> answer = 6/7

Draw hand of 13 cards and let X = number of aces and Y = number of spades
  * Cov[X,Y] = E[XY] - E[X]E[Y], then calculate E[XY] by conditioning on X.
    Answer is zero.
  * X and Y aren't independent. P(X = 13, Y = 4) = 0 != P(X = 13) * P(Y = 4)

Put m items into n cells. Each cell has a normalized weight 
  * Expected number of collisions: collisions = m - (# full) = m - n + # empty.
    E[# empty] = sum(Xi) with P(Xi) = (1-pi)^m --> answer = m - n + sum(1-pi)^m

Put n items in box H and m items in box T. Flip biased coin and remove an item
  * Expected number of flips until both empty: consider first m+n flips. E[X] =
    sum(E[N|iH] P(iH)) = sum(f(n-1, -(n-i)) (m+n)Ci p^i (1-p)^i). The
    expectation `f_ab` will have one subscript zeroed out (since we emptied 
    either H or T box), and the value is (n-i)/p or (i-n)/(1-p) (neg. bin. mean)

Pick 3 cards. X is number of aces in hand
  * E[X|ace of spades chosen] = 1 + 3 * 2/51 = 57/51
  * E[X|>=1 ace chosen] = 4 * P(Xi|A) = 4 * (3/52 / (1 - (48 47 46)/(52 51 50)))

Flip biased coin until getting nH or mT
  * Expected flips: max(X,Y) + min(X,Y) = X+Y --> E[N] = E[X] + E[Y] -
    E[max(X,Y)]. E[X] = n/p, E[Y] = m/(1-p). Condition like box problem to get
    E[max(X,Y)]. Final answer is long expression

Hat problem has r hat sizes, ni men wearing size i, hi hats of size i
  * Expected number matching: Y = sum over r sum over ni (Xi). P(Xi) = hi / n
    --> answer = sum(hi ni) / n

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
