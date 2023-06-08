# Software design by ArjanCodes and others

## Design guide

1. What does this code do?
  * How does it work, and what are the main components?
  * Zoom out (think broadly), then zoom in (what to build first)
2. UI
  * Use UI mockups
  * Don't use clever design, use clear design
3. Technical specification
  * Libraries, algorithms, database design, classes, design patterns
  * Use UML to draw main classes
  * Consider edge cases and errors
4. Testing and security
  * Consider side effects of new features
  * Develop a tester's mindset -- how could things break?
5. Deployment
  * Migration, architecture, DevOps, microservices
  * Development, Testing, Acceptance/Staging, Production environments
6. Planning
  * Estimate time, steps, milestones, risks, requirements
7. Context
  * Limitations and extensions

## Code diagnosis workshop

Easy to understand, change, and test

Don't randomly refactor. Instead, write down problems.

Warning signs
  * Big functions, classes, files (>500 lines).
  * Many variables, esp. instance variables.
  * Big initializers.
  * Many imports.
  * Nested if/else
  * Deep inheritance -- changes in parents require changes in children
  * Mixed inheritance
  * Inappropriate intimacy / Law of Demeter -- passing too much data 
  as fct argument 
  * Repeated code. Use dict/emum instead, e.g.
  * Creating and using resource in same code. Makes testing hard.

Name variables, classes, constants consistently.

Need updated docstrings and comments.

Use type annotations.

Avoid overpowered Python magic, like extensive custom decorators.

Use abstraction to decouple code. E.g., create Protocol class to 
encapsulate needed data/functions.
  * Useful when fct/class loads only a few variables/fcts from 
  source.

## Refactoring data science code

Tons of imports, using TensorBoard to track NN training, parameters define 
NN training. Use Torch to train.

Containers collect data during training. Every epoch has training and testing. 

Dataset file gets/loads dataset.

Problem -- don't overwrite `x = fct_a(); x = fct_b(); ...`. Use function 
composition instead, like Torch sequential network / sklearn pipeline.
  * Can use nested function calls, or (better) define a compose function

`ComposableFunction = Callable[[float], float]`. 
`def compose( *functions : ComposableFunction ) -> ComposableFunction: 
return functools.reduce( lambda f, g: lambda x: g(f(x)), functions )`.

Then call with `compose( fct1, fct2, fct3,... )`

Don't use "utils" as filename. Too generic.

Use `Enum` and `auto()` to toggle between few values, instead of frozen 
data class. Use `.name` property instead of raw enum (int).

Abstract class should only have abstract methods, not typed variables. Use 
`@abstractmethod` decorator.
  * `Protocol` is generally better, since you don't need decorators.

If class inherits from abstract base class (ABC), then the main function 
should only call methods included in the ABC to encourage trivial 
implementation swapping.
  * In other words, ABC sketches the interface.
  * Keep clear separation between ABC and child class. Put in separate files.

Be explicit and consistent about types, esp. float vs real.
  * Can use `Any` type for generic placeholder
  * Can use `Optional[type] = None` keyword in `__init__`

Dataclass doesn't need `__init__` method. Must initialize values in constructor 
list. Initialize empty list with `= field(default_factory=list)`
  * Dataclass also takes care of `__str__` method (when printing object)

Don't create reset method. Instead, just instantiate new object.

Software design should follow data flow. Tasks should be undertaken by classes 
that have direct access to relevant data (information expert design pattern).

Carefully consider how to consolidate repeated code. Perhaps make a class.

Notate private methods with leading underscore, like `_fct`.

Create `main` method, like in C. Keep the statements abstract!
  * Write constants (including files) in all caps at top of main file.
  * Use `pathlib` module for file paths. Gives you `Path` type.

Don't mix running a function with validating/testing!
  * E.g., don't intersperse `assert` statements. Keep them in a separate unit / 
  data validation testing file.

## Code smells

1. Imprecise types
  * Use Enum rather than string for finite possibilities
2. Duplicate code
  * Roll up fcts into one, using extra parameter if needed
3. Not using built-in fcts
  * Use list comprehensions!
4. Vague identifiers
  * Specify units
5. Using `isinstance` to separate behavior
  * Use inheritance and class methods. Don't forget to add as abstract 
  method too.
6. Using boolean flags within a fct to enable different functionality
  * Just make different functions
7. Catching but ignoring exceptions
  * Can accidentally ignore SyntaxErrors. Just get rid of try-except 
  block if not using.
8. Not using custom exceptions
  * Make class which is subclass of desired exception type, with parameters 
  in `__init__` fct to describe error.

1. Too many parameters
  * Indicates "feature envy", where object/method needs too many details 
  from elsewhere. Better to roll into one, or split differently.
  * Use `@dataclass` to bundle many vars into a struct, then pass one struct.
  * Add default values to `@dataclass` class variables.
2. Too deep nesting
  * Split methods
  * Create intermediate variables with meaningful names. Avoids super-long 
  single lines of code.
  * Use logical operations to combine conditions
  * Deal with errors first, then keep main code outside the `if` statement
  * Can use walrus operator `:=` to return result of assignment.
3. Wrong data structure
  * Use hashmaps (`dict`) and `.get(key)` to find elements, rather than 
  looping through list. May need hashable `Tuple` as key 
4. Nested conditionals in `return` statement
  * Just use regular `if` statements
5. Wildcard imports
  * Only import what you need, or (generally, better) import module
6. Asymmetrical code, or doing the same thing in different ways
  * Use built-in dunder methods like `__str__` or `__repr__`. str produces 
  human-readable string and repr produces full representation for object.
