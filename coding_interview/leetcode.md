# Leetcode problems

Good collection by topic [here](https://leetcode.com/discuss/study-guide/448285/List-of-questions-sorted-by-common-patterns.)

[14 Patterns](https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed)

## Blind 75

I was doing Neetcode 150, but there's some real duds (P-355 Design Twitter, P-4
Median of 2 Sorted Arrays)

Arrays and Hashing
  * 🟩 P-217 Contains Duplicate ☑️
  * 🟩 P-242 Valid Anagram ☑️
  * 🟩 P-1 Two Sum ☑️
  * 🟨 P-49 Group Anagrams ☑️
  * 🟨 P-347 Top K Frequent Elements ☑️
  * 🟨 P-238 Product of Array Except Self ☑️
  * 🟨 LOCKED Encode/Decode Strings
  * 🟨 P-128 Longest Consecutive Sequence ☑️

Two Pointers
  * 🟩 P-125 Valid Palindrome ☑️
  * 🟨 P-15 3-Sum ☑️
  * 🟨 P-11 Container with Most Water ☑️

Sliding Window
  * 🟩 P-121 Best Time to Buy/Sell Stock ☑️
  * 🟨 P-3 Longest Substring without Repeats ☑️
  * 🟨 P-424 Longest Repeating Character Replacement ☑️
  * 🟥 P-76 Minimum Window Substring ☑️

Stack
  * 🟩 P-20 Valid Parentheses ☑️

Binary Search
  * 🟨 P-153 Find Minimum in Rotated Sorted Array ☑️
  * 🟨 P-33 Search in Rotated Sorted Array ☑️

Linked List
  * 🟩 P-206 Reverse Linked List ☑️
  * 🟩 P-21 Merge Two Sorted Lists ☑️
  * 🟨 P-143 Reorder List 
  * 🟨 P-19 Remove Nth Node From End ☑️
  * 🟩 P-141 Linked List Cycle
  * 🟥 P-23 Merge K Sorted Lists

Trees
  * 🟩 P-226 Invert Binary Tree
  * 🟩 P-104 Maximum Depth of Binary Tree ☑️
  * 🟩 P-100 Same Tree ☑️ 
  * 🟩 P-572 Subtree of Another Tree
  * 🟨 P-235 Lowest Common Ancestor of BST
  * 🟨 P-102 Binary Tree Level Order Traversal ☑️
  * 🟨 P-98 Validate Binary Search Tree ☑️
  * 🟨 P-230 Kth Smallest Element in a BST
  * 🟨 P-105 Construct Binary Tree from Preorder and Inorder Traversal
  * 🟥 P-124 Binary Tree Maximum Path Sum
  * 🟥 P-297 Serialize and Deserialize Binary Tree

Tries
  * 🟨 P-208 Implement Trie
  * 🟨 P-211 Add and Search Word
  * 🟥 P-212 Word Search II

Heap
  * 🟥 P-295 Find Median from Data Stream ☑️

Backtracking
  * 🟨 P-39 Combination Sum ☑️
  * 🟨 P-79 Word Search ☑️

Graphs
  * 🟨 P-200 Number of Islands
  * 🟨 P-133 Clone Graph
  * 🟨 P-417 Pacific Atlantic Water Flow
  * 🟨 P-207 Course Schedule
  * 🟨 LOCKED Number of Connected Components in an Undirected Graph
  * 🟨 LOCKED Graph Valid Tree
  * 🟥 LOCKED Alien Dictionary 

Dynamic Programming
  * 🟩 P-70 Climbing Stairs ☑️
  * 🟨 P-198 House Robber ☑️
  * 🟨 P-213 House Robber II
  * 🟨 P-5 Longest Palindromic Substring
  * 🟨 P-647 Palindromic Substrings
  * 🟨 P-91 Decode Ways
  * 🟨 P-322 Coin Change ☑️
  * 🟨 P-152 Maximum Product Subarray
  * 🟨 P-139 Word Break
  * 🟨 P-300 Longest Increasing Subsequence ☑️
  * 🟨 P-62 Unique Paths
  * 🟨 P-1143 Unique Paths

