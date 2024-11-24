#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include "plateau.h"      // Source : fichier plateau.h pour les fonctions de gestion du plateau
#include "Mode2joueurs.h" // Source : fichier Mode2joueurs.h pour les fonctions utilitaires comme gotoligcol

#define CASE 9 // Taille de la grille

// Fonction pour afficher les informations d'un joueur
// Source : creation basee sur le concept d'affichage structurant des donnees d'un joueur
void afficherInfoJoueur4(int ligneBase, char *nom, int score, char pion, int nbBarriere) {
    gotoligcol(ligneBase, 60); // Affiche le nom du joueur
    printf("Nom: %s", nom);
    gotoligcol(ligneBase + 1, 60); // Affiche le score du joueur
    printf("Score: %d", score);
    gotoligcol(ligneBase + 2, 60); // Affiche le pion choisi par le joueur
    printf("Pion: %c", pion);
    gotoligcol(ligneBase + 3, 60); // Affiche le nombre de barrieres restantes
    printf("Barrieres restantes: %d", nbBarriere);
}

// Fonction principale pour le mode 4 joueurs
// Source : implemente les regles de base du jeu en mode 4 joueurs
void Mode4joueurs() {
    char plateau[CASE][CASE];
    initialiserPlateau(plateau); // Source : utilise la fonction initialiserPlateau pour configurer le tableau

    printf("Nouvelle partie a 4 joueurs demarree !\n");

    // Definition des variables pour les joueurs
    char prenoms[4][50]; // Noms des joueurs
    char jetons[4];      // Pions des joueurs
    int barrieres[4] = {10, 10, 10, 10}; // Nombre de barrieres pour chaque joueur
    int scores[4] = {0, 0, 0, 0};        // Scores des joueurs

    // Demander les noms des joueurs
    // Source : boucle d'interaction utilisateur avec verification basique
    for (int i = 0; i < 4; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%49s", prenoms[i]);
    }

    // Choisir les pions des joueurs
    // Source : gestion d'unicite des pions a partir d'une validation par boucle
    for (int i = 0; i < 4; i++) {
        bool pionValide;
        do {
            pionValide = true;
            printf("Joueur %d (%s), choisis ton pion : ", i + 1, prenoms[i]);
            scanf(" %c", &jetons[i]);

            // Verifier que les pions sont uniques
            for (int j = 0; j < i; j++) {
                if (jetons[i] == jetons[j]) {
                    printf("Les pions doivent etre differents !\n");
                    pionValide = false;
                    break;
                }
            }
        } while (!pionValide);
    }

    // Initialisation des positions des joueurs
    // Source : choix arbitraire de positions initiales sur un plateau de taille 9x9
    int positions[4][2] = {{0, 4}, {8, 4}, {4, 0}, {4, 8}};
    for (int i = 0; i < 4; i++) {
        plateau[positions[i][0]][positions[i][1]] = jetons[i];
    }

    bool partieEnCours = true;
    int joueurActuel = 0; // Debut avec le joueur 1

    // Boucle principale du jeu
    // Source : implemente les tours de jeu selon une logique simple de rotation des joueurs
    while (partieEnCours) {
        system("cls"); // Nettoyer l'ecran

        // Afficher le plateau de jeu
        // Source : affiche un tableau a deux dimensions representant le plateau
        afficherPlateau(plateau);

        // Afficher les informations de chaque joueur
        for (int i = 0; i < 4; i++) {
            afficherInfoJoueur4(5 + i * 5, prenoms[i], scores[i], jetons[i], barrieres[i]);
        }

        // Instructions pour le joueur actuel
        gotoligcol(6 + CASE * 2 + 2, 5);
        printf("A toi de jouer, %s !\n", prenoms[joueurActuel]);
        printf("\n1) Deplacer ton pion.\n2) Poser une barriere.\n3) Quitter la partie.\n");
        int action;
        scanf("%d", &action);

        if (action == 3) { // Quitter la partie
            partieEnCours = false;
            printf("\nFin de la partie.\n");
            break;
        }

        if (action == 1) { // Deplacement du pion
            printf("\n1) Avancer\n2) Aller a gauche\n3) Aller a droite\n4) Reculer\n");
            int deplacement;
            scanf("%d", &deplacement);

            int x = positions[joueurActuel][0];
            int y = positions[joueurActuel][1];
            plateau[x][y] = ' '; // Effacer l'ancienne position

            // Deplacer selon les directions
            if (deplacement == 1 && x < CASE - 1) x++;       // Avancer
            else if (deplacement == 2 && y > 0) y--;         // Aller a gauche
            else if (deplacement == 3 && y < CASE - 1) y++;  // Aller a droite
            else if (deplacement == 4 && x > 0) x--;         // Reculer

            // Verifier que la case est libre
            if (plateau[x][y] == ' ') {
                positions[joueurActuel][0] = x;
                positions[joueurActuel][1] = y;
                plateau[x][y] = jetons[joueurActuel];
            } else {
                printf("Deplacement invalide !\n");
            }
        } else if (action == 2) { // Poser une barriere
            printf("\nEntrez la position de la barriere (ligne colonne) : ");
            int ligne, colonne;
            scanf("%d %d", &ligne, &colonne);

            // Convertir les coordonnees en indices de tableau
            ligne--;
            colonne--;

            // Verifier que la position est valide
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
