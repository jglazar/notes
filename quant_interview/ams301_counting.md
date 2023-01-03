#Applied combinatorics -- counting

## General counting

### Basics

✅ Make sure events are disjoint

Addition -- ways to select from n mutually disjoint sets = sum(ri)

Multiplication -- ways to create procedure from mutually independent 
steps is prod(ri) if all outcomes are distinct
  * Set composition principle -- possible members of 1st and 2nd parts 
  must be disjoint. E.g., cannot pick women in 1st part and then further 
  women in 2nd part. That would make 2 processes produce same output.

E.g, How many ways to make 3-letter word from abcdef with an e and 
repeats allowed?
  * Cannot just do 3 * 6^2 because that overcounts eex and eee
  * exx = 6^2, yex = 5 * 6, yye = 5 * 5 (x can be e, y cannot be e)
  * Alternatively, use incl-excl to get 3 * 6^2 - 3 * 6 + 1 where we 
  add all possibilities, remove eex, then add back eee

E.g., How many ways are to pick spade then non-queen?
  * 2 cases -- non-QS = 12 * 47, QS -- 1 * 48

For identical object collections, create a pair (ai,bi) and find 
total possible combos na * nb. Subtract 1 to remove (0,0) empty pair.
  * Nonempty collections of 5 apples and 8 oranges = 6 * 9 - 1

Easy to subtract out required conditions
  * 3-letter non-repeating sequences from abcdef with either e or f 
  or both = 6 * 5 * 4 - 4 * 3 * 2

Can stick together repeated letters to create new mega-letter
  * Words from "systems" with sss = ytemsss = 5!

Beware of overlapping cases
  * 7 women, 4 men. Create 4-person committee with >= 2 women. 
  C(7,2) * C(9,2) double counts w1 w2 m1 w3 and w1 w3 m1 m2. Instead, 
  break into cases: 2 women + 2 men, 3 women + 1 man, 4 women.

### Arrangement / selection with repetition

For "a appears before b", just allocate slots in C(n,2) ways, then place 
a first and b second (1 way). Then fill in rest of word

Subpositions can be handled by counting collection of slots, then 
filling in 1 way. Then count remaining ways to fill other slots. 
  * arrangements of banana with b before all a's. Select 6C4 slots and 
  fill with b a a a, then fill remaining slots with n's in 1 way.

Permutations with repeating objects can be counted with n!/r1!r2!... 
or nCr1 * n-r1Cr2 * ...

Hot dog problem -- allocate n identical objects to c categories in 
n+c-1Cn ways. Can also be used to collect objects from types.

Lower bound -- satisfy condition first, then count remaining possibilities. 
  * 5+3-1C5 ways to collect 10 balls from 3 colors, with at least 5+ red balls.

Upper bound -- count total - upper+1.
  * 10+3-1C10 - 4+3-1C4 ways to collect 10 balls from 3 colors, minus 
  ways including 6+ red balls

❗️ Hot dog problem subtraction includes all further cases -- no need to 
overcount!
  * Subtracting off 4+3-1C4 is sufficient to cover 6,7,8,9,10 red balls!
  * Subtracting off 5+3-1C5 is sufficient to cover 11,12,13,14,15,16 dimes 
  if only 10 available
  * ONLY incl-excl multiple boxes getting too many items, not one box 
  getting limit+1, limit+2, ... items

Equivalent to hot dog problem:
  * Select r objects with repetition from n types
  * Distribute r identical objects into n distinct boxes
  * Nonnegative int solutions to x1+x2+...+xn = r

Arrange/distribute distinct objects without repetition -- nPr, 
with repetition -- n^r, restriction -- nPr1,r2,r3 (some elements identical).

Combine/distribute identical objects without repetition -- nCr, 
with repetition -- n+r-1Cr 

### Distributions

Unique objects --> assign each object a label
  * Deal 52 cards to 4 players = 52!/13!13!13!13! 

Identical objects --> hot dog problem
  * Diophantine integer equation solutions

### Tricks

1. Consecutive elements -- glue together to make new single element
2. Relative order of subset -- pick positions and fill in 1 way, then proceed
3. Nonconsecutive elements -- arrange xxAxBxCxDxx and fill each middle 
slot with one element (in 1 way), then arrange remaining elements as-desired. 
Finally, arrange ABCD in any order (4! ways)

