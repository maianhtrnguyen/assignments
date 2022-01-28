#include <stdio.h>
#include <string.h>

// define struct snack
struct snack {
    char name[128];
    float cost;
    int quantity;
};

int main() {
    // define three snacks and store them in an array
    struct snack snackBar[3] = {{"Oolong bubble tea", 1.50, 4}, {"Matcha mousse", 15.5, 6}, {"Blueberry bagel", 0.5, 0}};
    float money;
    int snackOption;
    printf("Welcome to Mai Anh Nguyen's Snack Bar.\n\n");
    printf("How much money do you have? ");
    scanf("%f", &money); // user input
    printf("\n");  

    // print out the menu
    for (int i = 0; i < 3; i++) {
  	printf("%d) %s\t cost: $%.2f \t quantity: %d \n", i, snackBar[i].name, snackBar[i].cost, snackBar[i].quantity);
    }

    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &snackOption);

    // handle requests
    if (money < snackBar[snackOption].cost) {
        printf("You can't afford it!\n");
    } else {
    	if (snackBar[snackOption].quantity == 0) {
            printf("Sorry, we are out of %s\n", snackBar[snackOption].name);
        } else {
            printf("You bought %s \nYou have $%.2f left\n", snackBar[snackOption].name, money - snackBar[snackOption].cost);
       	}
    }

    return 0;
}