Greedy
  * 🟨 P-53 Maximum Subarray ☑️
  * 🟨 P-55 Jump Game ☑️

Intervals
  * 🟨 P-57 Insert Interval
  * 🟨 P-56 Merge Intervals
  * 🟨 P-435 Nonoverlapping Intervals
  * 🟩 LOCKED Meeting Rooms
  * 🟨 LOCKED Meeting Rooms 2

Math
  * 🟨 P-48 Rotate Image ☑️
  * 🟨 P-54 Spiral Matrix
  * 🟨 P-73 Set Matrix Zeros

Bit Manipulation
  * 🟩 P-191 Number of 1 Bits ☑️
  * 🟩 P-338 Counting Bits
  * 🟩 P-190 Reverse Bits
  * 🟩 P-268 Missing Number ☑️
  * 🟨 P-371 Sum of Two Integers

## Arrays and hashing

### Filling in solution

Run through array(s), filling in `result` array as you go
  * Sometimes easier to go back to front to avoid shifts
  * ❗️ Don't forget array bounds checks within code blocks
  * Fast/slow pointer methods are useful for filling in 1st `k` elements
    * Fast = read, slow = write
 
P-1089 Duplicate Zeros has two solutions
  * Go front to back, adding extra zero to `res` and incrementing again 
  if `arr[p] == 0`
    * `O(N)` time and `O(N)` space
  * Count total zeros then decrement from back, placing elements `p + 
  zeros` ahead if possible. Decrement `zeros` and place extra 0 when 
  `arr[p] == 0`
    * `O(N)` time and `O(1)` space!

P-977 Squares of Sorted Array has no simple in-place solution
  * Square each element, then run 2 pointers from front and back to fill 
  solution array based on bigger element. Finally, flip array.
  
P-88 Merge Sorted Array goes backwards and fills in elements `m+n+1` ahead

Fast/slow pointers is great for deleting elements
 * `should_write` -- indicates when to pause `fast` pointer to write
 * `return slow` gives number of valid elements at beginning of `arr`

```
def should_write(l, r):
    pass
slow = fast = 0
while fast < len(arr):
    if should_write(slow, fast):
        arr[slow] = arr[fast]
        slow += 1
    fast += 1
return slow
```

Easy problems: 
  * P-27 Remove Element
    * `should_write(l, r): return arr[r] != val`
  * P-26 Remove Duplicates from Sorted Array
    * `slow = fast = 1` because 1st element is trivially valid
    * `should_write(l, r): return arr[l-1] != arr[r]`
  * P-283 Move Zeros
    * `should_write(l, r): return arr[r] != val`
    * `arr[slow], arr[fast] = arr[fast], arr[slow]`
  * P-905 Sort Array by Parity
    * `should_write(l, r): return arr[r] % 2 == 0`
    * `arr[slow], arr[fast] = arr[fast], arr[slow]`

### 2-pointers

You define:
  * `pick_left(l, r)` -- indicates when to increment `left`
  * `score(l, r)` -- e.g., width of window
  * If searching, halt search when item found

```
def pick_left(l, r):
    pass
def score(l, r):
    pass
left, right = 0, len(height)-1
best = score(left, right)
while left < right:
    if pick_left(left, right):
        left += 1
    else:
        right -= 1
    best = max(best, score(left, right))
return best

```

P-11 Water Container
  * `pick_left(l, r): return height[l] <= height[r]`
  * `score(l, r): return min(height[l], height[r]) * (r - l)`

P-15 3-Sum can be solved via hashing or 2-pointer trick
  * Hashing: Create hashmap, then do `O(N^2)` check over all pairs to find last
    remaining element
  * 2-pointers: Sort list, then do `O(N^2)` check down list with 2-pointers
    * `pick_left(l, r): return arr[l] + arr[r] < target`
    * If `pick_left(l, r)`, then decrementing `r` will never enable the correct
      answer -- increment `l` instead. Vice versa for `r`

