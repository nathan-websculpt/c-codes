#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Current idea is to run commands that will help to visualize what malloc and calloc are doing and analyze dynamic memory
// run commands:
//
// malloc or calloc
// int or char
// space to create
//
//examples:
//          m i 5    --    malloc(sizeof(int) * 5)
//          m c 8    --    malloc(sizeof(char) * 8)
//          c i 10   --    calloc(10, sizeof(int))
//          g i 0    --    get what is at the address of index 0 ( results from m i 5 )
//          g c 1    --    get what is at the address of index 1 ( results from m c 8 )
//          f        --    free allocated memory
//          t        --    display tree

#define BUFFER_SIZE 4096
#define	ARRAY_SIZE 100

int addresses[ARRAY_SIZE];
int addr_size = 0;


void handleMalloc(char *subStrArray[]) {
	printf("handleMalloc called\n");

	//look for second item in command - i for int and c for char
	switch (subStrArray[1][0])
	{
		case 'i':
			printf("for type Int\n");
			int size = atoi(subStrArray[2]);
			int *int_ptr = malloc(sizeof(int) * size);
			printf("ptr: %p\n", int_ptr);
			printf("more info: %p\n", &int_ptr);

			//load mock data
			for (int i = 0; i < size; i++) int_ptr[i] = size - i;
			//display mock data
			for (int i = 0; i < size; i++)
				printf("[%d] = %d\n", i, int_ptr[i]);

			//store address on addresses array
			addresses[addr_size++] = int_ptr;
			break;
		case 'c':
			printf("for type Char\n");
			char *char_ptr = malloc(sizeof(char) * atoi(subStrArray[2]));
			printf("ptr: %p\n", char_ptr);
			printf("more info: %p\n", &char_ptr);

			addresses[addr_size++] = char_ptr;
			break;
		default:
			printf("Did not find 'i' or 'c' at index 1\n");
			break;
	};

	//TODO: free
}

void handleCalloc(char *subStrArray[]) {
	printf("handleCalloc called\n");

	//look for second item in command - i for int and c for char
	switch (subStrArray[1][0])
	{
		case 'i':
			printf("for type Int\n");
			int *int_ptr = calloc(atoi(subStrArray[2]), sizeof(int));
			printf("ptr: %p\n", int_ptr);
			printf("more info: %p\n", &int_ptr);

			addresses[addr_size++] = int_ptr;
			break;
		case 'c':
			printf("for type Char\n");
			char *char_ptr = calloc(atoi(subStrArray[2]), sizeof(char));
			printf("ptr: %p\n", char_ptr);
			printf("more info: %p\n", &char_ptr);

			addresses[addr_size++] = char_ptr;
			break;
		default:
			printf("Did not find 'i' or 'c' at index 1\n");
			break;
	};

	//TODO: free
}

void makeChristmasTree() {
	int height = 22;
	for (int i = 1; i <= height; i++) {
		// from 1 up to 2x height - 1
		int starCount = (i * 2) - 1;
		int spaceCount = height - i + 1;
		for (int j = 0; j < spaceCount; j++)
			printf(" ");
		for (int j = 0; j < starCount; j++)
			printf("*");
		printf("\n");
	}
	// trunk
	for (int i = 0; i < 3; i++)	{
		// spaces to center
		for (int j = 0; j < height-2; j++)
			printf(" ");
		printf("*****\n");
	}
}

void handleGet(char *subStrArray[]) {
	int index = atoi(subStrArray[2]);
	printf("GETTING SOME DATA\n");
	int known_address = addresses[index];

	//switch on pointer type
	switch (subStrArray[1][0])
	{
	case 'i':
		printf("READING for type Int\n");
		// Cast the address to a pointer of the appropriate type
		int *ptr = (int *)known_address;
		// Read the value by dereferencing the pointer
		int value = *ptr;

		//currently just testing with ints...
		//test re-setting data::
		//for (int i = 0; i < value; i++) ptr[i] = 10 - i;

		//display data
		for (int i = 0; i < value; i++)
			printf("[%d] = %d\n", i, ptr[i]);

		printf("Value at address 0x%lx: %d\n", (unsigned long)known_address, value);
		break;
	case 'c':
		printf("READING for type Char\n");
		char *char_ptr = (char *)known_address;
		char char_value = *char_ptr;
		printf("Value at address 0x%lx: %d\n", (unsigned long)known_address, char_value);
		break;
	default:
		printf("READING ... did not find 'i' or 'c' at index 1\n");
		break;
	};
}

void init() {
	printf("FIRST:'m' for malloc() or 'c' for calloc()\n");
	printf("THEN:'i' for int or 'c' for char\n");
	printf("EXAMPLES:\n");
	printf("          m i 5    --    malloc(sizeof(int) * 5)\n");
	printf("          m c 8    --    malloc(sizeof(char) * 8)\n");
	printf("          c i 10   --    calloc(10, sizeof(int))\n");
	printf("          g i 0    --    get what is at the address of index 0 ( results from m i 5 )\n");
	printf("          g c 1    --    get what is at the address of index 1 ( results from m c 8 )\n");
	printf("          t        --    display tree\n");
	printf("          q        --    QUIT\n");
	printf("__________________________________________________________________________________________>\n\n\n");
}

void freeMemory() {
	printf("FREEING MEMORY\n");
	for(int i = 0; i < addr_size; i++) {
		free(addresses[i]); // TODO:
		printf("Freed memory at address: %p\n", (void *)addresses[i]);

		// TODO: clear the address in the array
	}
	addr_size = 0; // reset the size of addresses array
}

int main() {
	init();
	char buffer[BUFFER_SIZE];
	int length = 0;
	int breaker = 1;

	while (breaker) 
	{
		printf("\n\n__>: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		length = strlen(buffer);
		buffer[length - 1] = '\0';

		//split string by space character
		char *splitChar = strtok(buffer, " ");
		int i = 0;
		char *subStrArray[100];
		while (splitChar != NULL)
		{
			subStrArray[i] = splitChar;
			splitChar = strtok(NULL, " ");
			i++;
		}

		switch (subStrArray[0][0])
		{
			case 'm':
				handleMalloc(subStrArray);
				break;
			case 'c':
				handleCalloc(subStrArray);
				break;			
			case 'g': //read data at an address: g i index_of_arr
				handleGet(subStrArray);
				break;
			case 't':
				makeChristmasTree();
				break;
			case 'q':
				breaker = 0;
				break;
			case 'f':
				freeMemory();
				break;
			default:
				printf("Did not find 'm' or 'c' at index 0\n");
				break;
		};		
	}

	return 0;
}
