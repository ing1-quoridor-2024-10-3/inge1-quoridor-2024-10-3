cmake_minimum_required(VERSION 3.29)
project(inge1_quoridor_2024_10_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(inge1_quoridor_2024_10_3
    main.c
        menu.c
        plateau.c
        Mode2joueurs.c
        initialerPlateau.c
        scores.h
        scores.c
        sauvegarde.c
        sauvegarde.h
        afficherplateau.c
        Mode4joueurs.h
        Mode4joueur.c)
