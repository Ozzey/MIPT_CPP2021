# Exceptions:
## General idea:
 - **Motivation for using exceptions.:** 
     To tell user if something can be used as input etc
     
 - The `throw` statement and the `try/catch` block.  
   ```c++
     void divide(const int input){
      if(input != 0)
          std::cout<<"dividing"<<std::endl;

      else
          throw std::string ("Cant divide by zero");
    }

    int main(){
        int input;
        std::cin>> input;

        try{
            divide(input);
        }catch(std::string error){
            std::cout<<"Error : "<<error<<std::endl;
        }
    }
   ```
   + Exceptions interrupts all the functions until it is caught  
      ![image](https://user-images.githubusercontent.com/49760167/173134740-66f09a7b-b33c-4a3c-982a-0466ab589fe5.png)  
      It can be used to reverse the code execution. Error wont be discarded even in this case.

 - Examples of standard operators that throw exceptions (Universal Catch Block).
    + Normal exception
      ```c++
        int main(){
          try{
              throw float();
          }catch(double x){
              std::cout<<"Error double "<<std::endl;
          }catch(int x){
              std::cout<<"Error int "<<std::endl;
          }
          catch(...){
              std::cout<<"Arbitrary error "<<std::endl;
          }
      }
      ```
     + Examples [here](https://pastebin.com/m0DP7iGk)
     
 
## Difference between exceptions and runtime errors. Errors that are not exceptions and exceptions that are not errors.

## Rules for catching and re-throwing exceptions, casting types when catching exceptions.  
  Catching all exceptions. The rules for choosing a catch block by the compiler in the case when different blocks are suitable.  
  Type conversion : Only child to parent
   ```c++
        struct a{};
        struct b : a{};

        int main(){
            try{
                throw b();
            }catch(a a_instance){
                std::cout<<"Error b instance captured "<<std::endl;
            }catch(int x){
                std::cout<<"Error b instance NOT captured "<<std::endl;
            }
            catch(...){
               std::cout<<"b instance captured in UNIVERSAL Capture "<<std::endl;
            }
        }
   ```  
   So, here signature doesnt matter, order matters.
  
 
   
## Copying when throwing and catching exceptions. Features of catching exceptions by value and by reference.
   ```c++
     struct a{
      a() = default;

      a(const a& other){
          std::cout<<"Copy constructor executed"<<std::endl;
      }
      };

      int main(){
          try{
              throw a();
          }catch(a a_instance){  ///here change a by a&

          }
      }
  ```  
   + Same as using function argument : ```void f(a bi_value){}```  
   + So copy will be created, so instead, use refrence to avoid unnecessary copy.
   + In case of non const refrence we can't modify the initial refrence, 
    so a copy is created since the since the scope of original instance is finished. 
    This is somewhat of an optimisation technique.

## Old-style exception specifications and their problems  
  - Unexpected exceptions. 
  - C++ 11 style exception specifications 
    ```c++
      // BEFORE C++11 (deprecated in C++17)
    void f () throw(double, std::string) {
        throw 1.;
        throw std::string("asd");
    }
    ```
    Problem is that we had to specify all types which would throw error.
    
 - `noexcept` operator and specifier  
    + It is modern way of telling to compiler that this functioon wont throw exception.
    ```c++
      void f () noexcept {}
      void g () {}
      
      int main(){
        std::cout << noexcept(f()) << std::endl; ///true
        std::cout << noexcept(g()) << std::endl; ///false
        }
    ```
      + Conditional noexcept.  
        * Normal noexcept  
        ```c++
          template <size_t n>
          void h () noexcept(n % 2) {}
          
          int main(){
             std::cout << noexcept(h<4>()) << std::endl; ///false
             std::cout << noexcept(g<5>()) << std::endl; ///true
            }
        ``` 
        * Noexcept with constructor  
        ```c++   
        template <class vt>
        void f1 () noexcept(noexcept(vt())) {
            std::cout << "Functor call wrapper" << std::endl;
            vt();
        }

        struct a {
            a () { throw "Hi"; }
        };

        struct b {
            b () noexcept = default;
        };

        int main () {
            std::cout << noexcept(f1<a>()) << std::endl; /// false
            std::cout << noexcept(f1<b>()) << std::endl; /// true
        }
        ```
        * Allows us to create a condition when function can throw an exception
        * Only statementes executed at compile time are allowed

##  DO NOT THROW MAJOR EXCEPTION IN CONSTRUCTOR, DESTRUCTOR AND VIRTUAL FUNCTIONS
  - Exceptions in constructors and the problem of memory leaks on exceptions.
  - Exceptions in destructors.
  - Security guarantees for exceptions: basic and strict.  
 ***Can cause vulnerability issues***
 
 
 ## Your own exception class
   ```c++
   struct my_own_exception : std::exception {
        explicit my_own_exception (const std::string cause): _cause(cause) {}
        const char* what () const noexcept override { return _cause.data(); }

    private:
        std::string _cause;
    };

    int main () {
        try {
            throw my_own_exception("Some description");
        } catch (const my_own_exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
   ```
   
 ## Built-in exception type
 ```c++
   int main () {
      std::vector<int> vec({ 1, 2, 3 });
      vec.at(0); /// OK, element with index 0 is present
      try {
          vec.at(3); ///Exception,no element with the index 3 in the vec object
      } catch (const std::out_of_range& out_of_range) {
         std::cout << "Out of range exception: " 
                   << out_of_range.what() 
                    << std::endl;
      }
  }
 ```
  - Thrown when trying to access element that doesnt exist in the vector
 
