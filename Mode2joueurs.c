#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pour le tirage aléatoire
#include <stdbool.h>
#include "plateau.h"
#include "scores.h"
#include "barriere.h"
#include <windows.h>

// Fonction pour positionner le curseur dans la console
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

// Fonction pour afficher les informations des joueurs
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
// Fonction pour poser une barrière sur le plateau étendu
void poserBarriere(char plateau[2 * CASE + 1][2 * CASE + 1], char orientation, int ligne, int colonne) {
    ligne = 2 * (ligne - 1);   // Convertir en coordonnées de la grille étendue
    colonne = 2 * (colonne - 1);

    if (orientation == 'H') { // Barrière horizontale
        if (ligne >= 0 && ligne < 2 * CASE && colonne >= 0 && colonne < 2 * CASE) {
            if (plateau[ligne + 1][colonne] == ' ' && plateau[ligne + 1][colonne + 2] == ' ') {
                plateau[ligne + 1][colonne + 1] = '@'; // Barrière au milieu
                plateau[ligne + 1][colonne + 2] = '@'; // Barrière droite
                plateau[ligne + 1][colonne] = '@';     // Barrière gauche
                printf("Barrière horizontale placée avec succès !\n");
            } else {
                printf("Position invalide pour une barrière horizontale (déjà occupée) !\n");
            }
        } else {
            printf("Position hors des limites pour une barrière horizontale !\n");
        }
    } else if (orientation == 'V') { // Barrière verticale
        if (ligne >= 0 && ligne < 2 * CASE && colonne >= 0 && colonne < 2 * CASE) {
            if (plateau[ligne][colonne + 1] == ' ' && plateau[ligne + 2][colonne + 1] == ' ') {
                plateau[ligne + 1][colonne + 1] = '@'; // Barrière centrale
                plateau[ligne + 2][colonne + 1] = '@'; // Barrière inférieure
                plateau[ligne][colonne + 1] = '@';     // Barrière supérieure
                printf("Barrière verticale placée avec succès !\n");
            } else {
                printf("Position invalide pour une barrière verticale (déjà occupée) !\n");
            }
        } else {
            printf("Position hors des limites pour une barrière verticale !\n");
        }
    } else {
        printf("Orientation invalide ! Utilisez 'H' pour horizontale ou 'V' pour verticale.\n");
    }
}
// Fonction pour choisir un joueur au hasard
int choisirPremierJoueur(int nbJoueurs) {
    srand(time(NULL)); // Initialiser le générateur aléatoire
    return rand() % nbJoueurs; // Retourne un nombre entre 0 et nbJoueurs - 1
}

// Fonction de vérification de victoire
int verifierVictoire(int x1, int x2) {
    if (x1 == CASE - 1) return 1; // Joueur 1 a gagné
    if (x2 == 0) return 2;        // Joueur 2 a gagné
    return 0;                     // Aucun joueur n'a encore gagné
}

