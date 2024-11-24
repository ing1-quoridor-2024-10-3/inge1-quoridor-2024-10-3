
#include <stdio.h>
#include <windows.h>
#include "plateau.h"
#include "Mode2joueurs.h"
void afficherPlateau(char plateau[CASE][CASE]) {
    gotoligcol(5, 5); // Position du plateau à gauche
    printf("   ");
    for (char col = 'A'; col < 'A' + CASE; col++) {
        printf(" %c  ", col);
    }
    printf("\n");

    for (int i = 0; i < CASE; i++) {
        gotoligcol(6 + i * 2, 5); // Barres horizontales
        printf("  +---+---+---+---+---+---+---+---+---+\n");
        gotoligcol(7 + i * 2, 5); // Contenu des cases
        printf("%d ", i + 1); // Numéro des lignes
        for (int j = 0; j < CASE; j++) {
            printf("| %c ", plateau[i][j]);
        }
        printf("|\n");
    }
}