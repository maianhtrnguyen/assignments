#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main() {

  // todo: call read_ppm
  int height, width = 0;
  struct ppm_pixel* two_d_array = read_ppm("feep-ascii.ppm", &width, &height);

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  printf("Testing file feep-ascii.ppm: %d %d\n", width, height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = i * width + j;
      printf("(%hhu %hhu %hhu) ", two_d_array[index].red, two_d_array[index].green, two_d_array[index].blue);
    }
    printf("\n");
  } 

  free(two_d_array);
  two_d_array = NULL;
  return 0;
}

