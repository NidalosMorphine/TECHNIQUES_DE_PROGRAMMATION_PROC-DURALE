/*
    Labo 2 - Exercices 4, 6, 7 et 8

    Ex 4 : déplace les fonctions de calcul de l'exercice 2 dans un module stats.
    - stats.h contient uniquement les prototypes.
    - stats.c contient le code et inclut stats.h.
    - main.c inclut "stats.h" et compile avec gcc main.c stats.c -o notes.

    Ex 6 : compilation séparée à la main.
    - Compile chaque fichier avec gcc -c et observe les .o produits.
    - Lie-les avec gcc main.o stats.o -o notes.
    - Essaie de lier SANS stats.o et explique l'erreur.

    gcc -c main.c puis gcc -c stats.c me donnent main.o et stats.o.
    Si je lie seulement main.o, j'ai "undefined reference to `moyenne'" : main.c compile
    sans souci parce que stats.h donne les prototypes, mais au moment du lien le code de
    moyenne() est dans stats.o et je ne l'ai pas donné à ld.

    Ex 7 et 8 : voir le Makefile.
*/

#include "stats.h"

#define MAX_NOTES 30


int main(void) {

    double notes[MAX_NOTES];
    int n = saisirNotes(notes, MAX_NOTES);

    afficherBilan(notes, n);

    return 0;
}