Subsequences are represented with binary, with 1 = "in" and 0 = "out". 
2^n possible ways (including empty subsequence)
  * Number of subsets of 6 ints between 1-20 with no consecutive ints = 
  x1x0x1x0x1x0x1x0x1x0x1xx = 9+7C9

H/T with run of H is same as hot dog problem, but boxes are spaces 
between T
  * 3H, 9T, how many ways with 5T in a row? Set up xHxHxHx and allocate 
  5T to one of the slots in 4 ways, then distribute the rest of the T in 
  4+4-1C4 ways

### Binomial relations

(1+x)^n = nC0 + nC1 x + nC2 c^2 + ... nCk x^k
  * alternating sum is therefore (1 + -1)^n = 0
  * x = 1 gives 2^n

Pascal's triangle has levels 1, 11, 121, 1331, 14641, ... which correspond 
to nCk for the kth element of the nth row (counting k and n from 0)
  * Combinatorial interpretation -- walk from (0,0) to (n,k) requires 
  walking n blocks and turning right k times. This leads to k R's and 
  (n-k) L's. There are therefore nCk ways to get to a given space.
  * Addition rule of Pascal's triangle therefore requires that nCk = 
  n-1Ck + n-1Ck-1

## Generating functions

Hot dog problem can be recast as finding coefficient of x^r in generating 
function expansion. Bounds can be modeled as minimal/maximal exponents.
  * x^6 coefficient of (x + x^2)^4 gives number of ways to choose 
  6 objects from 4 types with a min count of 1 and a max count of 2

Polynomial expansions
  * 1 / (1-x) = 1 + x + x^2 + ...
  * (1 - x^(m+1)) / (1-x) = 1 + x + x^2 + ... + x^m
  * 1 / (1-x)^n = 1 + i+n-1Ci * x^i + ...
  * (1 + x)^n = nC0 + nC1 x + nC2 c^2 + ... nCk x^k
  * (1 - x^m)^n = 1 + (-1)^k nCk x^km
  * product gives coefficient arb0 + ar-1b1 + ... + a0br for x^r

nC0^2 + nC1^2 + ... nCn^2 = 2nCn due to (1+x) * (1+x) generating fcts

Pull out common x^k to get (1 + x + ...) form

E.g., 8T, 17H, no run of 6H or more. Set up xTxTxT...xTx which yields 
9 boxes, each of which can have up to 5 items. (1+x+x^2+x^3+x^4+x^5)^9 = 
[(1-x^6)/(1-x)]^9 = (1-x^6)^9 * 1/(1-x)^9. These have coefficients 
summing to 17 for 0-17, 6-11, 12-5 --> 1 * 17+9-1C17 - 9C1 * 11+9-1C11 + 
9C2 * 5+9-1C5. This does incl-excl for us!

Probability generating function has coeff of t^r as chance that X=r.
  * Binomial -- P(t) = (q + pt)^n for n trials
  * Neg. Binomial for number needed until 5th head -- P(t) = (1/2)^5 + 
  (1/2)^6 * 5C1 + (1/2)^7 * 6C2 + ... = (1/2)^5 * ( 1 / (1-t/2) )^5

Partition is (1+x+x^2+...) * (1+x^2+x^4) * (1+x^3+x^6) * ... because 
we can select singles, doubles, triples, ... like making change

Exponential generating functions contribute > 1 weight per integer solution.
  * e.g., number of words with a+b+c=4 and a<=2 has each solution give 4!/a!b!c!
  * divide each summation term x^r by r!, then multiply each 
  answer's coefficient by r!

Exponential expansions
  * exp(x) = 1 + x + x^2/2! + ... + x^r/r! + ... 
  * exp(x)^n = exp(nx) = 1 + nx + n^2 x^2/2! + ... + n^r x^r/r! + ... 
  * 1/2( exp(x) + exp(x) ) = 1 + x^2/2! + x^4/4! + ...
  * 1/2( exp(x) - exp(x) ) = x + x^3/3! + x^5/5! + ...

Constructing generating functions from A(x), B(x), and C(x)
  * if bn = d * an, then B(x) = d * A(x) 
  * if cn = an + bn, then C(x) = A(x) + B(x)
  * if cn = sum( ai + bn-i), then C(x) = A(x) * B(x)
  * if bn = an-k or 0 if i < k, then B(x) = x^k * A(x)
  * multiplying ar * r = derivative of a(x) wrt x, times x
  * build polynomials in r by repeatedly taking derivatives
  * a(x) * 1/(1-x) yields ar = sum(ai) to r

