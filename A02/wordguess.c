#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>

int checkGuess(char *word, char guess, char *guessed_word, int remaining_chars) {
    int guess_count = 0;

    for (int i = 0; i < strlen(word) - 1; i++) {
        if (word[i] == guess && guessed_word[i] == '_') {
            guessed_word[i] = guess;
            guess_count += 1;
            remaining_chars -= 1;
        }
    }

    if (guess_count == 0) {
        printf("Sorry, %c not found!\n\n", guess); 
    }

    return remaining_chars;
}

int main() {
    FILE *infile = fopen("words.txt", "r");

    if (infile == NULL) {
        printf("Error: unable to open file %s\n", "words.txt");
        exit(1);
    }

    srand(time(0));
    char guess;
    char buffer[64]; 
    char word[64]; // word to be guessed
    int turn = 0;

    fgets(buffer, sizeof buffer, infile); // get the number of words 
    int num_words = atoi(buffer);

    int random_number = rand() % num_words + 1;

    for (int i = 0; i < random_number; i++) { 
        if (fgets(buffer, sizeof buffer, infile) != NULL) { 
            strcpy(word, buffer);
        }
    }

    char guessed_word[64];
    int word_len = strlen(word) - 1;    
    int remaining_chars = word_len;

    printf("Welcome to Word Guess!\n\n"); 

    for(int i = 0; i < word_len; i++){
        guessed_word[i] = '_';
    }

    while(remaining_chars > 0) {
        turn += 1;
        printf("Turn: %d\n\n", turn);

        for (int i = 0; i < word_len; i++) {
            printf("%c ", guessed_word[i]);
        }

        printf("\nGuess a chatacter: "); 
        scanf(" %c", &guess); 
        printf("\n");

        remaining_chars = checkGuess(word, guess, guessed_word, remaining_chars);
    }

    // print final result
    for (int i = 0; i < word_len; i++) {
        printf("%c ", guessed_word[i]);
    }

    printf("\nYou won in %i turns! \n", turn); 

    fclose(infile);

    return 0; 
}
