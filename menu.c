//
// Created by znaor on 18/11/2024.
//
#define CONSOLE_WIDTH 120
#include <stdio.h>
#include <stdlib.h>
int NouvellePartie() {
    system("cls");
}
int ReprendrePartieSauv() {
    system("cls");
}
    void aide(){
        system("cls");
        printf("===============================================================================\n");
        printf("|                               AIDE - QUORIDOR                               |\n");
        printf("===============================================================================\n");
         printf("PRESENTATION :\n");
         printf("\n");
        printf("- Quoridor est un jeu de plateau strategique ou chaque joueur doit atteindre\n");
         printf("  le cote oppose du plateau tout en bloquant son adversaire avec des barrieres.\n");
         printf("\n");
         printf("BUT DU JEU :\n");
         printf("\n");
         printf("- etre le premier a deplacer son pion sur la ligne opposee du plateau.\n");
         printf("\n");
         printf("ELEMENTS DU JEU :\n");
         printf("\n");
         printf("- Plateau de jeu : Une grille carree de 9x9 cases.\n");
         printf("- Pions : Chaque joueur dispose d'un pion qui commence sur la ligne centrale\n");
         printf("  de son cote du plateau.\n");
         printf("- Barrieres : Chaque joueur possede 10 barrieres qu il peut placer pour\n");
         printf("  ralentir son adversaire.\n");
         printf("\n");
         printf("REGLES :\n");
         printf("\n");
         printf("1. Chaque joueur joue a tour de role.\n");
         printf("2. a chaque tour, un joueur peut soit :\n");
         printf("   - Deplacer son pion d'une case (haut, bas, gauche ou droite).\n");
         printf("   - Placer une barriere pour bloquer le chemin de l adversaire.\n");
         printf("3. Les barrieres doivent etre placees entre deux cases, en respectant\n");
         printf("   les lignes du plateau.\n");
         printf("4. Les pions ne peuvent pas traverser les barrieres.\n");
         printf("5. Il doit toujours exister un chemin permettant a chaque joueur\n");
         printf("   d'atteindre la ligne opposee.\n");
         printf("6. Si un pion est adjacent a celui de l'adversaire et qu'il n'y a pas\n");
         printf("   de barriere derriere, le joueur peut sauter par-dessus.\n");
         printf("\n");
         printf("STRATEGIE :\n");
         printf("\n");
         printf("- Utilisez vos barrieres avec sagesse pour bloquer l adversaire sans\n");
        printf("  vous enfermer.\n");
         printf("- Trouvez le chemin le plus court vers votre objectif tout en perturbant\n");
         printf("  celui de votre adversaire.\n");
         printf("\n");
         printf("CONSEILS :\n");
        printf("\n");
         printf("- Ne gaspillez pas vos barrieres trop tot.\n");
         printf("- Observez les mouvements de votre adversaire et adaptez votre strategie.\n");
         printf("- Gardez toujours un chemin ouvert pour votre pion.\n");
         printf("\n");
        printf("===============================================================================\n");
        printf("| Appuyez sur 0 pour revenir au menu principal                                |\n");
        printf("===============================================================================\n");
        int retourMenu;
        do {
            printf("\nAppuyez sur 0 pour revenir au menu principal : ");
            scanf("%d", &retourMenu);
        } while (retourMenu != 0);
        system("cls");
    }
