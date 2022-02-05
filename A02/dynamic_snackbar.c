#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define struct snack
struct snack {
    char name[128];
    float cost;
    int quantity;
};

int main() {
    char name[128]; 
    float cost; 
    int quantity; 
    int number_of_snacks; 

    printf("Enter a number of snacks: ");
    scanf("%d", &number_of_snacks); 

    struct snack* snack_bar = malloc(sizeof(struct snack) * number_of_snacks); 

    if (snack_bar == NULL) { 
        printf("Cannot allocate new array. Exiting..."); 
        exit(1);
    } else { 
        for (int i = 0; i < number_of_snacks; i++) { 
            struct snack current_snack;
            
            printf("Enter a name: "); 
            scanf("%s", name); 

            printf("Enter a cost: ");
            scanf("%f", &cost);  

            printf("Enter a quantity: "); 
            scanf("%i", &quantity); 

            strcpy(current_snack.name, name); 
            current_snack.cost = cost; 
            current_snack.quantity = quantity; 
            snack_bar[i] = current_snack; 
        }

        printf("\nWelcome to Mai Anh's Snack Bar.\n\n"); 
        
        for (int i = 0; i < number_of_snacks; i++) { 
            printf("%d) %s\t cost: $%.2f \t quantity: %d \n", i, snack_bar[i].name, snack_bar[i].cost, snack_bar[i].quantity); 
        }
    }

    free(snack_bar); 

    snack_bar = NULL; 
    return 0;
}
