
# Templates:

## Functions specialization:  
   ![image](https://user-images.githubusercontent.com/49760167/173131458-578ee919-08f8-4a3b-a784-e9e513ef560e.png)


## What are templates (motivation):
   We want to write universal code for different data-types.
   Template classes and functions, examples
    
  - For functions:  
    ```c++
    template <typename type>
    void swap(type& first, type& second){
        type temp = first ;
        first = second;
        second = temp;
     }
    ```
  - For class:  
    ```c++
     template<typename type>
     class A(){
        // do something
     }
    ```
    + Created in compile time
 

    
## Template specializations:
Used to create a particular case of type, so we dont need to specify type on function call.  
```c++
   template <template type>
    void f(type x){
        ///....
    }

    template<>
    void f(int x){
        ///
    }

    int main(){
        f(1.); /// [type = double]
        f(1); /// [type = int]
    }
```
    
 - The principle: `particular is preferable to general`
    - The principle is `the exact match is better`
    - Partial and full specializations  
   
    ```c++
    template <template first, template second>
    void f(first x,second y){
        ///....
    }

    template <template second>
    void f(int x,second y){
        ///....
    }

    template<>
    void f(int x, int y){
        ///...
    }

    int main(){
        f(1.,1.); //first called
        f(1,1.); // second called
        f(1,1); // third called
    }
    ```
 - Function specialization vs template function specialization
 - Compiler selection rules for specialization and overloading candidates 
                Can cause error since all types are preferable
    ![image](https://user-images.githubusercontent.com/49760167/173125491-b4fdd3e7-a253-436e-a718-40a03ffca654.png)
     to fix, create a new specialization
     ```c++
        template<>
        void f(int x, int y){
            ///...
        }
     ```

- ***Template parameters that are not types (example: `std::array`).*** 
    A non-type template argument provided within a template argument list is an expression whose value can be determined at compile time. Such arguments must be constant expressions, addresses of functions or objects with external linkage, or addresses of static class members. Non-type template arguments are normally used to initialize a class or to specify the sizes of class members.
    ```c++
    template<typename type, size_t size>
    class array{
        //...
     }
    ```
    
    
- ***Template template parameters***:  
    A template argument for a template template parameter is the name of a class template.
When the compiler tries to find a template to match the template template argument, it only considers primary class templates. (A primary template is the template that is being specialized.) The compiler will not consider any partial specialization even if their parameter lists match that of the template template parameter. For example, the compiler will not allow the following code:
    ```c++
    template<class T, int i> class A {
           int x;
        };

        template<class T> class A<T, 5> {
           short x;
        };

        template<template<class T> class U> class B1 { };

        B1<A> c;
    ```
    
- `typedef` keyword
    ```c++
    typedef a_class<int, std::vector<int>> shortname;
    ```
- `using` keyword: template and non-template `using` versions  
    Used to create alias
   ```c++
    template <class type>
    using short_name_template = a_class<int, std::vector<type>>;
   ```

-  ***Variadic Template*** ,template recursion: ideas and usage (example: function `print_all`):  
    Variadic arguments are very similar to arrays in C++. We can easily iterate through the arguments, find the size(length) of the template, can access the values by an index, and can slice the templates too. 

So basically, Variadic function templates are functions that can take multiple numbers of arguments.
  ```c++
    #include <iostream>
    using namespace std;

    // To handle base case of below recursive
    // Variadic function Template
    void print()
    {
        cout << "I am empty function and "
                "I am called at last.\n";
    }

    // Variadic function Template that takes
    // variable number of arguments and prints
    // all of them.
    template <typename T, typename... Types>
    void print(T var1, Types... var2)
    {
        cout << var1 << endl;

        print(var2...);
    }

    // Driver code
    int main()
    {
        print(1, 2, 3.14,
              "Pass me any "
              "number of arguments",
              "I will print\n");

        return 0;
    }
  ```
 - ***Functors***  
   A Functor is a object which acts like a function. Basically, a class which defines operator().
   ```c++
   class MyFunctor
    {
       public:
         int operator()(int x) { return x * 2;}
    }

    MyFunctor doubler;
    int x = doubler(5);
   ```