## Recurrence relations

### Basics
Arranging items -- an = n * a(n-1) yields factorial

Climbing stairs 1 or 2 -- an = a(n-1) + a(n-2) = Fibonacci sequence if 
a0 = a1 = 1

Drawing lines on page -- an = a(n-1) + n, because each new line bisects 
n existing regions into 2n, an increase of n

Towers of Hanoi -- an = a(n-1) + 1 + a(n-1), solution is 2^n - 1

No 012 in ternary sequence -- start with full n sequence and chop off 
from front: 1xxxx and 2xxxx are fine, but 0xxxx has issues with 012xx. 
So an = a(n-1) + a(n-1) + (a(n-1) - a(n-3)) = 3 * a(n-1) - a(n-3).

No 222 in ternary sequence -- consider n=4. 0xxx, 1xxx are ok but 2xxx is 
broken into 20xx, 21xx, which are ok but 22xx is broken into 220x, 221x, 
which are ok but 222x is disallowed. 
an = 2 * a(n-1) + 2 * a(n-2) + 2 * a(n-3)

Expected number of flips until HHH -- use total expectation. 
E(x) = E(x|T)P(T) + E(x|HT)P(HT) + E(x|HHT)P(HHT) + E(x|HHH)P(HHH) 
= (x+1)/2 + (x+2)/4 + (x+3)/8 + (3)/8 --> x = 14. Could try to find 
probability by counting fails with an = a(n-1) + a(n-2) + a(n-3) but 
Tribonacci sequence is unwieldy in calculations.

Solve recurrence relations with backwards substitution or 
guess a solution + check with induction.

Collecting items -- an,k = an-1,k + an-1,k-1 which is Pascal's Triangle

Distributing items with 2-4 objects per box -- an,k = an-2,k-1 + an-3,k-1 + 
an-4, k-1. With 3 colors gives i+3-1Ci prefactor

Placing parentheses -- an = sum from 1 to n-1 of ( ai * a(n-i) )

Ternary sequences with even number of 0s -- a(n-1) + a(n-1) + ( 3^(n-1) - 
a(n-1) )

Multiple conditions, like ternary sequences with even number of 0s and 1s -- 
an = even 0 and even 1, bn = even 0 and odd 1, cn = odd 0 and even 1, 
3^n - an - bn - cn gives odd 0 and odd 1. Then construct an = b(n-1) + 
c(n-1) + a(n-1) for starting with 1, 0, or 2 respectively.

All recurrence relations may be written as difference relations 
  * delta a = an - a(n-1)
  * delta^2 a = delta an - delta a(n-1) = an - 2a(n-1) + a(n-2)
  * a(n-1) = an - delta an
  * a(n-2) = an - 2 delta an + delta^2 an

### Divide and conquer

Recursively halve the problem, especially with binary trees

Typically has form an = c * a(n/2) + f(n)
  * c = 1, f(n) = d --> an = d * ceil( log2(n) ) + A
  * c = 2, f(n) = d --> an = An - d
  * c > 2, f(n) = dn --> an = A * n^( log2(c) ) + (2d/(2-c)) * n
  * c = 2, f(n) = dn --> an = d * n * ( ceil(log2(n)) + A )

Large n and f(n) ~ n^logk(c) yields an ~ n^logk(c) * log2(c). 
Large n and f(n) ~ p * n^q where q < logk(c) yields an ~ n^logk(c)

Set A to satisfy initial conditions. Replace 2 with k if k-ary tree. 
If k = c and f(n) = d, then an = A * n - d/(k-1)

Need to break into n = odd and n = even

Find biggest and smallest number in set. Naive method takes 2n comparisons. 
With DNC, we get 3n/2 - 2 comparisons. an = 2 * a(n/2) + 2 
if n even or an = a((n+1)/2) + a((n-1)/2) + 2 if n odd

Multidigit multiplication. Naive method takes n^2 multiplications. With 
DNC, split x = x1 * 10^(n/2) + x1 and y = y1 * 10^(n/2) + y2 so x * y = 
(x1 * y1) * 10^n + (x1 * y2 + x2 * y1) * 10^(n/2) + x2 * y2 and 
x1 * y2 + x2 * y1 = (x1 + x2) * (y1 + y1) - x1 * y1 - x2 * y2. Thus 
only 3 rather than 4 multiplications are needed! an = 3 * a(n/2) yields 
an ~ n^1.6

