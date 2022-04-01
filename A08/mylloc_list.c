#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used_size;
  struct chunk *next;
};

struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* cnk = (struct chunk*) memory;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  return;
}

void fragstats(void* buffers[], int len) {
  int total_free_chunks = 0;
  int in_used_chunks = 0;
  int largest_unused_memory = 0;
  int smallest_unused_memory = 0;
  float average_unused_memory = 0.0;
  int total_unused_memory = 0;
  int largest_size = 0;
  int smallest_size = 0;
  float average_size = 0.0;

  for (int i = 0; i < len; i++) {
    if (buffer[i] != NULL) {
      struct chunk* current_chunk = (struct chunk*) buffer[i];
      total_free_chunks += 1
      
    }
  }

}

