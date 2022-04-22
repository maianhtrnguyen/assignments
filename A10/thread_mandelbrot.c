#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "read_ppm.h"

struct t_arg {
    struct ppm_pixel *palette;
    struct ppm_pixel *two_d_array; 
    int size;
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    int row_start;
    int row_end;
    int col_start;
    int col_end;
    int maxIterations;
};

void * computeMandelbrot(void* args) {
  //cast to a struct t_arg from void*
  struct t_arg * myargs = (struct t_arg *) args;
  printf("Thread %lu) sub-image block: cols (%d,%d) to rows (%d,%d)\n", pthread_self(), myargs->col_start, myargs->col_end, myargs->row_start, myargs->row_end);

  for (int col = myargs->col_start; col < myargs->col_end; col++) {
    for (int row = myargs->row_start; row < myargs->row_end; row++) {
      float xfrac = ((float)row)/(float)myargs->size;
      float yfrac = ((float)col)/(float)myargs->size;
      float x0 = myargs->xmin + xfrac * (myargs->xmax - myargs->xmin);
      float y0 = myargs->ymin + yfrac * (myargs->ymax - myargs->ymin);

      float x = 0;
      float y = 0;
      int iter = 0;

      while (iter < myargs->maxIterations && (x * x + y * y < 2 * 2)) {
        float xtmp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtmp;
        iter += 1;
      }

      int index = (col * myargs->size) + row;

      if (iter < myargs->maxIterations) {
        // write color to image at location (row,col)
        myargs->two_d_array[index].red = myargs->palette[iter].red;
        myargs->two_d_array[index].green = myargs->palette[iter].green;
        myargs->two_d_array[index].blue = myargs->palette[iter].blue;
      } else {
        // assign black color 
        myargs->two_d_array[index].red = 0; 
        myargs->two_d_array[index].green = 0;
        myargs->two_d_array[index].blue = 0;
      }
    }
  }
  printf("Thread %lu) finished\n", pthread_self());
  return NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  int nthreads = 4;
  double timer;
  struct timeval tstart, tend;
  srand(time(0));
  pthread_t threads[4]; // 4 threads
  struct t_arg *myargs = malloc(sizeof(struct t_arg) * 4);
  struct ppm_pixel* two_d_array = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel) * maxIterations);  // generate pallet
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
  gettimeofday(&tstart, NULL);
  
  for (int i=0; i < nthreads; i++){
    myargs[i].palette = palette;
    myargs[i].two_d_array = two_d_array;
    myargs[i].size = size;
    myargs[i].xmin = xmin;
    myargs[i].xmax = xmax;
    myargs[i].ymin = ymin;
    myargs[i].ymax = ymax;
    myargs[i].maxIterations = maxIterations;

    if (i == 0) {
      myargs[i].row_start = 0;
      myargs[i].row_end = myargs[i].size/2;
      myargs[i].col_start = 0;
      myargs[i].col_end = myargs[i].size/2;
    } else if (i == 1) {
      myargs[i].row_start = 0;
      myargs[i].row_end = myargs[i].size/2;
      myargs[i].col_start = myargs[i].size/2;
      myargs[i].col_end = myargs[i].size;
    } else if (i == 2) {
      myargs[i].row_start = myargs[i].size/2;
      myargs[i].row_end = myargs[i].size;
      myargs[i].col_start = 0;
      myargs[i].col_end = myargs[i].size/2;
    } else if (i == 3) {
      myargs[i].row_start = myargs[i].size/2;
      myargs[i].row_end = myargs[i].size;
      myargs[i].col_start = myargs[i].size/2;
      myargs[i].col_end = myargs[i].size;
    }

    pthread_create(&threads[i], NULL, computeMandelbrot, (void*) &myargs[i]);
  }

  for (int i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %.6f seconds\n", size, size, timer);
  sprintf(output_filename, "mandelbrot-%d-%.ld.ppm", size, time(0));
  printf("Writing file: %s\n", output_filename);
  write_ppm(output_filename, two_d_array, size, size);

  free(palette);
  palette = NULL;
  free(two_d_array);
  two_d_array = NULL;
  free(myargs);
  myargs = NULL;
  return 0;
}
