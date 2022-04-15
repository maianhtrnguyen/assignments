#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  int size = 2000;
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
  // generate pallet
  // compute image

  double timer;
  struct timeval tstart, tend;

  srand(time(0));

  int shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size, 0644 | IPC_CREAT);
  if (shmid == -1) {
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }

  struct ppm_pixel* two_d_array = shmat(shmid, NULL, 0);
  if (two_d_array == (void*) -1) {
    perror("Error: cannot access shared memory\n");
    exit(1);
  }

  struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel) * maxIterations);
  int rowsAndCols[4][4]; // 2D array
  char output_filename[128];

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

  gettimeofday(&tstart, NULL);
  for (int i = 0; i < numProcesses; i++) {
    int pid = fork();

    if (i == 0) {
      rowsAndCols[i][0] = 0;
      rowsAndCols[i][1] = size/2;
      rowsAndCols[i][2] = 0;
      rowsAndCols[i][3] = size/2;
    } else if (i == 1) {
      rowsAndCols[i][0] = 0;
      rowsAndCols[i][1] = size/2;
      rowsAndCols[i][2] = size/2;
      rowsAndCols[i][3] = size;
    } else if (i == 2) {
      rowsAndCols[i][0] = size/2;
      rowsAndCols[i][1] = size;
      rowsAndCols[i][2] = 0;
      rowsAndCols[i][3] = size/2;
    } else if (i == 3) {
      rowsAndCols[i][0] = size/2;
      rowsAndCols[i][1] = size;
      rowsAndCols[i][2] = size/2;
      rowsAndCols[i][3] = size;
    }

    if (pid == 0) {
      for (int col = rowsAndCols[i][2]; col < rowsAndCols[i][3]; col++) {
        for (int row = rowsAndCols[i][0]; row < rowsAndCols[i][1]; row++) {
          float xfrac = ((float)row)/(float)size;
          float yfrac = ((float)col)/(float)size;
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

          int index = (col * size) + row;

          if (iter < maxIterations) {
            // write color to image at location (row,col)
            two_d_array[index].red = palette[iter].red;
            two_d_array[index].green = palette[iter].green;
            two_d_array[index].blue = palette[iter].blue;
          } else {
            // assign black color 
            two_d_array[index].red = 0; 
            two_d_array[index].green = 0;
            two_d_array[index].blue = 0;
          }
        }
      }
      exit(0);
    } else {
      printf("Launched child process: %d\n", pid);
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d,%d)\n", pid, rowsAndCols[i][2], rowsAndCols[i][3], rowsAndCols[i][0], rowsAndCols[i][1]);
    }
  }

  for (int i = 0; i < numProcesses; i++) {
    int status;
    int ret = wait(&status);
    printf("Child process complete: %d\n", ret);
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %.6f seconds\n", size, size, timer);
  sprintf(output_filename, "multi-mandelbrot-%d-%.ld.ppm", size, time(0));
  printf("Writing file: %s\n", output_filename);
  write_ppm(output_filename, two_d_array, size, size);

  if (shmdt(two_d_array) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }   

  free(palette);
  palette = NULL;
  return 0;
}