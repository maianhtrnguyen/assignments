#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void* initial_top = sbrk(0);
  printf("The initial top of the heap is %p\n", initial_top);
  void* memory;
  
  for (int i=0; i < 10; i++) {
    memory = malloc(100);

    if (memory == NULL) {
      printf("ERROR: malloc failed!\n");
      exit(1);
    }

    free(memory);
    memory = NULL;
  }

  void* final_top = sbrk(0);
  printf("The final top of the heap is %p\n", final_top);
  int difference = (int) (final_top - initial_top);
  printf("Increased by %d (0x%0x) bytes\n", difference, difference);
  return 0 ;
}
