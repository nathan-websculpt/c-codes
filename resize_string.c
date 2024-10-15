#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// Pointer variable (memory address of dynamically allocated block)
	char *string;

	// string is: memory address for this block of memory
	string = malloc(5);

	// Copy the string "abcd" into the block of memory
	strcpy(string, "abcd");

	// Output the string  
	printf("%s\n", string);

	// re-allocate a larger block of memory.
	string = realloc(string, 6);

	// We could then write additional string characters to the block of memory
	// (which we can access using array notation).
	string[4] = 'e';
	string[5] = '\0';

	//  string:  a  b  c  d  e  \0
	//   index:  0  1  2  3  4  5

	// Output the string after making it larger
	printf("%s\n", string);

	// We could also make the block of memory smaller
	string = realloc(string, 4);

	// We'll now have the string "abc"
	string[3] = '\0';

	printf("%s\n", string);

	free(string);

	return 0;
}