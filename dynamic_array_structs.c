#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A struct for representing a point, the description member is expected to
// point to dynamically allocated memory where a string will be stored.
typedef struct {
	int x;
	int y;
	char *description;
} Point;

int main(int argc, char *argv[])
{
	// Declare a Point struct (on stack)
	Point p1;

	// Initialize members
	p1.x = 5;
	p1.y = 2;

	// Output the members
	printf("(%d, %d)\n", p1.x, p1.y);

	// Pointer variable called p2
	// Stores memory address of a point struct on the heap
	Point *p2 = malloc(sizeof(Point));

	// set the struct members (on the heap) either by	
	(*p2).x = 6;// dereferencing the pointer and then using the dot operator, 
	p2->y = 10;// or by using the arrow operator.

	// Output the members
	printf("(%d, %d)\n", (*p2).x, p2->y);

	// Free the dynamically allocated memory to make it available again and
	// to prevent a memory leak.
	free(p2);

	
	//dynamically allocating space for an array of structs and then using realloc() to increase the length of the array.

	// Declare and initialize a length variable to keep track of the length of
	// the array
	int length = 3;

	// Pointer variable that also stores the memory address of a Point struct
	// but this time it will store the memory address of the first Point struct in an array of Point structs
	Point *array = malloc(sizeof(Point) * length);

	// We can access and set the members of each struct in the array with this
	// syntax, here we set the members of the first struct in the array.
	array[0].x = 1;
	array[0].y = 1;

	// Setting the members of the second struct in the array
	array[1].x = 2;
	array[1].y = 2;

	// Setting the members of the third struct in the array
	array[2].x = 3;
	(*(array + 2)).y = 3;

	// Output the values of the members of the elements of the array...
	printf("\n");
	printf("Array...\n");
	for (int i = 0; i < length; i++)
	{
		printf("(%d, %d)\n", array[i].x, array[i].y);
	}
	printf("\n");

	length = 4;

	// call realloc() to allocate space for this larger block of memory
	// to store the larger array.  
	array = realloc(array, sizeof(Point) * length); // The 2nd argument to realloc() is the size of the new block of memory.  

	// After increasing the size of the array, it will have a 4th element, and
	// we can set the members of that element
	array[3].x = 4;
	array[3].y = 4;

	// Output the values of the members of the elements of the array that is
	// now one element larger so we can see the difference
	printf("\n");
	printf("Array...\n");
	for (int i = 0; i < length; i++)
		printf("(%d, %d)\n", array[i].x, array[i].y);
	printf("\n");

	// Free the dynamically allocated array to make the memory avaiable again
	// and to prevent a memory leak.
	free(array);

	return 0;
}