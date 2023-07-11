# Questions from the web

## Jane street questions on Glassdoor

Would you roll one die and square the result or roll two dice and multiply?
  * `E[X^2] = 1/6(1+4+9+16+25+36)`, `E[XY] = E[X] E[Y] = 7/2*7/2` (independence)
  * Compare to median of 5 rolls: `f(a) = 5C2 F(a)^2 f(a) (1-F(a))^2`. Be sure
    to include lower number in `1-F(x)`. Answer is 10.07, lowest of 3 options.

Smallest number whose digits multiply to 10000
  * Split into factors 22225555, then agglomerate and rearrange to 255558

Paint a 3x3x3 cube, then cut into 1x1x1 cubes. Pick random cube and roll. What
is the chance a painted side is face-up
  * 1 center w 0 painted sides, 6 middles w 1, 12 edges w 2, 8 corners w 3.
    `P(paint) = P(paint|ctr)P(ctr) + P(paint|mid)P(mid) + P(paint|edge)P(edge) +
    P(paint|cnr)P(cnr) = 1/3`

Sum of odd numbers to 50
  * Total sum is `n(n+1)/2`, which is evens + odds. But each even number is just
    1 more than the odds. So evens + odds = (odds + n/2) + odds. Solve for odds.

A and B play baseball for 2 innings. Could A have better batting avg in both
innings but B has better avg overall?
  * Yes, A gets 9/10 and 71/100 and B gets 89/100 and 7/10

Want to win 2 in a row: ABA or BAB for playing against A and B, with A stronger
  * P(WWW) + P(LWW) + P(WWL) for each to find 2ab-aab vs 2ab-bba. Want ABA

Find a subset of {1,2,3...,29,30} with all numbers coprime to one another
  * Trivial subsets of {x} exist
  * Largest subset would be all the primes

Probability of even sum of 2 dice
  * Instead of considering 2,3,...,11,12, consider state space EE, EO, OE, OO.
    Get even sum for EE and OO, so total chance is 50%

Win if first 2 cards are same color. Prefer 52-card deck or 26-card deck? How
about 26-card sample from 52-card deck?
  * Prefer big deck for lower impact on ratio (25/51 vs 12/25). Prefer
    randomized deck bc could have more prevalent color, in which case its more
    likely to be pulled twice

Which has higher chance: roll 2 dice and get (6,6) or roll 10 dice and get no 6?

Expected pay of rolling 2 dice, with sum = 7 winning $1, sum = even losing $1,
and other sums re-rolling

Pick 4 numbers from first 15 primes. Chance their sum is odd?
  * Need to pick the number 2, which would have 4/15 chance (chance of 2
    appearing in first 4 digits of random permutation) 

Largest number s.t. product of digits is 32

Throw 1000 darts w 50% chance of scoring. First 500 earn 1 point each, last 500
earn 3 points each. Find E[number of 3-pointers | 1500 points total]

I throw 2 dice and say one is a 6. Chance of two 6s?

Min and max correlation of X and Z given Corr(X,Y) = 0.8 and Corr(Y,Z) = 0.8

Clock breaks into 3 pieces with same sum of numbers. What are the pieces?

A throws 1 die 4 times and wins with 6. B throws 2 dice 24 times and wins with
(6,6). Who has greater chance of winning?

Throw a 64-sided die, then get paid $x or pay $1 to roll again. Find EV

Given 3 black and 2 white balls, find strategy to maximize E[b-w]

Time to get HHT in coin flip sequence

Bear catches fish with probability 1/2, and leaves when 3 are caught.
Probability of 5th fish getting caught?

Play a game with 2 dice where (6,6) earns $100, (6,not 6) loses $x, all other
cases re-roll

How many races to find fastest 3, given 25 total horses and 5 race at a time

Given an unfair coin with P(H)=1/3, make an event with 50% probability
  * Expected number of flips until event
  * How to minimize flips, esp. in case of arbitrary coin bias

Chance of needing a 7th game in a best-of-7 series

Length of longest segment of 3 substicks from unit stick

Planets rotate around sun with period 60 years, 84 years, 140 years. Find the
next time they'll align

