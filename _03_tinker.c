#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int main() {
    void *addresses[MAX];
    int addr_length = 0;

    int *int_ptr = malloc(sizeof(int) * 10);
    if (int_ptr) {
        addresses[addr_length++] = int_ptr;
    }

    // GOOD: Print pointer properly
    printf("As pointer: %p\n", addresses[0]);

    // Free properly
    for (int i = 0; i < addr_length; ++i) {
        free(addresses[i]);
    }

    return 0;
}
