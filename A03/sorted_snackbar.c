//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name: Mai Anh Nguyen
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

    struct snack *new_snack; // create new struct snack
    new_snack = malloc(sizeof(struct snack));

    if (new_snack == NULL) {
      printf("Cannot allocate new memory. Exitting ....");
      exit(1);
    }

    strcpy(new_snack->name, name);
    new_snack->quantity = quantity;
    new_snack->cost = cost;
    new_snack->next = NULL;

    if (snacks == NULL) {
      // if the current linked list is empty, new_snack will be the head of the list
      return new_snack;
    }

    struct snack* current_snack = snacks; // current pointer
    struct snack* previous_snack = NULL;

  // go over each element in the linked list until finding the one that has alphabetical order after new_snack.name
  while (current_snack != NULL) {
    if (strcmp(current_snack->name, new_snack->name) < 0) {
      previous_snack = current_snack;
      current_snack = current_snack->next;
    } else {
      break;
    }
  }

  // add new_snack right before current_snack
  new_snack->next = current_snack;
  
  if (previous_snack == NULL) {
    return new_snack;
  }

  previous_snack->next = new_snack;
  return snacks;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  struct snack* current_snack = snacks;
  struct snack* next_snack;

  // go over each element in the linked list and free it
  while (current_snack != NULL) {
    next_snack = current_snack->next;
    free(current_snack);
    current_snack = next_snack;
  }

  snacks = NULL;
}

int main() {
  char name[128]; 
  float cost; 
  int quantity; 
  int number_of_snacks; 

  printf("Enter a number of snacks: ");
  scanf("%d", &number_of_snacks); 

  struct snack* first_snack = NULL;

  for (int i = 0; i < number_of_snacks; i++) { 
      printf("Enter a name: "); 
      scanf("%s", name); 

      printf("Enter a cost: ");
      scanf("%f", &cost);  

      printf("Enter a quantity: "); 
      scanf("%i", &quantity); 

      // add new snack to the stack
      first_snack = insert_sorted(first_snack, name, quantity, cost);
  }

  printf("\nWelcome to Mai Anh's Snack Bar.\n\n"); 

  int index = 0;
  struct snack* head_snack = first_snack;

  // print out the menu
  while (first_snack != NULL) {
    printf("%d) %s\t cost: $%.2f \t quantity: %d \n", index, first_snack->name, first_snack->cost, first_snack->quantity); 
    index += 1;
    first_snack = first_snack->next;
  }
  
  clear(head_snack);
  return 0;
}


