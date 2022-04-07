#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  int size = 2000;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  // generate pallet
  srand(time(0));
  double timer;
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  struct ppm_pixel* two_d_array = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* palette = malloc(sizeof(struct ppm_pixel) * maxIterations);
  char output_filename[128];

  if (two_d_array == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  if (palette == NULL) {
    printf("ERROR: malloc failed!\n");
    exit(1);
  }

  // generate random colors
  for (int i = 0; i < maxIterations; i++) {
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }

  // compute image
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      float xfrac = row/size;
      float yfrac = col/size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;

      while (iter < maxIterations && (x * x + y * y < 2 * 2)) {
        float xtmp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtmp;
        iter += 1;
      }

      int index = (row * size) + col;

      if (iter < maxIterations) {
        // write color to image at location (row,col)
        two_d_array[index] = palette[iter];
      } else {
        // assign black color 
        two_d_array[index].red = 0; 
        two_d_array[index].green = 0;
        two_d_array[index].blue = 0;
      }
    }
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %.6f seconds\n", size, size, timer);
  sprintf(output_filename, "mandelbrot-%d-%.ld.ppm", size, time(0));
  printf("Writing file: %s\n", output_filename);
  write_ppm(output_filename, two_d_array, size, size);
  free(two_d_array);
  free(palette);
  two_d_array = NULL;
  palette = NULL;
  return 0;

}

