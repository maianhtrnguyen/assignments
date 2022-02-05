#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include <stdbool.h>

int main() {
    srand(time(0));
    FILE *infile;
    infile = fopen("words.txt", "r");

    // check if the file can be read or not 
    if (infile == NULL) {
        printf("Error: unable to open file %s\n", "words.txt");
        exit(1);
    }

    // initialize variables
    char guess; // guess the character
    char buffer[64]; 
    char word[128]; // word to be guessed
    int num_words; 
    int turn = 0; // number of turns to gess
    bool game_over = false;
    
    // get the number of words 
    if (fgets(buffer, 64, infile) != NULL) { 
        sscanf(buffer, "%d", &num_words); 
    }

    // pick a random word index
    int random_number = rand() % num_words + 1; 

    // get the word with the above index
    for (int i = 0; i < random_number; i++) { 
        if (fgets(buffer, 64, infile) != NULL) { 
            sscanf(buffer, "%s", word); 
        }
    }

    printf("Welcome to Guess Word.\n");

    // I pick 2 * strlen(word) because I want to create separated space between the characters
    char* current_word = malloc(sizeof(char) * 2 * strlen(word)); 
  
    if (current_word == NULL) { 
        printf("Cannot allocate new memory. Exiting... \n"); 
        exit(1); 
    }

    // fill even indices with "_" and leave odd indices with blank space
    for (int i = 0; i < strlen(word) * 2; i++) { 
        if (i % 2 == 0) {
            strcpy(&current_word[i], "_"); 
        } else { 
            strcpy(&current_word[i], " "); 
        }
    }

    // Play until the game is over
    while (!game_over) { 
        turn += 1; 
        bool char_found = false; 
        printf("Turn: %d\n\n", turn);
        printf("%s\n", current_word); 

        printf("Guess a chatacter: "); 
        scanf(" %c", &guess); 

        for (int i = 0; i < strlen(word); i++) { 
            if (word[i] == guess) { 
                char_found = true; 
                current_word[i * 2] = guess; 
            }
        }
    
        if (!char_found) { 
            printf("Sorry, %c not found!\n\n", guess); 
        }
    
        game_over = true; 

        for (int i = 0; i < strlen(word); i++) { 
            if (current_word[i * 2] == '_') { 
                game_over = false; 
            }
        }
    }

    printf("%s\n", current_word); 
    printf("You won in %i turns. \n", turn); 

    free(current_word); 
    current_word = NULL; 

    return 0; 
}