### Solving recurrence relations

an = c1 * a(n-1) + ... + cr * a(n-r) has solution b^n. 

Sub in for each term and divide eqn by smallest power to get 
characteristic eqn with r roots. 

Linear combos of b = root solutions are also equations. 
Choose the one that satisfies the initial conditions.

Fibonacci -- an = a(n-1) + a(n-2) --> b^n = b^(n-1) + b^(n-2) --> 
b^2 = b + 1 --> roots are (1+sqrt(5))/2 and (1-sqrt(5))/2. Initial 
conditions a1 = 1 and a2 = 1 give coefficient 1 = 1/sqrt(5) * (1+sqrt(5))/2 
and coefficient 2 = -1/sqrt(5) * (1 - sqrt(5))/2

Homogeneous recurrence relations have only dependence on ak. 
Inhomogeneous can involve f(n) in recurrence.

Similar to diff eqn, solve the homogeneous part first then add one 
"particular" solution to the inhomogeneous part.
  * f(n) = d --> particular solution = B (some constant)
  * f(n) = d * n --> particular solution = B1 * n + B0
  * f(n) = d * n^2 --> particular solution = B2 * n^2 + B1 * n + B0
  * f(n) = e * d^n --> particular solution = B * d^n

Can solve with generating functions by writing y = f(x,y) and solving 
for y.
  * an = a(n-1) + n --> an * x^n = a(n-1) * x^n + n * x^n --> 
  y - a0 = sum( an * x^n ) = sum( a(n-1) * x^n + n * x^n ) = x * y + 
  sum( n * x^n ). Then set a0 = initial condition and isolate y to 
  eventually get coefficient of x^n for value of an.

## Inclusion-Exclusion

2 sets --- N(A or B) = N(A) + N(B) - N(A and B), or 
N(not A and not B) = N(not (A or B)) = N - N(A or B)

✅ Define events A, B, C... and count the items in NONE of the sets. 
E.g. A = digit 1 <= 1, B = digit 10 >= 8, we want N(notA and notB)
  * Good for "void" problems -- ways to make sure 1 and 3 appear, 
  numbers relatively prime to some number, hands with at least one 
  card of each suit

E.g., How many arrangements of 0-9 have digit 1 > 1 and digit 10 
< 8?
  * Define A = digit 1 <= 1 and B = digit 10 >= 8. Then 
  N(notA and notB) = N - N(A) - N(B) + N(A and B) = 
  10! - 2 * 9! - 2 * 9! + 2 * 8! * 2

E.g., How many positive ints <= 70 are relatively prime to 70?
  * Define A = multiple of 5, B = multiple of 2, C = multiple of 7. 
  We want N( notA and notA and notC ) = N - N(A) - N(B) - N(C) + 
  N(A and B) + N(A and C) + N(B and C) - N(A and B and C)

✅ Draw out Venn diagram for problems involving 3 or fewer sets 
  * Good for visualizing weird intersections that don't immediately 
  work well with incl-excl principle
  * Define events which are easiest to count

General formula is: N(notA and notB and notC...) = N - S1 + S2 - 
S3 + ... + (-1)^k Sk + ... + (-1)^n Sn, where Sk is the sum of 
k-wise intersections
  * This is because an element in m of the sets is counted 
  1 - C(m,1) + C(m,2) - C(m,3) + ... (-1)^k C(m,k) + ... (-1)^m 
  C(m,m) = (1+x)^m = sum over k from 0 to m of x^k C(m,k) where 
  x = -1 --> count = 0
  * Corollary -- N(A or B or ...) = S1 - S2 + ... + (-1)^(k-1) Sk + 
  ... + (-1)^(n-1) Sn
  * Generally, Sk is a sum of C(n,k) different intersections

Generating functions automatically account for incl-excl

E.g., Count derangements of n items.
  * Want notA and notB and notC..., where notA = nC1(n-1)!, 
  notA and notB = nC2(n-2)!, etc.
  * Final sum is N - S1 + S2 - ... = n! sum(0, n, (-1)^k/k!)
  * The alternating sum limits to exp(-x)
  * Can actually use recurrence relation Dn = nDn-1 + (-1)^n

E.g., Graph coloring avoiding neighbor clashes
  * Total colorings N = c^v, event A = edge A has clash, event B = ...

