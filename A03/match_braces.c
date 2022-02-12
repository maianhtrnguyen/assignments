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
  struct node *new_node; // create new node
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
    // if the current stack is empty, the new_node will be the first element in this stack
    return new_node;
  }

  // otherwise, assign new_node to be the new top of the stack
  new_node->next = top; 
  top = new_node;

  return top;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if (top == NULL) {
    // if the current stack is empty, there is no node to be popped
    return NULL;
  }

  // remove the current top and move on to the next node
  struct node* next_node = top->next; 
  free(top);
  top = NULL;
  return next_node; // next_node is now top of the stack
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node* current_node = top; 
  struct node* next_node;

  // go over each node and free it
  while (current_node != NULL) {
    next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }

  top = NULL;
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  while (top != NULL) {
    printf("symbol: %c\t linenum: $%d \t colnum: %d \n", top->sym, top->linenum, top->colnum); 
    top = top->next;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) { 
    // Print the usage if the user inputs an incorrect number of command line arguments
    printf("usage: ./match_braces\n");
    return 0;
  }

  FILE *infile = NULL;
  infile = fopen(argv[1], "r"); // open the file
  char c;
  int line_number = 1; // line number starts at 1 because we are already at the first line
  int column_number = 0; // since we haven't read any characer, column number starts at 0
  struct node* top = NULL; 

  if (infile == NULL) {
    // Print an error if the program cannot open the file
    printf("Cannot open file: %s\n", argv[1]);
    exit(1);
  }
  
  // read the file one character at a time
  while(c != EOF) {
    c = fgetc(infile);
    column_number += 1; // Update the current column as we read in each character

    if (c == '\n') {
      // Update the current line number when we encounter \n
      line_number += 1;
      column_number = 0; // column_number is reset to 0 when moving to the new line
    }

    if (c == '{') {
      top = push(c, line_number, column_number, top);
    }

    if (c == '}') {
      if (top == NULL) {
        // If the symbols pushed and popped do not match, there is an error
        printf("Unmatched brace on Line %d and Column %d\n", line_number, column_number);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", top->linenum, top->colnum, line_number, column_number);
        top = pop(top);
      }
    }
  }

  // if there are still '{' symbols left in the stack, these are unmatched braces
  while (top != NULL) {
    printf("Unmatched brace on Line %d and Column %d\n", top->linenum, top->colnum);
    top = pop(top);
  }

  fclose(infile);
  clear(top);
  return 0;
}

