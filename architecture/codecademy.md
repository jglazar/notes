# Computer Architecture

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

defines the list of all the functions that the CPU can understand and how to translate a message between the hardware and software  

* Complex Instruction Set Computer (CISC) -- old -- x86
* Reduced Instruction Set Computer (RISC) -- new -- ARM
* modified RISC design (MIPS) -- new -- embedded processors

heirarchy:  programs --> high-level language --> compiler --> assembly --> ISA --> hardware  

## central processing unit (CPU)

comprises:  
* control unit (CU)  --  handles input/output, contains clock
* arithmetic and logic unit (ALU)  --  performs work
* registers (immediate access store)  --  high speed memory, 8/16/32/64 total
