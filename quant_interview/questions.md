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
