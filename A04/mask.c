#include <stdio.h>

int main() {
    int value = 0;
    printf("Enter a value: ");
    scanf(" %d", &value);

    unsigned int mask = 0x000000;
    int result = mask & value;
    

}