# Cracking the coding interview -- data structures

## Arrays + Strings

### Hash Tables

✅ Hashmaps are useful for constant lookup, with worst case O(N) 
(if many collisions)

Loading into hashmap, then iterating through another array is 
O(N) + O(N) = O(N)

Hashmaps are implemented in `set` (unordered) and `dict` (ordered) 
in Python
  * can freely use during coding interview

To insert key into hashmap:
1. calculate hash
2. hash % array length gives array index
3. append key to linked list at that array's index

Could also implement with balanced binary search tree instead of 
array, with O(log N) lookup time and less space (no empty array slots)

### ArrayList / resizeable array

Double array size when full

Offers O(1) amortized insertion with SOMETIMES O(N) access 
due to copying

Inserting N elements takes O(N) work because 
1 + 2 + ... + N/2 = N * (1/2 + 1/4 + ...) = N

### StringBuilder (Java)

Copying strings into sentence costs O(x * N^2) because you 
copy sentence N times and x + x + ... + Nx = N * (N+1) / 2

StringBuilder creates resizable array with all strings, copying 
only when necessary -- O(x * N)

### Tips

Use modular arithmetic to cyclically change array in-place, with 
temp variables if needed
  * Little hack -- keep track of number visited, and compare to len(arr)

Two pointer trick -- define what you want `slow` pointer to track and 
`fast` pointer to track. Be careful about update conditions and overflow.
  * e.g. `slow` tracks lead zero, `fast` tracks next non-zero
  * e.g. `slow` tracks latest unique, `fast` finds next that differs 
  from `slow`
  * e.g. `slow` tracks lowest price, `fast` tracks each new price after

Sliding window trick -- drop first element, add next element to sublist
  * ✅ Useful for optimality, like longest sequence or shortest sequence 
  of something that satisfies a given condition.
  * Can have fixed length (max sum of size k) or dynamic length 
  (smallest sum greater than x). Subtract off arr[i-(k-1)] as you go
  * Auxiliary datastructures like hashmaps useful for longest substring 
  with no more than k distinct characters, e.g.
  * Better than brute force b/c reduces duplicate brute force work O(kn)

### Problems

1. determine if string has all unique characters. what if no other 
data structure allowed?
2. find if two strings are permutations of one another
3. replace all spaces with `%20`
4. check if string is permutation of palindrome
5. check if two strings are 1 or 0 edits away
6. compress string `aabcccccaaa` -> `a2b1c5a3` and check if compressed 
string is shorter
7. rotate NxN matrix 90 degrees. is it possible in-place?
8. zero-out rows and columns containing any 0s
9. check if one string is a rotation of another, with 1 call 
to `isSubstring`

## Linked Lists

O(N) access because you follow trail until getting to node

Adding / removing from beginning is O(1)

Each node needs: 
1. pointer to next node (could be None/NULL)
2. data, usually an `int`

Initialize node with next=None, then overwrite if needed

Access list through head node

Deleting node just reconfigures prior to point to next

✅ Runner (2nd pointer) technique is useful
  * e.g. move fast ptr 2x per move for slow ptr, so that 
  fast gets to middle of list
  * can weave elements from 2nd half into 1st half

Recursion plays well with linked list problems

### Problems

1. remove duplicates. what if temporary buffer not allowed?
2. find kth to last element
3. delete node, given only access to that node
4. partition list into left (< x) and right (>= x)
5. add two numbers, each stored in reversed link list
6. check if list is palindrome
7. find intersecting node between two lists
8. find beginning of loop

## Stacks + Queues

### Stack 

last-in-first-out

has methods: 
  * `pop` -- remove top
  * `push(item)` -- add item to top
  * `peek` -- return top value
  * `isEmpty` -- check if stack is empty

O(N) access, O(1) add/remove

Can be implemented as linked list if add/remove done from same side

Just need to define head

✅ Sometimes useful with recursion and backtracking (if recursive 
check failed, e.g.)
  * also useful for converting recursion -> iteration

### Queue

first-in-first-out

has methods:
  * `add(item)` -- add to end, creating new tail
  * `remove` -- remove 1st item, removing head
  * `peek` -- return top value
  * `isEmpty` -- check if queue is empty

Can be implemented as linked list if add/remove done from opposite sides

Need to define head and tail. Be careful when updating!

✅ Useful for breadth-1st search and caching. Helps processes in 
order of viewing

### Problems

