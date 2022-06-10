# Memory management:

### Operators `new`, `delete`, `new[]`, `delete[]`  

   - Operator `new` :
        * *Allocates new chunk of data via operating system call. Size of the chunk is 
getting calculated with the formula: `sizeof(T)`*
        * **Calls default (or non-default) constructor.**
   - Operator `delete` :  
        * **Calls destructor.**
        * *Deallocates the chunk of the data via operating system call*
   - Operator `new[]` :
        * **Allocates new chunk of data via operating system call. Size of the chunk is 
getting calculated with operator sizeof: `sizeof(T) * n`.**
        * **Calls default constructor n times (for every object in the array). **
    - Operator delete :
        * Calls destructor of every object in the array.
        * **Deallocates the chunk of the data via operating system call.**
        
       
   > Italics are called with help of OS  
   > Bold are implicit behaviour

   - Logger : prints its construction and destruction
        * For `new` and `delete`:  
     ```c++ 
        struct logger {
            logger () { std::cout << "Object constructed at " << this << std::endl; }
            ~logger () { std::cout << "Object at " << this << " destructed" << std::endl; }
            
            logger (const int x, const double y) {
            std::cout << "Object constructed with args " 
                        << x << ", " 
                        << y << " at "
                        << this <<std::endl;
             }
        };

        int main () {
            std::cout << "operator new used" << std::endl;
            logger* obj = new logger(1,2.4);
            std:: cout << "operator delete used" << std::endl;
            delete obj;
        }
     ```  
        * For `new[]` and `delete[]`:  
       ```c++
       struct logger {
        logger () { std::cout << "Object constructed at " << this << std::endl; }
        ~logger () { std::cout << "Object at " << this << " destructed" << std::endl; }

        logger (const int x, const double y) {
           std::cout << "Object constructed with args " 
                        << x << ", " 
                        << y << " at "
                        << this <<std::endl;
             }

        int main () {
            std::cout << ""operator new used, 3 logger objects" << std::endl;
            logger* objs = new logger[3];
            std:: cout << "operator delete used on all obj" << std::endl;
            delete obj;
            delete[] objs;
        }
       ```
       *
       
        
### Alignas new
    + Size of structures
    + Alignof
    + Alignas specifier
    
### Lifecycle of the data:

   - Every memory can be in three state :  
        + Non-allocated (empty data)
        + Allocated (raw data)
        + Constructed (allocated and defined)
   When operator new is getting called, operating system tries to allocate requested amount of bytes, and if it fails – throws `std::bad_alloc exception`.
   
   There is a special version of operator `new (nothrow operator new)` that doesn’t throw   `std::bad_alloc` when allocation fails, – it returns nullptr instead
    
