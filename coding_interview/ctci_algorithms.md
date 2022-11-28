# Cracking the coding interview -- algorithms

## Big O

May involve multiple variables 
  * don't reuse N multiple times!
  * consider different array lengths as separate variables

### Terminology

* big O = upper bound (can be even higher than lowest upper bound)
* big omega = lower bound (can be even lower than higher lower bound)
* big theta = tight bound, which is what we'll use

* best case is fairly useless
* worst case and expected case tend to be same, which is what we'll use

### Space 

Stack space that waits during recursion counts 

Branches don't exist in memory simultaneously, so branch problems 
are typically O(N)

### Runtime

Sequential operations add runtimes. Only keep the bottleneck.

Nested operations multiply

Drop any constant prefactors

O(x^x) and O(x! * 2^x) are both worse than O(x!)

A nice series to remember: x + x/2 + x/4 + ... = 2x

O(log N) happens when you divide problem each iteration
  * base doesn't matter bc it only multiplies by a constant factor

Branching processes in recursive calls normally cause O(branches^depth) 
runtime
  *  exponent base DOES matter, unlike in log

Memoization can bring down exponential to linear time (e.g. Fibonacci)

## Sorting + Searching

Most important search is binary
  * iterative or recursive methods can be tricky with +/- 1 

Also consider leveraging binary trees and hash tables

❗️General format:
1. Develop notation for states. Must be unique and hashable. Strings are good.
2. Establish hmap (Python `set`) with visited states -- can skip or use 
dict as memo to speed up search
3. Implement queue (BFS) or stack (DFS) for next state to search
4. pop, evaluate, add to visited, propose more moves, add to stack/queue

Takes O(branches^depth) time --> O(s) time with visited memo.
Takes O(s) space for stack/queue. s = state space, which will have 
problem-specific dependence on input length

### Sort

Bubble -- try swap 1+2, then 2+3,... then repeatedly start over
  * O(n^2) time, O(1) space

Selection -- put smallest at front, then 2nd smallest, ...
  * O(n^2) time, O(1) space

❗️Merge -- mergesort halves, then merge A and B (which are sorted): 
iterate through A and B, adding min element to helper until both empty
  * O(n log n) time, space is typically O(n)

❗️Quick -- pick middle element to partition around (ideally, 
true median). then find larger number to left and smaller number to 
right and swap
  * O(n log n) time with worst-case O(n^2), O(n log n) space
  * Can also be done more simply with helper `less`, `equal`, and 
  `greater` lists, concatenating in the end

❗️Radix/bucket -- group ints into 0-9 buckets on place i starting 
from ones place, using queue. Then dequeue in 0-9 order to make 
new array. Repeat.
  * O(kn) time where n = # elements and k = # passes (depth of ints), 
  * get digit using `(num // 10**digit) % 10`
  * instead of right -> left, go left -> right for strings

### Problems

1. Merge B into A, where B and A are already sorted
2. Sort array of strings with anagrams next to one another
3. Find element in rotated sorted array
4. Find index containing value x in array with no `length` method
5. Find location of given string in array interspersed with empties
6. How would you sort a 20Gb file with one string per line?
7. Generate an integer not occurring in a 4-billion entry file, using 
less than 1Gb memory
8. Print all duplicates in array with length up to 32k, using only 
4kb memory
9. Find an element in column-wise and row-wise sorted matrix
10. Track ranks in stream of integers
11. Sort array into alternating peaks and valleys

## Recursion + Dynamic Programming

✅ Useful for:
  * problem with subproblems
  * "compute the n'th" or "compute all"
  * "list the first n"

❌ Can be very space inefficient -- at least O(depth)
  * Consider implementing it iteratively (using a stack) instead, 
  discussing tradeoffs
  * Recursive depth limit in Python is 1000

Bottom-up: build solution up from simple case

Top-down: divide problem into subproblems

Half-and-half: cut dataset in half, like in binary search or merge sort

Dynamic programming takes advantage of overlapping subproblems 
(repeated calls) with a cache
  * Observe recursion call tree for repeated nodes
  * Call `function( input, memo )` instead of `function( input )`
  * Can sometimes just use last k members of memo, in which case you 
  can just dynamically change k individual variables (constant space)

✅ Use `@lru_cache` decorator before recursive function to create 
automatic memoization. Requires that function arguments are hashable, 
so that Python can create a dict behind-the-scenes

### Problems

1. Count possible ways to climb stairs, taking 1/2/3 steps at a time
2. Find grid path between top-left and bottom-right, with some 
forbidden cells
3. Find an index with a[i] = i in a sorted array with distinct ints
4. Return all subsets of a set
5. Multiply 2 positive ints using +, -, and bit shifting only
6. Towers of Hanoi
7. List all permutations of a string with unique characters
8. 7, but can be non-unique characters
9. List all valid combinations of n pairs of parens
10. Change contiguous color region on 2D grid
11. Calculate total number of ways to represent n cents using 
quarters, dimes, nickels, and pennies
12. List all ways of arranging 8 queens on an 8x8 chessboard to 
avoid attacks
13. Calculate height of tallest possible stack of WxHxD boxes, s.t. 
lower boxes are strictly larger than higher boxes
14. Count total number of ways to parenthesize boolean expression that 
returns some result
