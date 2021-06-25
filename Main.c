#include <stdio.h>
#include <Windows.h>



/*****************Data Type*******************

This is the enum of data type , we can add anything we want here , it will be used in the stack initilization later
*************************************/
typedef enum {
	m_CHAR,
	m_INT,
	m_UINT64,

}DataType;



/*****************STACK Definition*******************

Here is the core of the stack which will contains a very important members :_

Data :- its the data/elements that will be added/removed (push/pop) in the stack
top :- it represent ESP which will point to the top of the stack.
base :- its represents EBP which will point to the base of the stack.

type:- its the datatype that will be used to be allocated in the heap.

size :- its a custom size that the user will add to be allocated in memory and it will multiplied with the data type size.

*************************************/
typedef struct STACK {

	void* data;
	void* top; // top of the stack -> ESP
	void* base; // Base of the stack -> EBP
	DataType type;
	size_t size; //unsigned int 
	
}STACK;

size_t SizeOfTheStack;
/*********************Stack Initialization*****************************

Here is the stack initialization , which will take 2 arguments, the data type and size 
It will just prepare the required data and the size of the stack
/***************************************************/


STACK Stack_Init(DataType type, size_t size) {

	size_t dynamicSize = 0;
	if (type == m_CHAR) {
		dynamicSize = sizeof(char) * size;
	}
	else if (type == m_INT) {
		dynamicSize = sizeof(int) * size;

	}
	else if (type == m_UINT64) {
		dynamicSize = sizeof(UINT64) * size;

	}
	STACK st1 =
	{
		.type = type,
		.size = size,
		.data = malloc(dynamicSize),
		
		
	};
	

	return st1;
}
int i = 0;


/************************* STACK PUSH **********************************

1-)The user is insert the stack pointer, the element that will be pushed/added to the stack , and the size (index of that element).

2-) First it will do a loop to insrt that element in the stack with a notice that element will be added based into its index (size) and it should be auto-increment like the example in the main function (First element should have '1' indext , second element' 2' ...etc)

3- ) Each Last element is added on the stack will  point to the top of the stack based in LIFO ordering , and this is how ESP always point to.

4-) Always the base of the stack (EBP) will point to the first element which is index is 0



***********************************************************/
void STACK_PUSH(STACK* stack ,int element, size_t size) {


	
	for ( i; i < size; i++) {
		((int*)stack->data)[i] = element;
		stack->top = ((int*)stack->data)[i] + 0;
		printf("The Element %d has been added to the stack at index: %d \n", stack->top , i);

	}

	stack->base = ((int*)stack->data)[0];
	printf("The Top of the stack is : %d\n", stack->top);

	printf("The base of the stack is : %d\n", stack->base);
	

}
/******************STACK POP UP****************************

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


**********************************************/
void STACK_POP(STACK* stack,  int element) {

	int i = 0;
	for (i; i < SizeOfTheStack; i++) {
		
		if (((int*)stack->data)[i] == element && ((int*)stack->data)[i] != stack->base) {
			printf("We found the element at index %d ,Now we are removing it\n", i);
			((int*)stack->data)[i] = 0;
			if (((int*)stack->data)[i + 1] == NULL) { // Dirty check if the next pointer is valid or not, if its not valid thats means we have reached the end of stack (not always true xD) , so the top of the stack should point to the previous element
				stack->top = ((int*)stack->data)[i - 1] + 0;
				stack->base = ((int*)stack->data)[0];
			}
			else { // If the next pointer is valid , thats mean we have more entries in the stack , so the next element will be point to the top of the stack.

				stack->top = ((int*)stack->data)[i + 1] + 0;
				stack->base = ((int*)stack->data)[0];
				printf("The Top of the stack is : %d\n", stack->top);

			}
			break;
		}
		else if (((int*)stack->data)[i] == element && ((int*)stack->data)[i] == stack->base) 
		{
			printf("We found the element at index %d ,Which is the Base element, Removing it now and set to Zero\n", i);

			((int*)stack->data)[i] = 0; // Setting the element by zero 

			if (((int*)stack->data)[i + 1] == NULL) { // Checking if the next pointer is valid or not, if its not valid thats means we have reached the end of stack (not always true xD) , so the top of the stack should point to the previous element
				stack->top = ((int*)stack->data)[i - 1] + 0;

				stack ->base = stack->top;
				printf("The Top of the stack is : %d\n", stack->top);

			}
			else { // If the next pointer is valid , thats mean we have more entries in the stack , so the next element will be point to the top of the stack.

				stack->top = ((int*)stack->data)[i + 1] + 0;
				stack->base = ((int*)stack->data)[0] + 0;
				printf("The Top of the stack is : %d\n", stack->top);

			}
			break;
		}
		else {
			printf("We didnt found the required element !\n");
			//break;
		}

	}

	
	printf("The Top of the stack is : %d\n", stack->top);

	printf("The Base of the stack is : %d\n", stack->base);



}

void STACK_Clean(STACK* stack) {

	
	stack->data = NULL; // Setting All Data to NULL as its like a simulation for deallocation

	printf("The stack has been Cleaned !\n");

}
int main() {

	SizeOfTheStack = 10;
	STACK st1 = Stack_Init(m_CHAR, SizeOfTheStack); //Passing the datatype and the size of the stack
	
	STACK_PUSH(&st1, 10, 1); // Passing the pointer of st1,the element that will be added , the index
	STACK_PUSH(&st1, 20, 2);
	STACK_PUSH(&st1, 30, 3);

	
	STACK_Clean(&st1);
	

	getchar();
}
