/*
    Labo 2 - Exercice 1 : Réindenter et renommer

    Ce code fonctionne mais personne n'a envie de le relire.
    - Réindente-le correctement (4 espaces).
    - Renomme chaque variable et la fonction avec un nom explicite.
    - Ajoute une constante à la place du nombre magique.

    int f(int a[],int b){int c=0;for(int i=0;i<b;i++){if(a[i]>=10)c++;}return c;}
    int main(void){int x[5]={12,8,15,10,4};printf("%d\n",f(x,5));return 0;}

    Sortie attendue : 3
*/

#include <stdio.h>

#define SEUIL_REUSSITE 10
#define NB_NOTES 5


int compterReussites(const int notes[], int nbNotes) {

    int nbReussites = 0;

    for (int i = 0; i < nbNotes; i++) {
        if (notes[i] >= SEUIL_REUSSITE) {
            nbReussites++;
        }
    }

    return nbReussites;
}


int main(void) {

    int notes[NB_NOTES] = { 12, 8, 15, 10, 4 };

    printf("%d\n", compterReussites(notes, NB_NOTES));

    return 0;
}
