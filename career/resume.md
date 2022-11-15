# Resume

## basics

primary memory = RAM, volatile (lost if power out)  
secondary memory = disk, non-volatile (kept if power out)    
bus = high-speed wire  
* data  --  send data bidirectionally
* address  --  carry addresses, unidirectional
* control  --  carry control+clock signals, unidirectional

8 bits = byte  
2 bytes = word  

## instruction set architecture (ISA)

defines:  
* list of functions the CPU can understand  
* how to translate a message between the hardware and software  

3 popular styles:
* Complex Instruction Set Computer (CISC) -- old -- x86 -- machine code length varies
  * tries to reduce total number of instructions
* Reduced Instruction Set Computer (RISC) -- new -- ARM -- machine code same length
  * many pipelined single-cycle instructions
* Microprocessor without Interlocked Pipeline Stages (MIPS) -- new RISC -- embedded processors
  * 3 instruction types:
    * register -- arithmetic and logic
    * immediate -- data transfer and operations on constants
    * jump -- used in loops
  * 32 registers total
  * format is `opcode` `source_register1` `source_register2` `destination_register` `bit_shift` `extra_functions`

heirarchy:  programs --> high-level language --> compiler --> assembly --> ISA --> hardware  

first few bits are operation code (OPCODE)  
remaining bits are operands  

## central processing unit (CPU)

comprises:  
* control unit (CU)  --  handles input/output, contains clock
* arithmetic and logic unit (ALU)  --  performs work
* registers (immediate access store)  --  high speed memory, 8/16/32/64 total

## assembly

1. preprocessing -- remove comments, expand macros, perform code maintenance
2. compiling -- translate code into assembly
3. assembling -- translate assembly into machine code
4. linking -- fill in functions, objects, and libraries

MIPS assembly language uses format `opcode operand_1 operand_2 ...`  
direct register addresses begin with `$`  
adding takes 3 operands: source_1, source_2, target. optionally a constant   
can load and store words (32 bits)  
can branch on equality or < / > zero  
can jump to register and execute its code  
($#) tells language that the value is an address + to use value in THAT address (not this one)  

## cache

processor speeds outperform memory  
each entry in cache contains tag (address in main memory) and value  
cache hit = data found in cache, so no need to query main memory  

replacement policy determines which cache entry is overwritten when new data wants to enter cache  
* first-in-first-out
* least-recently used (hard to implement)
* random replacement (may cause more misses)

cache associativity = assigning data to specific cache blocks   
* fully associative  --  data can go anywhere
* directly mapped  --  one cache entry for each location in main memory
* n-way set associative  --  cache partitioned into sets of n blocks

write policy determines which cache entry is overwritten when new data must be written out  
* write-through  --  write to cache and main memory
* write-back  --  only write to main memory if cache must be overwritten

some policies may be quicker based on how data is input.  
ideally, keep queries to the same data bunched together so data can just stay in cache.  

## instruction parallelism

the instruction cycle comprises:  
1. fetch  --  copy instruction address from program counter (PC) to instruction register (IR)
2. decode  --  instruction turned into control signals 
3. execute 
4. memory access (if needed)
5. registry write-back (if needed)

"pipelining" performs independent tasks simultaneously through same execution units  
e.g., fetch instruction 2 while decoding instruction 1   

pipelining hazards include:  
* structural  --  hardware limitations in memory access, ALU speed, etc.  
  * solution: better cache design
* data  --  one instruction is dependent on another
  * solution: can pass results between instructions
  * solution: reorder instruction sequence
  * solution: create bubble/stall until required data is available
* control  --  if, loop, branch. processor doesn't know what to do until branch processed
  * (bad) solution: long stall until branch is processed
  * solution: branch prediction
  * solution: inline method to avoid calls
  * solution: unroll loops

"superscalar" architecture spreads instructions across several execution units using dispatcher  
allows for specialization (one ALU for integers, another for floats, e.g.)  

superscalar hazards include:
* structural  --  poor assignments, registry conflicts
* data  --  could execute 2nd instruction before 1st
* control  --  if, loop, branch. 
  * solution: speculative execution (execute both branches and keep the right one)

superscaling is limited by:
* instruction set parallelism
* cost of dependency checking
* cost of branch checking

## data-level parallelism

single instruction, multiple data (SIMD)  
....same function applied to each data element

includes:  
### vector processing
process multiple related values simultaneously  
* only one instruction fetch + decode needed  
* overlapping memory accesses  
* internal looping keeps track of which element to process next  
* uses vector registers to store vectors  
* each vector lane can independently handle a chunk of the vector  

### SIMD extensions
scalar processors with some components of vector processors  
* has unique vector asssembly commands like `ADDPS` and `VADDPS` 

### GPUs
contain many simple functional units  
slower clock speeds than CPUs  
very inefficient at branching 
use single instruction multiple thread:
* small processing units ("threads") synchronously process data 
