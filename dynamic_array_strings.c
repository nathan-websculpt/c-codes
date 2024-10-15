#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main()
{
	// pointer-to ... a pointer-to ... a character
	// dynamically allocate enough space to store enough pointers to characters on the heap
	// used to store a dynamically allocated array of pointers to char
	char **strings;

	// stores the total number of strings to be stored
	int total = 0;

	// ask user for the number of strings
	printf("Enter Number Of Stjrings: ");
	scanf("%d", &total);

	strings = malloc(total * sizeof(char *)); //allocating space for strings to point to a number (total) of pointers-to-characters (char *)

	// buffer will be used to accept each string of input from the user, we give 
	// it a very large amount of space.
	char buffer[BUFFER_SIZE];

	// length will store the length of the string the user enters
	int length = 0;

	// if we do not flush the stdin stream there will still be a HANGING \n character from scanf 
	// and the first call to fgets will store an empty string into the buffer 
	while (getchar() != '\n');

	printf("\n");
	for (int i = 0; i < total; i++)
	{
		// ask the user for the string, store it into buffer, get string length
		printf("Enter string %d: ", i + 1);
		fgets(buffer, BUFFER_SIZE, stdin); //using fgets to accept input from user
		length = strlen(buffer); //get the string length

		// fgets will store the \n char entered by the user when they hit enter, 
		// we assume the user does not want this so we shift up the null 
		// terminator by one char so the \n is eliminated from the string
		buffer[length - 1] = '\0'; //special character to terminate a string, and this moves it up one character in the string

		// dynamically allocate enough space to store the the string, store the 
		// pointer to this block of memory in strings[i]
		strings[i] = malloc(length * sizeof(char));

		// copy the string from the buffer to the dynamically allocated memory
		strcpy(strings[i], buffer);
	}

	// print out the array of strings to verify success
	printf("\nResulting strings array:\n\n");
	for (int i = 0; i < total; i++)
	{
		printf("strings[%d] = %s\n", i, strings[i]);
	}
	printf("\n");

	return 0;
}