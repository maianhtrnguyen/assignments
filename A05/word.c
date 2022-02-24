#include <stdio.h>
#include <string.h>

int main() {
  char word[128];
  unsigned int number = 0;
  printf("Enter 4 characters: ");
  scanf("%s", word);

  for (int i = strlen(word) - 1; i >= 0; i--) {
    unsigned int shifted_character = word[i] << 8 * (strlen(word) - 1 - i);
    number += shifted_character;
    printf("Debug: %c = 0x%08X\n", word[i], shifted_character);
  }
  printf("Your number is: %d (0x%08x)\n", number, number);
  return 0;
}



