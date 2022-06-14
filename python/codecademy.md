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

### threads
"thread" = actual sequence of processor instructions  
* at least one thread per process  
* share common resources like memory pages and active files  
* fast communication and context switching b/t threads
* e.g. user input thread, sound thread, video thread within game process

"multithreading" = single CPU core executes multiple threads  
* pro: tasks evenly split between threads 
* con: complex and non-deterministic (depends on CPU timing)
  * data race -- multiple threads write to same data
  * deadlock -- multiple threads wait for each other

"kernel thread" = thread built into existing process  
* OS kernel is aware of and manages thread   

"user thread" = thread only in user space  
* OS does not manage, so more efficient  
* needs to be mapped to kernel thread for execution
  * 1:1 kernel-level threading for simple system
  * N:1 user-level threading for ultra-light threads
    * no hardware acceleration
  * M:N hybrid threading

### Python

threads  
* define threads with `import threading; thr = threading.Thread(target=fnct, args=(a1,a2,...,))`  
  * need trailing "," at end of arglist if only one arg 
* start thread with `thr.start()`  
* Python waits until the last thread to finish before terminating program  
  * but will claim to be done after last thread begins  
* use `thr.join()` after all `thr.start()` to force Python to wait for all thread execution to finish  
  * use separate for-loops for start and join
* threads may not finish in the order they are started  

async  
* defines functions as "coroutines", which may be be paused/resumed to mimic multitasking
  * use `async def fn`
* run with `asyncio.run(fn)`
* `await` command waits for condition to finish before continuing 
* `await asyncio.gather(*tasks)` groups all tasks together and allows them to run concurrently
  * `*tasks` unpacks tasks list
  * output order will be deterministic

multiprocessing  
* same syntax as threads: `import multiprocessing; proc = multiprocessing.Process(target=fnct, args=(a1,a2,...,))`
* start with `proc.start()`, then join with `proc.join()`
* output order is non-deterministic, like threads

can use `time.perf_counter()` to track code performance  

personal test:  
`for t in range(10000000): 46271902.01283094 / (t+1.2)`  
perform 3 times  
results:  
* multiprocessing ~ 0.6 s
* sequential ~ thread ~ 1.8 s
* async ~ 2.7 s

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

