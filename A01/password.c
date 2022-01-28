#include <stdio.h>
#include <string.h>

int main() {
    char password[128];
    printf("Enter a word: ");
    scanf("%s", password); // user input
    
    for(int i = 0; i <= strlen(password); i++) {
  	if (password[i] == 'e') {
		password[i] = '3';
	} else if (password[i] == 'l') {
        	password[i] = '1';        
        } else if (password[i] == 'a') {
        	password[i] = '@';        
        }
    }
    
    printf("Your bad password is %s\n", password);
    return 0;
}
