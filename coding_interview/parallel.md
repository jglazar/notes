# Parallel Programming -- Concepts and Practice

## Introduction

Common issues include race conditions, deadlocks, and scaling.

Distributed vs shared memory.

Consider problem partitioning, communication patterns, synchronization, 
and load balancing.

Definitions
  * Speedup = time for 1 proc / time for p procs
  * Efficiency = speedup / p = time for 1 proc / ( time for p procs * p )
  * Cost = time for p procs * p
  * Comp-to-comm ratio = time spent calculating / time spent communicating

Typically want to measure the above metrics for different numbers of 
processors.
  * Strong scalability -- only vary number of procs
  * Weak scalability -- vary input size with number of procs

E.g., splitting sum of `n = 2^k` numbers across `p = 2^q` processors is 
weakly scalable because communication costs dominate when fewer than 32 
numbers per processor
  * Data distribution time = 3q (takes 3 timesteps to communicate)
  * Computing local sums time = n/p - 1
  * Collecting partial results time = 3q
  * Adding partial results = q
  * Total time = 2^(k-q) - 1 + 7q
  * Speedup increases until 128 procs (for 1024 inputs), after which 
  speedup declines!

Longer communication time --> use fewer procs for peak efficiency.

### Parallelism basics

Communication on distributed memory system occurs via interconnection 
network. CPUs use point-to-point communication or collective communication 
(broadcasts).

Network is point-to-point or switched. Protocols include ethernet and 
infiniband. Topology determines scalability.

Data distribution is main issue. E.g., may need to copy extra data from 
each processors' neighbors.
  * partitioned global address space method assigns partitions of 
  global memory to each processor.

Shared memory gives each core access to same central memory, plus local 
cache to reduce expensive main memory accesses (von Neumann bottleneck).

Cache coherence -- cached values must match main memory values.
  * Modern architecture is cache-coherent non-uniform access architecture 
  (ccNUMA)

Threads read from / write to common memory. Avoid race conditions wherein 
2 threads access shared variable simultaneously. Use mutexes, atomics, 
or condition variables to avoid.

Processes take 12 ms to initialize. Threads take 0.03 ms!

OpenMP uses `pragma` preprocessor directives to generate multi-threaded 
code. Modern accelerators like GPUs can have thousands of threads.

Considerations
  * Partitioning -- data, task, or model decomposition
  * Communication -- amount and type of comms b/t processes / threads
  * Synchronization b/t processes / threads
  * Load balancing -- minimize idle times

Loop-carried data dependency -- iteration i depends on i-1. 
  * Prefix sum finds `A[i] += A[i-1]`. Perform local prefix sum on each 
  proc's slice. Create new array from last elements of each slice. Perform 
  prefix sum on those. Then add corresponding value to next local slice. 
  * Recursive prefix takes log(p) time, or p time if using serial prefix 
  method on proc-level array. First and last steps take n/p time.
  * No communication necessary if shared memory
  * Synchronization provides barriers between stages

Data parallelism often scales well, whereas task parallelism doesn't 
(typically only a fixed number of tasks).

Embarrassingly parallel -- no communication necessary.

Dynamic scheduling helps with load balancing.

Model parallelism helps with huge NNs that don't fit in GPU memory. Split 
model weights among GPUs. Requires communication and synchronization 
for NN predictions.

### Exercises

2. What is speedup for parallel prefix on n/4 cores where the input length 
n is a power of 2?
  * Communication costs 3p, but shared mem doesn't need comms! Do n/p 
  work to calculate local prefixes, the recursive prefix takes log2(p) 
  time, then do n/p work to finalize. Speedup is `(n-1)/( log2(n) + 4 )` 
  in this case, since each processor has exactly 4 values.

