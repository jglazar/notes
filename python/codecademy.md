# Advanced Python

## functional programming

functions store and manipulate data  
can be passed into and out of other functions (first-class citizens)  

### imperative vs. declarative
imperative describes step-by-step solution  --  concerned with "how to solve"  --  OOP/procedural  
declarative relies on framework  --  concerned with "what to solve"  --  functional  
....declarative hides details away  

### functional programming guidelines
function outputs are deterministic  
functions shouldn't have side effects (pure functions are ideal)  
functions shouldn't rely on global variables  
use recursion rather than loops -- loops rely on external counter variables  
use lambda functions to define small functions  
use multithreading when possible  

### data types
use immutable data types for thread-safe manipulation and preventing accidental changes  
....namedtuples are nice  --  `var = namedtuple("var", ["field1", "field2", ...])`  
lambda functions can be stored as variables!  

### filter, map, and reduce
input iterable and processing function, return iterable  
* filter and map take in one iterable and a one-parameter function  
* reduce takes in one iterable and a two-parameter function called an "accumulator"  
  * need to import functools to access reduce method  
* can combine functions to map or reduce on filtered dataset, e.g.  
* can find min element in dataset using `reduce(lambda x,y: x if x.val<y.val else y)`  
* reduce + map is useful for iterating through dictionaries

## concurrent programming

* concurrent -- multiple tasks running and completing in overlapping periods
  * many elements in few groups, one executor (juggling)  
  * Python `threading` module
* parallel -- multiple tasks running on multiple CPUs
  * many elements in few groups, many executors (delegating)
  * Python `multiprocessing` module
* asynchronous -- elements may be executed out-of-order 
  * Python `asyncio` module

### processes
"process" = running program which operates independently and doesn't share data
....aka "task" or "job"  
....seen in Task Manager in OS

process lifecycle:  
1. `new` -- program is started + waits to be put into memory
2. `ready` -- process waiting to be picked up by processor
  * process may be placed here upon preemption
3. `running`
4. `blocked` -- process waiting for contested resource
  * allows processor to prioritize quicker processes
5. `finished`
"context switching" between states has overhead  

process sections:  
* text  -- compiled code
* data -- initialized variables
* stack -- local variables in functions
* heap -- dynamic memory allocation

process control block sections:
* process ID + parent IDs
* process state
* process runtime + time limits
* allowed resources + permissions
* process priority
* program counter for address of current instruction
* addresses of registers with intermediate values
* info for memory management like page+segment tables 
child processes have most properties of parent processes  
parent processes generally wait for children before terminating  

## misc

### decorators
decorators help make code more readable  

recall:  
* functions are objects
  * they live at memory addresses
* functions can be defined within other functions
* functions can be returned from other functions
  * just define function_small within function_big and `return function_small`

decorators take in a function and output an augmented function  
wrappers are common. e.g.:  
* `def decorator(fn):`
  * `def wrapper(): <do thing>; fn;`
  * `return wrapper`

`decorated_function = decorator( basic_function )`    
or  
put `@decorator` above basic_function definition to have Python automatically apply decorator  

if `basic_function` takes arguments, then you need to:  
* define wrapper with `def wrapper(*args, **kwargs)`
* call `basic_function(*args, **kwargs)` in wrapper definition

`@property` decorator refers to built-in function with arguments:  
* `fget`  --   getter
* `fset`  --   setter
* `fdel`  --   delete
* `doc`  --  docstring  

define property with `@property; def prop(self): return self.prop` (getter method)    

then define `fset` and `fdel` with `@prop.setter` and `@prop.deleter`  

