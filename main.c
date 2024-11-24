#include <stdbool.h>
#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include "plateau.h"
#include <windows.h>
#include "Mode2joueurs.h"
#include "scores.h"

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

    initialisationFichierScores(); // Créer ou vérifier le fichier des scores

    info_joueurs tableau_scores[JOUEURS_MAX];
    int nbJoueursTotal = 0; // Initialiser à zéro avant de l'utiliser

    lireScores(tableau_scores, &nbJoueursTotal); // Charger les scores

    // Afficher les scores actuels avant toute modification
    printf("Scores actuels avant mise a jour :\n");
    affichageScores(tableau_scores, nbJoueursTotal);

    // Mise à jour des scores : demander à l'utilisateur d'entrer un nom et un score
    char nom[TAILLE_MAX_NOM]; // Tableau pour stocker le nom du joueur
    int score; // Variable pour le score du joueur

    printf("\nEntrez le nom du joueur : ");
    scanf("%s", nom); // Demande à l'utilisateur de saisir un nom

    printf("Entrez le score de %s : ", nom);
    scanf("%d", &score); // Demande à l'utilisateur de saisir un score

    // Ajouter ou mettre à jour le score pour ce joueur
    miseAJour_scores(tableau_scores, &nbJoueursTotal, nom, score);

    // Afficher les scores après la mise à jour
    printf("\nScores apres mise a jour :\n");
    affichageScores(tableau_scores, nbJoueursTotal);

    // Sauvegarder les scores dans le fichier
    sauvegarderScores(tableau_scores, nbJoueursTotal);


    //plateau
    Plateau plateau;
    // Initialiser le plateau avec des cases vides ('.')
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            plateau.plateau[i][j] = '.'; // Toutes les cases sont vides au départ
        }
    }
    plateau.nbBarrieres = 0; // Aucun mur au départ

    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Sauvegarder le plateau\n");
        printf("2. Charger un plateau sauvegarde\n");
        printf("3. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                sauvegarderPlateau(&plateau);
            break;

            case 2:
                chargerPlateau(&plateau); // Charger un plateau sauvegardé
                afficherPlateau(&plateau); // Afficher le plateau pour vérifier
            break;
            case 3:
                printf("Au revoir !\n");
            break;
            default:
                printf("Choix invalide. Essayez encore.\n");
        }
    } while (choix != 3);

    return 0;
}
