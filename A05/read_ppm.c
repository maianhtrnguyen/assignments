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
  struct ppm_pixel *two_d_array;

  infile = fopen(filename, "rb"); // open the file

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

  fread(two_d_array, sizeof(struct ppm_pixel), (*w) * (*h), infile);
  fclose(infile);
  return two_d_array;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *infile = fopen(filename, "wb"); // open the file

  if (infile == NULL) {
    printf("Cannot open file: %s\n", filename);
    return;
  }

  fprintf(infile, "P6 \n%d %d\n255\n", w, h);
  // fwrite(pxs, sizeof(struct ppm_pixel), w * h, infile);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int index = i * w + j;
      fwrite(pxs[index].colors, 1, 3, infile); // write to your file
      // struct ppm_pixel currPixel = pxs[i*w + j];
      // fwrite(currPixel.colors, 1, 3, infile);
    }
  }

  fclose(infile);
}
