#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

char* binaryToChar(struct ppm_pixel* two_d_array, int width, int height, char* result_array) {
  int count, magnitude, bit_index, char_index = 0;

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      int pixel_index = i * width + j;
      for (int color_index = 0; color_index < 3; color_index++) {
        unsigned int value = two_d_array[pixel_index].colors[color_index];
        int exp = 7 - bit_index; 

        if (value == 1) {
          magnitude += 1 << exp;
        }

        bit_index += 1;
        count += 1;

        if (count == 8) {
          result_array[char_index] = (char) magnitude;       
          char_index += 1;
          count = 0;
          bit_index = 0;
          magnitude = 0;
        }
      }
    }
  }
  return result_array; 
}

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
  int symbol_count = (width * height * 3)/8;
  char* result_array = malloc(sizeof(char) * (width * height * 3)); 

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);
  printf("Max number of characters in the image: %d\n", symbol_count);  
  result_array = binaryToChar(two_d_array, width, height, result_array);
  printf("%s", result_array);

  free(two_d_array);
  two_d_array = NULL;
  free(result_array);
  result_array = NULL;
  return 0;
}
