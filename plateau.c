#include <stdio.h>
#include <stdlib.h>
#define CASE 9

void initialiserPlateau(char plateau[CASE][CASE]) {
    system("cls");
    int i=0;
    while (i<=CASE){
        int j=0;
        while (j<=CASE) {
            j++;
            plateau[i][j] = '.';
        }
        i++;
    }
    printf("    ");
    for (int i = 0; i < 9; i++) printf("%d   ", i + 1);
    printf("\n");

    for (int i = 0; i < 9; i++) {
        printf("  +---+---+---+---+---+---+---+---+---+\n");
        printf("%d ", i + 1);
        for (int j = 0; j < 9; j++) {
            printf("| %c ", plateau[i][j]);
        }
        printf("|\n");
    }
    printf("  +---+---+---+---+---+---+---+---+---+\n");
}
