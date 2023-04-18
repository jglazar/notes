# Online articles

## Design patterns

Site [here](https://neetcode.io/courses/lessons/8-design-patterns)

Factory -- class with no data, just methods that create another object

Builder -- class with one object, and methods that build up that object and a 
`build` method to return the object
  * `my_burger = BurgurBuilder().add_bun("sesame").add_patty("vegan").build()`

Singleton -- class with only one instance. Has static `instance` variable and
non-static `is_active` member. 
  * `@staticmethod get_state(): if not class.instance: class.instance = class(); 
  return class.instance`
  * Always initialize as `var = class.get_state()` 
  * Can have many vars acting as pointers to one instance

Observer / Pub-Sub -- Publisher creates events and Subscribers receive events. 
  * Pub class has list of Sub objects
  * Pub performs `notify_all(message): for s in self.subs: s.receive(message)`
  * Sub class has `receive` method to take in message

Iterators -- defined for most built-in collections, but can be customized with 
methods `__iter__(self)` to start at head and `__next__(self)` to proceed
  * `LinkedList` class has `head` and `current`, `ListNode` class has `val` and
    `next`
  * `__iter__(self): self.current = self.head; return self`
  * `__next__(self): if not self.current: raise StopIteration; else val = 
  self.current.val, self.current = self.current.next; return val`

Strategy -- define an abstract Strategy class with one method, then xStrategy 
subclasses with that fit the generic method's interface spec.
  * Strategy `@abstractmethod def my_fct(): pass`
  * xStrategy `def my_fct(): do x then return val`, yStrategy, ...
  * Now you can include Strategy where needed and call `my_fct`, and pass in
    different subclasses as-needed
  * Basically obviated bc Python allows passing functions

Facade -- wrapper to hide implementation details
  * Might wrap data structure in simple class with `push_back()` and 
  `pop_back()` public methods, plus `resize` private method

Adapter -- allow incompatable objects to interact. Extends class behavior
without modification
  * `class ABadapter: def __init__(self, A): perform modifications, then act
    like B`
