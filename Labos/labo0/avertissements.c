/*
    Labo 0 - Exercice 3 : Les avertissements sont vos amis

    Le programme compile... mais contient trois erreurs que gcc signale
    si on le lui demande.
    - Recopie le code, compile sans puis avec -Wall -Wextra.
    - Note chaque avertissement et explique-le en une phrase.
    - Corrige le code jusqu'à zéro avertissement.

    Version d'origine :

        int age;
        double taille = 1.82;
        printf("Age : %d\n", age);
        printf("Taille : %d\n", taille);
        if (age = 18) printf("Majeur\n");

    Avec -Wall -Wextra gcc sort 3 avertissements :
    - 'age' is used uninitialized : age n'a jamais reçu de valeur, j'affiche donc n'importe quoi.
    - format '%d' expects 'int' : taille est un double, il faut %f (j'ai mis %.2f).
    - suggest parentheses around assignment : avec un seul = j'affecte 18 à age au lieu
      de comparer, et le if est toujours vrai.
*/

#include <stdio.h>

int main(void) {

    int age = 20;
    double taille = 1.82;

    printf("Age : %d\n", age);
    printf("Taille : %.2f\n", taille);

    if (age >= 18) {
        printf("Majeur\n");
    }

    return 0;
}
