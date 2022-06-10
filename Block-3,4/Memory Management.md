# Memory management:

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