1. describe how to use a single array to implement 3 stacks
2. design special stack that can return minimum element in O(1)
3. implement `SetOfStacks` that overflows stacks when they hit threshold
4. implement queue using 2 stacks
5. sort a stack low to high, using temp stack but not copying to 
any other data structure
6. make stack with 2 types of objects, and their unique dequeue methods

## Trees + Graphs

Average case and worst case runtimes can vary

Tree comprises root node, child nodes, children of child nodes...
  * node has value and list of children (or just left and right)
  * node with no children is `leaf`

No cycles allowed

No need to implement `Tree` class, just `Node` class`

### Special trees

Binary search tree has all left descendants <= n < all right descendants
  * true for ALL descendants, not just immediate children
  * clarify how tree should handle duplicates with interviewer

Balanced = not ridiculously imbalanced, and balanced enough 
to ensure O(log N) `insert` and `find`
  * includes red-black and AVL trees

Complete = every level is fully filled
  * caveat: last level just has to be filled left-to-right, and can 
  stop before rightmost end

Full = every node has 0 or 2 children 

Perfect = Complete + Full
  * has 2^k - 1 nodes
  * very rare

### Traversal -- uses recursion

`traverse(node): if (node != null) then`...

in-order (most common) visits left, then current, then right
  * visits binary search tree nodes in ascending order
`traverse(left); visit(node); traverse(right)`

post-order visits current node before child nodes
`visit(node); traverse(left); traverse(right)`

pre-order visits current node after child nodes
`traverse(left); traverse(right); visit(node)`

### Binary heaps

max-heap is same as min-heap, just replace "smaller" -> "larger"

min-heap is a complete binary tree with each node smaller than 
its children
  * min element always at top

`insert` takes O(log N), where N = total # nodes
1. put new element at bottom-right to maintain complete tree 
structure
2. fix order by swapping with parent until appropriate spot found

`extract min` takes O(log N)
1. remove min (top node) and replace with bottom-right
2. bubble down new min with smallest child to maintain min-heap structure

### Tries (prefix trees)

n-ary tree with character at each node
  * alphabet size + 1 possible children per node

Comes up a lot in coding interviews!

Null nodes (with *)  represent completed word

✅ Useful for checking if string is a prefix of another string
  * takes O(s) time
  * can save current node if searching for many prefix matches 
  with similar root (e.g. save N in MAN for MANY, MANA, MANE, ...)
  * hashmap is useful for checking if string is word, but not prefix
    * hashmaps actually take O(s) instead of O(1) to check strings

### Graphs

Simply a collection of nodes with edges, either directed or undirected

Can have cycles and isolated subgraphs ("connected" if no islands)

Represented with:
  * adjacency list (most common) -- node stores list of edge tuples
  * adjacency matrix -- NxN boolean matrix with connections
    * symmetric if undirected graph
	* less efficient than lists bc must iterate through all nodes to 
	find neighbors of one node

`Graph` class should be used because there's no single root
  * can actually just use array/hashmap(dict) of 
	arrays/arraylists/linked-lists to store adjacency lists. No special
	classes required!
    * bad practice to not use distinct class, though

### Graph search

depth-first -- start at root (or other node) then completely explore 
branch before moving to next branch
  * ✅ useful for visiting every node (simpler than BFS)
  * ❌ won't find shortest path
  * similar to tree traversal
    1. if null, return. else, visit then flag as visited
	2. for each adjacent node, if not visited: search node

breadth-first -- start at root (or other node) then explore neighbor 
before children
  * ✅ useful for finding shortest (or any) path between 2 nodes
  * use a queue, not recursion!
    1. create queue, and enqueue root. while queue not empty:
	2. dequeue, then visit, 
	3. then for each adjacent unmarked node: mark and enqueue
  * O(k^d) nodes searched, where k = nodes/level and d = # levels

bidirectional -- find shortest path between 2 nodes
  * start a BFS from each node, then wait for collision
  * O(k^(d/2)) nodes searched

### Problems

1. determine if path exists between two nodes in directed graph
2. create binary search tree with minimal height out of sorted array 
with unique integer entries
3. create linked list of all nodes at each depth of binary tree
4. check if binary tree is balanced (heights of each subtree of a node 
are within 1)
5. check if binary tree is binary search tree
6. find next node of given node in binary search tree, given each node 
has link to parent
7. find a build order (or return error if none exists) of projects and 
their dependencies
8. find first common ancestor of 2 nodes in binary tree, without 
storing additional nodes
9. list all possible arrays that could create a binary search tree
10. determine if one tree is a subtree of another
11. return a random node from a tree
12. count number of downward-only paths that sum to given value