E.g., 6 teachers pick 12 kids (6 twins). How many ways to get no twins together?
  * N = 12C2 * 10C2 * ... = 12!/2^6, Ai = twins i assigned to same, 
  N(notA1) = 6 * 10!/2^5, N(notA1 and notA2) = 6 * 5 * 8!/2^4, ...

E.g., Assign 26 identical balls to 6 distinct boxes, with 1,2,3 having <7 balls
  * N = 31C26, N(notA1) = 24C19, N(notA1 and notA2) = 17C12, ...
  * ❗️ ONLY incl-excl across boxes, not within boxes

E.g., Derangements of odd numbers up to n (even numbers may/may not)
  * N = 8!, N(notA1) = 7!, N(notA1 and notA3) = 6!, ...

E.g., Arrangements of aaabbbccc avoiding 3-in-a-row
  * N = 9!, N(notA1) = 7!/3!3!, N(notA1 and notA2) = 5!/3!, ...

E.g., Arrangements of aaabbbccc avoiding 2-in-a-row
  * N = 9!, A1 = single pair -> N(notA1) = 8!/3!3!, A2 = two pairs which 
  can be done by aaa or aabb -> N(notA1 and notA2) = [ 7!/3!3! + 7!/3! ], 
  A3 = three pairs which can be done aaabb or aabbcc, 
  A4 = four pairs which can be done aaabbcc or aaabbb, 
  A5 = five pairs which can be done aaabbbcc, 
  A6 = six pairs which can be done aaabbbccc

Number of elements in exactly m sets is Sm - m+1Cm Sm+1 + m+2Cm Sm+2 - ... 
and number in at least m sets is Sm - mCm-1 Sm+2 + m+1Cm-1 Sm+2 - ...
  * Proof of overcounting and undercounting is similar to incl-excl proof

## Pigeonhole principle

If there are more than k times the number of items as slots, then some 
slot must contain at least k+1 items. It could be that one slot contains 
ALL items, though.

✅ Questions often include:
  * "guarantee"
  * "2 elements have same number"
  * "there must exist"

✅ Identify holes by breaking range into sets, then show that there are 
< n sets necessitating an overflow in one set

✅ Can also find average value of something, then claim that at least one 
element must have at least that value

✅ Can assign each element in an array a value or pair of values, then 
show that those values must reach certain point

E.g., 10 0s and 10 1s arranged in ring. 2 such random rings may be rotated 
s.t. disks have at least 10 matches
  * (unsure if correct) 2^10 = 1024 possible 10-in-a-row orderings. 
  20!/10!10! / 19 = 9724 possible rotationally-equivalent rings. 
  Too many pigeons (rings) for holes (orderings)
  * Or, each place must match in 10 of the 20 possible rotations. Total 
  number of matches = 20 * 10 = 200, so average number of matches is 10. 
  There must therefore always be at least 10 matches

E.g., n^2 + 1 distinct numbers always have n+1 increasing subsequence or 
n+1 decreasing subsequence
  * assign each number in set a pair (ai, bi) with ai = longest increasing 
  subsequence so far and bi = decreasing. ai and bi are nondecreasing. 
  If ai,bi <= n then max pairings is n^2, but there are n^2 + 1 numbers. 
  So ai or bi must increase to n+1.

Tricky example -- 15 computers, 10 printers, how many connections required 
to guarantee 10 computers can print simultaneously?
  * Consider computers available to printer i. Need 6 connections per 
  printer, bc if only 5 then the remaining 10 computers could request 
  only 9 printers. Total >= 60.

E.g., Directed K5 has two matching vertices with same degree.
  * each vertex has deg 4 -> 1,2,3,4 possible but 5 vertices!

E.g., Set of 7 distinct ints has pair whose difference is a mult. of 10
  * if ends in 0 -> cannot have other ending in 0, 1->9, 2->8, ... and 
  cannot have repeats like 3 and 13. So only 0,1,2,3,4,5 are allowed but 
  we need 7 numbers

E.g., n+1 distinct ints from 1...2n have a pair of consective ints
  * 1,3,5,... has only n, so you need to fill in once to get n+1 ints

E.g., 12 ints sum to 99. 2 consecutive days must sum to >=17.
  * 6 pairs, but 16 * 6 = 96 < 99. So you must bump one pair