### Nothrow `operator new`:
   ![image](https://user-images.githubusercontent.com/49760167/173154369-93302d6b-2b98-4fce-83f0-293ad9925106.png)
   - If an allocation fails, – std::bad_alloc() is getting thrown.We can use special operator (nothrow new) if we want to prevent throwing an error.  
   - In order to call nothrow operator new – you need to provide additional argument `std::nothrow`. It’s just a special value that is used especially for indicating that you want to call a nothrow operator new instead of normal one.  
   - Nothrow operator new doesn’t throw an exception even if an allocation fails, it just returns nulltpr instead.
    
### Raw data allocation and deallocation
   Using C-style allocation 
  - We use `void` bcause it represents raw data 
    ```c++
    int main () {
        size_t n = 5; /// amount of bytes.
        void* buffer = malloc(n);
        free(buffer);
    }
    ```
  - We can also use `char` because it is exactly 1 byte:
    ```c++
    int main () {
        size_t n = 7; /// amount of bytes.
        char* buffer = new char[n];
        delete[] buffer;
    }
    ```
### Calling destructor explicitly  
  Destructor is also a type of function so it can be called explicitly.
  - Example 1:
    ```c++
    int main(){
        logger obj;
        obj.~logger();
      }
    ```  
   
  - Example 2:
    ```c++
       struct point { /// 2 * 4B = 8B
            int _x, _y;
            point (int x, int y): _x(x), _y(y) {};
        };

        int main () {
            /**
             * -- ALLOCATE --
             *
             * We're using cast here in order to get the pointer of 
                the needed type (point)
             * so we'll be able to interact with the needed object.
             */
            point* object = reinterpret_cast<point*>(new char[sizeof(point)]);

            /**
             * -- CONSTRUCT --
             */
            // ???

            /**
             * -- DESTRUCT --
             */
            object->~point();

            /**
             * -- DEALLOCATE --
             *
             * Cast here is necessary!
             * We've allocated object as buffer of chars,
             * so we must deallocate it in the same way.
             */
            delete[] reinterpret_cast<char*>(object);

            return 0;
        }
    ```

### Operator placement new, calling constructor explicitly:
   We can't call constructor as an operator because it is not a callable method, it is used to create an object so there is not use on calling a constructor on an object that already exists.  
   - But we use operator placement new which only calls constructor without allocation data
   - It receives a pointer to an already allocated chunk of raw data and constructs the object in place with specified arguments
   - Previous example with constructor:
   ```c++
    struct point {
        int _x, _y;
        point (int x, int y): _x(x), _y(y) {};
    };


    int main () {
        /**
         * -- ALLOCATE --
         *
         * We're using cast here in order to get the pointer of the needed type
         * so we'll be able to interact with the needed object.
         */
        point* object = reinterpret_cast<point*>(new char[sizeof(point)]);

        /**
         * -- CONSTRUCT --
         *
         * Explicitly calling a constructor from 2 ints (see line 5)
         */
        new (object) point(2, 3);

        /**
         * -- DESTRUCT --
         */
        object->~point();

        /**
         * -- DEALLOCATE --
         *
         * Cast here is necessary!
         * We've allocated object as buffer of chars,
         * so we must deallocate it in the same way.
         */
        delete[] reinterpret_cast<char*>(object);

        return 0;
    }
   ```
   - Implementing this operator for basic functions: 
   ```c++
    struct point {
        point (double x, double y): _x(x), _y(y) {
            std::cout << "Point (" << _x << ", " << _y << ") 
                        constructed at " 
                        << this << std::endl;
        }

        ~point () {
            std::cout << 
                "Point (" << _x << ", " << _y << ") at " 
                << this << " destructed" << std::endl;
        }

        point (const point& other): _x(other._x), _y(other._y) {
            std::cout << "Point copy-constructed at " << this << std::endl;
        }

        /// Common implementation of assignment operator
        point& operator= (const point& other) {
           if (this != &other) {
                /// Want to destruct the current object first
                this->~point();
                /// Want to construct the object again using the copy constructor
                new (this) point(other);
            }

            return *this;
           }

    private:
        double _x, _y;
    };

    int main () {
        point first(2., 3.);
        point second(4., 5.);

        first = second;
    }
   ```

### `std::construct_at`, `std::destroy_at`

### Operator `new` VS function `operator new`
![image](https://user-images.githubusercontent.com/49760167/173157628-c61665c8-11af-4c1c-9706-335fd2529122.png)


### Signature of the function `operator new` 
![image](https://user-images.githubusercontent.com/49760167/173157580-e6a9e7e8-d5bf-460f-a972-e85e68fc9c9d.png)


### Signature of the function `operator delete`
![image](https://user-images.githubusercontent.com/49760167/173157671-126f6e0a-0558-4df0-b316-929ed538e89c.png)


### Array versions of functions "operator new" and "operator delete"
![image](https://user-images.githubusercontent.com/49760167/173157916-93ae84d5-d4ef-4ca8-9cf5-933f9191f3df.png)

   ```c++
    #include <new>
    
    class point {
    public:
        point (int x, int y, int z): _x(x), _y(y), _z(z) 
        { std::cout << "Constructed" << std::endl; }
        ~point () { std::cout << "Destructed" << std::endl; }
        int _x, _y, _z; /// 12 bytes
    };

    void* operator new (size_t bytes_count) {
        std::cout << "allocating " << bytes_count
        << " bytes" << std::endl;
        return malloc(bytes_count);
    }

    void operator delete (void* ptr) noexcept {
        std::cout << "deallocating chunk at " << ptr << std::endl;
        free(ptr);
    }


    void* operator new (size_t bytes_count, const std::nothrow_t&) noexcept {
        std::cout << "allocating (nothrow) " 
        << bytes_count << " bytes" << std::endl;
        return malloc(bytes_count);
    }

    void operator delete (void* ptr, const std::nothrow_t&) noexcept {
        std::cout << "deallocating (nothrow) chunk at " 
        << ptr << std::endl;
        free(ptr);
    }


    int main () {
        std::cout << "Standard versions:" << std::endl;
        point* first = new point(1, 2, 3);
        delete first;

        std::cout << std::endl << "Nothrow versions:" << std::endl;
        point* second = new (std::nothrow) point(3, 2, 1);
        second->~point();
        operator delete(second, std::nothrow);
    }
   ```

### Replacing functions "operator new" and "operator delete", motivation, example:
   - Motivation: you may have some additional information to help you to establish the most optimal allocation strategy for your program.

   - There is no way to overload operator new and operator delete themselves.All of the versions of function “Operator new” and function “Operator delete” can be replaced with the user-defined versions except the built-in function operator placement new.  
   
*RULE: if you replace operator new, you should also provide an overload of operator delete that receives the same additional arguments as new. There’s no way to replace standard function operator placement new, but there is a way to provide your own version of a function operator placement new. It’s called a user-defined function operator placement new.*

   - In order to do that, you should define a function operator new that’ll receive bytes count as first argument as always and other specific for you arguments. You’ll need to implement an analogue version of function operator delete in order to preserve the rule above.
   
   + Example 1: 
   ```c++
    #include <new>
    
    class point {
    public:
        point (int x, int y, int z): _x(x), _y(y), _z(z) 
        { std::cout << "Constructed" << std::endl; }
        ~point () { std::cout << "Destructed" << std::endl; }

        int _x, _y, _z; /// 12 bytes
    };


    void* operator new (size_t bytes_count, size_t max_bytes_count) {
        if (bytes_count > max_bytes_count)
            throw std::bad_alloc();

        void* ptr = malloc(bytes_count);
        std::cout << "Allocated successfully" << std::endl;

        return ptr;
    }

    template <typename T>
    void operator delete (void* ptr, size_t max_bytes_count) noexcept {
        free(ptr);
        std::cout << "Deallocated successfully" << std::endl;
    }

    int main () {
        size_t max_bytes_count;
        std::cout << "Enter bytes for allocations: ";
        std::cin >> max_bytes_count;

        try {
            point* first = new (max_bytes_count) 
                    point(1, 2, 3);
            operator delete<point>(first, max_bytes_count);
        } catch (...) {
            std::cout << "Struct is too big" << std::endl;
        }
    }
   ```
   + Example 2:
   ```c++
    class chunk_manager {
        private:
            const size_t k_buffer_size = 1024;
            size_t _type_size;
            size_t _allocations_count;
            size_t _deallocations_count;
            void* _buffer;

        public:
            explicit chunk_manager (const size_t type_size):
                    _type_size(type_size),
                    _allocations_count(0),
                    _deallocations_count(0),
                    _buffer(malloc(_type_size * k_buffer_size))
            {}

            ~chunk_manager () { free(_buffer); }

            void* alloc () {
                if (_allocations_count == k_buffer_size)
                    throw std::bad_alloc();

                return static_cast<void*>(static_cast<char*>(_buffer) 
                        + _type_size * (_allocations_count ++));
            }

            void dealloc () { ++ _deallocations_count; }
        };


        void* operator new (const size_t bytes_count, 
                            chunk_manager* manager) {
            return manager->alloc();
        }

        template <typename T>
        void operator delete (void* ptr, 
                            chunk_manager* manager) noexcept {
                static_cast<T*>(ptr)->~T();
                manager->dealloc();
        }


        class small_object { int a, b, c; }; /// 12B

        int main () {
            chunk_manager manager(sizeof(small_object));

            std::vector<small_object*> ptrs;
            size_t lowest_addr = -1;
            size_t highest_addr = 0;

            const size_t amount = 1024;

            for (size_t i = 0; i < amount; i ++) {
                small_object *ptr = new (&manager) small_object;

                /// DO SOMETHING HERE.
                ptrs.push_back(ptr);
                lowest_addr = std::min(lowest_addr, reinterpret_cast<size_t>(ptr));
                highest_addr = std::max(highest_addr, reinterpret_cast<size_t>(ptr));
                operator delete<small_object> (ptr, &manager);
            }

            const double fragmentation =
                    (
                            static_cast<double>(highest_addr - lowest_addr) +
                            static_cast<double>(sizeof(small_object))
                    ) / static_cast<double>(sizeof(small_object)) / 
                        static_cast<double>(amount);

            std::cout << "Fragmentation: " << fragmentation << std::endl;
        }

   ```
   Suppose that you’re developing a program that allocates 1000000 small objects in the loop, works with them, destroys them.  
    If we’ll use the standard operators new and delete – it’ll cause a big fragmentation of the memory. Allocated chunks of data won’t be structured 
efficiently because interpreter can’t predict the most efficient way for 
allocating our objects.   
    But we can. For example, we can provide our own version of operator new and delete that’ll be allocating 1 big chunk of data and manage it’s resources during the execution of the program.  

### Memory allocation mechanism, its interface
![image](https://user-images.githubusercontent.com/49760167/173160010-1b5e5166-829a-4164-bbc7-2fb9cde93aff.png)


### `std::allocator`
![image](https://user-images.githubusercontent.com/49760167/173160065-a28e4e52-c4da-461b-a360-b7283372dee5.png)

```c++
struct logger {
    explicit logger (const size_t id): _id(id) 
        { std::cout << "Constructed at " << this << std::endl; }
    ~logger () { std::cout << "Destructed at " << this << std::endl; }
    
    void print (const std::string &str) const 
        { std::cout << _id << ": " << str << std::endl; }

private:
    size_t _id; /// 8B
};

int main () {
    std::allocator<logger> alloc;

    const size_t n = 2;

    logger* chunk = alloc.allocate(n);

    for (size_t i = 0; i < n; i ++)
        alloc.construct(&chunk[i], i + 1);

    chunk[0].print("hello");
    chunk[1].print("bye");

    for (size_t i = 0; i < n; i ++)
        alloc.destroy(&chunk[i]);

    alloc.deallocate(chunk, n);
}
```


### `std::allocator_traits`: motivation, typedefs and methods, usage:
   ![image](https://user-images.githubusercontent.com/49760167/173160151-8d0a464c-2293-4aa9-b50f-b9064f55b990.png)
   ![image](https://user-images.githubusercontent.com/49760167/173160221-cb098522-f13b-4665-abd2-f41ee1f475fb.png)
   ![image](https://user-images.githubusercontent.com/49760167/173160246-a585097d-9c3f-4f7c-938d-06f95f69f107.png)
   
   - How to get typedefs
        + Let’s suppose that you want to get a const pointer field of an allocator.
        + Access the const_pointer field of the type that you’ve got at step 2. 
        + Because it’s static, you can call it without making an instance of class std::allocator_traits:  
     `
     std::allocator_traits
        <your_allocator_type<your_data_type>>::const_pointer
      `  
     
   *Hint: you can use typedefs in order to make code clearer:*  
`
typedef std::allocator_traits
    <your_allocator_type<your_data_type>> alloc_traits 
   `
   
   - How to call methods 
        + Create an instance of allocator that will be used for calling an allocate method.
        + Wrap your allocator type with std::allocator_traits:  `std::allocator_traits<your_allocator_type<your_data_type>>`
        + Access the allocate method on the type that you’ve got at step 2. Because it’s static, you can call it without making an instance of class std::allocator_traits:  `std::allocator_traits<your_allocator_type<your_data_type>>::allocate(…)`  
        + For allocate method, you should provide an instance of an allocator first, and then, provide arguments for allocate method of allocator itself:  
`std::allocator_traits<your_allocator_type<your_data_type>>::allocate(alloc, n)`

### Custom allocators: motivation, example:
   - What’s wrong with malloc/free and operators new/delete?  
        • General purpose  
        • Slow  
        • Fragmentation  
   - Whats the benefits of using custom allocators?  
        • Low number of mallocs  
        • Data structures  
        • Constraints  
   - Example:
   ```c++
   template <typename T>
    struct my_allocator {
        typedef T value_type;

        T* allocate (const size_t n) const {
            std::cout << "allocate called, n = " << n << ", sizeof(T) = " << sizeof(T) << std::endl;
            return reinterpret_cast<T*>(new char[n * sizeof(T)]);
        }

        void deallocate (T* ptr, const size_t n) const {
            std::cout << "deallocate called, n = " << n << std::endl;
            delete[] reinterpret_cast<char*>(ptr);
        }
    };

    struct triplet {
        int a, b, c; /// 12B

        triplet (const int a, const int b, const int c): a(a), b(b), c(c) {
            std::cout <<
                "called the constructor at " << this << " with args: " <<
                a << ", " << b << ", " << c << std::endl;
        }

        ~triplet () {
            std::cout << "called the destructor of (" <<
                a << ", " << b << ", " << c << ") at " << this << std::endl;
        }
    };


    int main () {
        typedef std::allocator_traits<my_allocator<triplet>> alloc_traits;

        /// Creating an instance of the allocator:
        alloc_traits::allocator_type alloc; /// Type of this variable is `my_allocator<int>`

        /// Allocation:
        alloc_traits::size_type n = 5;
        alloc_traits::pointer chunk_of_data = alloc_traits::allocate(alloc, n); /// triplet*

        /// Construction:
        for (alloc_traits::size_type i = 0; i < n; i ++) {
            int a, b, c;
            /// Cin triplet
            std::cin >> a >> b >> c;

            /// Call constructor of the i-th triplet and provide
            alloc_traits::construct(alloc, chunk_of_data + i, a, b, c);
        }

        /// Destruction:
        for (alloc_traits::size_type i = 0; i < n; i ++)
            alloc_traits::destroy(alloc, chunk_of_data + i);

        /// Deallocation:
        alloc_traits::deallocate(alloc, chunk_of_data, n);
    }
   ```

### Comparison of different common custom allocators
![image](https://user-images.githubusercontent.com/49760167/173161193-d357168a-bfbd-48da-a56c-658878a0b78b.png)

***Linear Allocator***
```c++
template <typename T>
class linear_allocator {
public:
    typedef T value_type;

    explicit linear_allocator (const size_t buffer_size = k_buffer_size):
        _buffer_size(buffer_size),
        _buffer(reinterpret_cast<T*>(new (std::nothrow) char[sizeof(T) * k_buffer_size])),
        _allocations_count(0)
    {}

    ~linear_allocator () { delete[] reinterpret_cast<char*>(_buffer); };

    T* allocate (const size_t n) {
        std::cout << "Allocating memory for storing n = " << n << " objects" << std::endl;

        /// We dont have enough space for allocating n objects:
        if (_allocations_count + n > _buffer_size)
            throw std::bad_alloc(); /// No space left, so we need to throw an exception.

        const size_t current_allocations_count = _allocations_count;
        _allocations_count += n;
        return _buffer + current_allocations_count;
    }

    void deallocate (T*, const size_t n) const noexcept {
        std::cout << "Deallocating memory with n = " << n << " objects" << std::endl;
    }

    size_t max_size () const noexcept { return _buffer_size; }

private:
    const static size_t k_buffer_size = 1024;

    size_t _buffer_size;
    T* _buffer;
    size_t _allocations_count;
};

struct logger {
    explicit logger (const size_t id): _id(id) { std::cout << "Constructed at " << this << std::endl; }
    ~logger () { std::cout << "Destructed at " << this << std::endl; }
    void print (const std::string &str) const { std::cout << _id << ": " << str << std::endl; }

private:
    size_t _id;
};

int main () {
    typedef std::allocator_traits<linear_allocator<logger>> alloc_traits;

    alloc_traits::allocator_type alloc;

    std::cout << "Max size supported by an allocator: " << alloc_traits::max_size(alloc) << std::endl;

    alloc_traits::size_type n = 1025;

    alloc_traits::pointer chunk = alloc_traits::allocate(alloc, n);

    for (size_t i = 0; i < n; i ++)
        alloc_traits::construct(alloc, chunk + i, i + 1);

    chunk[0].print("hello");
    chunk[1].print("bye");

    for (size_t i = 0; i < n; i ++)
        alloc_traits::destroy(alloc, chunk + i);

    alloc_traits::deallocate(alloc, chunk, n);
}
```

