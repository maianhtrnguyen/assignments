#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main() {
    char word[32];
    int count;
    printf("Enter a word: ");
    scanf("%s", word);  
    printf("Enter a count: ");
    scanf("%d", &count);

    char* output = (char *) malloc(strlen(word) * count + count); 

    if (output == NULL) { 
        printf("Cannot allocate new string. Exiting... \n"); 
        exit(1);
    } 

    strcpy(output, word);

    for (int i = 0; i < count; i++) { 
        strcat(output, word);
    }

    printf("Your word is: %s \n", output); 

    free(output); 
    output = NULL; 

    return 0;
}

