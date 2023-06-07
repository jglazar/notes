# Memory and allocation

## SamWho.dev article on memory allocation

`malloc(int x)` returns void pointer to `x` bytes of contiguous space
  * `malloc(0)` is implementation-defined. Just don't do it.

`free(int *p)` frees that space

Simplest allocator just tracks pointer to next free piece of memory and never
frees -- fast and useful if memory use is small

Easy allocator -- keep separate list of `(start, size)` pairs of free memory
  * `malloc(size)` finds first free block and removes `(start, size)` from list
  * `free(start)` adds `(start, size)` back to list
  * Contiguous free blocks don't know they're contiguous! Prevents big
    allocations
  * Must use "coalescing" to combine contiguous free blocks if possible

Fragmentation is irreversible -- to prevent, try:
  * Overallocating -- e.g., always reserve at least 4 bytes 
  * "Slab" allocating -- separating small from large allocations

"Boundary tag allocators" store memory bookkeeping in bytes alongside allocation
  * Allocate 3 bytes for `size`, `state` (free/used), and `size` again (at end)
  * Obviates searching free list to find block size. Just set state to free!
  * Extra `size` block at end lets next block check to coalesce with previous
  * Buffer overwrites or freeing middle of allocation can be catastrophic!
    * Can store extra "magic value" in 3rd byte to double-check `free(p)` 

## Vavrusa.com article on C memory

Protected mode gives access to virtual address space. Virtual space is not
bounded by or entitled to real memory

Virtual memory allocator may overcommit -- give access to memory it doesn't
control
  * If you dereference a pointer in this memory, an OOM killer should kill the
    program

`alloca(int x)` allocates `x` bytes for current stack frame. Gets deallocated
when you leave scope
  * `alloca` and variable-length arrays (VLAs) go on stack and can overflow
  * `getrlimit()` gets and sets resource limits
  * `sigtalstack()` lets you catch stack overflow segfaults
  * Split-stacks create many stacklets that grow dynamically. Use
    `-fsplit-stack` flag to activate in GCC. Can be finnicky

