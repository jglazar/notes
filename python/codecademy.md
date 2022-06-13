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
filter and map take in one iterable and a one-parameter function  
reduce takes in one iterable and a two-parameter function called an "accumulator"  
....need to import functools to access reduce method  


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
* pass *args and **kwargs to `basic_function` in wrapper definition 