5. Apply operator x dot y = x + y + xy to all pairs of primes 1 - 1000 s.t. 
only one number remains. What is best combo to provide least final result?
  * x dot y is commutative and associative, so we get the same number 
  regardless of the order we take. Split array into binary tree and 
  assign leaves to cores (as threads, e.g.). Then combine leaves using 
  dot going upwards. Has n/p operations at each leaf, followed by 
  log2(p) combination steps. Distributed memory has communication costs too.

## Theory

Parallel random access machine (PRAM) is idealized shared memory machine. 
  * n processors that execute read phase (read 1 data item), compute 
  phase (1 fundamental operation, then store in register), then write 
  phase (write to shared mem) in lock-step with one another.
  * Exists in 4 combinations of exclusive/concurrent read/write.
  * Race condition: priority wins, random wins, no one wins if 
  values are different, or combination is written.
  * Constant time accumulations / broadcasts for concurrent read + write, 
  logarithmic time for exclusive read + write.

Real systems don't have uniform memory access to all locations.

Exclusive-write prefix: 
  * With n procs, perform recursive doubling where each item takes 
  simple 2-part sum from previous step's array. Can skip slots over 
  time to avoid double-counting. Takes `log_2(n)` time with `n log(n)` cost.
  * With n/log(n) procs, perform local prefix in log(n) time. Then 
  perform above method on the n/log(n) final sums for log( n/log(n) ) time. 
  Finally, add corresponding values to chunks in log(n) time. Overall 
  cost is just `log(n) n/log(n) = n` which is much optimal (efficiency=1).

Array compaction: convert sparse array into array with values and array 
with coordinates. First, create boolean array to indicate nonzero values. 
Second, perform parallel prefix on boolean array. This gives coordinates 
in new array for each nonzero element. Now simply assign nonzero values to 
their new coordinates in the new value array. Finally, assign original 
coordinates to new coordinates in new coords array.

Optimal cost is same as serial cost, s.t. efficiency = 1. If parallel 
time with n^3 procs is log(n) and serial cost is n^3, then instead try 
to use n^3/log(n) procs s.t. efficiency = 1.

### Networks

Shared (ethernet bus, e.g.) communicates one message at a time. Switch 
communicates many messages between different pairs of nodes.

Ideally want constant graph degree (to scale without adding excessive 
connections), low graph diameter (for fast pairwise comms), and high 
bisection width (to avoid bottlenecks).
  * Linear array has degree 1, diameter n, bisection width 1.
  * 2D mesh or torus has degree 1, diameter sqrt(n), BW sqrt(n).
  * 3D mesh or torsus has degree 1, diameter cbrt(n), BW n^(2/3)
  * Binary tree has degree 1, diameter log(n), BW 1
  * Hypercube has degree log(n), diameter log(n), BW n

### Speedups

Amdahl's law -- assume parallelizable part has linear speedup. Then, 
`S = (ser + par) / (ser + par/p) = 1/(f + (1-f)/p)` where f is fraction 
of total runtime which is serial. There's a cap on speedup!
  * Only applies for constant problem size (strong scalability)

Gustafson's law -- assume that parallelizable part of code grows with 
problem size, but serial part remains constant. Then `S = (f + z(1 - f) / 
(f + z(1 - f)/p)` where z is the problem scale-up. 

Both Amdahl and Gustafson neglect communication costs

### Design

Foster's parallel algorithm design methodology 
  1. Partitioning -- domain/data parallelism is generally finer grained 
  than functional/task parallelism.
  2. Communication -- Specify data transfer between tasks. Consider 
  local/global, static/dynamic, and synchronous/async.
  3. Agglomeration -- coarsen the tasks to improve efficiency through 
  reducing communcation and increasing data locality.
  4. Mapping -- minimize communication, execute in parallel, and balance 
  the workload.

Communication time between processors = startup (latency) + size / bandwidth 

### Exercises

