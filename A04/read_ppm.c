#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile = NULL;
  infile = fopen(filename, "r"); // open the file

  if (infile == NULL) {
    // Print an error if the program cannot open the file
    printf("Cannot open file: %s\n", argv[1]);
    exit(1);
  }



  return NULL;
}

int main() {

}