## Brain stellar

Roulette with 1 vs. 2 bullets
  * 1 bullet:  bxxxxx, xbxxxx, xxbxxx, xxxbxx, xxxxbx, xxxxxb. 1/5 vs 1/6
  * 2 bullets: bbxxxx, xbbxxx, xxbbxx, xxxbbx, xxxxbb, bxxxxb. 1/4 vs 1/3

Pirates divy 100 gold. If 50% agree, vote passes. Else, kill captain and retry
  * Think recursively about each pirate's position upon killing the captain 
  * n = 1: 100
  * n = 2: 100 0
  * n = 3: 99 0 1
  * n = 4: 99 0 1 0
  * n = 5: 98 0 1 0 1

A tiger can eat a sheep, but becomes it. Does the sheep survive with 100 tigers?
  * Think recursively about each tiger's position upon eating the sheep
  * n = 1: no -- single tiger eats it
  * n = 2: yes  -- tiger won't eat bc he'll then be eaten
  * n = 3: no -- tiger eats, then is safe ...
  * n = 100: yes -- even number leads to sheep being eaten

Why can't dominos tile a chessboard with opposite corners removed?
  * Each domino covers 1B 1W. Opposite corners are same color, so now B != W

Which is bigger: e^pi or pi^e
  * Expansion method: `exp(pi/e - 1) > 1 + (pi/e - 1)` --> `exp(pi/e)/e > pi/e`
    --> `exp(pi) > pi^e` QED
  * `x^(1/x)` method (general): `e^pi ~ pi^e` --> raise both sides to `1/(pi e)`
    --> `e^(1/e) ~ pi^(1/pi)`. Take derivative using `log(x^(1/x))` to get `(1 -
    ln(x))/x^2`. So the derivative of `log(x^(1/x))` is strictly increasing
    before `x = e` and strictly decreasing afterwards. But log is monotonic, so
    `e^(1/e) > pi^(1/pi)`

Can use the fact that `x^(1/x)` reaches peak at `x = e` to solve:
  * `e^pi^2 ~ pi^e^2` --> raise both sides to `1/(pi pi e e)` and square
  * `e^sqrt(pi) ~ pi^sqrt(e)` --> raise both sides to `1/sqrt(pi e)` and sqrt

Place $1 bet on any die number. Roll 3 biased dice. Win $1 per correct face
  * Expected winnings: E[X] = 3 p (1-p)^2 + 6 p^2 (1-p) + 3 p^2, then integrate
    from 0 to 1 for all p to get 3/2, then subtract 1 for $1 cost to bet
  * Alternatively, place a bet on each number then win guaranteed $3. Expected
    winnings per ticket = $0.50

Pick balls from 50B 50R urn
  * Expected number of color changes: Xi is i'th position has B then (i+1)th has
    R. P(Xi) = 50/100 50/99 --> answer = 1/2 50/99 * 99 * 2 (for BR and RB) = 50

Archer shoots 2 arrows and is told 1 is better than 2
  * Prob 3rd shot is best: list possibilities 123 132 213 231 312 321 then keep
    only 123 132 312 --> answer = 1/3

