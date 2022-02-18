#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main() {

  // todo: call read_ppm
  int height, width = 0;
  struct ppm_pixel* two_d_array = read_ppm("feep-ascii.ppm", &width, &height);

  printf("Testing file feep-ascii.ppm: %d %d\n", width, height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("(%hhu %hhu %hhu) ", two_d_array[i * width + j].red, two_d_array[i * width + j].green, 
      two_d_array[i * width + j].blue);
    }
    printf("\n");
  } 

  free(two_d_array);
  two_d_array = NULL;
  return 0;
}

