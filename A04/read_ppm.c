#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  // initialize variables
  FILE *infile = NULL;
  char str[512];
  unsigned char r; 
  unsigned char g; 
  unsigned char b; 
  struct ppm_pixel *two_d_array;

  infile = fopen(filename, "r"); // open the file

  if (infile == NULL) {
    // Print an error if the program cannot open the file
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }

  fgets(str, 512, infile); // skip line with ASCII type
  fgets(str, 512, infile); 

  if (str[0] == '#' || str[0] == ' ') {
    fgets(str, 512, infile); // skip comment line or blank line
  }

  // get width and height
  *w = atoi(&str[0]);
  *h = atoi(&str[2]);
  fgets(str, 512, infile); // skip line with Maximum color value

  // create 2D array
  two_d_array = malloc(sizeof(int) * (*w) * (*h));

  if (two_d_array == NULL) {
    printf("ERROR: malloc failed!\n");
    return NULL;
  }

  // read each pixel in the 2D array one by one
  for (int i = 0; i < *h; i++) {
    for (int j = 0; j < *w; j++) {
      int index = i * (*w) + j;
      fscanf(infile, " %hhu %hhu %hhu", &r, &g, &b);
      two_d_array[index].red = r;
      two_d_array[index].green = g;
      two_d_array[index].blue = b;
    }
  }

  fclose(infile);
  return two_d_array;
}