Pull balls from kB 1R urn. First person to grab R wins
  * Go 1st or 2nd: list out possibilities. RB BR (doesn't matter), RBB BRB BBR
    (P1), RBBB BRBB BBRB BBBR (doesn't matter), RBBBB BRBBB BBRBB BBBRB BBBBR
    (P1). So doesn't matter if k even and go 1st if k odd

Jar has 10R 20B 30G balls
  * Prob of a B and a G remaining after last R: set up xxR1xxR2...xxR10xx then
    find P(deplete B before R) = 29C9/30C10 = 1/3. P(deplete G before R) =
    39C9/40C10 = 1/4. Intersection = 2 * 1/12 = 1/6 (2 for orderings). answer =
    1 - (1/4 + 1/3 - 1/6) = 7/12
  * Alternatively, consider last candy is B with prob 20/60. Then arrange
    remaining 40 candies, for which prob of last candy = G is 30/40. Similarly
    for last candy is G --> answer = 20/60 30/40 + 30/60 20/30 = 7/12

Noodle problem: bowl has n=100 noodles. Take one end and connect to random other
end until you no longer can
  * Use recursion to note pattern. Start from n=1
  * Expected number of loops: set up recursion E[N] = 1/(2n-1) (E[N-1] + 1) +
    (2n-2)/(2n-1) E[N-1]. E[N] = 1 + 1/3 + 1/5 + ... + 1/(2N-1). N=100 -->
    answer ~= 3.28
  * Probability of one big loop: find recursion Pn = 1 2/3 4/5 ...
    (2N-2)/(2N-1). N=100 --> answer ~= 8.8%

Draw n numbers with replacement from 1,2...,n
  * Expected number of distinct values: D = n - F, so E[D] = n - E[F]. E[F] =
    sum(P(Xi)) = n P(Xi) = n (1-1/n)^n --> answer = n(1 - (1-1/n)^n) ~= n(1-1/e)

Place n points on a circle, then draw a convex hull connecting them all
  * Chance hull surrounds center: this event is same as saying there exists no
    semicircle containing all points. P(0 semicircle) = 1 - P(>= 1 semicircle) =
    1 - n (1/2)^(n-1), where each point can be origin of a semicircle. Construct
    semicircle with circumference through the point and center.

Keep adding U(0,1) variables until exceeding 1
  * P(N>=n): P1 = 0, P2 = 1/2 (set up triangle in XY unit square), P3 = 1/6 (set
    up pyramid in XYZ unit cube)... Pn = 1/n!
  * E[N] = sum(n/n!) = e
  * Alternatively, set E[N] as fct of x `f(x) = 1 + integral from 0 to x
    (f(x-y))`. Then take derivative to get `f'(x) = f(x)` so `f(x) = k exp(x)`.
    f(0) = 1 gives k = 1, then f(1) = e

Start at 0 and take random walk until hitting +a or -b
  * P(hit +a before -b): set n = a+b. We seek f(0) and know f(a)=1 and f(-b)=0.
    Then f(-b+1) = 1/2 f(-b) + 1/2 f(-b+2) = 1/2 f(-b+2), f(-b+2) = 1/2 f(-b+1)+
    1/2 f(-b+3),... backsubstitution gives f(-b+x) = x/(x+1) f(-b+x+1). So
    f(a-1) = f(-b+n-1) = (n-1)/n f(a) = (n-1)/n. Backsolving gives f(-b+x) =
    x/n. Finally, f(0) = f(-b+b) = b/n = b/(a+b)

## QuantNet

Note: like in rejection sampling for MC integration, the subset will be
uniformly sampled if the superset is uniformly sampled.
  * Useful reminder for listing out all outcomes, even if some end early

Bet on best-of-3 match ending in 2 or 3 rounds?
  * AAA, AAB, ABA, BAA, ABB, BAB, BBA, BBB -- 50-50, but if one team is better
    then the chances shift towards 2
  * List out all 3-game options. Don't end at 2 for some! Undersamples due to
    lower number of games (lower entropy)
  * Can also solve with binomial distribution: P(goes to 3) = P(1W1L) = 2C1 p
    (1-p)

Odds of going to game 7 of world series, if both teams are equally matched
  * Draw Bertrand's poll problem chart. Want to get to (3,3) then go to (4,3) or
    (3,4). Total ways to get to (3,3) is 6C3 = 20, then x2 to get 40. Total
    orderings of all games is 2^7 = 128. Final answer is 40/128
  * Can also solve with binomial distribution: P(goes to 6) = P(3W3L) = 6C3 p^3
    (1-p)^3

Place 3 dots randomly on square edges. Chance of distinct edges?
  * 4! / 4^4 = 6/64

Total handshakes for 10 people
  * 10C2

Win if top 2 cards are red. Pick 52-card deck or 104-card deck?
  * 104-card deck has less finiteness impact

Calculate 39 x 41
  * (40-1)(40+1) = 1600 - 1 = 1599

Determine average salary anonymously
  * 1st person writes their salary plus a random number. Each next person adds
    their salary. Finally, first person subtracts random number to get sum.

How many digits in 99^99?
  * `99^99 = (10*9.9)^99 = 10^99 * 9.9^99 = 10^99 * 10^(99 log10 9.9)`... then I
    got stuck
  * Use limit to e: 99^99 = 100^99 * (1-1/100)^99 ~ 10^198 * 1/e, so 198 digits
  * Definitely smaller than 10^198 (because it's smaller than 100^99). Now set
    up `(100/99)^99 = (1+1/99)^99 < e < 10`. So 10 * 99^99 > 100^99 --> 99^99 <
    10^197. So 99^99 is sandwiched between 198 and 199 digits. Must be 198

Drunk passenger with 100 total passengers.
  * Not the same as a random permutation!
  * Set up base cases: n=2: AB or BA --> 1/2, n=3: ABC BAC BCA CAB --> 1/2.
  * In general, 1/n chance of correct seat, 1/n chance of your seat, 1/n chance
    of bumping 2nd guy (who then becomes drunk), 1/n chance of 3rd guy...
  * `1/n (1 + (n-1 problem) + (n-2 problem) + ... + (2-problem) + 0) = 1/n (1 +
    (n-2)*1/2) = 1/2`, since all subproblems have solution 1/2 (by induction)

Sum of numbers 1 to 100
  * Use sum formula `100*101/2 = 50*101 = 5050`

Measure 4 gallons using a 3-gallon and a 5-gallon jug
  * (0,0) (3,0) (0,3) (3,3) (1,5) (1,0) (0,1) (3,1) (0,4)

A has n+1 coins and B has n. Probability of A having strictly more H?
  * (from green book) for first n, x + y + x = 1, where x is P(A has more H)
    and y is P(same H). P(A wins) = 0.5*y + x = 0.5(1-2x) + x = 0.5
  * Can also argue from symmetry

Probability of drawing 2 cards of same color, without replacement
  * Draw any color, then 25/51

3 light switches. Allowed 1 visit. How to determine wiring?
  * Set (on,off,off) for a while. Then quickly set (off,on,off) and check. Hot
    but off one is first switch, on one is 2nd, other off is 3rd

Probability of even number of heads in 100 throws?
  * For odd number of throws, distribution is symmetric (0H - 5H, e.g.). Adding
    another toss shouldn't change anything greatly, so the probability at least
    goes to zero as n goes to infinity
  * Simpler: even/odd H is only determined by final toss. 50-50.

Probability of no BB for 3R, 2B?
  * Total orderings is 5C2 = 10. Orderings with BB is 4C1 = 4. Answer is 6/10

Least multiple of 15 with only 0s and 1s
  * 15n = (10+5)n = 10n + 5n. n must be even bc all odd multiples of 5 have a 5.
    So 15(2n) = 30n = 10 * 3n -- it must be a multiple of 3. 3,6,9,12,15,18,...
    99,102,105,108,111. Can skip over middle because 10s place is non-0/1.
    Answer = 111 * 10 = 1110
  
Is 1027 prime?
  * No, because 1027 = (10^3 + 3^3) = (a^3 + b^3), which can be factorized

Does volatility increase price of a call?
  * Yes, as does more time to expiry

Put 2B and 2R in a box. Get $1 for each correct guess. EV of game?
  * List all games BBRR, BRBR, BRRB, RRBB, RBRB, RBBR. Guess more likely color,
    with ties going to B. Then price out winnings for each game. EV = 17/6

What is the singles digit of 2^230?
  * Powers of 2 have single digits pattern 2,4,8,6,2,4,8,6... 230 is an even
    number but not a multiple of 4, so the answer is 4.

## Jane street guide

Probability of product of 2 d6 rolls is odd? 3 rolls?
  * Make a table. Find 9/36 = 1/4 for 2 rolls. Extending out into 3rd dimension
    halves each odd cell, leading to 1/8 
  * Alternatively: Product is only odd if each number is odd. Thus, (1/2)^n

Probability of 2H given at least 1T for 3 coin tosses
  * List possibilities: HHH, HHT, HTH, THH, TTH, THT, HTT, TTT. Remove 1st
    option. Thus, answer is 3/7
  * Alternatively: P(2H | >=1T) = P(2H and >=1T) / P(>=1T) = 3/7

Probability of 2H in a row
  * Set up Markov chain linear equations and solve
  * Note that E[T] = E[start], since flipping a T is like starting over
  * Recursion relation starts from end: E[nH] = 1/2(E[n-1H] + 1) + 1/2(E[n-1H] +
    1 + E[nH])
    * Make it to n-1H, then flip H (success) or T (fail, and start over)

## Aaron Cao guide

Write code to generate the integer partitions of a given number
  * Can generate partitions themselves using backtracking
  * Can generate number of partitions using DP. Same as P-518 Coin Change 2

How to cluster variables by covariance?
  * Easy: use k-means clustering with pairwise distance = 1 - Corr[A,B]

Expected number of adjacent pairs of aces in shuffled deck?
  * Easy way: glue 2 aces in 12 ways, then arrange 51 new cards. 12/52 = 3/13
  * Indicators: probability that ith and i+1th cards are aces is 4C2 / 52C2 = 6
    / 1326. Now take E[sum(E[Xi])] = sum(E[Xi]) = 51 * 6/1326 = 3/13

What problems arise with multiple inheritance?
  * Diamond problem: does D implement B's or C's virtual function?
  * C++ requires explicit statement, like `B::fct`

Generate all partitions of a given natural number

Generate all valid anagrams of a word, given a dictionary
  * Brute force: generate all anagrams then check which are valid. Takes O(s!)
    time. Can use backtracking
  * Better: sort all words in dictionary, or make into set/Counter object. Check
    if your sorted word/Counter is in the dictionary. Takes O(w s) or O(w s log
    s) time

Expected number of card draws until an ace?
  * Set up `___A1___A2___A3___A4___`, then expect 48/5 in each blank. Add 1 to
    get 53/5 = 10.6

Alice samples once from U(0,1). Bob samples until beating Alice. E[Bob samples]?
  * E[B] = integral(E[B|A=a] P(A=a) da) = integral(1/(1-x) dx) from 0 to 1 using
    expectation of geometric variable. Integral does not converge

Given n unit vectors in n-dim space, find a vector with same angle to all
  * Find center of (n-1)-dim sphere intersecting vector ends by solving n
    equations with n unknowns (O(n^2) time)
  * Alternatively: note that our vector `w` is orthogonal to all `vi - v1`.
    Compute the subspace orthogonal to span(vi - v1) in O(n) time using
    Gram-Schmidt

How to prevent overfitting?
  * Add more data, augment data, use sparser models, regularization,
    cross-validation, early stopping, ensemble methods such as bootsrapping or
    bagging 

Sample uniformly from a unit circle
  * Rejection sampling: get x and y (-1,1), then check if `x^2 + y^2 <= 1`
  * Rotational sampling: get t (0,2pi) and u (0,1), then calculate sqrt(u) to
    get final radius.
    * `Y = sqrt(U)` --> `U = Y^2 [Y>=0]`. `fY(y) = fU(y^2) |2y| ~ y`, which is
      desired because Jacobian volume infinitesimal is `r dr dt`

Determine the eigenvalues of a matrix with n on diagonal and 1 elsewhere
  * Action of this matrix clamps down and extends along 45-deg direction,
    shrinking orthogonal directions.
  * Manual way with 2D example gives eigenvalues (n+1), (n-1). In higher
    dimensions, there's still 1 n+1 eigenvalue but now many copies of n-1 
  * Answer is apparently (2n-1) instead of (n+1)

X and Y are iid std Normals. Find P(X | X+Y >0)
  * Long way: find P(X, X+Y) = `[[1,0],[1,1]] [X, Y] = [X, X+Y]` with `mu =
    [0,0], cov = [[1,1][1,2]]`. Then take integrals
  * Short way: `P(X | X+Y>0) P(X+Y>0) = P(X+Y>0 | X) P(X)` --> `P(X=x | X+Y>0) =
    2 cdf(x) pdf(x)`, where `cdf(x) = P(x+Y > 0) = P(Y > -x) = P(Y < x)`

Implement a stack with 2 queues. Now with 1 queue
  * 2 queues: pop n-1 to other queue, then go vice versa
  * 1 queue: enqueue(pop) n-1 times

Bob claims he can discern candy color by taste. He tastes 3 candies and says 2
colors correctly. There are 5 total colors. Is he legit? How about 40/100?
  * Test hypothesis `p > 0.2`. Under null, `P(X >= 2) = P(2) + P(3) = 3C2 (.2)^2
    (.8) + 3C3 (.2)^2 = 0.104`, not significant
  * Use Normal approx with `Normal(20, 100 * 0.2 * 0.8 = 16)`. Significant

Optimal bet sizing for $100 bankroll, p = 0.5, winnings = 1.2x
  * Kelly criterion: maximize `f_final = f0 * (1+wx)^p (1-lx)^(1-p)` w.r.t. x to
    get `x = p/l - (1-p)/w`. Here, `l = 1`, `w = 1.2`, `p = 0.5`, so 1/12

### Statistics

What happens to R^2 when adding independent variables?
  * Generally get a better fit, but R^2 can increase or decrease. Could overfit.

If A and B are covariance matrices, is AB?
  * No, unless specifically AB = BA in which case it's symmetric. AB remains
    positive semidefinite

Bounds on correlation between X and Z if Corr(X,Y) and Corr(Y,Z) given
  * Set up correlation matrix, then take determinant and set >= 0
  * Don't forget that full range is (-1, 1)!

How to generate points on uniform disk from Normal dist? Vice versa?
  * Use Box-Muller in reverse! Generate 2 Normal points, then scale out to lie
    on desired radius. Vice versa is just traditional Box-Muller

X and Y are indep. Normals. 
  * P(Y > 3X | Y > 0)?
    * Joint pdf is circularly symmetric, so draw desired region and figure out
      angle = arctan(3). Thus, probability = 1 - arctan(3)/pi ~= 60%
  * P(Y > 3X)?
    * Draw diagram and see that it's 1/2 by circular symmetry
  * P(Y > X | Y>0 and X>0)?
    * Again, 1/2 by symmetry

## Other

Calculate 1/(1 + 1/(1 + ...))
  * Recursion: x = 1/(1+x) --> x^2 - x + 1 = 0 --> x = (-1 +/- sqrt(5))/2. 

Stick-breaking questions
  * Expected length of smaller of 2 segments: integral from 0 to 1/2 of (x) +
    integral from 1/2 to 1 of (1-x) = 2 * 1/8 = 1/4
  * Expected length of smallest of 3 segments: set up square, then specify X <=
    Y (top-left 1/2 of square), X <= Y-X, X <= 1-Y (1/3 of possible mins). Do
    integral from x=0 to x=1/3 of integral from y=2x to y=(1-x) of (x). Then
    multiply by 3 for min possibilities and then 2 for X <= Y. This represents
    normalization for the pdf. Final answer 1/9
  * Chance of forming triangle: set up square, then specify X <= Y, X <= Y-X <=
    1-Y. These conditions require normalization constant 2 * 3! = 12. Area is
    bounded by Y=1/2, Y=(X+1)/2, and Y=2X. Find areas of two triangles = 1/64 +
    1/192, then multiply by 12 to get 1/4
    * Triangle area can be found via `1/2 det(x0 y0 1, x1 y1 1, x2 y2 1)`
    * Alternatively, set up equilaterial triangle wherein points represent stick
      lengths (by altitude theorem). Success if point in middle triforce.

Egg drop: given 2 eggs, create an algorithm to minimize worst-case time to
determine floor threshold for egg breakage
  * Simplest: 1,3,5,...,99 then you immediately know. This is 50 in worst case.
  * Skips: 10,20,30,...100 then you iterate through 9. This is 19 in worst case.
  * Dynamic: start at x, then increment by (x-1),(x-2),...,1. This is x in worst
    case. Solve 1+2+...+x = 100 --> x = 13.6 --> answer = start at 14, then 27,
    then 39, then 50,... then increment when needed.
