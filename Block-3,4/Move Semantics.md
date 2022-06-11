# Move semantics:

### Rvalues and lvalues in C++07 (recap), troubles with them (examples):
  - **Definition: lvalue** (locator value) is an object that occupies an identifiable location in memory (for example, every named object)
  - **Definition: rvalue** is defined by exception, saying that any expression is either an lvalue or an rvalue
  - Thus, the definition of an lvalue implies that an rvalue is an expression that does not represent an object that occupies an identifiable memory location

### Temporary objects:
  - **Definition:** temporary object is an object without name
  - **How to create:** just call the constructor without naming the resulting object.
  - **Property:** temp object is always an rvalue
  - **Examples** 
      ```c++
      std::vector<int> a = std::vector<int>(1000);
      some_function(3, 4.0, std::vector<int>(10), std::string(“hello”))
      some_class function_get_temp () { return some_class(); 
      ```

### General idea of the new value mechanism in C++11: solving troubles of C++07 :  
![image](https://user-images.githubusercontent.com/49760167/173162124-670ae285-ec65-485b-9e37-82e95bb452bc.png)
![image](https://user-images.githubusercontent.com/49760167/173162143-e167c416-f1de-4e37-a757-19dabb478549.png)
![image](https://user-images.githubusercontent.com/49760167/173162169-780dc398-9f12-428d-b56a-a45f42114fef.png)
![image](https://user-images.githubusercontent.com/49760167/173162743-a4263bba-dd9d-4de4-b5a9-764b3744592d.png)
![image](https://user-images.githubusercontent.com/49760167/173162770-4b44fda8-4e8e-4186-8e8b-25c42a045a0f.png)

  - **GENERAL IDEA :**
    * **Problem :**  It is not possible to create optimal assignment and construction algorithms for class objects that will work optimally with temporary objects.  
    * **Idea of solution:** We can introduce some new kind of a reference into the language that can be bound specifically to temporary objects. Since temporary objects are rvalues, we will call such references rvalue references.
    * **How it should work:** : An rvalue reference will indicate that the object bound to it should be treated as temporary. Since the original object is not to be used anywhere else, we can leave it in an invalid state. Thus, the rvalue reference allows us to steal content from the source object

### Rvalue references
![image](https://user-images.githubusercontent.com/49760167/173162533-7c17014f-3c23-4297-921a-5d60c2bf5a37.png)

### `std::move`, invalidation of the initilial objects after move
![image](https://user-images.githubusercontent.com/49760167/173162802-c596f48d-9129-443d-a48a-06871503cbfe.png)
  - **Invalidation**
  std::move(…) creates rvalue reference to the initial object. Rvalue reference allows to steal the contents of the initial object, so, when passed to constructor or operator=, the insides of the object will be taken and it’ll be invalidated
  ```c++
  template <typename T>
  void swap (T& x, T& y) {
    T temp = std::move(x);
    x = std::move(y);
    y = std::move(temp);
  }
  ```
  - All operations were performed by stealing the contents of objects. 
  - This is optimal, because instead of byte-wise copying, we can simply move all the content at once to another object
### Move constructor, its signature and implementation
![image](https://user-images.githubusercontent.com/49760167/173163073-6cf7c500-bbbe-40d3-aa53-834e11fd68df.png)
  - **Signature**:
    ```c++
    struct cl {
      cl (cl&& other) noexcept { … }
    }
    ```
    + It receives an rvalue reference (a reference to a temp object).
    + It’s highly recommended to mark the move constructor as noexcept and never throw exceptions from it.
 
 - Comparison with Copy Constructor : 
    ```c++
    struct cl {
      cl (const cl& other) noexcept { … }
    }
    ```
    + Copy constructor receives a const lvaluereference.
    + lvalue-reference is denoted by one ampersand. 
    + Copy constructor can be non-noexcept and can throw exceptions
 
 - **Implementation**:
    ```c++
    struct cl {
      cl (cl&& other) noexcept { … }
    }
    ```
    + Move constructor should steal the contents via the provided rvalue.
    + We don’t care about the other object, so we can invalidate it in order to optimally move the data from it to the object that we want to construct
    
### Move assignment operator, its signature and implementation
![image](https://user-images.githubusercontent.com/49760167/173163323-209fa632-39c4-418f-823c-6bba7d5e2859.png)
- **Signature**:
    ```c++
    struct cl {
      cl&  operator=(cl&& other) noexcept { … }
    }
    ```
    + It receives an rvalue reference (a reference to a temp object).
    + It returns a reference to the current object (lvalue reference, not rvalue reference!).
    + It’s highly recommended to mark the move constructor as noexcept and never throw exceptions from it.
 
 - Comparison with Copy Constructor : 
    ```c++
    struct cl {
      cl& operator=(const cl& other) noexcept { … }
    }
    ```
    + Copy assignment operator receives a const lvaluereference.
    + lvalue-reference is denoted by one ampersand. 
    + Copy assignment can be non-noexcept and can throw exceptions
    
  - **Implementation**:
    ```c++
    struct cl {
      cl (cl&& other) noexcept { … }
    }
    ```
    + Move constructor should steal the contents via the provided rvalue.
    + We don’t care about the other object, so we can invalidate it in order to optimally move the data from it to the object that we want to construct 

### Default move constructor and move assignment operator
![image](https://user-images.githubusercontent.com/49760167/173163738-aef48225-6145-4fc2-a70c-a106708efc08.png)
![image](https://user-images.githubusercontent.com/49760167/173163768-744f82f5-f003-48b9-b431-2cf883679a2f.png)

### The rule of **three/five/zero**
  - **Rule of 3 : **   
      If a class requires a user-defined destructor, a user-defined copy constructor, or a user defined copy assignment operator, it almost certainly requires all three
  
  - **Rule of 5:** Because the presence of a user-defined destructor, copy-constructor, or copy-assignment operator prevents implicit definition of the move constructor and the move assignment operator, any class for which move semantics are desirable, has to declare all five special member functions.

  - **Rule of 0:** Classes that have custom destructors, copy/move constructors or copy/move assignment operators should deal exclusively with ownership. Other classes should not have custom destructors, copy/move constructors or copy/move assignment operators
  - Example [here](https://github.com/Costello1329/cpp-mipt-2021/blob/master/lectures/lecture-21/examples/example-1.cpp):
### Copy elision, RVO, NRVO:
  - **Copy Elision:**
    ![image](https://user-images.githubusercontent.com/49760167/173163907-ca3942d9-7f0c-4a65-bb80-8153b5237e4f.png)
    
  - **RVO (Return Value Optimization):**
    * Omits calling the copy constructor when an object is getting assigned to a temporary return value of a function.
    ```c++
    std::vector<int> get_big_vec () { return std::vector<int>(1000); }
    int main () {
    std::vector<int> vec = get_big_vec();
    }
    ```
    * C++07: Temp object will be constructed, then the returned and used as an lvalue for copy constructor.
    * C++11: No copy or move constructor calls
  
  - **NRVO (Named Return Value Optimization)**
    * Same as an RVO, but works for named (non-temp) objects.
    ```c++
    void get_big_vec () {
    std::vector<int> vec(1000);
    return vec;
    }
    int main () {
    std::vector<int> vec = get_big_vec();
    }
    ```
    * C++07: Object will be constructed, then the returned and used as an lvalue for copy constructor
    * C++11: No copy or move constructor calls


### Complete and incomplete tyeps

### Universal references

### `std::remove_reference`

### `std::move` implementation

### `std::forward`, its implementation

### Value categories in C++11: `glvalue`, `rvalue`, `lvalue`, `prvalue`, `xvalue`

### Reference qualifiers

### Noexcept specifiers in C++17, conditional noexcept specifiers in C++17, potentially throwing functions in C++17, noexcept operator in C++17