void Mode2joueurs() {
    char plateau[CASE][CASE];
    initialiserPlateau(plateau);

    // Configuration des joueurs
    printf("Nouvelle partie démarrée !\n");
    printf("Nom du premier joueur : ");
    char prenomUn[50];
    scanf("%49s", prenomUn);
    printf("Nom du deuxième joueur : ");
    char prenomDeux[50];
    scanf("%49s", prenomDeux);

    // Choisir le joueur qui commence
    int premierJoueur = choisirPremierJoueur(2); // 2 joueurs
    printf("\nLe joueur qui commence est : %s\n", premierJoueur == 0 ? prenomUn : prenomDeux);
    bool joueurUnFlag = (premierJoueur == 0); // Définit le premier joueur

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
    } while (jetonUn == jetonDeux);


    int barriereUn = 10, barriereDeux = 10;
    int scoreUn = 0, scoreDeux = 0; // Initialisation des scores

    int x1 = 0, y1 = 4; // Position initiale du joueur 1
    int x2 = 8, y2 = 4; // Position initiale du joueur 2

    plateau[x1][y1] = jetonUn;
    plateau[x2][y2] = jetonDeux;

    bool partieEnCours = true;

    while (partieEnCours) {
        system("cls"); // Nettoyer l'écran

        // Afficher le plateau
        afficherPlateau(plateau);

        // Afficher les informations des joueurs
        afficherInfoJoueur(5, prenomUn, scoreUn, jetonUn, barriereUn);
        afficherInfoJoueur(12, prenomDeux, scoreDeux, jetonDeux, barriereDeux);

        // Afficher les instructions sous le plateau
        gotoligcol(20 + CASE, 5); // Placer les commandes sous le plateau (ligne 10 + taille du plateau)
        printf("A toi de jouer, %s !\n", joueurUnFlag ? prenomUn : prenomDeux);
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

            if (joueurUnFlag) { // Joueur 1
                if (deplacement == 1 && x1 < CASE - 1) { plateau[x1][y1] = ' '; x1++; plateau[x1][y1] = jetonUn; }
                else if (deplacement == 2 && y1 > 0) { plateau[x1][y1] = ' '; y1--; plateau[x1][y1] = jetonUn; }
                else if (deplacement == 3 && y1 < CASE - 1) { plateau[x1][y1] = ' '; y1++; plateau[x1][y1] = jetonUn; }
                else if (deplacement == 4 && x1 > 0) { plateau[x1][y1] = ' '; x1--; plateau[x1][y1] = jetonUn; }
            } else { // Joueur 2
                if (deplacement == 1 && x2 > 0) { plateau[x2][y2] = ' '; x2--; plateau[x2][y2] = jetonDeux; }
                else if (deplacement == 2 && y2 > 0) { plateau[x2][y2] = ' '; y2--; plateau[x2][y2] = jetonDeux; }
                else if (deplacement == 3 && y2 < CASE - 1) { plateau[x2][y2] = ' '; y2++; plateau[x2][y2] = jetonDeux; }
                else if (deplacement == 4 && x2 < CASE - 1) { plateau[x2][y2] = ' '; x2++; plateau[x2][y2] = jetonDeux; }
            }

            // Vérification de victoire
            int gagnant = verifierVictoire(x1, x2);
            if (gagnant == 1) {
                calculScore(&scoreUn, &scoreDeux, prenomUn, prenomDeux); // Mise à jour des scores
                printf("\n%s a gagné !\n", prenomUn);
                partieEnCours = false;
            } else if (gagnant == 2) {
                calculScore(&scoreUn, &scoreDeux, prenomDeux, prenomUn); // Mise à jour des scores
                printf("\n%s a gagné !\n", prenomDeux);
                partieEnCours = false;
            }
        } // Fonction pour poser une barrière entre deux cases
else if (action == 2) { // Pose de barrière
    printf("\nEntrez la ligne (1 à %d) et la colonne (1 à %d) de la première case de la barrière : ", CASE, CASE);
    int ligne, colonne;
    scanf("%d %d", &ligne, &colonne);

    // Convertir les entrées pour les adapter aux indices 0-based
    ligne--;
    colonne--;

    if (ligne >= 0 && ligne < CASE && colonne >= 0 && colonne < CASE) {
        printf("\nChoisis la direction de la barrière (1 pour horizontale, 2 pour verticale) : ");
        int direction;
        scanf("%d", &direction);

        if (direction == 1) { // Barrière horizontale
            // Vérification si la position est valide pour une barrière horizontale
            if (colonne < CASE - 1 && plateau[ligne][colonne] == ' ' && plateau[ligne][colonne + 1] == ' ') {
                plateau[ligne][colonne] = 'b';       // Remplacer le côté gauche de la case par une barrière
                plateau[ligne][colonne + 1] = 'b';   // Remplacer le côté droit de la case par une barrière

                // Décrémenter le nombre de barrières restantes
                if (joueurUnFlag) barriereUn--;
                else barriereDeux--;

                printf("\nBarrière horizontale posée entre (%d,%d) et (%d,%d) !\n", ligne + 1, colonne + 1, ligne + 1, colonne + 2);
            } else {
                printf("\nLes cases sont occupées ou la position est invalide pour une barrière horizontale.\n");
            }
        } else if (direction == 2) { // Barrière verticale
            // Vérification si la position est valide pour une barrière verticale
            if (ligne < CASE - 1 && plateau[ligne][colonne] == ' ' && plateau[ligne + 1][colonne] == ' ') {
                plateau[ligne][colonne] = 'b';       // Remplacer le côté supérieur de la case par une barrière
                plateau[ligne + 1][colonne] = 'b';   // Remplacer le côté inférieur de la case par une barrière

                // Décrémenter le nombre de barrières restantes
                if (joueurUnFlag) barriereUn--;
                else barriereDeux--;

                printf("\nBarrière verticale posée entre (%d,%d) et (%d,%d) !\n", ligne + 1, colonne + 1, ligne + 2, colonne + 1);
            } else {
                printf("\nLes cases sont occupées ou la position est invalide pour une barrière verticale.\n");
            }
        } else {
            printf("\nDirection invalide ! Choisis 1 pour horizontale ou 2 pour verticale.\n");
        }
    } else {
        printf("\nPosition invalide !\n");
    }
}

        joueurUnFlag = !joueurUnFlag; // Passer au joueur suivant
    }
}