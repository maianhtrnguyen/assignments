#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

void calculateIntensity(int r, int g, int b) {
  int average_intensity = (r + g + b)/3;

  if (0 <= average_intensity && average_intensity <= 25) {
    printf("@");
  } else if (26 <= average_intensity && average_intensity <= 50) {
    printf("#");
  } else if (51 <= average_intensity && average_intensity <= 75) {
    printf("%%");
  } else if (76 <= average_intensity && average_intensity <= 125) {
    printf("*");
  } else if (126 <= average_intensity && average_intensity <= 150) {
    printf(";");
  } else if (151 <= average_intensity && average_intensity <= 175) {
    printf(":");
  } else if (176 <= average_intensity && average_intensity <= 200) {
    printf(",");
  } else if (201 <= average_intensity && average_intensity <= 225) {
    printf(".");
  } else if (226 <= average_intensity && average_intensity <= 255) {
    printf(" ");
  }
}

int main(int argc, char** argv) {
  // todo
  if (argc != 2) { 
    // Print the usage if the user inputs an incorrect number of command line arguments
    printf("The input does not have enough 2 arguments.\n");
    return 0;
  }

  int height, width = 0;
  struct ppm_pixel* two_d_array = read_ppm(argv[1], &width, &height);

  if (two_d_array == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", argv[1], width, height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = i * width + j;
      calculateIntensity(two_d_array[index].red, two_d_array[index].green, two_d_array[index].blue);
    }
    printf("\n");
  }

  free(two_d_array);
  two_d_array = NULL;
  return 0;
}

