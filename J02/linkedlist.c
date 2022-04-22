#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

struct cake makeCake(const char* flavor, float cost) {
  struct cake newCake;
  strncpy(newCake.flavor, flavor, 16);
  newCake.cost = cost;
  newCake.next = NULL;
  return newCake;
}

// todo: implement cheapestCake
void cheapestCake(struct cake* firstCake) {
  struct cake *current_cake = malloc(sizeof(struct firstCake));
  struct cake *cheapest_cake = malloc(sizeof(struct firstCake));
  int min = current_cake.cost;

  while (current_cake != Null) {
    printf("cake: %s %d", current_cake.flavor, current_cake.cost);
    current_cake = current_cake.next;
    if (current_cake.cost < min) {
      min = current_cake.cost;
      cheapest_cake = current_cake; 
    }
  }

  printf("The cheapest cake is: %s", cheapest_cake.flavor);
}
 
int main() {
  struct cake cake1 = makeCake("red velvet", 2.00);
  struct cake cake2 = makeCake("chocolate", 1.75);
  struct cake cake3 = makeCake("mocha", 3.50);
  struct cake cake4 = makeCake("oolong boba", 2.56);
  // todo: define 4th cake

  cake1.next = &cake2;
  cake2.next = &cake3;
  cake3.next = &cake4; 
  // draw stack and heap here

  // todo: call cheapestCake
}
