# Elements of Programming Interviews -- Algorithms

## Recursion

### Overview

✅ Useful for searching, enumeration, divide-and-conquer, and decomposition
  * Consider smaller cases, like dividing parameters by 2. Can many small cases be 
  combined into a bigger case?
  * How can you call the same function with a smaller argument?
  * Try forming a recurrence relation, like T(n) = T(n-1)+1+T(n-1) -> T(n)=2^n - 1

Requires base cases and progress toward base cases

Can be used instead of deeply nested iteration loops

Can be replaced with stack data structure, or simple while loop if tail-recursive 
(recursion only appears at last line of function, so no branching)

Use dynamic programming cache if function called with same args multiple times

### Examples

* Tiling chessboard with one corner missing using L-shaped pieces
* Towers of Hanoi, esp. with conditions
* Non-attacking queens
* Generating permutations
* Generating power set
* Generating all subsets of size k
* Generating strings of matches parentheses
* Generating palindromes
* Generating binary trees
* Solving sudoku
* Computing Gray code

## Dynamic Programming

### Overview

✅ Useful for optimizing, searching, and counting, especially when choices can be 
made along the way

Can fill cache bottom-up to conserve storage
  * e.g. only keep queue of length 2 for Fibonacci cache

Use memoryless principle to build up solution

### Examples

1. Unbounded knapsack
  * Create array with best value for that weight. Compare 
  max(v1 + m[w-w1], v2 + m[w-w2], ...) to get best value up to point
  * Coin change. Compare min( m[n-ca], m[n-cb], ... ) then add 1
2. 0/1 knapsack
  * Create matrix with best value up to that weight (j), given possible 
  subsequence of items (i). Compare diagonally with max( m[i-1, j-wj] + 
  vi, m[i-1,j] ) to decide to accept/reject new item
    * Switching indices: best value up to weight (i) given possible subsequence
      (j). Compare max( vj + m[i-wi,j-1], m[i,j-1] )
  * Longest increasing subsequence. Create array with longest subsequence 
  ending in that element. Requires iterating over previous elements of 
  array repeatedly -- O(n^2). m[i] = max( [m[i]+1 if n[i] < num] )
