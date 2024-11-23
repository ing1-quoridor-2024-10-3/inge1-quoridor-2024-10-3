#include <stdio.h>
#include <windows.h>
#include "plateau.h"

void afficherPlateau(char plateau[CASE][CASE]) {
    short tab[9] = {'A','B','C','D','E','F','G','H','I'};
    printf("   ");
    for (int i = 0; i < 9; i++) printf(" %c  ", tab[i]);
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("  +---+---+---+---+---+---+---+---+---+\n");
        printf("%d ", i + 1); // Numéro des lignes
        for (int j = 0; j < 9; j++) {
            printf("| %c ", plateau[i][j]);
        }
        printf("|\n");
    }
    printf("  +---+---+---+---+---+---+---+---+---+\n");
}

