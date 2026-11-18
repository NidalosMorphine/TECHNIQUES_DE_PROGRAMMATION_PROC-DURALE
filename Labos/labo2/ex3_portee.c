/*
    Labo 2 - Exercice 3 : Portée des variables

    Prédis la sortie de ce programme AVANT de l'exécuter, puis vérifie.
    - Écris ta prédiction ligne par ligne.
    - Exécute et explique chaque différence.

    Sortie :
        n=1 local=1 compteur=1
        n=2 local=1 compteur=2
        n=3 local=1 compteur=3

    compteur est globale, elle vit tout le programme donc elle continue d'augmenter.
    n est static : elle n'est initialisée qu'une fois et garde sa valeur entre deux appels.
    local est recréée à chaque appel, elle repart de 0 et vaut donc toujours 1.
*/

#include <stdio.h>

int compteur = 0;


void appel(void) {

    static int n = 0;
    int local = 0;

    n++;
    local++;
    compteur++;

    printf("n=%d local=%d compteur=%d\n", n, local, compteur);
}


int main(void) {

    appel();
    appel();
    appel();

    return 0;
}