E.g., 8 distinct ints 1...14 always contain divisible pair
  * Can't have 1 or 2, then 3 doesn't work. 14-7 backwards barely 
  captures 7.
  * Or, break into divisible sets {2,4}, {3,9}, {4,8}, {5,10}, 
  {6,12}, {7,14}, and the remaining {11,13}. Must take 8 from 7 groups

E.g., Set of n ints has pair of ints whose difference is divisible by n-1
  * Consider a-b, a-c, a-d,... which may be (n-1)x+1, (n-1)y+2, ... 
  There are n-1 such pairs, but only n-2 possible remainders (no 0 or n)
 
E.g., Set of 8 ints summing to 20 has subset summing to 4.
  * Must have 1111 or 112 or 22 or 13. Can't have just 3+ because 8 * 3 
  = 24. Can't have just 1 or just 2 and 3+ because 7 * 3 = 21. Can't 
  have 12 because 3 * 6 = 18 > 17. Can't have 111 because 4 * 5 = 20 > 17

E.g., 10 distinct ints between 1 and 60 has 2 disjoint subsets with same sum.
  * There are 2^10 - 1 = 1023 nonempty subsets. There is a max subset sum 
  difference of 52+53+...+60 - 1 = 503. So subsets (pigeons) must be 
  assigned to overlapping sums (holes)

E.g., Each day has >=1 hour, each week has <=11 hours. 7 weeks total. 
Show that there is contiguous slice of days with exactly 20 hours.
  * (this proves that there must be two slices with the same sum) 
  There are 49+48+...+2+1=1225 possible contiguous slices of days. 
  There are 1,2,...,11 * 7=77 possible sums
  * Let f(n) be the number of hours studied up to day n. We prove that 
  f(n) and f(n)+20 are in the set. n ranges 0-49, f(n) ranges 0-77. 
  There are 100 pairs of f(n) and f(n)+20, and each f(n) is distinct 
  because there are no 0-days allowed. f(n)+20 ranges up to 97. So 
  there are 100 pairs vying for 97 slots, meaning there must be a pair of 
  f(n) and f(n)+20 in the set.

E.g., In a party with >=6 people, there are at least 3 pairwise friends 
or 3 pairwise strangers.
  * Pick a vertex. That vertex has 5 edges of color red (friends) or 
  blue (strangers). There must be at least 3 of one color. The ends of 
  those edges cannot make a monochrome triangle. Therefore, you must 
  pick the opposite color for those edges. This just creates a monochrome 
  triangle of the opposite color though.

Examples:
1. Sock pair picking has c holes, n = c+1 pigeons to get a pair
2. Hand shaking has n-1 holes (0 or n-1 is empty), n pigeons. 
Analogous to showing that degrees of vertices must have matching pair
3. Subset sum -- break range into {i, 10-i} classes, then n+1 items must 
not be able to each fit into different classes

## Induction

1. Set up base case(s)
2. Assuming theorem holds for 1,2,...,n-1, show it must hold for n
  * Equivalently, assume it works for n, then prove for n+1
  * Can also assume conclusion make math easier, then verify and remove 
  that assumption.

E.g., sn = n * (n-1)/2. Base case s1 = 1 * 2/2=1. Assume s(n-1) = (n-1)n/2. 
Can expand sn = s(n-1) + n = (n-1)n/2 + n = 1/2 * [ (n-1)(n) + 2n ] 
= 1/2 * [ (n+1)(n) ]  = sn formula. QED.

E.g., Every number >1 has a prime factorization. p2 = 2, p3 = 3, ... pn = 
n if n prime. If composite, then n = k * m, where k,m < n. But all numbers 
less than n can be prime factorized, so k and m are prime factorized, so 
n is prime factorized. QED.

E.g., 2^n > n^2 for n>=5. Base case 32>25. 2^(n+1) = 2 * 2^n > 2 * n^2 = 
n^2 + n * n > n^2 + 5n = n^2 + 2n + 3n > n^2 + 2n + 1 = (n+1)^2

## Probability

Make sure the elementary events (outcomes) all have the same probability, 
then construct compound events
  * Box with 5R and 10B. P(R)? Sample space is not {R,B}, but rather 
  {BBBBBBBxBBRRRRR} -- 15 different cases

Collection of all elementary events comprise sample space

For trials (multiple dice throws, coin tosses), elementary events are 
now sequences of single outcomes

✅ In probability problems, treat all objects as distinct!
  * Each coin, die, ball, etc gets its own id number, with its own outcomes
