/*
    Labo 2 - Exercice 9 : Module de saisie sécurisée

    Toutes les saisies du cours passeront par ce module.
    - saisie.h / saisie.c : lire un entier dans un intervalle et une chaîne
      sans débordement.
    - Une saisie invalide (lettres, hors intervalle) redemande la valeur.
    - Vide le tampon d'entrée après une erreur.

    int lireEntier(const char *invite, int min, int max);
    void lireChaine(const char *invite, char *dest, int taille);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saisie.h"


static void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void lireChaine(const char *invite, char *dest, int taille) {

    printf("%s", invite);

    if (fgets(dest, taille, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }

    // s'il n'y a pas de \n c'est que la ligne était trop longue : le reste traîne encore dans stdin, je le vide
    if (strchr(dest, '\n') == NULL) {
        viderBuffer();
    }

    dest[strcspn(dest, "\n")] = '\0';
}


int lireEntier(const char *invite, int min, int max) {

    char ligne[64];
    char *fin;
    long valeur;

    while (1) {

        // je lis toute la ligne puis je convertis avec strtol, comme ça pas de scanf qui laisse des déchets dans le buffer
        lireChaine(invite, ligne, sizeof ligne);

        valeur = strtol(ligne, &fin, 10);

        if (fin != ligne && *fin == '\0' && valeur >= min && valeur <= max) {
            return (int) valeur;
        }

        printf("Valeur invalide.\n");

        if (feof(stdin)) {
            exit(EXIT_FAILURE);
        }
    }
}