1. Compute matrix product for 2 n x n square matrices using n^3 procs
  * Assign each output n procs. Assign each proc one Aik Bkj product, 
  which takes constant time. Then get sum of that output's array using 
  recursive pairwise sum (like binary tree). 
  * Not an issue of n isn't power of 2. Only difference is during log 
  agglomeration step, where the array can be padded with zeros.
  * To make optimal, use n^3/log2(n) procs. Then each output value has 
  n/log2(n) elements to sum. Following sum takes log2(n) time as well. 
  Same overall runtime, but now the cost is optimal.

2. Compress arrays of sorted key-value pairs, with repeats.
  * Same as compressing sparse arrays, but now indicate which values 
  to keep by checking if A[i] != A[i-1]. Using n is not cost optimal, but 
  n/log2(n) (probably) is.

3. Compute distance matrix from two arrays-of-vectors
  * Same idea as in problem 1, I think.

4. PRAM binary search in sorted array
  * If n procs, then just assign each proc one value. If input is equal to 
  that proc's value, then output that index and stop entire program. Overall 
  cost is n and efficiency is log2(n) / n, which is bad.
  * Assign n/log2(n) procs, do binary search on each proc which takes 
  log2(log2(n)) time, then agglomerate in log(n/log2(n)) time (or just 
  halt when found?). Overall cost is n/log2(n) log2(log2(n)) which is 
  still not optimal, but better than above.
  * Unsure if below works:
  * If log2(n)/log2(log2(n)) procs, do binary search on each proc, then 
  do binary agglomeration log2(log2(n)) times. This has overall cost of 
  log2(n)/log2(log2(n)) log2(log2(n)) which is optimal.

13. PCAM for matrix chain ordering problem (dynamic prog.)
  * This problem looks good!

## Architectures

Push toward multi-core. Main slowdown is reading data from main 
memory (von Neumann bottleneck). Optimizing levels of shared/local 
caches. SIMD and vector registers.

### Caches

CPUs have L1/2/3, GPUs have 2 levels. Higher levels have bigger storage 
but slower access. Can be shared between cores or private to one core.

E.g., CPU with 8 cores, 3GHz clock, 16 double-prec flop per core per 
clock cycle. Peak compute performance = 3 * 8 * 16 = 384 GFlop/s. CPU 
connected to DRAM with peak memory transfer at 51.2 Gb/s. Dot product of 
two vectors with size `n = 2^30` has 2 operations per element --> 2^31 
Flop. Vectors of total size 2^31 * 8B = 16 Gb are transferred to CPU. 
So computation takes 2/384 = 5.2 ms and data takes 16/51.2 = 312.5 ms.

L1 has few kb, L3 has few Mb, main memory has many Gb.

All loads and saves go through cache.

Can assume cache access takes single clock cycle. This helps make 
tasks compute-bound instead of memory-bound. Optimized packages like 
general matrix multiplication from BLAS can reach 100% capacity.

E.g., Multiply two 128 x 128 matrices with 8 B per entry (double prec.) on 
same CPU as above, but with 512 kB cache. 128 * 128 * 8 = 128 kB, which all 
fits on cache. Transfer two matrices into cache then transfer output 
to main memory takes 384/51.2 = 7.5 microseconds. Computation takes 
2 * n^3 operations = 2^22 Flop, or 2^22/384 = 10.4 microseconds.
  * Traversing rows for A and B properly reduces runtime by 10x.
  * Can partition A and B into small rectangular tiles that fit in cache.

Cache algorithms determine replacement policies to maximize hit ratio.
  * Spatial locality -- load neighboring data into cache, since that's 
  likely to be called next.
  * Temporal locality -- find where in cache to put data. 
    * Direct mapped places data from main memory into 1 possible 
	cache line
	* Two-way set associative places data from main memory into 1 of 2 
	possible cache lines. Choose least-recently used cache line.
	* Fully associative allows any cache line. Typically too costly.

Coherence between cache and main memory is achieved through:
  * Write-through -- write all changes in cache to main memory.
  * Write-back -- mark written cache lines as dirty, then write to main 
  memory upon cache eviction.

