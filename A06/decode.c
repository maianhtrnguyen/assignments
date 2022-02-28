#include <stdio.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
    // todo: call read_ppm
  if (argc != 2) { 
    // Print the usage if the user inputs an incorrect number of command line arguments
    printf("The input does not have enough 2 arguments.\n");
    exit(1);
  }

  int height, width = 0;
  char* filename = argv[1];
  struct ppm_pixel* two_d_array = read_ppm(filename, &width, &height);

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = i * width + j;
      for 
    }
    printf("\n");
  } 

  free(two_d_array);
  two_d_array = NULL;
  return 0;
  return 0;
}

