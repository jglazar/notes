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

### Examples
