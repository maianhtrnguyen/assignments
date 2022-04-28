#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

struct args {
  int dotproduct;
  int* v;
  int* u;
  int size;
};

void *routine(void *args){
  struct args *info = (struct args *)args;
  int dotproduct = 0;

  for (int i = 0; i < info->size; i++) {
    info->dotproduct += info->u[i] * info->v[i];
  } 

  // printf("Product: %d\n", info->dotproduct);
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;

  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

//   pthread_t *thread_array = malloc(SIZE * sizeof(pthread_t));
  pthread_t threads[4];
  struct args info[4];
  int subsize = SIZE/4;

  for (int i = 0; i < 4; i++){
    info[i].dotproduct = 0;
    info[i].v = &v[subsize * i];
    info[i].u = &u[subsize * i];
    info[i].size = subsize;
  }
  
  printf("Test with 4 threads\n");
  for (int i = 0; i < 4; i++){
    pthread_create(&threads[i], NULL, routine, &info[i]);
  }

  for (int i = 0; i < 4; i++){
    pthread_join(threads[i], NULL);
  }

  int total = 0;

  for (int i = 0; i < 4; i++){
    total+=info[i].dotproduct;
  }

  printf("Answer with 4 threads: %d\n", total);
  
  return 0;
}