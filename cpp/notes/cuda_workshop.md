# CUDA workshop, 5 November 2022

## Basics

CUDA (Compute Unified Device Architecture) exposes GPU parallelism

Main components are CPU `host` and GPU `device`, each with separate memories.

The CUDA `kernel` is executed N times by N threads
  * Copies input from host to device, and caches data on chip.
    * PCI bus (slow) connects CPU/bridge/memory and GPU/interconnect/DRAM
  * Use `__global__` keyword in (void) function
  * `ThreadIdx.x` gives thread index in 1 dimension
  * Specify number of threads with `<<<blocks,threads_per_block>>>`

Function types:
  * `__global__ void` calls from host and executes on device
  * `__device__ float` calls from device and executes on device (inlined)
  * `__host__ float` calls from host and executes on host

No static variables or malloc! Too much memory required. May use recursion

## Thread heirarchy

Grid has 1+ blocks. Block has 1+ threads, in 1D, 2D, or 3D (rare).
  * All blocks have the same number of threads (<= 1024)
  * Can specifically sync data
  * Block has own shared memory
  * No block-block communication

Block to core mapping is managed well (job scheduling and such)

BlockDim gives thread size, with `idx = idx.y * dim.x + idx.x`

`dim3` is a struct with x,y,z coords.

Example -- 4096 x 4096 matrix, want 16 threads per block in x and y
  * 4096 x 4096 / 16 / 16 = 256 x 256 = number of blocks needed
  * `x = blockIdx.x * blockDim.x + threadIdx.x`

## Memory

Pointers may be passed to/from device/host, but cannot de-reference in 
wrong place!

Use `CudaMalloc(), free(), Memcpy()`

GPU has global memory similar to RAM and constant memory that's read-only

Pass address to address: `Cudamalloc((void**)&deviceMemory, size)` then 
`CudaFree(deviceMemory)`

`CudaMemcpy(devicePtr, hostPtr, size, direction)` is done over PCIe
  * 1st parameter is destination, 2nd parameter is source

Kernel runs on device and uses size effects.

Example -- matrix multiplication is O(N^3)
  * Avoid accessing global memory many times in kernel
  * Memory is the killer, not the compute (opposite of CPU)
    * Mainly limited by number of blocks
  * Avoid global memory access on device -- assign each block its own local tile of 
  the matrix.

## Architecture

SM has many SPs (cores)

Warp is 32 threads from block running on SM. Warp is basic unit of 
job scheduling
  * May launch more threads than cores

Registers live on-chip and have zero latency
  * 768 threads, 8000 registers --> about 10 registers per thread.

Shared memory cannot be over-booked

Different types of memory are defined at compile time

Progression: GT08, GT200, Fermi, Kepler, Maxwell, Turing, Ampere
  * More cores, better memory and job scheduling
  * Modern devices: GEForce (gaming), Quaddro (workstation/graphics), 
  Tesla (computing)

`nvidia-smi.exe` gives GPU info. `-q` or `-a` gives more info.

`__syncthreads` acts like MPI barrier
  * Can only sync within block (own shared memory and context)
  * Each line has its own `__syncthreads` instance, so each thread must stop on same 
  line number's `__syncthreads` command!

## Advice

Try to hide memory latency
  * Use many threads-in-flight
  * Avoid branching

Global memory is best read in 1 sequential chunk. Avoid random access!

Check out NVIDIA GitHub code samples.

Avoid sync and if statements (could hang)

Break kernel into phases -- create a sliding window
  * Store window data in shared memory
  * Write to shared memory using `syncthreads` before and after
  * Beware of exceeding max threads per block or shared memory

Use `__exp/log/sin/pow` for speed, sacrificing precision
  * Vector types accept up to 4 elements

Avoid writing your own kernels
  * Use pre-built libraries on CUDA-X
  * Use Thrust, which is parallel version of STL
    * Copy using assign operator `=`
	* Can still interact with custom kernels
	* Also works on CPU through OpenMP
  * Only write your own CUDA if you're already patching together many 
  Thrust pieces

CUDA is great for SIMD and massively parallel computing
  * Determine critical problem size, operations, memory constraints
  * Main overhead is copying memory between CPU and GPU

Next big thing may be mobile or web
  * CUDA is mature, and tensor math / ray tracing are solved.

Instructor is scared of C++ parallelism!
