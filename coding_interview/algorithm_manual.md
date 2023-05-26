# Algorithm Design Manual by Steven Skiena

## Graphs

Definitions
  * Girth = length of shortest cycle 
  * Hamiltonian cycle = cycle that passes through every node once
    * NP-hard to find
  * Tree = undirected graph with no cycles
  * DAG = directed graph with no cycles
  * Connectivity = smallest number of nodes whose removal disconnects graph
  * Articulation node disconnects the graph (implies connectivity = 1)
  * Set `N` = number of nodes and `M` = number of edges

Two main choices for storing matrix
  * Adjacency matrix -- matrix with 0 or 1 indicating each edge
    * (+) `O(1)` time to lookup edge existence
    * (-) `O(N)` time to calculate degree of node
    * (+) `O(1)` time to insert or delete edge
    * (-) `O(N^2)` space, but can try to compress using triangular matrix or by
      packing as bit vector
  * Adjacency list -- array of pointers to linked lists
    * (-) `O(di)` time to check edges of `i'th` node, where `di` is degree
    * (+) `O(di)` time to calculate degree of node
    * (-) `O(di)` time to insert or delete edge
    * (+) `O(N + M)` space, which is efficient for sparse graphs (common)
    * Useful for planar graphs, which only have `M <= 3N - 6`
    * Useful for trees (which are also planar!), which only have `M = N - 1`
    * Can implement doubly linked list

Only takes `O(N^2)` time to convert between two forms

### Graph traversal

Traversing a graph is useful for
  * Printing node/edge content
  * Copying a graph
  * Translating between graph representations
  * Counting vertices/edges
  * Finding connected components
  * Finding paths between two vertices
  * Finding cycles -- runs in `O(N)` time because `M = N + 1` for trees
  * 2-coloring graphs -- alternate 0 and 1, checking for any neighbor clashes
  * Finding articulation node -- delete current node and traverse remaining
    graph to check for connectivity. Runs in `O(N(N+M))` time. Faster `O(N+M)`
    algorithm exists

Runs in `O(N + M)` time

Need to track each node's state
  * Undiscovered
    * Only add node to list of work if it's undiscovered
  * Discovered -- once found but not fully explored
    * Finding an already-discovered node indicates a cycle
  * Fully explored -- all edges have been traversed

There are 4 edge states
  * Tree edge
  * Back edge -- loops back to already-visited node
    * Tree and Back are only 2 types of edges for DFS
    * Back edges indicate a cycle
  * Forward edge -- skips ahead beyond immediate connections
  * Cross edge -- cuts across graph at same level

Each node is visited once, each edge is visited twice, each directed edge is
visited once

Breadth-first search uses a queue. Useful for shortest-path problems

```
for n in nodes: state[n] = "undiscovered", parent[n] = -1
state[start] = "discovered", parent[start] = -1, q = deque([s])
while q:
    n = q.popleft()
    process_node(n)
    for x in adjacent[n]:
        process_edge(n,x)
        if state[x] == "undiscovered": 
            state[x] = "discovered", parent[x] = n, q.append(x)
    state[n] = "fully_explored"
```

Depth-first search uses a stack. Useful for checking for cycles

```
def f(n):
    state[n] = "discovered"
    process_node(n)
    for x in adjacent[n]:
        process_edge(n,x)
        if state[x] == "undiscovered":
            parent[x] = n
            f(x)
    state[x] = "fully_explored"
```

Need to start from each connected component
  * Just wrap `f(n)` in loop over all nodes and search only if node is
    undiscovered
  * Can also track component count for each initiated search

### Topological sort

Only defined for DAG, bc cycles break ordering. Each DAG has >= 1 valid solution

Perform DFS, labeling nodes in order of marking them `"fully_explored"`
  * Lower nodes are marked `"fully_explored"` before higher nodes
  * Return in reverse order

### Minimum spanning tree

Prim's algorithm repeatedly selects smallest weight edge that enlarges tree
  * Runs in `O(NM)` time for naive algorithm
  * Runs in `O(N^2)` with Fibonacci heap
  * Good for dense graphs

```
start = nodes[0], tree_nodes = nodes[0], non_tree_nodes = nodes[1:]
tree_edges = [], non_tree_edges = edges
while non_tree_nodes:
    e = lightest edge between tree node and non-tree node
    n = associated node
    tree_edges.append(e), non_tree_edges.pop(e)
    tree_nodes.append(n), non_tree_nodes.pop(n)
```

Kruskal's algorithm starts with singleton trees, then merges trees
  * Runs in `O(NM)` time to check connectivity of each tree and add/remove from
    heap
  * Runs in `O(M log M)` time using union find
  * Good for sparse graphs

