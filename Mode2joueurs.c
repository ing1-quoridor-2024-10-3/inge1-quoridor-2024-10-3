#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <windows.h>
#include <stdbool.h>
#define CASE 9

void gotoligcol(int lig, int col) {
    // ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void afficherInfoJoueur(int ligneBase, char *nom, int score, char pion, int nbBarriere) {
    gotoligcol(ligneBase, 60); // Positionner à droite du plateau
    printf("Nom: %s", nom);
    gotoligcol(ligneBase + 1, 60);
    printf("Score: %d", score);
    gotoligcol(ligneBase + 2, 60);
    printf("Pion: %c", pion);
    gotoligcol(ligneBase + 3, 60);
    printf("Barrieres: %d", nbBarriere);
}

void Mode2joueurs() {
    char plateau[CASE][CASE];
    initialiserPlateau(plateau);

    // Configuration des joueurs
    printf("Nouvelle partie demarree !\n");
    printf("Nom du premier joueur : ");
    char prenomUn[50];
    scanf("%49s", prenomUn);
    printf("Nom du deuxieme joueur : ");
    char prenomDeux[50];
    scanf("%49s", prenomDeux);

    // Choisir les pions
    char jetonUn, jetonDeux;
    do {
        printf("Joueur 1 (%s), choisis ton pion : ", prenomUn);
        scanf(" %c", &jetonUn); // Le " " avant %c est important pour ignorer le '\n' restant dans le buffer
        printf("Joueur 2 (%s), choisis ton pion : ", prenomDeux);
        scanf(" %c", &jetonDeux);

        if (jetonUn == jetonDeux) {
            printf("Les deux joueurs doivent avoir des pions différents !\n");
        }
    } while (jetonUn == jetonDeux); // Assurez-vous que les pions sont différents

    int barriereUn = 10, barriereDeux = 10;
    int scoreUn = 0, scoreDeux = 0;
    bool partieEnCours = true, joueurUnFlag = true;

    int x1 = 0, y1 = 3; // Position initiale du joueur 1
    int x2 = 8, y2 = 4; // Position initiale du joueur 2

    plateau[x1][y1] = jetonUn;
    plateau[x2][y2] = jetonDeux;

    while (partieEnCours) {
        system("cls"); // Nettoyer l'écran

        // Afficher le plateau
        afficherPlateau(plateau);

        // Afficher les informations des joueurs
        afficherInfoJoueur(5, prenomUn, scoreUn, jetonUn, barriereUn);
        afficherInfoJoueur(12, prenomDeux, scoreDeux, jetonDeux, barriereDeux);

        // Afficher les instructions sous le plateau
        gotoligcol(6 + CASE * 2 + 2, 5);
        if (joueurUnFlag) {
            printf("A toi de jouer, %s !\n", prenomUn);
        } else {
            printf("A toi de jouer, %s !\n", prenomDeux);
        }

        printf("\n1) Deplacer son pion.\n2) Poser une barriere.\n3) Quitter.\n");
        int action;
        scanf("%d", &action);

        if (action == 3) { // Quitter
            partieEnCours = false;
            printf("\nFin de la partie.\n");
            break;
        }

        if (action == 1) { // Déplacement
            printf("\n1) Avancer\n2) Aller à gauche\n3) Aller à droite\n4) Reculer\n");
            int deplacement;
            scanf("%d", &deplacement);

            if (joueurUnFlag) {
                // Le jeton 1 (Joueur 1) doit descendre d'une case (se déplacer vers le bas)
                if (deplacement == 1 && x1 < CASE - 1) { plateau[x1][y1] = ' '; x1++; plateau[x1][y1] = jetonUn; }  // Descente vers le bas (ligne)
                else if (deplacement == 2 && y1 < CASE - 1) { plateau[x1][y1] = ' '; y1++; plateau[x1][y1] = jetonUn; }  // Descente vers la droite (colonne)
                else if (deplacement == 3 && y1 > 0) { plateau[x1][y1] = ' '; y1--; plateau[x1][y1] = jetonUn; }  // Montée vers la gauche (colonne)
                else if (deplacement == 4 && x1 > 0) { plateau[x1][y1] = ' '; x1--; plateau[x1][y1] = jetonUn; }  // Montée vers le haut (ligne)
            } else {
                // Le jeton 2 (Joueur 2) doit monter d'une case (se déplacer vers le haut)
                if (deplacement == 1 && x2 > 0) { plateau[x2][y2] = ' '; x2--; plateau[x2][y2] = jetonDeux; }  // Montée vers le haut (ligne)
                else if (deplacement == 2 && y2 > 0) { plateau[x2][y2] = ' '; y2--; plateau[x2][y2] = jetonDeux; }  // Montée vers la gauche (colonne)
                else if (deplacement == 3 && y2 < CASE - 1) { plateau[x2][y2] = ' '; y2++; plateau[x2][y2] = jetonDeux; }  // Descente vers la droite (colonne)
                else if (deplacement == 4 && x2 < CASE - 1) { plateau[x2][y2] = ' '; x2++; plateau[x2][y2] = jetonDeux; }  // Descente vers le bas (ligne)
            }
        } else if (action == 2) { // Pose de barrière
            printf("\nEntrez la position de la barriere (ligne colonne) : ");
            int ligne, colonne;
            scanf("%d %d", &ligne, &colonne);

            // Ajustement pour indices (base 1 vers base 0)
            ligne--;
            colonne--;

            if (ligne >= 0 && ligne < CASE && colonne >= 0 && colonne < CASE && plateau[ligne][colonne] == ' ') {
                plateau[ligne][colonne] = '@';
                if (joueurUnFlag) barriereUn--;
                else barriereDeux--;
            } else {
                printf("\nPosition invalide !\n");
            }
        }

        joueurUnFlag = !joueurUnFlag; // Changer de joueur
    }
}

