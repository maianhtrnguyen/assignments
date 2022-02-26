#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) { 
    // Print the usage if the user inputs an incorrect number of command line arguments
    printf("The input does not have enough 2 arguments.\n");
    exit(1);
  }

  int height, width = 0;
  char* filename = argv[1];
  int len = strlen(filename);
  char glitch_filename[128] = "";
  struct ppm_pixel* two_d_array = read_ppm(filename, &width, &height);

  if (two_d_array == NULL) {
    printf("Memory cannot be allocated for the image or the filename is invalid.");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);

  // add suffix "-glitch" to the filename
  strncpy(glitch_filename, filename, len - 4);
  glitch_filename[len - 4] = '\0';
  strcat(glitch_filename, "-glitch.ppm");

  printf("Writing file %s\n", glitch_filename);

  write_ppm(glitch_filename, two_d_array, width, height);
  free(two_d_array);
  two_d_array = NULL;
  return 0;
}