7. Unnecessary `self`
  * Use `@staticmethod` instead to remove `self` as parameter.
8. Not using `main()`

Use `pylint`, `pylance`, and `black` to help clean code

1. Wrong data structure
  * Only use SoA for performance. AoS is normally cleaner. Create separate 
  `@dataclass` struct to simplify.
2. Misleading names
  * Carefully consider `create...`, `get...`, and `delete...` methods. What 
  are you really creating/getting/deleting?
3. Classes with too many instance variables
  * Indicates class with too many responsibilities. E.g., tracking shopping 
  cart, order status, and customer info.
4. Verb/subject -- method gets one object as parameter and acts on that object
  * Ask-don't-tell principle -- ask object to perform task for you! Just 
  make it into a class method. Perhaps make into a `@property`.
5. Backpedaling, or calling a method without requisite data as args.
  * Similar to Law of Demeter. Method should not need to dig around another 
  object's data.
6. Hard-wired sequences in fixed order
  * Do sequences automatically instead, so user doesn't have to.
  * If performing outside of initializer (due to time, e.g.), create 
  asynchronous static method that returns an object.
7. Creating unrelated objects in the initializer
  * Use dependency injection -- pass object as arg instead. 
  * Use abstract base class / Protocol.
8. Not using keyword args
  * Better than manually writing long argument list.
  * Specify param name for each entry.

## ABC vs Protocol

ABCs require explicit imports of parent classes.

Removing abstract method implementation in child class causes type error.

Protocols rely on structural typing -- no explicit inheritance in children.

Indicate no implementation (abstract method) with `...`

ABCs catch error when creating instance. Protocols catch error when 
using method.

Protocols can mimic multiple inheritance. Can split one Protocol into 
many, with different names.

Protocols belong in the file that is using it.

## Functions

Can convert simple classes with only a few methods and no data into 
collection of fcts with appropriate names.

Instead of forcing child classes to define methods, instead pass 
functions as args into initializer. 
  * Customize function type with `LoadFunction = Callable[[Path], 
  pd.DataFrame]`, e.g.

Can further convert everything into functions to decouple data from methods. 
Can get messy though.

Above `LoadFunction` type requires same inputs (single path) and same 
outputs (df). Make more flexible with:
  * Closure -- define function that takes in parameters and 
  outputs desired `LoadFunction`. Then call closure fct with desired parameters 
  and pass resulting fct instead of original fct.
  * Partial -- perform partial application of parameterized fct before passing 
  along. E.g., `partial( my_fct, my_param=3 )`

## Inheritance vs Composition

Inheritance makes subclasses for different types of the main class.
  * E.g., Employee has salaried, freelance, and hourly, then with 
  commission and without commission. 
  * Heirarchy can get complicated!

Inheritance generally leads to code duplication. Can have classes with 
many responsibilities (bad).

Composition separates responsibilities, and allows chaining together more 
complex operations.

Can assign class some member vars which hold attributes. 
  * E.g., Employee can hold vars for Contract and `Optional[Commission]`

Functional approach uses decorators to tag different attributes, rather than 
multiple inheritance (right?)

## SOLID design principles

Single-responsibility principle
  * A class should have 1 reason to change. It should do 1 job
  * E.g., don't perform validation AND display -- those should be 2 classes

Open-closed principle
  * Entities like classes, modules, and functions should be open for extension
    (what the entity can do) but closed for modification (source code)
  * E.g., adding a new element directly to an array is bad. Create an
    ElementAdder entity that handles abstractly.

Liskov substitution principle
  * Superclass objects should be substitutable for subclass objects
  * E.g., Setting separate width and height for `Rectangle` class breaks for
    `Square` subclass. So don't make `Square` a subclass of `Rectangle`!

Interface segregation principle
  * A client shouldn't be forced to implement an interface it never uses
  * E.g., 2D shapes don't have `calculate_volume()` method. Create two
    superclasses instead, one for 2D shapes and one for 3D shapes

Dependency inversion principle
  * High-level modules shouldn't import anything from low-level modules
  * Abstractions should be independent of details
  * In other words, classes should depend on abstract interfaces, not the
    innards of concrete classes
  * E.g., writing a `Store` class with explicit methods handling Stripe
    payments. Create an abstract `Payments` class to handle payments instead

## Writing Python tests

Simplifying unit tests often highlights ways to simplify source code
  * Many interactions within a method make it hard to test

`pytest` auto-detects and executes tests in project `tests` directory
  * `pytest --cov` creates HTML report on method coverage

Start with tests for simple or important classes

Use `assert` to test simple (almost obvious) truths
  * E.g., `item = LineItem('paper', 100, 2); assert item.total == 200;`
  * Check for defaults. E.g., `item = LineItem(); assert item.total == 0`

Catch correctly-raised error by using `with pytest.raises(ErrorType): ...`

`pytest.MonkeyPatch` mocks input and overrides attributes
  * E.g., `def f(monkeypatch): inputs = [a, b, c];
    monkeypatch.setattr("builtins.input", lambda x: inputs.pop(0))`
  * Better -- make mock objects
  * Alternative -- use `pytest.fixture` to create standard testing objects 

Be sure that you:
  * Don't add API keys to source code, even in tests
    * Put them in separate `.env` file and import them as environment variables
      with `dotenv.load_dotenv` method
  * Don't upload API keys or `.env` files to GitHub
  * Don't hard code dates and expect them to always be in the future
  * Test the main functionality of a function, not the functions called therein
