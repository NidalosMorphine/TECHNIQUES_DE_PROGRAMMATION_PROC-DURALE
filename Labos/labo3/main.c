/*
    Correctif du labo 3

    gcc -std=c11 -Wall -Wextra main.c -o labo3
*/

#include <stdio.h>
#include <stddef.h>


void viderBuffer(void);
void afficherTableau(const int *t, int n);

void adressesEtTailles(void);
void tracerMemoire(void);

void echangerParValeur(int a, int b);
void echanger(int *a, int *b);
void testEchange(void);

void doubler(int *n);
void borner(int *n, int min, int max);
void testModifier(void);

int diviser(int a, int b, int *quotient, int *reste);
void testDiviser(void);

int minMax(const int *t, int n, int *min, int *max);
void testMinMax(void);

int sommeIndice(const int *t, int n);
int somme(const int *t, int n);
void testSomme(void);

void inverser(int *t, int n);
void testInverser(void);

int *trouver(int *t, int n, int valeur);
void testTrouver(void);


int main(void) {

    int choix;

    do {

        printf("\n===== LABO 3 =====\n");
        printf("1. Adresses et tailles\n");
        printf("2. Tracer la memoire\n");
        printf("3. Echange\n");
        printf("4. Modifier par adresse\n");
        printf("5. Division euclidienne\n");
        printf("6. Min et max\n");
        printf("7. Somme sans crochets\n");
        printf("8. Inverser un tableau\n");
        printf("9. Renvoyer un pointeur\n");
        printf("0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            choix = -1;
        }

        switch (choix) {
            case 1: adressesEtTailles(); break;
            case 2: tracerMemoire(); break;
            case 3: testEchange(); break;
            case 4: testModifier(); break;
            case 5: testDiviser(); break;
            case 6: testMinMax(); break;
            case 7: testSomme(); break;
            case 8: testInverser(); break;
            case 9: testTrouver(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}


void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void afficherTableau(const int *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}


/*
    Exercice 1 - Adresses et tailles

    Observer comment les variables sont rangées en mémoire.
    - Déclare un char, un int, un double et un tableau int t[3].
    - Affiche l'adresse et la taille de chacun.
    - Compare les adresses de t[0], t[1] et t[2] : quel écart ?

    L'écart est de 4 octets, c'est sizeof(int) : les cases d'un tableau sont collées.
*/

void adressesEtTailles(void) {

    char c = 'A';
    int i = 42;
    double d = 3.14;
    int t[3] = { 1, 2, 3 };

    // %p attend un void *, d'où mes casts
    printf("char   c    : %p  (%zu octet)\n", (void *) &c, sizeof c);
    printf("int    i    : %p  (%zu octets)\n", (void *) &i, sizeof i);
    printf("double d    : %p  (%zu octets)\n", (void *) &d, sizeof d);
    printf("int    t[3] : %p  (%zu octets)\n", (void *) t, sizeof t);
    printf("t[0] %p   t[1] %p   t[2] %p\n", (void *) &t[0], (void *) &t[1], (void *) &t[2]);
    printf("Ecart : %td octets\n", (char *) &t[1] - (char *) &t[0]);
}


/*
    Exercice 2 - Tracer la mémoire

    Sur papier d'abord : dessine les cases et les flèches après chaque ligne.
    - Donne les valeurs finales de a, b et *p.
    - Vérifie ensuite en exécutant le code.

    int a = 3, b = 7;      a=3  b=7
    int *p = &a;           p -> a
    *p = *p + b;           a=10
    p = &b;                p -> b
    *p = a * 2;            b=20
*/

void tracerMemoire(void) {

    int a = 3, b = 7;
    int *p = &a;

    *p = *p + b;
    p = &b;
    *p = a * 2;

    printf("a=%d b=%d *p=%d\n", a, b, *p);
}


/*
    Exercice 3 - L’échange (swap)

    Écris la fonction qui échange deux entiers de l'appelant.
    - Écris d'abord une version par valeur et constate qu'elle ne marche pas.
    - Écris la version par adresse.

    void echanger(int *a, int *b);
*/

void echangerParValeur(int a, int b) {
    // a et b sont des copies : j'échange les copies, les variables du main ne bougent pas
    int tmp = a;
    a = b;
    b = tmp;
}

void echanger(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void testEchange(void) {

    int x = 3, y = 8;

    printf("Avant : x=%d y=%d\n", x, y);

    echangerParValeur(x, y);
    printf("Par valeur : x=%d y=%d\n", x, y);

    echanger(&x, &y);
    printf("Apres : x=%d y=%d\n", x, y);
}


/*
    Exercice 4 - Modifier par adresse

    Plusieurs petites fonctions qui modifient la variable reçue.
    - doubler multiplie la valeur par 2.
    - borner ramène la valeur dans [min, max].
    - Teste-les avec plusieurs valeurs, y compris aux limites.
*/

void doubler(int *n) {
    *n *= 2;
}

void borner(int *n, int min, int max) {
    if (*n < min) {
        *n = min;
    } else if (*n > max) {
        *n = max;
    }
}

void testModifier(void) {

    int tests[] = { 150, -5, 0, 100, 50 };
    int v = 21;

    doubler(&v);
    printf("doubler(21)         -> %d\n", v);

    for (int i = 0; i < 5; i++) {
        v = tests[i];
        borner(&v, 0, 100);
        printf("borner(%d, 0, 100) -> %d\n", tests[i], v);
    }
}


/*
    Exercice 5 - Division euclidienne

    Une fonction qui renvoie deux résultats et signale une erreur.
    - Le quotient et le reste sortent par pointeurs.
    - La fonction renvoie 0 en cas de division par zéro ou de pointeur
      NULL, 1 sinon.
*/

int diviser(int a, int b, int *quotient, int *reste) {

    if (b == 0 || quotient == NULL || reste == NULL) {
        return 0;
    }

    *quotient = a / b;
    *reste = a % b;

    return 1;
}

void testDiviser(void) {

    int a, b, q, r;

    printf("a b : ");
    scanf("%d %d", &a, &b);

    if (diviser(a, b, &q, &r)) {
        printf("%d = %d x %d + %d\n", a, q, b, r);
    } else {
        printf("Erreur : division par zero.\n");
    }
}


/*
    Exercice 6 - Minimum et maximum en un appel

    Parcourir un tableau une seule fois pour trouver les deux extrêmes.
    - La fonction remplit *min et *max.
    - Elle renvoie 0 si le tableau est vide.
*/

int minMax(const int *t, int n, int *min, int *max) {

    if (n <= 0) {
        return 0;
    }

    *min = t[0];
    *max = t[0];

    for (int i = 1; i < n; i++) {
        if (t[i] < *min) *min = t[i];
        if (t[i] > *max) *max = t[i];
    }

    return 1;
}

void testMinMax(void) {

    int t[] = { 14, 3, 27, 9, 3, 18 };
    int min, max;

    printf("Tableau : ");
    afficherTableau(t, 6);

    if (minMax(t, 6, &min, &max)) {
        printf("min = %d, max = %d\n", min, max);
    }
}


/*
    Exercice 7 - Parcourir avec un pointeur

    Réécrire la somme du tableau {12, 7, 30, 5, 31} sans utiliser de crochets.
    - Version 1 : *(t + i) avec un indice.
    - Version 2 : un pointeur p qui avance de t jusqu'à t + n.
*/

int sommeIndice(const int *t, int n) {

    int total = 0;

    for (int i = 0; i < n; i++) {
        total += *(t + i);
    }

    return total;
}

int somme(const int *t, int n) {

    int total = 0;

    // t + n pointe juste après le dernier élément, je m'arrête avant
    for (const int *p = t; p < t + n; p++) {
        total += *p;
    }

    return total;
}

void testSomme(void) {

    int t[] = { 12, 7, 30, 5, 31 };

    printf("Somme (indice)   : %d\n", sommeIndice(t, 5));
    printf("Somme (pointeur) : %d\n", somme(t, 5));
}


/*
    Exercice 8 - Inverser un tableau

    Inverser l'ordre des éléments en place, avec deux pointeurs qui se
    rapprochent.
    - Un pointeur part du début, l'autre de la fin.
    - Réutilise ta fonction echanger de l'exercice 3.
*/

void inverser(int *t, int n) {

    int *debut = t;
    int *fin = t + n - 1;

    while (debut < fin) {
        echanger(debut, fin);
        debut++;
        fin--;
    }
}

void testInverser(void) {

    int t[] = { 1, 2, 3, 4, 5, 6 };

    printf("Avant : ");
    afficherTableau(t, 6);

    inverser(t, 6);

    printf("Apres : ");
    afficherTableau(t, 6);
}


/*
    Exercice 9 - Renvoyer un pointeur

    La recherche renvoie l'adresse de l'élément trouvé, ce qui permet
    de le modifier.
    - Renvoie un pointeur vers la première valeur égale, ou NULL.
    - Utilise le résultat pour remplacer la valeur trouvée par 0.
*/

int *trouver(int *t, int n, int valeur) {

    for (int i = 0; i < n; i++) {
        if (t[i] == valeur) {
            return &t[i];
        }
    }

    return NULL;
}

void testTrouver(void) {

    int t[] = { 5, 12, 7, 12, 3 };
    int *p;

    printf("Avant : ");
    afficherTableau(t, 5);

    p = trouver(t, 5, 12);
    if (p != NULL) {
        printf("Remplacement du premier 12...\n");
        *p = 0;
    }

    printf("Apres : ");
    afficherTableau(t, 5);

    // je teste toujours le NULL avant de déréférencer
    if (trouver(t, 5, 99) == NULL) {
        printf("99 introuvable.\n");
    }
}
