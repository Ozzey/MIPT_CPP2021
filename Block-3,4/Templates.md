### Templates:
- Functions specialization
- What are templates (motivation):
    - Template classes and functions, examples
- Template specializations:
    - The principle: `particular is preferable to general`
    - The principle is `the exact match is better`
    - Partial and full specializations
    - Function specialization vs template function specialization
    - Compiler selection rules for specialization and overloading candidates 
- Template parameters that are not types (example: `std::array`). Template template parameters
- `typedef` keyword
- `using` keyword: template and non-template `using` versions
-  template recursion: ideas and usage (example: function `print_all`)

### Inheritance:
- Inheritance declaration:
    - `protected` access modifier.
    - Difference between `private`, `public` and `protected` inheritance.
    - Difference between `class` inheritance and `struct`.
    - Keyword `final`
- Finding names when inheriting:
    - Hiding names of the base class methods.
    - Explicit call of the parent methods of the inheritor (Using `operator ::`).
    - The order in which constructors and destructors are called in inheritance. The problem with the initialization of the parents when defining the constructor of the inheritor, again using the initializer lists to solve it.
    - Multiple inheritance, ambiguity with it, diamond inheritance problem. Examples of disambiguation using type conversions and the `operator ::`.
- Typecasting between parent and child:
    - Trimming when copying, casting pointers, casting references.
    - Operator `dynamic_cast`
- `virtual` functions, their general idea and difference from non-virtual ones:
    - Features of allocation of classes with `virtual` functions in memory
    - `virtual` inheritance.
    - Concept of the `v-table`
    - `virtual` destructor and its purpose
- The concept of dynamic polymorphism, polymorphic classes
- Placement in memory of classes
- Abstract classes:
    - `pure virtual` functions, their features.
    - `pure virtual` destructor (and why it causes the linker error).
    - Keyword `override`.
    - keyword `final` (for methods)
- Curiously recurring template pattern 

### Exceptions:
- General idea:
    - Motivation for using exceptions.
    - The `throw` statement and the `try/catch` block.
    - Examples of standard operators that throw exceptions.
- Difference between exceptions and runtime errors. Errors that are not exceptions and exceptions that are not errors.
- Rules for catching and re-throwing exceptions, casting types when catching exceptions. Catching all exceptions. The rules for choosing a catch block by the compiler in the case when different blocks are suitable.
- Copying when throwing and catching exceptions. Features of catching exceptions by value and by reference.
- Old-style exception specifications and their problems, unexpected exceptions. C++ 11 style exception specifications, `noexcept` operator and specifier. Conditional noexcept.
- Exceptions in constructors and the problem of memory leaks on exceptions.
- Exceptions in destructors.
- Security guarantees for exceptions: basic and strict.



### Memory management:
+ Operators `new`, `delete`, `new[]`, `delete[]`, recap and how they work in details
+ Alignas new
    + Size of structures
    + Alignof
    + Alignas specifier
+ Lifecycle of the data
+ Nothrow `operator new`
+ Raw data allocation and deallocation
+ Calling destructor explicitly
+ Operator placement new, calling constructor explicitly
+ `std::construct_at`, `std::destroy_at`
+ Operator `new` VS function "operator new"
+ Signature of the function "operator new"
+ Array versions of functions "operator new" and "operator delete"
+ Replacing functions "operator new" and "operator delete", motivation, example
+ Memory allocation mechanism, its interface
+ `std::allocator`
+ `std::allocator_traits`: motivation, typedefs and methods, usage
+ Custom allocators: motivation, examples
+ Comparison of different common custom allocators

### Move semantics:
+ Rvalues and lvalues in C++07 (recap), troubles with them (examples)
+ Temporary objects
+ General idea of the new value mechanism in C++11: solving troubles of C++07
+ Rvalue references
+ `std::move`, invalidation of the initilial objects after move
+ Move constructor, its signature and implementation
+ Move assignment operator, its signature and implementation
+ Default move constructor and move assignment operator
+ The rule of **three/five/zero**
+ Copy elision, RVO, NRVO
+ Complete and incomplete tyeps
+ Universal references
+ `std::remove_reference`
+ `std::move` implementation
+ `std::forward`, its implementation
+ Value categories in C++11: `glvalue`, `rvalue`, `lvalue`, `prvalue`, `xvalue`
+ Reference qualifiers
+ Noexcept specifiers in C++17, conditional noexcept specifiers in C++17, potentially throwing functions in C++17, noexcept operator in C++17
