#include <stdio.h>

// Pointers are variables that store a memory address (of another variable)
// of the type that the pointer is pointing to
// 
// int *a;
// Declares a pointer variable that points to an int variable
// So a will store a memory address, and we expect it to
// store the memory address of an int variable
//
//
// &variable
// The & operator returns the memory address of a variable

int main(void)
{
	int b = 42;

	int *a = &b; // at this point: a is pointing to b - a stores memory address of b
	// & operator is getting the memory address of &some_variable

	printf("b: %d\n", b);    // value of b
	printf("&b: %p\n", &b);  // memory address of b
	printf("a: %p\n", a);    // value of a (will be the memory address of b)

	// So we have this situation where a is storing the memory address of b
	// This means we can use a to modify the value of b (use the pointer to access value contained IN b)
	// the * operator Allows us to "dereference a pointer" (accessing the value in the variable at the memory address stored in the pointer)
	// ... accessing the data that is being pointed to

	*a = 50; //*a is saying: go get what a is pointing to and use THAT

	printf("b: %d\n", b);
	printf("&b: %p\n", &b);
	printf("a: %p\n", a);

	return 0;
}