#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void charToBinary(char c, char* binary_str) {
    int decimal = (int) c;

    for (int i = 0; i < 8; i++) {
      binary_str[i] = decimal % 2;
      decimal = decimal / 2;
    }
}

void encode(char* binary_str, struct ppm_pixel* two_d_array) {
  int current_index = 0;

  for (int i = 0; i < 8; i++) {
    for (int color_index = 0; color_index < 3; color_index++) {
      if ((binary_str[i] == 1 && two_d_array[current_index].colors[color_index] % 2 == 0) || 
          (binary_str[i] == 0 && two_d_array[current_index].colors[color_index] % 2 == 1)) {
        if (two_d_array[current_index].colors[color_index] < 255) { 
          two_d_array[current_index].colors[color_index] += 1; 
        } else { 
          two_d_array[current_index].colors[color_index] -= 1; 
        }
      } 
    }
  }
}

int main(int argc, char** argv) {
   // todo: call read_ppm
  if (argc != 2) { 
    // Print the usage if the user inputs an incorrect number of command line arguments
    printf("The input does not have enough 2 arguments.\n");
    exit(1);
  }

  int height, width = 0;
  char phrase[128];
  char* filename = argv[1];
  int len = strlen(filename);
  char encoded_filename[128] = "";

  struct ppm_pixel* two_d_array = read_ppm(filename, &width, &height);
  int symbol_count = (width * height * 3)/8;
  char* result_array = malloc(sizeof(char) * (width * height * 3)); 
  char* binary_str = malloc(sizeof(char) * (width * height * 3)); 

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  if (result_array == NULL || binary_str == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);
  printf("Max number of characters in the image: %d\n", symbol_count);  
  printf("Enter a phrase: ");
  scanf("%s", phrase);

  strncpy(encoded_filename, filename, len - 4);
  encoded_filename[len - 4] = '\0';
  strcat(encoded_filename, "-encoded.ppm");

  for (int i = 0; i < strlen(phrase); i++) {
    charToBinary(phrase[i], binary_str);
  }

  encode(binary_str, two_d_array);
  write_ppm(encoded_filename, two_d_array, width, height);
  printf("Writing file %s\n", encoded_filename);

  free(two_d_array);
  two_d_array = NULL;
  free(result_array);
  result_array = NULL;
  free(binary_str);
  binary_str = NULL;
  return 0;
}

