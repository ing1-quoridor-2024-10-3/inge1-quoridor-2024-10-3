#include <stdbool.h>
#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include "plateau.h"

void clear() {
#ifdef _WIN32
    system("cls");

#else

#endif
}
int main(void) {
    int choixMenu;
    char plateau[CASE][CASE];
    while (true) {
        do {
            printf("\n");
            printf("  #     #  #####  #     #  #     #\n");
            printf("  ##   ##  #      ##    #  #     #\n");
            printf("  # # # #  #####  # #   #  #     #\n");
            printf("  #  #  #  #      #  #  #  #     #\n");
            printf("  #     #  #####  #     #   ##### \n");
            printf("\n");
            printf("1. Lancer une nouvelle partie      \n");
            printf("2. Reprendre une partie sauvegardee\n");
            printf("3. Afficher l aide                 \n");
            printf("4. Afficher les scores des joueurs \n");
            printf("5. Quitter le jeu                  \n");

            scanf("%d", &choixMenu);

            if (choixMenu<0 || choixMenu>4)
                printf("Erreur\n");
        }while(choixMenu<0 || choixMenu>4);
        int a = 550;
        switch (choixMenu) {
            case 0: return 0;
            case 1: initialiserPlateau(plateau);
            break;
            case 2:
                break;
            case 3:aide();
            break;
            case 4:
                break;
            case 5:
                break;

        }
    }
}
