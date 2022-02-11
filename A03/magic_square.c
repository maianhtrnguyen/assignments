//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Mai Anh Nguyen
//
#include <stdio.h>
#include <stdlib.h>

int checkForMagicSquare(int** magic_square, int row, int column) {
    // go over each row
    int diagonal_sum_1 = 0;
    int diagonal_sum_2 = 0;

    for (int i = 0; i < row; i++) {
        diagonal_sum_1 += magic_square[i][i];
        diagonal_sum_2 += magic_square[i][row-i-1];
    }

    if (diagonal_sum_1 != diagonal_sum_2) {
        return 0;
    }

    for (int i = 0; i < row; i++) {
        int row_sum = 0;
        int column_sum = 0;
        for (int j = 0; j < column; j++) {
            row_sum += magic_square[i][j];
            column_sum += magic_square[j][i];
        }
        if (row_sum != column_sum || row_sum != diagonal_sum_1) {
            return 0;
        }
    }

    return diagonal_sum_1;
}

int main() {
    int row;
    int column;
    int num;
    int** magic_square;

    scanf("%d %d", &row, &column);

    magic_square = malloc(sizeof(int*) * row);

    if (magic_square == NULL) {
        printf("Cannot allocate new memory. Exitting ....");
        exit(1);
    }

    for (int i = 0; i < row; i++) {
        magic_square[i] = malloc(sizeof(int*) * column);
        if (magic_square[i] == NULL) {
            printf("Cannot allocate new memory. Exitting ....");
            exit(1);
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            scanf(" %d", &magic_square[i][j]);
        }
    }

    // print matrix
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d \t", magic_square[i][j]);
        }
        printf("\n");
    }

    // check for magic square
    int result = checkForMagicSquare(magic_square, row, column);

    if (result == 0) {
        printf("M is NOT a magic square!\n");
    } else {
        printf("M is a magic square (magic constant = %d)\n", result);
    }


    for (int i = 0; i < row; i++) {
        free(magic_square[i]);
        magic_square[i] = NULL;
    }

    free(magic_square);
    magic_square = NULL;
    return 0;
}


