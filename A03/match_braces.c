//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Mai Anh Nguyen
//
#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node *new_node;
  new_node = malloc(sizeof(struct node));

  if (new_node == NULL) {
    printf("Cannot allocate new memory. Exitting ....");
    exit(1);
  }

  new_node->sym = sym;
  new_node->linenum = line;
  new_node->colnum = col;
  new_node->next = NULL;

  if (top == NULL) {
    return new_node;
  }

  top->next = new_node;
  top = new_node;

  return top;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if (top == NULL) {
    return NULL;
  }
  struct node* temp = top;
  top = top->next;
  free(temp);
  return top;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node* current_node = top;
  struct node* next_node;

  while (current_node != NULL) {
    next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  int index = 0;

  while (top != NULL) {
    printf("%d) symbol: %c\t linenum: $%d \t colnum: %d \n", index, top->sym, top->linenum, top->colnum); 
    index += 1;
    top = top->next;
  }
}

int main(int argc, char* argv[]) {
  FILE *infile = fopen(argv[0], "r");
  char c;
  int line_number = 1;
  int column_number = 0;
  struct node* top = NULL;
  int size = sizeof(argv)/sizeof(argv[0]);

  if (size > 1) {
    printf("usage: ./match_braces");
  }

  if (infile == NULL) {
    printf("Cannot open file: %s", argv[0]);
  }

  while(1) {
    c = fgetc(infile);
    column_number += 1;
    if (c == '\n') {
      line_number += 1;
    }

    if (c == '{') {
      top = push(c, line_number, column_number, top);
    }

    if (c == '}') {
      top = pop(top);
      if (top == NULL) {
        printf("Unmatched brace on Line %d and Column %d", line_number, column_number);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)", top->linenum, top->colnum, line_number, column_number);
      }
    }
  }
  
  clear(top);
  return 0;
}

