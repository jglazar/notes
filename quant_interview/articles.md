# Articles

## Catalan numbers

Many equivalent forms 
  * `Cn = 1/(n+1) C(2n, n)`
  * `Cn = Product from k=2 to k=n of (n+k)/k`
  * `Cn = 1/(2n+1) C(2n+1, n)`
  * `Cn = C(2n, n) - C(2n, n-1) = C(2n, n) - C(2n, n+1)`
  * Sequence starting from `n = 0` is 1,1,2,5,14,42,132,429...

Satisfies recurrence relation `C0 = 1`, `Cn+1 = Sum from k=0 to k=n of Ck Cn-k`
  * Or, `Cn+1 = 2(2n+1)/(n+2) Cn`

Grows as `Cn ~ 4^n / (sqrt(pi) * n^(3/2))`

The only odd Catalan numbers are where `n = 2^a - 1`

It's the answer to popular problems asking for the number of...
  * Dyck words with `n` As and `n` Bs, where no substring starting from the
    beginning has more Bs than As
  * Valid open/close parentheses strings with `n` pairs of parens
  * Ways to parenthesize `n` factors
  * Non-isomorphic ordered trees
  * Lattice paths from `(0,0)` to `(n,n)` not passing above the diagonal
  * Ways to form `n` triangles from a polygon without intersecting lines
  * Permutations of `1...n` without a 3-unit increasing run 

Typical problem has structure like:
  * Every Dyck word can be written as `XaYb`, where `a` and `b` are Dyck words.
    This has recurrence relation above.

Nice solution from reflection principle, using lattice path interpretation:
  * Easier to see on diagonal grid with only (even, even) or (odd, odd) points
  * Consider paths ending at -2 height. Flip those paths across
    horizontal line at -1. Now those paths end at 0 height with at least one
    point touching horizontal line at -1. Reflection Principle states that those
    paths comprise all the bad paths.
  * Total bad paths = `C(2n, n-1)`

## Bertrand's ballot problem

Given `n` total votes with `a = n(1-p)` for A and `b = np` for B, with `0 < p <=
0.5`, what is the probability B is never ahead of A as the ballots are counted?

Same as Catalan, but with A != B
  * Total ways = `C(n, b)`
  * Bad ways = `C(n, b-1)` by reflection about -1 line
  * Good probability is `(a+1 - b) / (a+1) = (n(1-p)+1 - np) / (n(1-p)+1) =
    (n-2np+1) / (n-np+1)`

If no ties allowed, give A 1 vote then proceed with `n-1`, `a-1`, `b`
  * Good probability is `a/n * (a-b)/a = (a-b)/n = (n(1-p) - np) / n = 1 - 2p`
    * `a/n` is probability of getting first vote as A
