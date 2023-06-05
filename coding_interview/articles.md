# Online articles

## Design patterns

Site [here](https://neetcode.io/courses/lessons/8-design-patterns)

Factory -- class with no data, just methods that create another object

Builder -- class with one object, and methods that build up that object and a 
`build` method to return the object
  * `my_burger = BurgurBuilder().add_bun("sesame").add_patty("vegan").build()`

Singleton -- class with only one instance. Has static `instance` variable and
non-static `is_active` member. 
  * `@staticmethod get_state(): if not class.instance: class.instance = class(); 
  return class.instance`
  * Always initialize as `var = class.get_state()` 
  * Can have many vars acting as pointers to one instance

Observer / Pub-Sub -- Publisher creates events and Subscribers receive events. 
  * Pub class has list of Sub objects
  * Pub performs `notify_all(message): for s in self.subs: s.receive(message)`
  * Sub class has `receive` method to take in message

Iterators -- defined for most built-in collections, but can be customized with 
methods `__iter__(self)` to start at head and `__next__(self)` to proceed
  * `LinkedList` class has `head` and `current`, `ListNode` class has `val` and
    `next`
  * `__iter__(self): self.current = self.head; return self`
  * `__next__(self): if not self.current: raise StopIteration; else val = 
  self.current.val, self.current = self.current.next; return val`

Strategy -- define an abstract Strategy class with one method, then xStrategy 
subclasses with that fit the generic method's interface spec.
  * Strategy `@abstractmethod def my_fct(): pass`
  * xStrategy `def my_fct(): do x then return val`, yStrategy, ...
  * Now you can include Strategy where needed and call `my_fct`, and pass in
    different subclasses as-needed
  * Basically obviated bc Python allows passing functions

Facade -- wrapper to hide implementation details
  * Might wrap data structure in simple class with `push_back()` and 
  `pop_back()` public methods, plus `resize` private method

Adapter -- allow incompatable objects to interact. Extends class behavior
without modification
  * `class ABadapter: def __init__(self, A): perform modifications, then act
    like B`

## System design 

Video [here](https://neetcode.io/courses/lessons/20-sysdes-concepts)

### Hardware

Scaling
  * Vertical -- upgrade hardware in response to increased demands (more user 
  requests, e.g.)
  * Horizontal scaling -- add machines to handle requests in parallel
    * adds redundancy and fault tolerance
    * adds complexity, like load balancing

Load balancing -- "reverse-proxy" server evenly distributes incoming work across 
resources
  * Round robin -- cycle through all nodes 
  * Hashing -- hash request ids like `job_id % num_nodes`
  * Load balancer can route requests to nearest geographical server

Content delivery network -- network of worldwide servers with copies of your
files (cache)

Caching -- copy data to enable faster fetching
  * Browsers cache data from web on local machine
  * Computer copies disk data to RAM; copies RAM to CPU cache

Sharding splits data horizontally across servers
  * Shard key specifies which data belongs to which machines
  * Can get complicated

Replication copies (rather than splits) data across machines
  * Leader-follower -- leader is read/write, follower is read-only 
  * Leader-leader -- both are read/write
    * Can have data inconstencies. Best if replicas are geographically far

CAP theorem -- pick 2 of 3: consistency, availability, partition (network)
  * Note that "consistency" here is different from ACID consistency
  * PACELC theorem -- Can partition -> pick availability or consistency; 
  cannot partition -> pick latency or consistency

### Protocols

IP uniquely identifies devices on networks
  * TCP/IP (which includes UDP) sets protocols for sending/receiving data
  * TCP ensures resending if data is missing. 
    * Reliable, so used in HTTP and WebSocket

DNS translates domains to IP addresses
  * `A (address) record` maps name to IP
  * Browser caches DNS query results to avoid checking with DNS server

HTTP is an application-layer protocol 
  * Follows client-server model: client sends request with header and body

HTTP APIs 
  * REST -- stateless, standardized error codes, uses JSON
  * GraphQL -- single request (query) for many resources
  * gRPC -- server-server comms with protocol buffers serialized into binary

WebSocket is an application-layer protocol
  * HTTP for chat would require constant polling
  * WebSocket allows automatic pushing/pulling of messages (bidirectional comms)

Relational database management systems include MySQL and PostRef
  * B-trees allow efficient data access
  * SQL is efficient language for communicating requests
  * Typically ACID compliant
    * Atomic -- all-or-nothing requests
    * Consistent -- foreign key constraints, e.g., are always enforced
    * Isolation -- concurrent transaction don't interfere with one another
    * Durable -- data is stored on-disk, so rebooting doesn't destroy data

NoSQL is a non-relational database
  * Consistency prevents horizontal scaling and sharding
  * Key-value stores (DynamoDB), Document stores (MongoDB), Graph databases
    (neo4j)

Message queues are like databases -- durable storage, can be replicated or
sharded
  * Allows persistent data for server to deal with one-by-one
  * Helps with decoupling

## Python tools

Site [here](https://neetcode.io/courses/lessons/python-for-coding-interviews)

### Math 

Negative math can be tricky
  * Negative integer division rounds down instead of towards zero
    * Round towards zero with `int(a/b)` 
  * Negative modulo is weird -- `-10 % 3 = 2`
    * `math.fmod(a, b)` from `math` module is better

`math` module includes useful `floor`, `ceil`, `sqrt`, and `pow` methods

Infinity is `float("inf")` or `float("-inf")`

Python numbers don't overflow

### Lists

`l.append` and `l.pop` act like stack data structure

`l.reverse()` and `l.sort(reverse=bool, key=fct)` act in-place
  * Can sort with custom lambda key function 

`l.insert(idx, val)` is useful, but takes `O(N)` time

Multiplication creates one list: `[0] * 4 = [0, 0, 0, 0]`

Indexing beyond end does not go out of bounds, just caps out at end

loop through two lists with `for i, j in zip(l1, l2)`

`range` takes beginning (incl), end (excl), and step (can be negative to go
backwards)

### Strings

Strings are immutable -- cannot assign `s[3] = 'd'`

Can add strings with `+` -- creates new string and take `O(N)` time

ASCII value of character "a" is `ord("a")` (yields 97) 

### Queues

`from collections import deque`

Can `q.append(val)` (to right), `q.appendleft(val)`, `q.pop()` (from right), 
`q.popleft()` 

### HashSets and HashMaps

HashSet is `set`
  * `s = set()`, `s.add(val)`, `s.remove(val)`
  * Can feed in list -- `s = set(l)`
  * Can use set comprehension -- `s = {i for i in range(n)}`
  * No duplicates

HashMap is `dict`
  * `d = dict()`, `d[key] = val`, `d.pop(key)`
  * Can use dict comprehension -- `d = {i:2*i for i in range(n)}`
  * Loops through keys by default. 
    * Loop through values with `d.values()`
    * Loop through key and val with `d.items()`

Check for membership with `val in s` or `val in d`
  * Searched in `O(1)` time

Insertions and deletions are `O(1)` time

### Tuples

Tuples are like immutable lists

Can be used as key for HashSet or HashMap, unlike lists

### Heaps

`import heapq` module

Defaults to min-heap. 
  * Implement max-heap by pushing and popping negative elements

Methods act on lists
  * `heaq.heapify(l)` acts in-place
  * `heapq.heappush(h, val)`, `heapq.heappop(h)`
  * `print(h)` defaults to first value

### Functions

Nested functions copy in and use local version of outer variables
  * Use `nonlocal` to modify outer variable 

Class methods always require `self` as first argument

## 14 Patterns

Link [here](https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed)

1. Sliding window 
  * Perform operation on window which can grow, shrink, or stay constant
  * Start from 1st element and shift right, adjusting window length
  * 🕵️ Look for linear data structure, longest/shortest substring/subarray, find
    specific value
  * 📖 Longest subarray with all 1s, max sum subarray of size k, longest
    substring with k distinct characters, string anagrams
2. 2 pointers
  * Iterate through data structure unitl one or both pointers hits condition
  * With only one pointer, you need to repeatedly look back for `O(N^2)` time
  * 🕵️ Look for pairs/triplets/subarray, data is sorted, multiple comparisons, 
  fulfilling constraints
  * 📖 Squaring a sorted array, triplets summing to zero, comparing strings
    containing backspaces
3. Fast and slow pointers
  * Useful for cyclic linear data structures -- two pointers are guaranteed to
    meet
  * 2 pointer method doesn't work on singly linked lists, but fast/slow does
  * 🕵️ Look for loops, require position of element or length of data structure
  * 📖 Linked list cycle, palindrome linked list, cycle in circular array
4. Merge intervals
  * Useful for finding or merging overlapping intervals
  * 🕵️ Look for producing list with mutually exclusive intervals, overlapping
    intervals
  * 📖 Intervals intersection, max CPU load
5. Cyclic sort
  * Iterate over array: if current is at wrong index, then swap to place
    correctly
  * 🕵️ Look for sorted array with numbers in a given range, find
    missing/smallest/duplicate number in sorted/rotated array
  * 📖 Find the missing number, find smallest missing positive number
6. In-place reversal of linked list
  * Point to head and previous, then advance in lock-step along list
  * 📖 Reverse sublist, reverse every k-element sublist
7. Tree BFS
  * Pop root from queue, visit, the push kids onto queue
  * 🕵️ Look for tree traversal level-by-level
  * 📖 Binary tree level-order traversal, zigzag traversal
8. Tree DFS
  * curr-left-right (pre-order), left-curr-right (in-order), left-right-curr
    (post-order)
  * Make recursive call for each child
  * 🕵️ Look for searching where node is closer to leaf
  * 📖 Sum of path numbers, all paths for a sum
9. 2 Heaps
  * Useful for finding smallest element of one part and biggest of another
  * Store first half in max-heap and second half in min-heap; median is
    calculated from top element of each heap
  * 🕵️ Look for scheduling, finding smallest/largest/median element of set,
    binary trees
  * 📖 Find median of number stream
10. Subsets
  * Start with empty set, then add `l[0]` to all sets to create new sets, then 
  add `l[1]` to all sets to create new sets, then ...
  * 🕵️ Look for combinations/permutations
  * 📖 Subsets with duplicates, string permutations by changing case
11. Modified binary search
  * Useful for sorted arraysG
  * `m = s + (s+e)//2; if key==l[m] then return; if key<l[m] then e = m-1 else s
    = m + 1`
  * 📖 Order-agnostic binary search, search in sorted infinite array
12. Top/bottom/frequent k elements
  * Find top k numbers: insert 1st k elements into min-heap, then iterate 
  through the rest of the elements. Pop out root and heap-insert new element if 
  new element > root
  * 🕵️ Look for sorting an array to find an exact element
  * 📖 Top k numbers, top k frequent numbers
13. K-way merge
  * Given k sorted arrays, use heap to perform sorted traversal of all elements
  * Push smallest element of each array into min-heap, then pop overall min and
    heap-insert next element from that array
  * 🕵️ Look for sorted arrays/lists/matrix, merging sorted lists, finding
    smallest element in sorted list
  * 📖 Merge k sorted lists, k pairs with largest sums
14. Topological sort
  * Find linear order of elements with dependencies
  * Store graph as adjacency list using hashmap; use keep count of in-degrees
    with hashmap; 0-in-degree nodes are sources and are store in queue; for each
    source: add to sorted list, get all kids, decrement kids' in-degree, add any
    kids with 0-in-degree to sources list
  * 🕵️ Look for acyclic directed graphs, updated objects in sorted order
  * 📖 Task scheduling, min height of tree

## Concurrency

Link [here](https://hackernoon.com/top-5-concurrency-interview-questions-for-software-engineers-x48i30qu)

Mutex provides one-at-a-time access to resource. 

Semaphore provides k-at-a-time access. Also allows signaling between threads

Best practices
  * Minimize sharing mutable data to prevent safety issues (data races) and 
  performance hit from lock.
    * Immutable data is always thread-safe
  * Minimize waiting 

Deadlocks/livelocks can occur when using mutexes or semaphores

### Exercises

1.  ReadWrite lock -- many readers, one writer
  * Define APIs exposed by class -- acquireReadLock, releaseReadLock, 
  acquireWriteLock, releaseWriteLock
  * Cannot have any readers while writer works. Can have multiple readers.
  * ❌ Don't place acquisition and release of mutex across separate methods.
    Could have writer die, leaving deadlock
  * ❗️ Don't let writer wait forever while new readers come in -- allow writer
    to lock reader mutex
2. Dining philosophers -- 5 people, 5 forks (all stationary)
  * Each person needs the left and right fork to eat
  * ❗️ Avoid circular wait condition -- impose order on condition variables 
  and pick lower fork
  * ❗️ Avoid starvation -- could cycle between 2 states, neither of which allow
    one person to eat
3. Uber -- Can have 4A, 4B, or 2A2B rideshares
  * Ride requestors are threads. Each thread calls `seated()` then one calls 
  `drive()`
  * Create `seatA()` and `seatB()` methods
  * Create `AWaiting` and `BWaiting` semaphores
  * Count A and B separately, with lock/mutex to increment
4. Async to sync 
  * Make `ASyncExecutor.execute(fct)` block
  * Create notification/singaling mechanism like semaphore, or condition 
  variable + mutex
  * Extend a new `SyncExecutor` and override `execute()` method, invoking
    `super()` as needed
  * ❗️ Async and sync code could try to access unusable shared resource
    (deadlock) -- set up signaling to tell main thread to continue on
5. Barber shop 
  * Barber sleeps if no customers, customer leaves if shop full, customer wakes
    barber if needed
  * Maintain count of waiting customers, semaphore for waiting status, signaling
    for waking barber
  * ❗️ Deadlock could occur if barber and new customer check each others' status
    simultaneously
  * ❗️ Starvation could occur if customers are served out-of-order -- use a
    queue

## Bucket sort

1. Initialize empty buckets
2. Scatter elements into buckets
3. Sort non-empty buckets
  * Insertion sort works well if number of elements per bucket is small
  * Could recursively call bucket sort here
4. Gather elements from buckets in order

Works best for uniformly distributed elements. Clustering hurts performance.

Radix sort works recursively
  * Runs in `O(N k)` time, where `k` is length of max integer
  * Can make efficient parallelizable version, like merge sort
  * Most-significant digit sorting is useful for strings or fixed-length ints
    * Scatter each element into bucket based on first digit
    * Recursively sort into smaller buckets based on next digit, stopping when
      a bucket has 1 element
    * Flatten buckets out to get final sorted collection
  * For least-significant digit (more common):
    * Scatter each element into bucket based on last digit
    * Flatten out buckets to overwrite array, then recurse on next digit

```
def radix_sort(arr):  # by least-significant digit
    bins = [[] for _ in range(10)]
    biggest_int = max(len(str(x)) for x in arr)
    for i in range(biggest_int):
        for x in arr:
            digit = (x // 10**i) % 10
            bins[digit].append(x)
        arr = [x for s in bins for x in s]
        bins = [[] for _ in range(10)]
```
