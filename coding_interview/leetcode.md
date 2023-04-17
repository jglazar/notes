# Leetcode problems

Good collection by topic [here](https://leetcode.com/discuss/study-guide/448285/List-of-questions-sorted-by-common-patterns.)

General binary search template [here](https://leetcode.com/discuss/study-guide/786126/Python-Powerful-Ultimate-Binary-Search-Template.-Solved-many-problems)

## Recursion

Some languages can optimize tail recursion calls s.t. further calls overwrite
prior calls' memory locations
  * Only possible if sole recursion call is in final `return` statement
  * Python is not one of these languages

### Linked Lists

Linked lists are good candidates for recursion practice
  * Simplest implementation is typically stack, so you can reverse
  * Recursion incurs `O(n)` space and emulates stack
  * Better method is typically iteration with two pointers for `O(1)` space

Common idiom for LL recursion is `if not h: return None; h.next = f(h.next); 
return h if condition else h.next`
  * This zips to the end of the list, then unravels back like a stack
  * See P-83 Remove Duplicates or P-203 Remove Values

P-206 Reverse -- keep iterator on previous and current

P-234 Palindrome has easy `O(n)` space stack solution. 
  * `O(1)` space reverses latter half of list, then checks in tandem 
  with two pointers. "Floyd's algorithm"
  * Emulate stack with (ugly) recursion -- zip to end like above, then check 
  against nonlocal header node and set nonlocal flag if bad.

Useful tip: initialize dummy header that points to real header, then do work, 
then return `dummy.next` at the end. Helps deal with empty edge cases.

P-21 Merge Two has simple and efficient iterator solution with one pointer on
each list, a `current` pointer, and a `dummy_head` for safety
  * Recursion compares two nodes, then edits the min node's `next` field 
  via `min_node.next = f(min_node.next, max_node)` and finally `return min_node`

## Math

P-50 Power has simple `O(n)` iteration/recursion, but you can get `O(log n)` 
time by halving the exponent if even, and subtracting one if odd.

P-779 Kth Symbol has brute force `O(2^n)` recursion solution, building up 
rows one at a time. 
  * Better is to use rules to find patterns for even/odd indices, then 
  traverse backwards one row at a time. `O(n)` time.

P-231 Power of 2 recursion checks if `x==1`, then if `x%2==0` proceed to halve. 
  * Don't forget to check for `x<=0`, for which the answer is False

P-1232 Check if Line requires check for vertical line (divide by zero). Can also
use triangle rule to see if every group of 3 (consecutive) points has zero area
  * `1/2 * det(A_ij), A_i =[[x_i, x_j], [y_i, y_j]]`, where typically `j = i+1`
  * Shoelace formula gets sum of overlapping dets `det(A_12) + det(A_23) + ... + 
  det(A_n1) = det([[x1,x2,...,xn,x1],[y1,y2,...,yn,y1]]) = det(transpose)`
    * Shoelace formula reduces `2n` columns to `n` columns
  * Very useful for calculating area of polygon with `n` points

## Divide and Conquer

1. Divide `sub_problems = divide(p)`
2. Solve `solutions = [f(p) for p in sub_problems]`
3. Merge `return merge(solutions)`

General framework:
  * define `Problem` and `Solution` objects 
  * `f` maps one Problem to one Solution
    * `def f(p): evaluate current problem, then 
    return merge([ f(pl) for pl in divide(p) ])`
    * Evaluation ensures `divide` doesn't get too small a problem
  * `merge` maps a list of Solutions to one Solution
    * `def merge(ss): ...`
  * `divide` maps one Problem to a list of Problems
    * `def divide(p): ...`
    * Can filter out irrelevant subproblems

May need to only apply `f(pl)` to some subproblems -- e.g., quick-sort

### Examples

Validate BST
  * `class Problem: TreeNode node, int lo, int hi`
  * `class Solution: bool valid` -- can simplify to raw bool
  * `def f: if not p.node: return Solution(True); 
  if p.node.val <= p.lo or p.node.val >= p.hi: return Solution(False); 
  return merge([f(pl) for pl in divide(p)])`
  * `def merge: return Solution(ss[0].valid and ss[1].valid)`
  * `def divide: return 
  [ Problem(p.node.left, p.lo, min(p.hi, p.node.val)), 
  Problem(p.node.right, max(p.lo, p.node.val), p.hi) ]`
  * Finally, call `f( Problem(root, -1<<32, 1<<32) ).valid` to get desired bool

Validate BST -- alternative explanation
  * remember to include lower and upper bounds! Can have tricky tree 
  where all subtrees are BSTs, but there's a violation further up the tree.
  * If going left, pass along new upper bound `max(hi, r.val)`. If going right,
    pass along new lower bound `min(lo, r.val)`.

Merge-sort -- focuses on `merge` step
  * `class Problem: List nums` -- can simplify to raw list
  * `class Solution: List nums` -- can simplify to raw list
  * `def f: if len(p) <= 1: return p;
  return merge([f(pl) for pl in divide(p)])`
  * `def merge: fill up long list by iterating through each short list`
  * `def divide: return [ p[:len(p)//2], p[len(p)//2:] ]
  * Finally, call `f(p)` to get desired sorted list

Merge-sort -- alternative explanation
  1. Split down middle to create only 2 subproblems
    * Just `return p` if empty or single
  2. Recurse with `merge( p[:len//2], p[len//2:] )`
  3. Merge: zip together each of the two arrays into a third array using iterators
    * If either iterator is at end, then trivially append other array to result
      array
    * Otherwise, pick the min of the two elements and increment the iterator

Merge-sort takes `O(n)` time for the zip stage, which happens `O(log n)` times.
Time complexity is `O(n log n)` and space is `O(n)` to store other array.

Quick-sort -- focuses on `divide` step
  * `class Problem: List nums` -- can simplify to raw list
  * `class Solution: List nums` -- can simplify to raw list
  * `def f: if len(p) <= 1: return p;
  return merge([f(pl[0]), pl[1], f(pl[2])])` -- skip over middle (equal to pivot) 
  to avoid infinite recursion!
  * `def merge: concatenate lists in order (inputs are pre-ordered!)`
  * `def divide: pick pivot, then create lists with x < p, x==p, and x > p`
  * Finally, call `f(p)` to get desired sorted list

Quick-sort has `O(N log N)` time complexity if median is selected every time.
`O(N^2)` time if min or max is selected, in which case it's equivalent to
insertion sort. `O(log N)` space due to recursion (no cost to build sublists?)

### Tips

⚠️  Some problems seem like DnC, but can more easily and efficiently be solved via
tree traversal (linear time rather than product of logarithm)
  * E.g., P-240 search 2D matrix is actually a binary tree starting from
    the top-right corner. This gives `O(m + n)` time
  * 👍 Good example of using all the rules, plus changing perspective
  * My DnC solution considers each of 4 submatrices, throwing out those whose
    range (topleft - bottomright) doesn't include target. I think this gives
    `O(log m log n)` time. If only 1 submatrix is valid at each pass, you get 
    best case `O(logmn) = O(log m + log n)` time

### Master theorem

Time complexity has general recurrence `T(n) = a * T(n/b) + f(n)`
  * `f(n)` is time to divide and merge, which is normally `O(n^d)`
  * Typically, `a = b` since all subproblems need to be solved

3 cases
  1. `a < b^d` or `d < log2(a) / log2(b)` --> `O(n^logb(a))`
    * e.g., max depth of binary tree has `a = b = 2` and `d = 0`
  2. `a = b^d` or `d = log2(a) / log2(b)` --> `O(n^d log(n))`
    * e.g., binary search has `a = 1`, `b = 2`, `d = 0`
    * e.g., merge-sort has `a = 2`, `b = 2`, `d = 1`
  3. `a > b^d` or `d > log2(a) / log2(b)` --> `O(n^d)`
    * e.g., quickselect has `a = 1`, `b = 2`, `d = 1`

Only works if subproblems are the same size! Won't work for fibonacci, e.g.

## Backtracking

Build candidates, then abandon those as soon as it cannot yield a valid solution

Useful for constraint satisfaction problems

Similar to DFS

General framework:
  * define `Candidate` object, global current solution variable, and global
    solutions vector or counter
  * `f` handles `Candidate` and returns nothing, altering global variable along
    the way
    * `def f(c): if at_end(c): output(c); return; else for cl in possible_next(c): 
    if is_valid(cl): place(cl), f(cl), remove(cl)`
  * Each recursion is next step closer to end. Each iteration within recursion 
  is at same spot 
  * Backtracking should happen within iteration
  * `is_valid` prunes search zones, like `not_attacked` for N-queens
  * `place` and `remove` are symmetric

### Examples

Traverse trie to find word -- if current node has wrong letter, then
backtrack and move to next candidate. If it has correct letter, continue
downwards

P-52 Number of ways to place N queens on NxN chess board -- iterate over rows 
and cols, placing queen if not under attack. Remove queen if bad solution.
  * `Candidate` need not be full `(x,y)` coord bc we need exactly 1 queen per
    row
  * `def f(row, count): for col in range(n): if not_attacked: place_queen and if 
    bottom then increment count, else count = f(row+1, count); remove_queen; 
    return count`
  * `remove_queen` peels back queens for next iteration

P-37 Sudoku solve
  * `Candidate` is `(x,y,n)`
  * Keep track of board, empty squares, and finished state
  * Use standard template for `f(c)` 
  * `is_valid` checks row and column and box
  * `place` pops from `empties` and edits board
  * `remove` appends empty spot back to `empties` and updates board
  * `possible_next` takes (not pops!) from end of `empties` and constructs 9
    possible numbers for that coord
  * `at_end` checks if `empties` is empty
  * `output` sets `finished` flag to `True` 

P-77 Combinations
  * Easiest solution is 2 pointers
  * One backtracking-ish answer has lists as `Candidate`, which obviates
    `current_list` variable and `place`, `remove`, and `is_valid` functions
  * True backtracking has one integer as `Candidate`
  * `is_valid` checks if committee is empty or if `Candidate > committee[-1]`
  * `place` appends Candidate to committee, `remove` pops if not empty
  * `possible_next` is every int from 1 to n
  * `output` appends committee to list. Don't erase committee! Use
    `committee.copy()`!
  * `at_end` checks if `len(committee) == k`

P-22 Generate Parentheses
  * `is_valid`: `(` just checks if count exceeds n, `)` checks if count exceeds
    n and if there are at least as many matching `(` in string already
  * `place` appends paren to string
  * `possible_next` is just `["(",")"]`
  * `output` appends string to list. 
  * `at_end` checks if `len(string) == 2n`

P-78 Subsets
  * `Candidate` is `(value, idx, active)` tuple
  * `is_valid`: pass
  * `place/remove` adds/pops value to list if Candidate is active
  * `possible_next` is just next value in nums, either active or inactive
  * `output` appends (copy of) list to solutions list. 
  * `at_end` checks if `idx == len(nums)-1`

P-78 can also be solved by converting each binary number to a string with length
`len(nums)`, then interpreted as keep/skip
  * Another solution has nested iteration: `solns = [[]]; for n in nums:
    solns += [[n] + r for r in solns]`
 

## Unfold recursion to iteration

Helps prevent recursion stack overflow
  * Tail recursion optimization can help, but is not guaranteed

Recursion adds function call overhead and can duplicate calculations

Iteration is often much faster

Initialize stack or queue, push elements on, then iterate while stack/queue
isn't empty

P-100 Same Tree 
  * `deq = deque([(p, q),]); while deq: p, q = deq.popleft(); if not check(p,
    q): return False; if p: deq.append((p.left, q.left)), deq.append((p.right, 
    q.right)); after entire while loop return True`
