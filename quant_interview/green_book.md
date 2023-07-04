# A practical guide to quantitative finance interviews

## Calculus and linear algebra

Lagrange multipliers: `del f + sum(lambdai del gi) = 0`, w constraints `gi = 0`
  * E.g., min distance from origin to plane `2x + 3y + 4z = 12`. `g = 2x + 3y +
    4z - 12 = 0`. `f = x^2 + y^2 + z^2`. 

Positive semidefinite matrices have all eigenvalues >= 0

## Probability and statistics

## Markov chains

Problems

Wald's rule -- 

Problems

## Dynamic programming

Start from the end (known boundary conditions) and work backwards using
recursion relation

Find the best strategy and expected payout for a dice game where you win $1 for
each pip shown, except for 6 which wipes out all winnings and ends the game.
  * Walk in payoff space. 
  * Stop if EV of continuing is less than current payout
  * `E[x] = max(x, 1/6(x+1 + x+2 + x+3 + x+4 + x+5) + 1/6*0)`
  * Boundary conditions: value at 15, 16, 17, 18, 19 is self (bc we stop game)
  * Payout after building table using recursion relation is E[0] = $6.15

Find the best strategy and expected payout for a card game where you win $1 for
each red card and lose $1 for each black card
  * We walk through (b, r) space, where b and r are cards remaining in deck.
    Current payout is b-r. Probability of next black is b / b+r. 
  * Stop if EV of continuing is less than b-r
  * `E[(b,r)] = max(b-r, b/b+r E[b-1,r] + r/b+r E[b,r-1])`
  * Boundary conditions: value at (0,r) is $0, (b,0) is $b
  * Payout after building table using recursion relation is E[26,26] = $2.62

