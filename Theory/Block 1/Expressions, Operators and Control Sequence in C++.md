## Expressions:
### Operators:

![Operators](https://github.com/Ozzey/MIPT_CPP2021/blob/main/resources/operators.jpg)

   - Assignment operator, concept of lvalue and rvalue in C ++ 07:
      * If a value can be used a s a left operand of the assignment operator, it is called an `lvalue`
      * Otherwise , it is called an `rvalue` 
      * This mechanism is changed drmamtically in C++11.

 
   - Arythmetical operators:
    ![Operators](https://raw.githubusercontent.com/Ozzey/MIPT_CPP2021/Ozzey-patch-2/resources/ar%20operator.bmp)
    
   - Сompound assignment operators
      ```
      x+=3; 
      x-=3;
      x*=3;
      x/=3;
      x%=3;
      ```
   - Increment and decrement operators:
      ```
      x++ ; //postfix : will print original value of x
      x-- ; // postfix : will print original value of x
      --x ; // prefix : will print new value of x
      ++x ; // prefix : will print new value of x
      ``` 
      
   - Comparison operators:
      * Equality operators : 
        ```
        x == y ; 
        x != y ;
        ```
      * Relational Operators: 
        ```
        x < y ; 
        x > y ; 
        x <= y ; 
        x >= y ;
        ```

   - Logical operators 
      Only used for boolean values:
      ```
      !a ;  // not a
      a && b ; // a and b 
      a || b ; // a or b
      ```
      
   - Operator sizeof() :
      It recieves the tyoe, literal or identifier and returns an amount of bytes, needed for provided value to be stored in memory.
      ```
      sizeof(int) ; \\ return 4
      sizeof(10)  ;  \\ returns 4 because 10 is int and requires 4 bytes of memory.
      ```
      *NOTE : sizeof(char) =< sizeof(int) =< sizeof(long) =< sizeof(long long)*
      
   - [Bitwise operators, storing integer types in memory](https://bit.ly/3oQ8U5u) :
      * Unary :  
        ``` ~a ```
      * Binary :
        ```
        a & b ; // bitwise and
        a ^ b ; // bitwise xor
        a | b ; //bitwise or
        a << b ; //bitwise left shift (formula : a<<b = a*2^b , given that result is less than equals to 2^32-1 -> max possible value for unsigned)
        a >> b ; //bitwise right shift (formula : a>>b = a*2^b mod 2^32)
        ```
        *Note : There is compound assignment version of each binary bitwise operator: `` &= , ^= , |= , <<= , >>= `` *
        
   - Ternary operator : /n 
      * `` a ? b : c `` &rarr; returns b if a is true else returns c.
   
   - C-style case : 
      * `` unsugned short a = (unsigned short)5 + (unsigned short) true `` &rarr; converts values into different types.
      *Note In CPP , more advanced Cast operators are available so dont use C style casts*
      
   - Scope resolution operator : 
      * std::cout<<...<<std::endl;
      * Has the lowest possible precedence (1) so it is calculated first.
      
   - Function call operator 
      * `` func_name(arg1 , arg2....,argn) ``
      * In order to call our function we use function call operator.
      
   - Comma operator:
      * Takes multiple arguments and discards all except the last one.
      * ![input](https://github.com/Ozzey/MIPT_CPP2021/blob/Ozzey-patch-2/resources/comma%20input.jpg)
      * ![output](https://github.com/Ozzey/MIPT_CPP2021/blob/Ozzey-patch-2/resources/comma%20output.jpg)
        
      
   - Operator precedence and associativity

   - Cast operators: `static_cast`, `reinterpret_cast`, `const_cast`, `dynamic_cast`

   -*Note: Logical operators are applicable in case of bool also*
    
![Operators](https://github.com/Ozzey/MIPT_CPP2021/blob/Ozzey-patch-2/resources/operators2.jpg)

______________________________________________________________________________________________________________________________________________

## Control Sequences

### If - Else if - Else:

    if (statement 1){
          do something ; 
      }

    else if (statement 2){
          do something ;
       }

    else{
          do something ; 
        }
      

   
### Loops:

#### While loop

    while (statement is true){
           something keeps happening until something is false ; 
         }


#### Do While Loop

     do 
        something is happening unconditionally ;
     while(some condition is checked);
     
#### For loop :

    for(delcaration || expression *int i=0* ; bool expression *i<10* ; iterative statement || composite statement *i++*){
            something happens ; 
            iteration-expression ;
        }


### [Switch/Case](https://www.tutorialspoint.com/cplusplus/cpp_switch_statement.htm): 

``` 
switch (expression){
    case boolean expression:
          statements
          [break ; ] //optionally we can put break
    ...
    default:
          statements
          [break ; ] //optionally we can put break
    }
```

- *Continue : Unconditionally proceeds to the next iteration of the current loops*
- *Break : Stops the loop without returning anything (if there is no return statement before it)*
