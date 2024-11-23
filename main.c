#include <stdbool.h>
#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include "plateau.h"
#include <windows.h>
#include "Mode2joueurs.h"

void clear() {
#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
    }

    int main(void) {
        setvbuf(stdout, NULL, _IOFBF,0);
        int choixMenu;
        char plateau[CASE][CASE]={ {' '} };

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

            while(choixMenu<0 || choixMenu>4);
            switch (choixMenu) {
                case 0: return 0;

                //Lancer le jeu
                case 1:
                    printf("Vous voulez jouer a 2 ou 4 joueurs ?\n");
                    int nbrJoueurs;
                    scanf("%d", &nbrJoueurs);
                    if (nbrJoueurs==2) {
                        clear();
                        initialiserPlateau(plateau);
                        Mode2joueurs(plateau);
                    }
                break;
                case 2:
                    break;
                case 3:aide();
                break;
                case 4:
                    break;
            }

        return 0;
    }
