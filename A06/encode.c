#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void charToBinary(char c, char* binary_str, int *memory_count) {
    int decimal = (int) c;

    for (int i = 0; i < 8; i++) {
      binary_str[8 - i - 1] = decimal % 2;
      *memory_count += 1;
      decimal = decimal / 2;
    }
}

void encode(char* binary_str, struct ppm_pixel* two_d_array, int memory_count) {
  int current_index = 0;
  int color_index = 0;

  for (int i = 0; i < memory_count; i++) {
      if ((binary_str[i] == 1 && two_d_array[current_index].colors[color_index] % 2 == 0) || 
          (binary_str[i] == 0 && two_d_array[current_index].colors[color_index] % 2 == 1)) {
        if (two_d_array[current_index].colors[color_index] < 255) { 
          two_d_array[current_index].colors[color_index] += 1; 
        } else { 
          two_d_array[current_index].colors[color_index] -= 1; 
        }
      } 
    color_index += 1; 
    if (color_index == 3) { 
      color_index = 0; 
      current_index += 1; 
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
  char* filename = argv[1];
  int len = strlen(filename);
  char encoded_filename[128] = "";
  int memory_count = 0;

  struct ppm_pixel* two_d_array = read_ppm(filename, &width, &height);
  int symbol_count = (width * height * 3)/8;
  char *phrase = malloc(width * height * 3/8+1);
  char* binary_str = malloc(sizeof(char) * (width * height * 3)); 

  if (phrase == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  if (binary_str == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);
  printf("Max number of characters in the image: %d\n", symbol_count);  
  printf("Enter a phrase: ");
  scanf("%[^\n]s", phrase);

  strncpy(encoded_filename, filename, len - 4);
  encoded_filename[len - 4] = '\0';
  strcat(encoded_filename, "-encoded.ppm");

  for (int i = 0; i < strlen(phrase); i++) {
    charToBinary(phrase[i], binary_str, &memory_count);
  }

  binary_str[memory_count] = '\0'; 

  encode(binary_str, two_d_array, memory_count);
  write_ppm(encoded_filename, two_d_array, width, height);
  printf("Writing file %s\n", encoded_filename);

  free(two_d_array);
  two_d_array = NULL;
  free(binary_str);
  binary_str = NULL;
  free(phrase);
  phrase = NULL;
  return 0;
}