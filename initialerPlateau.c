#include <stdio.h>
#include "plateau.h"
#define CASE 9
void initialiserPlateau(char plateau[CASE][CASE]) {
    for (int i = 0; i < CASE; i++) {
        for (int j = 0; j < CASE; j++) {
            plateau[i][j] = ' ';
        }
    }
}