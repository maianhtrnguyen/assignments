#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
    void* initial_top = sbrk(0);
    printf("The initial top of the heap is %p\n", initial_top);
    void* current_top = sbrk(0);
    printf("The current top of the heap is %p\n", current_top);
    int difference = (int) (current_top - initial_top);
    printf("Increased by %d (0x%0x) bytes\n", difference, difference);
    return 0 ;
}
