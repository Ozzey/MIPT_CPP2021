# Inheritance:

## Basic Principle of OOP
OOP has three principles, they are listed below. These principles are present not only in C++, but in any object-oriented language. Below I have given a list of these principles and the mechanisms by which they are implemented in C++.  
   - Encapsulation: private and public access modifiers  
   - Polymorphism:  C++ polymorphism means that a call to a member function will cause a different function to be executed depending on the type of object that invokes the function.
      + static polymorphysm (compile-time): templates (eg: function overloading or operator overloading.)
      + dynamic polymorphysm (runtime): virtual functions & inheritance (eg: Function Overriding)   
   - Inheritance: inheritance:      

## Inheritence definition: 
```c++
struct animal{
public:
    void eat(){
        std::cout<<"Eat"<<std::endl;
    }
};

struct dog : animal{
public:
    void bark(){
        std::cout<<"bark"<<std::endl;
    }
};
struct cat : animal{
public:
    void meow(){
        std::cout<<"meow"<<std::endl;
    }
};

int main(){
    dog a;
    a.eat();
    a.bark();
}
```

## Inheritance declaration:
   - Initialization using base class:
      ![image](https://user-images.githubusercontent.com/49760167/173176098-b942e539-8467-4a11-9e55-ecfc097af643.png)

   - `protected` access modifier.
      + Imagine the situation: we have a base class that has a private member that we want to use somewhere inside the heir. 
      + This is where the problem arises: private members and methods are not inherited under any circumstances. 
      + Thus, we can’t refer to it in the derived classes.
      + A simple solution would be to make the field public, but in this case the user could access this field from outside.
      + This is where the protected access modifier comes handy. 
      + The thing is that protected fields can be inherited, but are not available to the user
      ![image](https://user-images.githubusercontent.com/49760167/173176300-3bcebcb1-9192-4657-914f-15bde8a02c14.png)

   - Difference between `private`, `public` and `protected` inheritance.
      + Public : Normal inheritence of all public members and methods.
      + Private : Private inheritance allows you to hide all inherited fields and methods from the user
      + Protected : 
      
      *note : details about changes in different member classes shown below*
   
   - Difference between `class` inheritance and `struct`.
      ![image](https://user-images.githubusercontent.com/49760167/173176381-b95cc2b2-23a6-4708-bbfe-42cad16d2574.png)
   - Example
      ![image](https://user-images.githubusercontent.com/49760167/173176763-2e0df350-0e87-46c1-9455-df9005d7cd06.png)

   - Keyword `final`
      ```c++
      struct Base1 final { };

      struct Derived1 : Base1 { };
      ```
   
## Finding names when inheriting:
   - Hiding names of the base class methods : When we re-declare same function in base class  
      Hiding can take place when one function in base class has the same name as one function in derived class, such as:
   - Explicit call of the parent methods of the inheritor (Using `operator ::`).
      ```c++
      class base{
      public:
          void func(){
              std::cout<<"base"<<std::endl;
          }
      };

      class derived : public base{
      public:
          void func(){
              std::cout<<"derived"<<std::endl;
          }
      };

      int main(){
          derived d;
          d.func();
          d.base::func();
      }
      ```
      *Note : We cannot access private bases like that*
      ```c++
      struct first {
          int a;
      };

      struct second : private first{
          int b;
      };

      struct thrid : public second{
          int c;

          void f(){
              thrid t;
              second s;
              ::first f; //works because ::f is global
              // first g; -> wont work ,first is derived
          }
      };
      ```
 
## The order in which constructors and destructors are called in inheritance. The problem with the initialization of the parents when defining the constructor of the inheritor, again using the initializer lists to solve it.
 The default constructor of the derived class will be invoked but before that the default constructor of all of the base classes will be invoke, i.e the order of invocation is that the base class’s default constructor will be invoked first and then the derived class’s default constructor will be invoked.
 
 The data members and member functions of base class comes automatically in derived class based on the access specifier but the definition of these members exists in base class only. So when we create an object of derived class, all of the members of derived class must be initialized but the inherited members in derived class can only be initialized by the base class’s constructor as the definition of these members exists in base class only. This is why the constructor of base class is called first to initialize all the inherited members. 
 
 ```c++
      using namespace std;

      // base class
      class Parent
      {
          public:

          // base class constructor
          Parent()
          {
              cout << "Inside base class" << endl;
          }
      };

      // sub class
      class Child : public Parent
      {
          public:

          //sub class constructor
          Child()
          {
              cout << "Inside sub class" << endl;
          }
      };

      // main function
      int main() {
          Child obj;
      }

   ```
   - The problem with the initialization of the parents when defining the constructor of the inheritor.
      + Child class constructor must call its parent class constructor. 
      + We can use initializer list to call the constructor of parent class
      
## Multiple inheritance, ambiguity with it, diamond inheritance problem. Examples of disambiguation using type conversions and the `operator ::`.  
   ```c++
     struct parallelogram {
             int a;
         };
         struct rectangle: public parallelogram{
             int b;
         };
         struct rhombus : public parallelogram{
             int c;
         };
         struct square : public rectangle, public rhombus{
             int d;
         };

         int main(){
             square s;
             s.d;
             s.c;
             s.b;
             s.rectangle::a;
      }
  ```
   + We need to use scope operator because it is a case of diamond multiple inheritence.
   + Since both rectangle and rhombus inherit parallelogram, 2 instances of parallelogram are created.
      
## `virtual` functions, their general idea and difference from non-virtual ones:

   - Features of allocation of classes with `virtual` functions in memory
   - **`virtual` inheritance :** Sharing of parent class between derived childe classes
      + Only one parent class is created in the whole heirarchy.
      ```c++
      struct parallelogram {
          int a;
      };
      struct rectangle: virtual public parallelogram{
          int b;
      };
      struct rhombus : virtual public parallelogram{
          int c;
      };
      struct square : public rectangle, public rhombus{
          int d;
      };

      int main(){
          square s;
          s.d;
          s.c;
          s.b;
          s.a; //Now it works
      }
     ```
     
   - Concept of the `v-table`
      ![image](https://user-images.githubusercontent.com/49760167/173179196-11402e32-cdec-4e84-91a1-6b607b89b1a9.png)

   
   - `virtual` destructor and its purpose
 
 ## Typecasting between parent and child:
   Converting derived class into base (down-casting) or vice versa.
   - Trimming when copying : Only members no available in base is copied.
      ```c++ 
      struct base {
       int x;

       explicit base(const int x): x(x) {};
      };
      struct derived : public base{
          int y;

          derived(const int x,const int y): base(x), y(y) {};
      };

      int main(){
          derived d(2,3);
          base b = d;
          b.x;
          // b.y; -> wont work because of trimming
          static_cast<derived&>(b).y  //-> works but can cause undefined behaviour
      }
      ```
   - casting pointers, casting references.
      + We can use static cast for refrence as demonstrated above.
      + We can use `reinterpret_cast(type *>(&x)` for pointers or refrence without changing anything at memory level.
      
   - Operator `dynamic_cast`
      ```c++
      const auto &other = dynamic_cast<const circle &>(another);
      ```
      + Fully runtime based.
      + Casted at runtime.
      + Can only be used on polymorphic types.
      
      
## The concept of dynamic polymorphism, polymorphic classes
   Dynamic Polymorphism implies the runtime resolution of function call. It is implies via Overriding which in turn is followed by inheritance in c++.
   ![image](https://user-images.githubusercontent.com/49760167/173179052-723f1f1c-44f4-433d-8cd4-5b9ee1d51137.png)  
   
   - **Polymorphic class** A class that declares or inherits a virtual function is called a polymorphic class


## Abstract classes:
   - `pure virtual` functions, their features.
      ```c++
      virtual int function() = 0;
      ```
      + We cannot make an instance of abstract class
      + SO we use pointers and arrow operators.
      
   - `pure virtual` destructor (and why it causes the linker error).
      + In case of non virtual destructor, wrong destructor is called.
      + In virtual destructor, first derived and then base destructor is called
      + But it cannot be pure since it can cause linker error.
      
   
   - Keyword `override` 
      It makes sure that the function is overriding some virtual function;
      ```c++
      struct base{
           virtual void f(){}
      }
      struct derived{
           void f() override {}
      }
      ```
   
   - keyword `final` (for methods)
      Makes sure the inherited class can't override the virtual function any furthur
      ```c++
      struct base{
           virtual void f(){}
      }
      struct derived{
           void f() final {}
      }
      ```


## Placement in memory of classes


## Curiously recurring template pattern 
