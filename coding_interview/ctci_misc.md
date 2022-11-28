# Cracking the coding interview -- miscellaneous

## Bit Manipulation

### xor, and, or 

XOR is commutative, associative, and self-cancelling so 
`A xor B xor A = A xor A xor B = (A xor A) xor B = 0 xor B = B`
  * ✅ Useful for reducing an array to find non-paired item

| 0             | 1                 | A             |
|---------------|-------------------|---------------|
| `A and 0 = 0` | `A and 1 = A`     | `A and A = A` |
| `A or 0 = A`  | `A or 1 = 1`      | `A or A = A`  |
| `A xor 0 = A` | `A xor 1 = not A` | `A xor A = 0` |

### Arithmetic
➕ Add binary just like base-10. Line up places and add with carry.

➖ Subtract binary just like base-10. Line up places and subtract with 
borrowing (borrows 2 from next left place, like borrowing 10 
from next left place).

✖️ Multiply binary just like base-10. Multiply each place individually, 
and add padding 0s for higher places. Then add each line.

Apply logic operations place-by-place

Left shift `<< x` pads out x 0s on the right end. Equivalent to 
multiplying by 2^x

Logical right shift `>>> x` moves everything right, annihilating 
rightmost places and replacing leftmost places with 0s.
  * makes 2s-complement positive

Arithmetic right shift `>> x` moves everything right, annihilating 
rightmost places but COPYING leftmost bit as it goes right. 
  * essentially equivalent to dividing by 2^x.
  * preserves sign

### Negative numbers

1s complement reverses roles of 0 and 1. Seems confusing

2s complement (more common) assigns leftmost place as sign. Remaining 
places represent 2^(N-1) - x, which is same as negating and adding 1.
  * e.g. 1101 -> negative 101 -> negative 5 -> negative 2^3 - 5 = 
  negative 3
  * or, 1101 -> negative 101 -> negative (010 + 1) -> negative (2 + 1) 
  = negative 3

### Useful tricks

Get x'th bit
1. shift 1 << x
2. AND with source number
3. compare to 0

Set x'th bit to 1 
1. shift 1 << x
2. OR with source number

Set x'th bit to 0
1. shift 1 << x and negate to get 111...101...111
2. AND with source number 

Clear x'th bit and left
1. shift 1 << x and subtract 1 to get 000...111
2. AND with source number

Clear x'th bit and right
1. shift -1 << x+1 to get 111...000 because -1 = 111...111
2. AND with source number

Update x'th bit to value = 0 or 1
1. shift 1 << x and negate to get 111...101...111
2. AND with source number
3. then OR that with value << x

n is xxx1000, n-1 is xxx0111, so n AND n-1 is xxx0000. In other words, 
it zeros out the least significant 1. Useful for counting number of 1s 
in a number.

## Math and Logic

### Prime numbers

Any number can be represented as 2^i0 + 3^i1 + 5^i2 + 
7^i3 + 11^i4 + ...

Greatest common divisor between two numbers is 
sum of prime\_i ^ min( ai, bi )

Least common multiple of two numbers is 
sum of prime\_i ^ max( ai, bi )

So, GCD * LCM = a * b

Naive prime checker checks for n % i == 0 from 2 to sqrt(n). 
Don't need to go past sqrt(n) because bigger numbers would 
necessarily be multiplied by smaller numbers, so we only need to 
check the smaller numbers.

Sieve of Eratosthenes generates list of primes by listing [1..n] 
and crossing out multiples of 2, 3, 5, 7, 11, ..., prime < sqrt(n) 
and advancing to next non-crossed-out number. Optimize by only 
using odd numbers

### General tips

Write down rules / patterns as they appear to you
  * e.g., burning rope problem lets you time x+y minutes by burning 
  both sequentially, or x/2 minutes by burning one from both ends

Use balancing for "worst-case minimization" problems
  * e.g., in 9-balls problem, penalize lone ball with extra balls
  * seems similar to branching

Must treat items differently

Start simple, then build up

## OOP

1. Clarify who will use it and how
2. Define core objects
  * Table, Party, Guest, Order, Server, Host
3. Define relationships (inheritance, member variables, etc.)
  * Party comprises Guest array, Server/Host inherit from Employee
4. Consider possible actions
  * Party requests Table from Host, who assigns with Reservation or 
  adds to queue

Singleton pattern ensures only 1 instance of class.

✅ Useful for global objects, like a single Restaurant

❌ Many people dislike it, as it can interfere with unit testing

Factory pattern creates instance of class, with subclasses deciding 
which class to make

## System Design + Scalability

Ask questions about goals and assumptions
  * Estimate data needed

Discuss tradeoffs and downsides, with estimates
  * Identify bottlenecks and potential usage peaks

Stay high-level
  * Draw diagram of system with servers

Validate interviewer concerns

To start developing algo, just pretend all data fits on one machine * Consider splitting up data next Consider failure, availability, reliability, reads (try cache) and 
writes (use a queue), and security

### Key concepts

Vertical scaling -- improve resources of node.

Horizontal scaling -- increase number of nodes

Use load balancing to prevent one server from crashing. Only possible 
if servers use same code and data

Denormalize database by adding redundant info, speeding up reads

NoSQL doesn't support joins, but scales better than SQL

Partition database ("shard"):
  * Vertically -- by feature
  * Hash-based -- hash, then spread over n servers with hash % n
  * Directory-based -- maintain lookup table 

Caching is easy way to speed querying

Pre-process or asynchronously run slow operations
  * ✅ Useful for things that don't need to be perfectly accurate

Networking:
  * Bandwidth -- data / second
  * Throughput -- total amount of data
  * Latency -- time to go from source to destination
    * Can be important, but there's little one can do to improve

MapReduce maps data to (key, values), then reduces to (key, value)
  * ✅ Useful for parallel processing / scalability

## Databases

Normalized minimizes redundancy

Denormalized optimized read time by copying relevant info to many tables.
  * ✅ Useful for scalable systems, avoids expensive joins

SELECT ... FROM ( A JOIN B ON x=y ) GROUP BY ...

SQL has built-in `count( table.feature ) AS [variable]`

## Threads + Locks

Threads in a given process share same memory space. Processes have 
distinct memory spaces.

Java's `synchronized` keyword prevents many threads from simultaneously 
executing code on same instance of some object

Locks synchronize access to shared resource by limiting to one 
thread at a time
  * Deadlock happens if thread A waits for a lock from thread B, and 
  vice versa. Requires 4 conditions:
    * mutual exclusion -- limited access to resource
	* hold + wait -- processes can request resources without giving up 
	existing resources
	* no preemption -- processes can't hijack resources
	* circular wait -- processes wait in circular chain. Easiest to 
	fix
