#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used_size;
  struct chunk *next;
};

struct chunk *flist = NULL;

// code copied from mhysa.c in Malloc reading
void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  struct chunk *next = flist; 
  struct chunk *prev = NULL;

  while(next != NULL) {
    if (next->size >= size) {
      next->used_size += size;

      if (prev != NULL) { 
        prev->next = next->next;
      } else {
        flist = next->next;
      }
      
      return (void*)(next + 1); 
    
    } else {
        prev = next;
        next = next->next;
    }
  }

  void *memory = sbrk(size + sizeof(struct chunk));

  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->used_size = size;
    return (void*) (cnk + 1);
  }
}

// code copied from mhysa.c in Malloc reading
void free(void *memory) {
  if (memory != NULL) {
    struct chunk *current_chunk = (struct chunk*)((struct chunk*) memory - 1);
    current_chunk->next = flist;
    current_chunk->used_size = 0;
    flist = current_chunk;
  } 
  return;
}

void fragstats(void* buffers[], int len) {
  int total_free_chunks = 0;
  int in_used_chunks = 0;
  int largest_unused_memory = 0;
  int smallest_unused_memory = 999999;
  float average_unused_memory = 0.0;
  int total_unused_memory = 0;
  int largest_size_free_chunk = 0;
  int smallest_size_free_chunk = 999999;
  float average_size_free_chunk = 0.0;
  int free = 0;

  // buffers has the memory currently in use and flist contains the memory not in use
  for (int i = 0; i < len; i++) {
    if (buffers[i] != NULL) {
      struct chunk *current_chunk = (struct chunk*) ((struct chunk*) buffers[i] - 1); 
      in_used_chunks += 1;
      int unused_memory = current_chunk->size - current_chunk->used_size;
      total_unused_memory += unused_memory;

      if (unused_memory < smallest_unused_memory) {
        smallest_unused_memory = unused_memory;
      } 
      
      if (unused_memory > largest_unused_memory) {
        largest_unused_memory = unused_memory;
      }
    }
  }

  average_unused_memory = (float) total_unused_memory/in_used_chunks;

  struct chunk *current_chunk = flist;

  while (current_chunk != NULL) {
    total_free_chunks += 1;
    free += current_chunk->size;
    if (current_chunk->size < smallest_size_free_chunk) {
      smallest_size_free_chunk = current_chunk->size;
    } 
    if (current_chunk->size > largest_size_free_chunk ) {
      largest_size_free_chunk  = current_chunk->size;
    }
    current_chunk = current_chunk->next;
  }

  average_size_free_chunk = (float) free/total_free_chunks;

  printf("Total blocks: %d Free: %d Used: %d\n", total_free_chunks + in_used_chunks, total_free_chunks, in_used_chunks);
  printf("Internal unused: total: %d average: %.1f smallest: %d largest: %d\n", total_unused_memory, average_unused_memory, smallest_unused_memory, largest_unused_memory);
  printf("External unused: total: %d average: %.1f smallest: %d largest: %d\n", free, average_size_free_chunk, smallest_size_free_chunk, largest_size_free_chunk);
}