```
tree_edges = []
heapify(edges), count = 0
while (count < n-1):
    e = edges.heappop()
    if e[0] and e[1] in different components:
       tree_edges.append(e)
       merge e[0] component and e[1] component
```

### Finding the shortest path

BFS finds shortest path if all edges have the same weight

Dijkstra's algorithm finds shortest path for differing weights
  * ❗️ Only works for non-negative weights! Relies on triangle inequality
  * Requires specifying start and target nodes
  * Runs in `O(N^2)` time
  * Basically the same as Prim's algorithm

```
seen = [start], last_seen = start
for n in nodes: dist[n] = infinity
for e in edges[start]: dist[e[1]] = weight[start][e[1]]
while last_seen != target:
    n = closest neighbor node to start
    for e in edges[n]:
        dist[e[1]] = min( dist[e[1]], dist[n] + weight[n][e[1]] )
    seen.append(n), last_seen = n
```

### Finding all-pairs shortest path

Could run Dijkstra's `C(N,2)` times for `O(N^3)` runtime

Floyd-Warshall algorithm also runs in `O(N^3)` time but is typically much faster
  * `dist[i][j][k]` is distance from `i` to `j` using only nodes indexed <= `k`

```
set up dist[i][j][0] as given weight matrix
for k in range(n):
    for j in range(n):
        for i in range(n):
            dist[i][j][k] = min( dist[i][j][k-1], 
                                 dist[i][k][k-1] + dist[k][j][k-1] )
```

## Data structures

Dictionaries -- locate, insert, and delete records associated with key/keys
  * Small number of items? Use simple data structure like array or linked list
    * Self-organized list places new elements in front for quicker repeat access
    * Typically not worth keeping it sorted
  * Consider skewed query distribution and query clustering
  * Use B-tree for large number of items that don't fit in memory
    * Abstracts away clusters of records
  * Main implementation is hash table
    * Keep array of size `m`, each with pointer to linked list.
    * Ideally, `m = number of items` and `m` is prime
    * Analyze statistics on linked list size distribution
  * Can use balanced search tree like AVL, red-black, or splay
    * Splay tree keeps frequent nodes sit at top of tree
  * Could use skip list, but typically isn't great

Priority queue -- quick access to smallest key
  * Only needed if mixing insertions, deletions, and queries. Else just sort
  * Dynamically changing priority? Use Fibonacci heap
    * Fibonacci gives `O(1)` decrease-key and insertion, `O(log N)`
      min-extraction and deletion
  * Sorted array/list has slow insertion
  * Binary heap enables `O(log N)` min-extraction and insertion
    * Great if you know size
  * Array of `n` linked lists, with pointer to first nonempty slot
    * `O(1)` min-extraction and insertion
    * Only useful if data bounds are known, like in bucket sort
  * Could also use binary search tree

Suffix trees/arrays -- find where query string `q` appears as substring of main
string `S`
  * Can speed up string processing from `O(N^2)` to `O(N)`
  * Equivalent to trie of strings that are suffixes of main string
    * Tries are useful for determining set membership of query string
  * Naive algorithm takes `O(N^2)` time and space to build, but clever algorithm
    takes `O(N)` time and space
  * Useful for finding occurences of `q` in `S` (`O(q+k)`), finding longest
    common substring of group of strings (`O(q)`), finding longest palindrome
  * Suffix arrays use 1/4 of memory. Enables substring search in `O(log N)` time
    * Just store pointers to original string rather than copying data
  * Can compute least common ancestor in `O(1)` time! Complicated algorithm

Set data structures -- check for membership, union/intersection, insert/delete
  * Sorting lets you check union/intersection in `O(N)` time with 2 pointers,
    and searching takes `O(log N)` time with bisection
  * Useful for representing hypergraphs (where sets of nodes are now nodes)
  * Bit vectors are efficient -- 1 means in and 0 means out, union/intersection
    is just `|` and `&` operations, `O(N)` time to identify all members
  * Dictionaries (sets) are useful for sparse subsets
    * Union takes `O(s1 + s2)`, searching takes `O(log N)`
  * Union find -- each node points to parent
    * Union simply involves pointing root 2 to root 1

kd-trees -- segment space into boxes using axis-aligned borders
  * At each iteration, segment into 2 halves. Stop when each point has own box
  * Cycle through dimensions, cut along largest dimension, or use quad/octtrees
    (good for images)
  * Useful for locating nearest neighbor of arbitrary given point (need to check
    nearby cells just in case, though)
  * Useful for finding points within arbitrary given box
  * Can perform partial key search if some attributes unknown. Perform binary
    search on attributes we do know
  * Breaks down after 20 dimensions bc points are too far apart
