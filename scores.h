#ifndef SCORES_H
#define SCORES_H

#define JOUEURS_MAX 10
#define TAILLE_MAX_NOM 50
#define TAILLE_PLATEAU 9 // Plateau 9x9

typedef struct {
    char nom[TAILLE_MAX_NOM];
    int score;
} info_joueurs;

// Structure pour représenter un plateau
typedef struct {
    char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]; // Contient les pions (ex. : 'P1', 'P2', '.', etc.)
    int barrieres[20][4]; // Contient les positions des barrières (max 20 barrières)
    int nbBarrieres; // Nombre actuel de barrières
} Plateau;


// Prototypes des fonctions
void initialisationFichierScores();
void lireScores(info_joueurs tableau_scores[], int *nbJoueursTotal);
void affichageScores(info_joueurs tableau_scores[], int nbJoueursTotal);
void miseAJour_scores(info_joueurs tableau_scores[], int *nbJoueursTotal, const char *nom, int points);
void sauvegarderScores(info_joueurs tableau_scores[], int nbJoueursTotal);
void sauvegarderPlateau(Plateau *plateau);
void chargerPlateau(Plateau *plateau);
void afficherPlateau(Plateau *plateau);
void calculScore(info_joueurs tableau_scores[], int *nbJoueursTotal, const char *gagnant, const char *perdant);



#endif //SCORES_H
