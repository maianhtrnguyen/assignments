#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char word[1024];
  // unsigned int number = 0;
  printf("Please enter a phrase: ");
  scanf("%[^\n]s", word);

  for (int i = 0; i < strlen(word); i++) {
    unsigned int second = word[i] & 0b00000010;
    unsigned int third = word[i] & 0b00000100;
    if (second == 0b0 && third == 0b0){
      word[i] = word[i];
    }
    else if (second == 0b00000000 && third == 0b00000100){
      word[i] = word[i] | 0b00000010;
      word[i] = word[i] & 0b11111011;
    }
    else if (second == 0b00000010 && third == 0b00000000){
      word[i] = word[i] & 0b11111101;
      word[i] = word[i] | 0b00000100;
    }
    else {
      word[i] = word[i];
    }
  }
  printf("scramble: %s\n", word);
  return 0;
}
