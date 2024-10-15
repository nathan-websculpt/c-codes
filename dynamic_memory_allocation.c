#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//NOTE: malloc will not guarantee the space is 0'd out first (in long-running programs, use calloc)
	//pointer set to point to block of allocated space on the Heap
	//malloc expects: number of bytes on the Heap to allocate space for
	//malloc returns a memory address to that space
	//*a is a pointer that is going to hold that memory address
	int *a = malloc(sizeof(int) * 10); // size of an int (on whichever system it runs on) times 10

	//access block of memory as if its an array
	//using Array Notation -- a[i]
	for (int i = 0; i < 10; i++) a[i] = 10 - i;

	for (int i = 0; i < 10; i++)
		printf("a[%d] = %d\n", i, a[i]);

	//print the memory address
	printf("memory address stored in a: %p\n", a);

	free(a); //HAVE TO DO THIS: allows space to be used again
    //freeing doesn't delete the data, BUT using calloc will delete the data (if you use this memory address again)
	return 0;
}

int main2(void)
{
	//calloc 0's out the data first!!!
	int *a = calloc(10, sizeof(int)); // takes: (number of things, size of thing)

	//access block of memory as if its an array
	//using Array Notation -- a[i]
	for (int i = 0; i < 10; i++) a[i] = 10 - i;

	for (int i = 0; i < 10; i++)
		printf("a[%d] = %d\n", i, a[i]);

	//print the memory address
	printf("memory address stored in a: %p\n", a);

	free(a); //HAVE TO DO THIS: allows space to be used again
	return 0;
}