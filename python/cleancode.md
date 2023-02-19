# Software design by ArjanCodes

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