Cache coherence issues arise in multi-core systems. Typically each core 
has a private L1 cache and shared L2 cache. Need to propagate changes to 
all copies of data.
  * Solutions include MESI protocol, with modified, exclusive, shared, and 
  invalid states to mark cached data lines.
  * These solutions mark the entire line, which leads to inefficiencies 
  if just a few members are edited. E.g. false sharing / cache line 
  ping-pong degrades multi-threaded performance.

Latency from reading from main memory can be hidden via simultaneous 
multi-threading (do something else while waiting) or prefetching (load 
data before needed, and do something else while waiting). Generally 
useful to interleave communication and computation.

### Parallelism

Single instruction single data (traditional von Neumann arch), Single 
instruction multiple data (data parallelism), Multiple instruction multiple 
data, and Multiple instruction single data (uncommon).

Each core has vector units that do SIMD.

Instruction-level parallelism is achieved via pipelining (overlapped 
execution of fetching, decoding, executing, accessign memory, writing) or 
superscalar parallelism (many procs executing many independent 
instructions in parallel).

Conditional statements are bad for SIMD. E.g., subtract `u[i] - v[i] if 
u[i] > 0 else u[i] + v[i]` requires the n ALUs to flag each element 
satisfying condition, then perform `u - v` and store if flagged, then 
perform `u + v` and store if not flagged. Only half as efficient as raw 
subtraction without condition.
  * Each nested if-statement halves the performance!

Intrinsics are assembly-coded functions. E.g., adding two size-8 vectors 
using `__m256` data type and `_mm256_add_ps(a,b)` function.
  * Matrix multiplication taking strides of 8 elements provides additional 
  6x speedup
  * Matrices need to be allocated on 32-byte boundaries though (use `_mm_malloc`)

Use SoA instead of AoS. Can even transpose, solve, then transpose back 
and it can be quicker.

### Exercises

1. (a) CPU with 1 core, 2.5 GHz clock, 8 single flop/core/cycle --> 20 GFlop/s. 
CPU-DRAM connection is 25.6 Gb/s. Cache is 256 Kb. Matrix size is 256 x 
256 x 4 = 256 Kb, which barely fits in cache. Modify in-place. Transfer in 
and out takes 256/25.6 * 2 = 20 microseconds. Calculation takes 256^2/20 = 
3.3 microseconds. 
(b) 5x5 mask cannot modify matrix in-place. This doesn't change ideal bound 
for comms though. Calculation now needs 25x more steps. Now compute-bound.
(c) Caching strategy might involve breaking matrix into square chunks. Stop 
writes early (load buffers around slice edges) to avoid cache misses.

4. Interleaved sum has each element in cache line edited by a different 
thread! Many false sharing issues. Use contiguous batches instead.

8. Jacobi stencil takes moving average. `B[i] = (A[i-1] + A[i] + A[i+1])/3` 
then `A[i] = B[i]`. Efficient solution could split A into chunks of 8 and B 
into chunks of 6, then compute transformation on middle 6. Slide in strides 
of 6. Write back in chunks of 8 once finished.

## C++ multithreading

C++ previously relied on POSIX threads or Intel Thread Building Blocks, but 
with C++11 there are now platform-independent ways to multithread.

Multiprocessing splits tasks over multiple compute units. Multithreading 
shares hardware resources to avoid idling. No need to distinguish real and 
virtual (hyper-) threads when programming.
  * But avoid oversubscription! Keep number of threads ~= number of cores.
  * Threads can communicate quickly. However, there are security issues.

`join` threads to have master thread wait for completion, or `detach` to 
move on. Each thread can be joined or detached once, and cannot be converted. 
  * Detaching is rarely useful.

Typical structure is 
  1. Make a `std::vector< std::thread >`
  2. Fill it with `threads.emplace_back( fct, arg1, arg2,... )`
  3. Join after filling entire vector with `thread.join()` for each thread
  * Use `auto&` when looping to join bc threads are move-only.
  * Cannot deduce type, so need to specify.
  * Need to compile code with `-pthread` flag.

