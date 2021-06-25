# CPU Stack Emulation
Emulation for CPU Stack and simplifying its process . Simplifying  x86 Assembly to C language

  This project is to simplify how the stack works and the process of PUSH/POP  
  ![The stack](  https://miro.medium.com/max/473/1*r4Bfo3rrFprzFM2zbgzZXA.jpeg)

  
  ## Here is a descriptions for some functions in the project :-  
# Data Type

This is the enum of data type , we can add anything we want here , it will be used in the stack initilization later  

# STACK Definition

Here is the core of the stack which will contains a very important members :_

Data :- its the data/elements that will be added/removed (push/pop) in the stack  
top :- it represent ESP which will point to the top of the stack.  
base :- its represents EBP which will point to the base of the stack.  

type:- its the datatype that will be used to be allocated in the heap.  

size :- its a custom size that the user will add to be allocated in memory and it will multiplied with the data type size.  


# Stack Initialization

Here is the stack initialization , which will take 2 arguments, the data type and size   
It will just prepare the required data and the size of the stack   

# STACK PUSH

1-)The user is insert the stack pointer, the element that will be pushed/added to the stack , and the size (index of that element).  

2-) First it will do a loop to insrt that element in the stack with a notice that element will be added based into its index (size) and it should be auto-increment like the example in the main function (First element should have '1' indext , second element' 2' ...etc)  

3- ) Each Last element is added on the stack will  point to the top of the stack based in LIFO ordering , and this is how ESP always point to.  

4-) Always the base of the stack (EBP) will point to the first element which is index is 0  

# STACK POP UP

1-First we are assuming that the stack hold 10 elements  
2-We are doing a search for the element And we are doint 3 checks :-  

A-) Check if We have found the element  and its not the base element (First one)  
B-) Check if we have found the element and its the base element .  
C-) We didnt found the element  

A-) If we have found the element and its not the base element :-  

1-) Set the found element to 0  
2-) Do a check for the next element (Checking the validation of the Pointer) if its exist or not , if its exist then set it as the Top element (ESP), if its not exist , then set the previous element as the top element.  
////////////////////////

B-)  if we have found the element and its the base element  :-  

1-) Set the found element to 0  

2-) Do a check for the next element (Checking the validation of the Pointer) if its exist or not , if its exist then set it as the Top element (ESP) and set the Base element as the first element in the stack, if its not exist , then we are at the first element and its the only element in the stack so set that element as the top element and the base element.  
  
** Pros :-  
1- ) Its almost like the stack cleaning in CPU  
2- ) Simple and help anyone to understand how the pop up operation works  

** Cons :-  
  
1-) The stack space is pre-defined (SizeOfTheStack) in the main function, we may need to make it dynmaic.  

2-) Using the validation of the next pointer is not a good technique because it will discard all elements after the element we are checking.  

