#include <stdio.h>
#include "plateau.h"
#define CASE 9
void initialiserPlateau(char plateau[CASE][CASE]) {
    int i=0;
    while (i<=CASE){
        int j=0;
        while (j<=CASE) {
            j++;
            plateau[i][j] = ' ';
        }
        i++;
    }
}
