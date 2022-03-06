#include <stdio.h>
#include <string.h>

int main() {
  char input[128];
  int magnitude = 0;
  printf("Enter 8 bits: ");
  scanf(" %s", input);

  for (int i = strlen(input) - 1; i >= 0; i--) {
    if (input[i] == '1') {
      int exp = strlen(input) - i - 1;
      printf("exp %d\n", exp);
      magnitude += 1 << exp;
    }
  }

  printf("Your character is: %c\n", (char) magnitude);
  return 0;
}

