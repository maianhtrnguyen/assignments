//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
  const char* name, int quantity, float cost) {
    struct snack *new_snack;
    new_snack = malloc(sizeof(*new_snack));

    if (new_snack == NULL) {
      printf("Cannot allocate new memory. Exitting ....");
      exit(1);
    }

    strcp(new_snack->name, name);
    new_snack->quantity = quantity;
    new_snack->cost = cost;

  while (snacks != NULL) {
    if (strcmp(snacks->name, new_snack->name) < 0) {
      snacks = snacks->next;
    } else {
      break;
    }
  }

  new_snack->next = snacks;
  snacks = new_snack;
  // todo
  return NULL;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
	struct snack* current_snack = snacks;
  struct snack next_snack;

  while (current_snack != NULL) {
    next_snack = *current_snack->next;
    free(current_snack);
    *current_snack = next_snack;
  }

  snacks = NULL;
}


int main() {
  return 0;
}