### Sliding window

You can normally make a simplifying greedy assumption to avoid backtracking the
`right` pointer, which incurs a `O(N^2)` cost

You define:
  * `invalid(w)` -- indicates when to increment `left`
  * Structure to use for `window` -- `set`, `Counter`, even just `tuple`
    * Also, update functions for adding/removing items from `window`
  * `score(l, r)` -- e.g., width of window, unique elements in `window`

```
def invalid(w):
    pass
def score(l, r):
    pass
window = set(arr[0])  # could instead be Counter, tuple, dict, etc
left = right = 0
best = score(left, right) 
while right < len(arr) - 1:
    right += 1
    window.add(s[right])
    while invalid(window) and left < right:
        window.remove(s[left]) 
        left += 1
    best = max(best, score(left, right))
return best
```

P-121 Buy Stock 
  * `invalid(w): return prices[w[0]] > prices[w[1]]`
  * Use `(left, right)` tuple for window
  * `score(l, r): return prices[right] - prices[left]`

P-3 Longest Nonrepeat Substring
  * `invalid(w): return w.total() - w.most_common(1)[0][1] > 1`
  * Use `Counter` object with counts for each char in string
    * Add: `window[s[idx]] += 1`, Remove: `window[s[idx]] -= 1`
  * `score(l, r) return right - left + 1`

P-424 Longest Repeating Character Replacement
  * `invalid(w): return w.total() - w.most_common(1)[0][1] > k`
  * Use `Counter` object with counts for each char in string
    * Add: `window[s[idx]] += 1`, Remove: `window[s[idx]] -= 1`
  * `score(l, r) return right - left + 1`

P-76 Minimum Window Substring
  * This problem inverts the others -- `invalid` is true at beginning and we
    seek the smallest valid solution
  * `invalid(w): return any( w[v] - ref[v] < 0 for v in ref )` 
    * Likely can make quicker by additionally considering new characters
      added/removed
  * Use `Counter` object with counts for each char in string
    * Add: `window[s[idx]] += 1`, Remove: `window[s[idx]] -= 1`
  * Track `best_l` and `best_r` instead of copying substring
  * Change to `while not invalid(window)` and put `best_l/r` update inside loop

### Hashing

❗️ Watch out for 0 -- checking for `a * val in hash` will be trivially `True`

Useful for making time-space tradeoff, esp. to avoid sorting
  * Watch out for bounded input space

P-1051 Height Checker has all heights 1 - 100. Use a dict to store counts, 
then iterate through dict in order to avoid sorting

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

Use `(int(math.log10(x)) + 1)` to get number of digits for `x >= 1`. Faster and 
less memory than `len(str(x))`.

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

Quick-select returns index `k` with `kth`-smallest number
  * All elements to the left of `k` are smaller, but not sorted
  * Runs in `O(N)` time bc `1 + 1/2 + 1/4 + 1/8 + ... = 2`
  * Can be used to solve P-973 K Closest Points 

Quick-select with Lomuto partition scheme (simpler, but slightly slower):
  * Can select random element in `[lo, hi]` range, then swap that element
    with hi, perform partition, and swap back to avoid `O(N^2)` worst case 
  * Hoare's partition has two converging pointers

```
l = [...]
def f(lo, hi, k):
    while True:
        if lo == hi: return lo
        pivot_val = l[hi], cutoff = lo
        for i in range(lo, hi):
            if l[i] < pivot_val: 
                swap(l[i], l[cutoff]), cutoff++
        if k < cutoff: hi = cutoff − 1
        if k > cutoff: lo = cutoff + 1
        if k = cutoff: return k
```

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
  * Each recursion is next step closer to end. Each iteration within recursion 
  is at same spot 
  * Backtracking should happen within iteration
  * `is_valid` prunes search zones, like `not_attacked` for N-queens
  * `place` and `remove` are symmetric
    
