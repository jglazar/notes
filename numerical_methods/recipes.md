# Numerical Recipes in C

## Linear algebra

## Sorting

In order from bad to good:
  1. Bubble sort sucks
  2. Insertion sort is best when `N < 50`
  3. Shell's method optimizes insertion sort -- good when `50 < N < 1000`
  4. Heapsort works in-place and is simple -- authors' favorite!
    * (+) Consistent +/- 20% of average performance
    * (+) Best case is `O(N)`
    * (-) Cache thrashing due to large jumps to heap children
  5. Quicksort is faster than heapsort by about 2x when `N > 1000`
    * (+) Much better cache coherency
    * (-) Requires some extra `2 log2 N` stack memory
    * (-) Somewhat complicated, esp. with optimizations
    * (-) Worst case is `O(N^2)` if data is sorted -- can fix with random pivot
  6. Quicksort with insertion sort when subarrays have `N < 7`

Shell's method sorts groups of offset pairs, then offset quads, then offset
octets...
  * Helps pre-sort to prevent insertion sort from wandering far down on inner loop
  * Worst case `O(N^3/2)`, average case `O(N^1.27)`

## Root finding

(Almost) always used bracketed search!

* No derivative -- Brent's method
* Can compute derivative -- Newton-Raphson with bounds
* Polynomial -- Laguerre's method
* Multidimensional -- Newton-Raphson, with great 1st guess

## Random numbers


