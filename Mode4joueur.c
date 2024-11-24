#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <windows.h>
#include <stdbool.h>
#define CASE 9
#include "Mode2joueurs.h"


void afficherInfoJoueur4(int ligneBase, char *nom, int score, char pion, int nbBarriere) {
    gotoligcol(ligneBase, 60);
    printf("Nom: %s", nom);
    gotoligcol(ligneBase + 1, 60);
    printf("Score: %d", score);
    gotoligcol(ligneBase + 2, 60);
    printf("Pion: %c", pion);
    gotoligcol(ligneBase + 3, 60);
    printf("Barrieres: %d", nbBarriere);
}

void Mode4joueurs() {
    char plateau[CASE][CASE];
    initialiserPlateau(plateau);

    // Configuration des joueurs
    printf("Nouvelle partie 4 joueurs demarree !\n");
    char prenoms[4][50];
    char jetons[4];
    int barrieres[4] = {10, 10, 10, 10};
    int scores[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%49s", prenoms[i]);
    }

    // Choisir les pions
    for (int i = 0; i < 4; i++) {
        bool pionValide;
        do {
            pionValide = true;
            printf("Joueur %d (%s), choisis ton pion : ", i + 1, prenoms[i]);
            scanf(" %c", &jetons[i]);

            for (int j = 0; j < i; j++) {
                if (jetons[i] == jetons[j]) {
                    printf("Les pions doivent etre differents !\n");
                    pionValide = false;
                    break;
                }
            }
        } while (!pionValide);
    }

    // Initialisation des positions
    int positions[4][2] = {{0, 4}, {8, 4}, {4, 0}, {4, 8}};
    for (int i = 0; i < 4; i++) {
        plateau[positions[i][0]][positions[i][1]] = jetons[i];
    }

    bool partieEnCours = true;
    int joueurActuel = 0;

    while (partieEnCours) {
        system("cls"); // Nettoyer l'ecran

        // Afficher le plateau
        afficherPlateau(plateau);

        // Afficher les informations des joueurs
        for (int i = 0; i < 4; i++) {
            afficherInfoJoueur4(5 + i * 5, prenoms[i], scores[i], jetons[i], barrieres[i]);
        }

        // Instructions pour le joueur actuel
        gotoligcol(6 + CASE * 2 + 2, 5);
        printf("A toi de jouer, %s !\n", prenoms[joueurActuel]);
        printf("\n1) Deplacer son pion.\n2) Poser une barriere.\n3) Quitter.\n");
        int action;
        scanf("%d", &action);

        if (action == 3) {
            partieEnCours = false;
            printf("\nFin de la partie.\n");
            break;
        }

        if (action == 1) { // Déplacement
            printf("\n1) Avancer\n2) Aller à gauche\n3) Aller à droite\n4) Reculer\n");
            int deplacement;
            scanf("%d", &deplacement);

            int x = positions[joueurActuel][0];
            int y = positions[joueurActuel][1];
            plateau[x][y] = ' '; // Effacer l'ancienne position

            if (joueurActuel == 0) { // Joueur en haut
                if (deplacement == 1 && x < CASE - 1) x++;       // Avancer = Bas
                else if (deplacement == 2 && y > 0) y--;         // Gauche = Gauche
                else if (deplacement == 3 && y < CASE - 1) y++;  // Droite = Droite
                else if (deplacement == 4 && x > 0) x--;         // Reculer = Haut
            } else if (joueurActuel == 1) { // Joueur en bas
                if (deplacement == 1 && x > 0) x--;              // Avancer = Haut
                else if (deplacement == 2 && y > 0) y--;         // Gauche = Gauche
                else if (deplacement == 3 && y < CASE - 1) y++;  // Droite = Droite
                else if (deplacement == 4 && x < CASE - 1) x++;  // Reculer = Bas
            } else if (joueurActuel == 2) { // Joueur à gauche
                if (deplacement == 1 && y < CASE - 1) y++;       // Avancer = Droite
                else if (deplacement == 2 && x > 0) x--;         // Gauche = Haut
                else if (deplacement == 3 && x < CASE - 1) x++;  // Droite = Bas
                else if (deplacement == 4 && y > 0) y--;         // Reculer = Gauche
            } else if (joueurActuel == 3) { // Joueur à droite
                if (deplacement == 1 && y > 0) y--;              // Avancer = Gauche
                else if (deplacement == 2 && x < CASE - 1) x++;  // Gauche = Bas
                else if (deplacement == 3 && x > 0) x--;         // Droite = Haut
                else if (deplacement == 4 && y < CASE - 1) y++;  // Reculer = Droite
            }

            // Vérification de la validité de la nouvelle position
            if (plateau[x][y] == ' ') {
                positions[joueurActuel][0] = x;
                positions[joueurActuel][1] = y;
                plateau[x][y] = jetons[joueurActuel];
            } else {
                printf("Deplacement invalide !\n");
            }
        } else if (action == 2) { // Pose de barrière
            printf("\nEntrez la position de la barriere (ligne colonne) : ");
            int ligne, colonne;
            scanf("%d %d", &ligne, &colonne);

            ligne--;
            colonne--;

            if (ligne >= 0 && ligne < CASE && colonne >= 0 && colonne < CASE && plateau[ligne][colonne] == ' ') {
                plateau[ligne][colonne] = '@';
                barrieres[joueurActuel]--;
            } else {
                printf("\nPosition invalide !\n");
            }
        }

        joueurActuel = (joueurActuel + 1) % 4; // Passer au joueur suivant
    }
}
