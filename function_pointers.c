#include <stdio.h>

// Function pointers store the memory address of a function 

void function(int x)
{
	printf("x: %d\n", x);
}

int main()
{
	// Make a variable that will be a pointer to a function 
	// Pointer to a function that has a void return value and accepts one integer 
	void(*function_pointer)(int);

	// set it to point to function above
	function_pointer = &function; //memory address of the function

	// now use the function pointer to call the function
	(*function_pointer)(4);

	return 0;
}