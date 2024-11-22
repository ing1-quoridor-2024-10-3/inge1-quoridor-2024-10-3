#include <stdio.h>
#include <windows.h>


void gotoligcol(int ligne, int colonne) {
    COORD mescoordonnes;
    mescoordonnes.X = colonne;
    mescoordonnes.Y = ligne;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mescoordonnes);
}


void afficherInfoJoueur(int lignedeBase, char *nom, int score, char pion, int nbBarriere) {
    gotoligcol(lignedeBase, 30);
    printf("Nom du joueur: %s", nom);
    gotoligcol(lignedeBase + 1, 30);
    printf("Score du joueur: %d", score);
    gotoligcol(lignedeBase + 2, 30);
    printf("Pion: %c", pion);
    gotoligcol(lignedeBase + 3, 30);
    printf("Barrieres : %d", nbBarriere);
}

int main(void) {
    char joueur1Nom[] = "Alice";
    int joueur1Score = 5;
    char joueur1Pion = 'A';
    int joueur1Barriere = 7;

    char joueur2Nom[] = "Bob";
    int joueur2Score = 3;
    char joueur2Pion = 'B';
    int joueur2Barriere = 5;


    gotoligcol(5, 5);
    printf("Plateau de jeu ici.");

    afficherInfoJoueur(5, joueur1Nom, joueur1Score, joueur1Pion, joueur1Barriere);
    afficherInfoJoueur(12, joueur2Nom, joueur2Score, joueur2Pion, joueur2Barriere);

    return 0;
}
