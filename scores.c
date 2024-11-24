#include <stdio.h>
#include <string.h>// Pour gérer les chaînes de caractères
#include "scores.h"


// Fonction pour vérifier/créer le fichier de scores
void initialisationFichierScores() {
    FILE *file = fopen("scores.txt", "a"); // Mode "a" crée le fichier s'il n'existe pas
    if (file == NULL) {
        printf("Erreur : Impossible de creer ou d'ouvrir le fichier scores.txt\n");
    } else {
        printf("Fichier scores.txt pret pour utilisation.\n");
        fclose(file);
    }
}

// Fonction pour charger les scores depuis le fichier
void lireScores(info_joueurs tableau_scores[], int *nbJoueursTotal) {
    FILE *file = fopen("scores.txt", "r");
    *nbJoueursTotal = 0; // Initialiser le nombre de joueurs à zéro
    if (file) {
        while (fscanf(file, "%s %d", tableau_scores[*nbJoueursTotal].nom, &tableau_scores[*nbJoueursTotal].score) == 2) {
            (*nbJoueursTotal)++;
        }
        fclose(file);
        printf("Scores charges depuis le fichier.\n");
    } else {
        printf("Aucun fichier de scores trouve, demarrage avec un tableau vide.\n");
    }
}

// Fonction pour afficher les scores dans la console
void affichageScores(info_joueurs tableau_scores[], int nbJoueursTotal) {
    printf("Liste des scores :\n");
    for (int i = 0; i < nbJoueursTotal; i++) {
        printf("Joueur : %s, Score : %d\n", tableau_scores[i].nom, tableau_scores[i].score);
    }
}

// Fonction pour mettre à jour les scores ou ajouter un nouveau joueur
void miseAJour_scores(info_joueurs tableau_scores[], int *nbJoueursTotal, const char *nom, int points) {
    // Vérifier si le joueur existe déjà
    for (int i = 0; i < *nbJoueursTotal; i++) {
        if (strcmp(tableau_scores[i].nom, nom) == 0) { // Comparer les noms
            tableau_scores[i].score += points; // Ajouter les points
            return; // Fin de la fonction si le joueur est trouvé
        }
    }

    // Vérifier si on a atteint la capacité maximale
    if (*nbJoueursTotal >= JOUEURS_MAX) {
        printf("Impossible d'ajouter un joueur, le tableau est plein.\n");
        return;
    }

    // Si le joueur est nouveau, on l'ajoute
    strcpy(tableau_scores[*nbJoueursTotal].nom, nom); // Copier le nom dans la nouvelle fiche
    tableau_scores[*nbJoueursTotal].score = points; // Attribuer le score au nouveau joueur
    (*nbJoueursTotal)++; // Incrémenter le nombre de joueurs dans le tableau
}

// Fonction pour sauvegarder les scores dans le fichier
void sauvegarderScores(info_joueurs tableau_scores[], int nbJoueursTotal) {
    FILE *file = fopen("scores.txt", "w"); // Ouvre le fichier en mode "write" pour écraser le contenu

    if (file == NULL) {
        printf("Erreur : Impossible de sauvegarder les scores dans le fichier scores.txt\n");
        return;
    }

    // Sauvegarder les scores dans le fichier
    for (int i = 0; i < nbJoueursTotal; i++) {
        fprintf(file, "%s %d\n", tableau_scores[i].nom, tableau_scores[i].score);
    }

    fclose(file); // Fermer le fichier après l'écriture
    printf("Scores sauvegardes dans le fichier scores.txt\n");
}

void sauvegarderPlateau(Plateau *plateau) {
    FILE *file = fopen("plateau.txt", "w"); // Ouvre le fichier en mode écriture

    if (file == NULL) {
        printf("Erreur : Impossible de sauvegarder le plateau.\n");
        return;
    }

    // Sauvegarder la matrice du plateau
    fprintf(file, "Plateau :\n");
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fprintf(file, "%c ", plateau->plateau[i][j]);
        }
        fprintf(file, "\n");
    }

    // Sauvegarder les positions des barrières
    fprintf(file, "\nBarrieres :\n");
    for (int i = 0; i < plateau->nbBarrieres; i++) {
        fprintf(file, "%d %d %d %d\n", plateau->barrieres[i][0], plateau->barrieres[i][1],
                plateau->barrieres[i][2], plateau->barrieres[i][3]);
    }

    fclose(file);
    printf("Plateau sauvegarde dans plateau.txt\n");
}

void chargerPlateau(Plateau *plateau) {
    FILE *file = fopen("plateau.txt", "r"); // Ouvrir le fichier en lecture

    if (file == NULL) {
        printf("Erreur : Impossible de charger le plateau (fichier introuvable).\n");
        return;
    }

    // Lire la matrice du plateau
    char buffer[100]; // Tampon pour lire les lignes du fichier
    fgets(buffer, sizeof(buffer), file); // Lire la première ligne "Plateau :"
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fscanf(file, " %c", &plateau->plateau[i][j]); // Lire chaque case
        }
    }

    // Lire les positions des barrières
    fgets(buffer, sizeof(buffer), file); // Lire la ligne vide ou "Barrières :"
    plateau->nbBarrieres = 0; // Réinitialiser le compteur des barrières
    while (fscanf(file, "%d %d %d %d",
                  &plateau->barrieres[plateau->nbBarrieres][0],
                  &plateau->barrieres[plateau->nbBarrieres][1],
                  &plateau->barrieres[plateau->nbBarrieres][2],
                  &plateau->barrieres[plateau->nbBarrieres][3]) == 4) {
        plateau->nbBarrieres++;
                  }

    fclose(file); // Fermer le fichier
    printf("Plateau charge depuis plateau.txt\n");
}
void afficherPlateau(Plateau *plateau) {
    printf("Plateau actuel :\n");
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            printf("%c ", plateau->plateau[i][j]);
        }
        printf("\n"); // Sauter à la ligne après chaque rangée
    }
    printf("\nNombre de barrieres : %d\n", plateau->nbBarrieres);
    for (int i = 0; i < plateau->nbBarrieres; i++) {
        printf("Barriere %d : %d %d %d %d\n", i + 1,
               plateau->barrieres[i][0], plateau->barrieres[i][1],
               plateau->barrieres[i][2], plateau->barrieres[i][3]);
    }
}

void calculScore(info_joueurs tableau_scores[], int *nbJoueursTotal, const char *gagnant, const char *perdant) {
    // Chercher le joueur gagnant et ajouter 5 points
    for (int i = 0; i < *nbJoueursTotal; i++) {
        if (strcmp(tableau_scores[i].nom, gagnant) == 0) { // Si c'est le gagnant
            tableau_scores[i].score += 5; // Ajouter 5 points
            return; // On s'arrête une fois que le score du gagnant est modifié
        }
    }

    // Si le perdant existe dans la liste, ne rien faire
    // Pas besoin de modifier le score du perdant, car on ne lui donne rien
}