```
def f(c): 
    if at_end(c): 
        output(c), return
    for cl in possible_next(c): 
        if is_valid(cl): 
            place(cl), f(cl), remove(cl)
```

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
 
P-39 and P-40 Combination Sum is straightforward
  * `Candidate` is `(value, idx, active)` tuple
  * `is_valid`: check if `sum(current) <= target`
  * `place/remove` adds/pops value to list if Candidate is active
  * (P-39) `possible_next` is next value with count up to `target//val`
  * (P-40) `possible_next `is next value with count up to `ctr[val]`, where 
  `ctr` is a Counter object and we iterate through `list(set(nums))` to 
  avoid duplicates
  * `output` appends (copy of) list to solutions list if `sum(current)==target`
  * `at_end` checks if `idx == len(nums)-1`

## Unfold recursion to iteration

Helps prevent recursion stack overflow
  * Tail recursion optimization can help, but is not guaranteed

Recursion adds function call overhead and can duplicate calculations

Iteration is often much faster

Initialize stack or queue, push elements on, then iterate while stack/queue
isn't empty

P-100 Same Tree 

```
deq = deque([(p, q),])
while deq: 
    p, q = deq.popleft(); 
    if not check(p, q): return False; 
    if p: deq.append((p.left, q.left)), deq.append((p.right, q.right)); 
return True
```

## Heaps

Heap is one way to implement the Priority Queue abstract data type, which
provides `O(1)` access to largest element 
  * Provides `O(log N)` insertion or deletion of any element
  * Other structures like array or linked list offer `O(1)` for one operation
    and `O(N)` for the other

Heap is a complete binary tree where the each node value >= values of children
  * Complete tree is filled top-bottom and left-right on each row

Insertion -- put new element in next slot to ensure complete tree criterion,
then swap upwards as-needed

Deletion -- replace desired node with last node in complete tree, then swap up
or down as needed
  * Usually only done on max element

Replacement -- replace node with new element and sift down. Avoid needless 
sift-up in extraction + insertion
  * Usually only done on max element

Cannot implement raw tree because we need to know where parents sit. Use 
underlying array where indexing starts at 1
  * `idx_parent = idx_current // 2`
  * `idx_left = idx_current * 2`
  * `idx_right = idx_current * 2 + 1`
  * Can store last element's idx in idx 0 for fixed-size arrays

Alternatively, start at index 0 and use:
  * `idx_parent = (idx_current - 1) // 2`
  * `idx_left = idx_current * 2 + 1`
  * `idx_right = idx_current * 2 + 2`

### Implementation

Keep heap and last index

Add value v to heap h:

```
h.append(v)
idx = last, parent = (idx-1)//2
while(h[idx] > h[parent] and idx > 0): 
    swap(idx, parent)
    idx = parent
    parent = (idx-1)//2
```
            
Delete top element:

```
save_top = h[0], h[0] = h[last], last -= 1, idx = 0; 
while(idx <= (last-1)//2): 
    l = idx*2+1, r = l+1
    if (h[idx] < h[l]) or (h[idx] < h[r]): 
        if (h[l] > h[r]): 
            swap(idx, left), idx = left 
        else: 
            swap(idx, right), idx = right; 
    else: 
        break
return save_top
```

### Examples

Python `heapq` module only implements min heap -- must negate items to implement
max heap

P-973 K Closest Points requires overwriting `<` operator
  * Can create custom class for items and define `__leq__(self, other)`
  * Better: bundle items into tuple with first element as key value

May be multiple ways to create heap
  * P-973 can create k-depth heap and loop through N items to get `O(N log k)`
  * Can instead heapify array, then pop off top k items for `O(N + k log N)`

## Arrays and hashmaps

Python `bisect` module has `insort(arr, val)` method to automatically do binary
search then insertion. 
  * Unfortunately, insertion still takes `O(N)` time
  * Performs Insertion similar to `bisect.insort(arr, val)`:
  
