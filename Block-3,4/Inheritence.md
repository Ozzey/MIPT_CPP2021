# Inheritance:

## Inheritance declaration:
   - `protected` access modifier.
   - Difference between `private`, `public` and `protected` inheritance.
   - Difference between `class` inheritance and `struct`.
   - Keyword `final`
## Finding names when inheriting:
   - Hiding names of the base class methods.
   - Explicit call of the parent methods of the inheritor (Using `operator ::`).
   - The order in which constructors and destructors are called in inheritance. The problem with the initialization of the parents when defining the constructor of the inheritor, again using the initializer lists to solve it.
   - Multiple inheritance, ambiguity with it, diamond inheritance problem. Examples of disambiguation using type conversions and the `operator ::`.
## Typecasting between parent and child:
   - Trimming when copying, casting pointers, casting references.
   - Operator `dynamic_cast`
## `virtual` functions, their general idea and difference from non-virtual ones:
   - Features of allocation of classes with `virtual` functions in memory
   - `virtual` inheritance.
   - Concept of the `v-table`
   - `virtual` destructor and its purpose
## The concept of dynamic polymorphism, polymorphic classes
## Placement in memory of classes
## Abstract classes:
   - `pure virtual` functions, their features.
   - `pure virtual` destructor (and why it causes the linker error).
   - Keyword `override`.
   - keyword `final` (for methods)
## Curiously recurring template pattern 
