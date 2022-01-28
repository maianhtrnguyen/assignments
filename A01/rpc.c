#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* This function returns -1 if AI wins, returns 1 if Human wins, or returns 0 if there is a tie
* @param: AI corresponds to AI's choice, and human corresponds to human's choice (either rock, paper, or scissors)
*/
int play(const char* AI, const char* human) {
    if (strcmp(AI, human) == 0) {
        // if both AI and human both make a same choice
        return 0;
    } 

    if (strcmp(AI, "rock") == 0) {
        if (strcmp(AI, human) < 0) {
            // human makes "scissors"
            return -1; // AI wins
        } else {
            // human makes "paper"
            return 1; // Human wins
        }
    } else if (strcmp(AI, "paper") == 0) {
        if (strcmp(human, "rock") == 0) {
            return -1; // AI wins
        } else {
            // human makes "scissors"
            return 1; // Human wins
        }
    } else {
        // AI makes "scissors"
        if (strcmp(human, "paper") == 0) {
            return -1; // AI wins
        } else {
            // human makes "rock"
            return 1; // Human wins
        }
    }
};

// This function converts random number 0, 1, and 2 to "rock", "paper", "scissors" respectively
const char* number_to_name(int random_number) {
    if (random_number == 0) {
        return "rock";
    } else if (random_number == 1) {
        return "paper";
    } 
    return "scissors";
};

// This function returns the rule based on 2 choices made by AI and human
const char* result_based_on_rules(const char* AI, const char* human) {
    if ((strcmp(AI, "rock") == 0 && strcmp(human, "paper") == 0)
        || (strcmp(AI, "paper") == 0 && strcmp(human, "rock") == 0)) {
        return "Paper covers rock\n";
    } else if ((strcmp(AI, "rock") == 0 && strcmp(human, "scissors") == 0)
        || (strcmp(AI, "scissors") == 0 && strcmp(human, "rock") == 0)) {
        return "Rock bashes scissors\n";
    } else {
        return "Scissors cut paper\n";
    }
};

int main() {
    int round;
    char human_choice[128];
    int AI_score = 0;
    int human_score = 0;

    printf("Welcome to Rock, Paper, Scissors!\n");
    printf("How many rounds do you want to play? ");
    scanf("%d", &round);  
    printf("\n");

    // go over each round
    for (int i = 0; i < round; i++) {
        printf("Which do you choose? rock, paper, or scissors? ");
        scanf("%s", human_choice);
        srand(time(0));
        int AI_number = rand() % 3; // get random number from 0 to 2
        const char * AI_choice = number_to_name(AI_number); // convert random number to string choice
        printf("AI chose %s\n", AI_choice);

        if (strcmp(human_choice, "rock") != 0 && strcmp(human_choice, "paper") != 0 && strcmp(human_choice, "scissors") != 0) {
            // if the user input is invalid
            printf("You entered an invalid choice: %s\n", human_choice);
        } else {
            int result = play(AI_choice, human_choice); // play the game

            if (result != 0) {
                const char* rule = result_based_on_rules(AI_choice, human_choice); 
                printf("%s", rule); // print out the rule

                // update scores of AI and human
                if (result == -1) {
                    AI_score += 1; 
                } else if (result == 1) {
                    human_score += 1;
                }
            }

        }

        printf("AI score: %d, Player score: %d\n\n", AI_score, human_score);
    }

    // print out the result
    if (AI_score > human_score) {
        printf("AI wins\n");
    } else if (AI_score < human_score) {
        printf("Player wins\n");
    } else {
        printf("Tie\n");
    }

    return 0;

}
