#include <stdio.h>
#include "saisie.h"


int main(void) {

    char nom[16];
    int choix = lireEntier("Choix (0-5) : ", 0, 5);

    lireChaine("Nom (15 car. max) : ", nom, sizeof nom);

    printf("Choix = %d, nom = \"%s\"\n", choix, nom);

    return 0;
}
