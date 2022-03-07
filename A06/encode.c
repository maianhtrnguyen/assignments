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
  char phrase[128];
  char* filename = argv[1];
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
    return NULL;
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);
  printf("Max number of characters in the image: %d\n", symbol_count);  
  printf("Enter a phrase: ");
  scanf("%s", phrase);

  strncpy(encoded_filename, filename, len - 4);
  encoded_filename[len - 4] = '\0';
  strcat(encoded_filename, "-encoded.ppm");

  for (int i = 0; i < strlen(phrase); i++) {
    if (phrase[i] == 2) {
      binary_str[i] == '1';
    }
  }


  // result_array = binaryToChar(two_d_array, width, height, result_array);
  // printf("%s", result_array);

  free(two_d_array);
  two_d_array = NULL;
  free(result_array);
  result_array = NULL;
  return 0;
}

