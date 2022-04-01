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
  if (memory != NULL) {
    struct chunk *current_chunk = (struct chunk*) ((struct chunk*) memory − 1); 
    current_chunk−>next = flist;
    flist = current_chunk;
  } 
  return;
}

void fragstats(void* buffers[], int len) {
  int total_free_chunks = 0;
  int in_used_chunks = 0;
  int largest_unused_memory = 0;
  int smallest_unused_memory = 0;
  float average_unused_memory = 0.0;
  int total_unused_memory = 0;
  int largest_size_free_chunk = 0;
  int smallest_size_free_chunk = 0;
  float average_size_free_chunk = 0.0;

  // buffers has the memory currently in use and flist contains the memory not in use
  for (int i = 0; i < len; i++) {
    if (buffer[i] != NULL) {
      struct chunk *current_chunk = (struct chunk*) ((struct chunk*) buffer[i] − 1); 
      in_used_chunks += 1;
      int unused_memory = current_chunk->size - current_chunk->used_size;
      total_unused_memory += unused_memory;

      if (unused_memory < smallest_unused_memory || smallest_unused_memory == 0) {
        smallest_unused_memory = unused_memory;
      } else if (unusued_memory > largest_unused_memory) {
        largest_unused_memory = unusued_memory;
      }
    }
  }

  average_unused_memory = total_unused_memory/in_used_chunks;

  struct chunk *current_chunk = flist;

  while (current_chunk != NULL) {
    total_free_chunks += 1;

    if (current_chunk->size < smallest_size_free_chunk || smallest_size_free_chunk == 0) {
      smallest_size_free_chunk = current_chunk->size;
    } else if (current_chunk->size > argest_size_free_chunk ) {
      argest_size_free_chunk  = current_chunk->size;
    }
  }







}