P-1046 Last Stone Weight is best solved with heap, but Timsort every iteration
could be quicker. Could also implement `bisect.insort` instead.

General binary search template [here](https://leetcode.com/discuss/study-guide/786126/Python-Powerful-Ultimate-Binary-Search-Template.-Solved-many-problems)
  * Returns `left` as index of minimal element that satisfies `condition`
  * You set:
    * `condition(idx)` function -- gives excuse to throw out right half of list
    * Left and right bounds -- could be [0, n], [1, n], etc.
    * Return value -- could be `left +/- 1`
  * Note: `left + (right-left)//2` helps avoid integer overflows, which aren't a
    problem in Python

Binary search problems
  * Find place to insert: 
    * `condition(idx): return arr[idx] > target`
    * `left, right = 0, len(arr)`
    * `return left`
  * P-704 Binary Search:
    * `condition(idx): return arr[idx] > target`
    * `left, right = 0, len(arr)`
    * `return -1 if (left==len(arr) or arr[left]!=target) else left`
  * P-153 Minimum in Rotated Array
    * ❗️ Check for order, not disorder! `condition` gives excuse to throw out
      boring region
    * ❗️ Need to edit `condition` to take in `mid` AND `right`
    * `condition(idx_l, idx_r): return arr[idx_l] < arr[idx_r]`
    * `left, right = 0, len(arr)-1`
    * `return nums[left]`

```
def binary_search(search_space) -> int:
    def condition(idx) -> bool:
        pass
    left, right = # min(search_space), max(search_space) 
    while left < right:
        mid = (left + right) // 2
        if condition(mid):
            right = mid
        else:
            left = mid + 1
    return left
```

## Union find

Useful for Kruskal's minimum spanning tree algorithm, e.g.

Runtimes
  * `simple_find` has `O(N)` worst case, since it crawls up the tree
  * `union` operations have `O(u log N)`, where `u` is number of `union`s called
  * `compress_find` has `O(f + f log N)`, where `f` is number of `find`s called
  * Combining `compress_find` and `rank_union` or `size_union` gives `O(u)`
    union time!

❗️ `find` must return `parents[v]` instead of `v` because intermediate steps
must all return forward answer, not themselves!

```
parents = {v:v for v in elements}
ranks   = {v:0 for v in elements}
sizes   = {v:1 for v in elements}
def simple_find(v):
    while v != parents[v]:
        v = parents[v]
    return parents[v]

def simple_union(a, b):
    parent_a, parent_b = find(a), find(b)
    parents[parent_a] = parent_b

def compress_find(i):
    # correct all intermediaries to point directly to set leader
    if v != parents[v]:
        parents[v] = find(v)
    return parents[v]

def rank_union(a, b):
    parent_a, parent_b = find(a), find(b)
    if parent_a == parent_b:
        return
    if ranks[parent_a] > ranks[parent_b]:
        parents[parent_b] = parent_a
    elif ranks[parent_b] > ranks[parent_a]:
        parents[parent_a] = parent[b]
    else:
        ranks[parent_b] += 1
        parents[parent_a] = parent_b
        
def size_union(a, b):
    parent_a, parent_b = find(a), find(b)
    if parent_a == parent_b:
        return
    if sizes[parent_a] > sizes[parent_b]:
        parents[parent_b] = parent_a
        sizes[parent_a] += sizes[parent_b]
    else:
        parents[parent_a] = parent_b
        sizes[parent_b] += sizes[parent_a]

def compress():
    for v in parents:
        parents[v] = find(v)
```

Can be used for P-128 Longest Consecutive Sequence
  * Each element is linked to next element in map, if it exists
    * `for v in parents: if v+1 in parents: union(v,v+1)`
    * Then compress to make sure each item points to highest parent
    * `return 1 + max( p-v for v,p in parents.items() )`
    * Better runtime but 2x memory: track sizes and `return max(sizes.values())`
  * Alternative: check if `x-1 in set`, then walk. Length of walk is `last -
    first`, which is then used to update `best_so_far`