### Accessing return values

No way to access return values. All functions should be of type `void`. 
  * Can write to variables by passing in pointer to function, then editing 
  variable in function.
  * Better to use promises and futures

Promises and futures -- master thread waits for all futures to be signaled.
  1. Master thread creates `promise` with `std::promise<type> p` and 
  assigns a `future` with `std::future<type> f = p.get_future()`
  2. Pass `p` to spawned thread as rvalue with `std::promise<type> && p`
    * `threads.emplace_back( fct, arg1, std::move(p) )` bc rvalues must be moved.
  3. The spawned thread fulfills the promise with `p.set_value(val)` and 
  synchs with the master. 
  4. Now the master can access the value with `f.get()`.
  5. join or detach threads at end of program.

Better still, `std::packaged_task` objects handle return values elegantly
  1. Create task with auto-assigned future `std::packaged_task< return_type 
  ( arg types )> t( fct )`
  2. Grab future `auto f = t.get_future()`
  3. Access future `f.get()`

Can create task factory function template to avoid specifying function 
return and arg types.

Asynchronous method is even simpler: `auto f = std::async(fct, arg1, 
arg2...)`. However, `async` may choose to not spawn a new thread and task 
may never execute if we don't access future.
  * `std::launch::async` policy immediately executes, while 
  `std::launch::deferred` policy executes lazily (upon calling `future.get()`).
  * Task gets serialized if future's destructor is called, e.g. by leaving 
  scope. Must store futures outside for-loop!

### Best practices

Don't spawn many more threads than there are cores. E.g., one thread per 
row in mat-vec multiplication. Instead, create threads with chunks of 
tasks or do cyclic distribution (take task p, 2p, 3p, ...) or combo.
  * Beware of false sharing for cyclic distribution. Can have overlap in 
  cache lines of written variables (output). Avoid with intermediate 
  variables stored locally.
  * s = p c tasks, where s is stride length and c is chunk size. c = 1 is 
  pure cyclic, c = m/p is pure chunk. Small c is good for load balancing 
  but can have false sharing issues. Big c is opposite. Choose c to cover 
  a complete cache line (8 doubles, e.g.).

Use lambda functions to capture global variables by reference. Pass in 
index number explicitly as input. Load threads and join to launch.

Branch-and-bound algorithms using backtracking have widely variable 
runtimes. Querying external data sources is also variable. Use dynamic 
scheduling to assign tasks during runtime.
  * Use global variable to denote first set (row, e.g.) of processed 
  chunk. Update this variable upon usage.
  * `std::mutex` in global portion can be controlled inside thread. 
  `std::lock_guard< std::mutex >` automatically unlocks mutex at end of 
  code block.
  * This obviates static blocks, so we don't need thread ID anymore.

Condition variables put waiting threads to sleep. 
  1. Signaling thread takes mutex and performs serial work, then sends 
  condition variable signal to one/all other threads. 
  2. Waiting thread acquires `std::unique_lock` (not`std::lock_guard`!) on 
  above mutex and calls `cv.wait()`

One-shot synchonization with futures and promises has future access synched 
with setting promise value. Future is only read once, so this is only 
useful if one thread signals one other thread. Shared future can handle 
multiple threads.
  1. Pass future to function
  2. Access future at beginning of function with `f.get()`
  3. Write any value to promise with `p.set_value()`

If number if tasks is unknown, then use a thread pool to maintain a fixed 
number of threads to incrementally process a list of tasks.
  * Enqueue fct and task id into thread pool, then add returned future 
  to vector.
  * Queue is type `std::queue< std::function< void(void) > >`

Atomics avoid expensive lock acquisition. Useful for signaling other 
threads to stop.

Branching algorithms like brute-force knapsack can get superlinear speedup 
due to lack of pruning power. Sequential algo wastes time exploring bad 
branch.
