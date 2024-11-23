#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <windows.h>
#include <stdbool.h>
#define CASE 9

void gotoligcol( int lig, int col )
{
    // ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void Mode2joueurs(char plateau[CASE][CASE])
{
    printf("Nouvelle partie demarree ! \n");
    printf("Nom du premier joueur :\n");
    char prenomUn[50]; scanf("%49s", prenomUn);
    printf("Nom du deuxieme joueur :\n");
    char prenomDeux[50]; scanf("%49s", prenomDeux);

    const char jetonUn = 'J';
    const char jetonDeux = 'Z';

    int barriereUn = 10;
    int barriereDeux = 10;

    char barriere = '@';

    bool partieEnCours = true;
    bool joueurUnFlag = true;

    int x1 = 8;
    int y1 = 3;
    int x2= 8;
    int y2= 4;
    plateau[x1][y1]=jetonUn;
    plateau[x2][y2]=jetonDeux;

    afficherPlateau(plateau);

    while (partieEnCours)
    {
        if (joueurUnFlag)
        {
            printf("A toi de jouer %s\n", prenomUn);
            printf("\n1) Deplacer son pion.\n2) Poser une barriere\n");
            int action;
            scanf(" %d", &action);
            getchar();
            if (action == 1)
            {
                printf("\nQuelle action voulez vous faire ?\n1) Avancer\n2) Aller a gauche\n3) Aller a droite\n4)Reculer\n");
                int deplacement;
                scanf(" %d", &deplacement);
                getchar();
                if (deplacement == 1) {if(x1>0){plateau[x1][y1]=' ';x1--;plateau[x1][y1]=jetonUn;}}
                else if (deplacement == 2) {if(y1>0){plateau[x1][y1]=' ';y1--;plateau[x1][y1]=jetonUn;}}
                else if (deplacement == 3) {if(y1<8){plateau[x1][y1]=' ';y1++;plateau[x1][y1]=jetonUn;}}
                else if (deplacement == 4) {if(x1<8){plateau[x1][y1]=' ';x1++;plateau[x1][y1]=jetonUn;}}

                afficherPlateau(plateau);

            }
            else if (action == 2) {
                printf("\nEntre quelles case voulez vous poser une barriere ? (lettre/chiffre)\n");
                char case1[3];
                char case2[3];
                printf("\nPremiere case :\n");
                scanf("%2s", case1);
                printf("\nDeuxieme case :\n");
                scanf("%2s", case2);
                getchar();

                int val1 = case1[1] - '0';
                int val2 = case2[1] - '0';
                int val3 = case1[0] - 'A' + 1;
                int val4 = case2[0] - 'A' + 1;

                int ligne; int colonne;

                if (val1==val2)
                    {
                    ligne = val1 * 2 + 1;
                    colonne = (val3 > val4 ? val4 : val3) * 4 + 2;
                    }
                else if (val3==val4)
                    {
                    ligne = (val1 > val2 ? val2 : val1) * 2 + 2;
                    colonne = val3 * 4;
                    }
                else {printf("Erreur!\nLes deux cases doivent être adjacente\n");return;}

                printf("Ligne : %d Colonne: %d\n", ligne, colonne);
                afficherPlateau(plateau);
                gotoligcol(ligne, colonne);
                printf("%c", barriere);

                gotoligcol(100, 0);

            }
            else {partieEnCours = false;}
            joueurUnFlag = false;
        }

        else
        {
            printf("A toi de jouer %s", prenomDeux);
            printf("\n\nQuelle action voulez vous faire ?\n1) Avancer\n2) Aller a gauche\n3) Aller a droite\n4)Reculer\n");
            int action;
            scanf(" %d", &action);
            getchar();

            if (action == 1) {if(x2>0){plateau[x2][y2]=' ';x2--;plateau[x2][y2]=jetonDeux;}}
            else if (action == 2) {if(y2>0){plateau[x2][y2]=' ';y2--;plateau[x2][y2]=jetonDeux;}}
            else if (action == 3) {if(y2<8){plateau[x2][y2]=' ';y2++;plateau[x2][y2]=jetonDeux;}}
            else if (action == 4) {if(x2<8){plateau[x2][y2]=' ';x2++;plateau[x2][y2]=jetonDeux;}}

            afficherPlateau(plateau);

            joueurUnFlag = true;
        }


        //printf(prenomUn, "tu commences ! n1) Avancer\n2) Reculer\n3) Aller a droite\n4) Aller a gauche\n");


        //partieEnCours = false;

    }
}
