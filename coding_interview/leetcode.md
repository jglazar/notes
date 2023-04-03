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

### Math

P-50 Power has simple `O(n)` iteration/recursion, but you can get `O(log n)` 
time by halving the exponent if even, and subtracting one if odd.

P-779 Kth Symbol has brute force `O(2^n)` recursion solution, building up 
rows one at a time. 
  * Better is to use rules to find patterns for even/odd indices, then 
  traverse backwards one row at a time. `O(n)` time.

P-231 Power of 2 recursion checks if `x==1`, then if `x%2==0` proceed to halve. 
  * Don't forget to check for `x<=0`, for which the answer is False

## Divide and Conquer

1. Divide `sub_problems = divide(p)`
2. Solve `solutions = [f(p) for p in sub_problems]`
3. Merge `return merge(solutions)`

Merge-sort array
  1. Split down middle to create only 2 subproblems
  2. Recurse
  3. Zip together each of the two arrays into a third array using iterators
    * If either iterator is at end, then trivially append other array to result
      array
    * Otherwise, pick the min of the two elements and increment the iterator

Merge-sort takes `O(n)` time for the zip stage, which happens `O(log n)` times.
Time complexity is `O(n log n)` and space is `O(n)` to store other array.

Validate BST -- remember to include lower and upper bounds! Can have tricky tree
where all subtrees are BSTs, but there's a violation further up the tree.
  * If going left, pass along new upper bound `max(hi, r.val)`. If going right,
    pass along new lower bound `min(lo, r.val)`.

Example problems -- merge-sort, validate BST, quick-sort
