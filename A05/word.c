#include <stdio.h>
#include <string.h>

int main() {
  char word[128];
  printf("Enter 4 characters:");
  scanf("%s", word);

  for (int i = 0; i <= strlen(word); i++) {
    printf("Debug: %c = 0x", word[i]);
    

  }
  return 0;
}
