/*
    Correctif du labo 5

    gcc -std=c11 -Wall -Wextra -g -fsanitize=address main.c -o labo5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef struct {
    char *nom;
    uint32_t ip;
} Equipement;


void viderBuffer(void);

void tableauCarres(void);
void verifierMalloc(void);

char *dupliquer(const char *s);
void testDupliquer(void);

char *concatener(const char *a, const char *sep, const char *b);
void testConcatener(void);

void tableauQuiGrandit(void);

int **creerMatrice(int lignes, int colonnes);
void libererMatrice(int **m, int lignes);
void testMatrice(void);

Equipement *creerEquipement(const char *nom, uint32_t ip);
void detruireEquipement(Equipement *e);
void testEquipement(void);

void chasseAuxBugs(void);
void listeDeMots(void);


int main(void) {

    int choix;

    do {

        printf("\n===== LABO 5 =====\n");
        printf("1. Tableau de taille choisie\n");
        printf("2. Verifier malloc\n");
        printf("3. Dupliquer une chaine\n");
        printf("4. Concatener\n");
        printf("5. Tableau qui grandit\n");
        printf("6. Matrice dynamique\n");
        printf("7. Creer / detruire un equipement\n");
        printf("8. Chasse aux bugs\n");
        printf("9. Liste de mots\n");
        printf("0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            choix = -1;
        }
        viderBuffer();

        switch (choix) {
            case 1: tableauCarres(); break;
            case 2: verifierMalloc(); break;
            case 3: testDupliquer(); break;
            case 4: testConcatener(); break;
            case 5: tableauQuiGrandit(); break;
            case 6: testMatrice(); break;
            case 7: testEquipement(); break;
            case 8: chasseAuxBugs(); break;
            case 9: listeDeMots(); break;
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


/*
    Exercice 1 - Tableau de taille choisie

    La taille du tableau n'est connue qu'à l'exécution.
    - Demande n, alloue un tableau de n entiers.
    - Remplis-le avec les carrés 1, 4, 9… puis affiche-le.
    - Libère la mémoire.
*/

void tableauCarres(void) {

    int n;
    int *t;

    printf("Taille : ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        viderBuffer();
        printf("Taille invalide.\n");
        return;
    }
    viderBuffer();

    t = malloc(n * sizeof *t);
    if (t == NULL) {
        printf("Plus de memoire.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        t[i] = (i + 1) * (i + 1);
        printf("%d ", t[i]);
    }
    printf("\n");

    free(t);
}


/*
    Exercice 2 - Toujours vérifier malloc

    Un programme robuste vérifie chaque allocation et libère tout.
    - Vérifie le retour de malloc et quitte proprement s'il vaut NULL.
    - Oublie volontairement le free, compile avec -g -fsanitize=address
      et lis le rapport.
    - Corrige et vérifie que le rapport disparaît.

    Sans le free, ASan affiche "detected memory leaks" et donne la ligne du malloc
    qui n'a jamais été libéré.
*/

void verifierMalloc(void) {

    double *notes = malloc(3 * sizeof *notes);

    if (notes == NULL) {
        fprintf(stderr, "Erreur : allocation impossible.\n");
        exit(EXIT_FAILURE);
    }

    notes[0] = 12.5;
    notes[1] = 14.0;
    notes[2] = 9.5;

    printf("Moyenne : %.2f\n", (notes[0] + notes[1] + notes[2]) / 3);

    free(notes);   // c'est ce free que j'ai commenté pour voir le rapport ASan
}


/*
    Exercice 3 - Dupliquer une chaîne

    Écrire sa propre version de strdup.
    - Alloue exactement la place nécessaire.
    - Renvoie NULL si la source est NULL ou si l'allocation échoue.
*/

char *dupliquer(const char *s) {

    char *copie;

    if (s == NULL) {
        return NULL;
    }

    copie = malloc(strlen(s) + 1);   // +1 pour le '\0', sinon j'écris en dehors
    if (copie == NULL) {
        return NULL;
    }

    strcpy(copie, s);
    return copie;
}

void testDupliquer(void) {

    const char *original = "sw-etage1";
    char *copie = dupliquer(original);

    if (copie == NULL) {
        return;
    }

    printf("Original : %s (%p)\n", original, (void *) original);
    printf("Copie    : %s (%p)\n", copie, (void *) copie);

    free(copie);
}


/*
    Exercice 4 - Concaténer dans une nouvelle chaîne

    Construire "prefixe-nom" sans modifier les chaînes d'origine.
    - Calcule la taille totale, alloue, copie, concatène.
    - C'est l'appelant qui libère le résultat.
*/

char *concatener(const char *a, const char *sep, const char *b) {

    size_t taille = strlen(a) + strlen(sep) + strlen(b) + 1;
    char *res = malloc(taille);

    if (res == NULL) {
        return NULL;
    }

    strcpy(res, a);
    strcat(res, sep);
    strcat(res, b);

    return res;
}

void testConcatener(void) {

    char *etiquette = concatener("BXL", "-", "rt-core");

    if (etiquette != NULL) {
        printf("BXL + - + rt-core -> %s\n", etiquette);
        free(etiquette);
    }
}


/*
    Exercice 5 - Un tableau qui grandit

    Lire des entiers jusqu'à 0 sans connaître leur nombre à l'avance.
    - Commence avec une capacité de 2.
    - Double la capacité avec realloc quand le tableau est plein.
    - Affiche les valeurs, la taille et la capacité finale.
*/

void tableauQuiGrandit(void) {

    int capacite = 2;
    int taille = 0;
    int valeur;
    int *t = malloc(capacite * sizeof *t);

    if (t == NULL) {
        return;
    }

    printf("Valeurs (0 pour finir) : ");

    while (scanf("%d", &valeur) == 1 && valeur != 0) {

        if (taille == capacite) {

            // ici j'utilise un pointeur tmp pour ne pas avoir de fuite mémoire si realloc échoue
            int *tmp = realloc(t, capacite * 2 * sizeof *t);

            if (tmp == NULL) {
                printf("Plus de memoire, on s'arrete la.\n");
                break;
            }

            t = tmp;
            capacite *= 2;
        }

        t[taille++] = valeur;
    }
    viderBuffer();

    printf("Lu : ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", t[i]);
    }
    printf("\nTaille %d, capacite %d\n", taille, capacite);

    free(t);
}


/*
    Exercice 6 - Matrice dynamique

    Allouer une matrice de L lignes et C colonnes.
    - Alloue un tableau de L pointeurs, puis chaque ligne.
    - Remplis m[i][j] = i * C + j, affiche, puis libère dans le bon ordre.
*/

int **creerMatrice(int lignes, int colonnes) {

    int **m = malloc(lignes * sizeof *m);

    if (m == NULL) {
        return NULL;
    }

    for (int i = 0; i < lignes; i++) {

        m[i] = malloc(colonnes * sizeof **m);

        if (m[i] == NULL) {
            // une ligne a raté : je libère celles déjà faites avant de partir
            libererMatrice(m, i);
            return NULL;
        }
    }

    return m;
}

void libererMatrice(int **m, int lignes) {

    if (m == NULL) {
        return;
    }

    // d'abord les lignes, puis le tableau de pointeurs (sinon je perds les adresses des lignes)
    for (int i = 0; i < lignes; i++) {
        free(m[i]);
    }

    free(m);
}

void testMatrice(void) {

    int L = 3, C = 4;
    int **m = creerMatrice(L, C);

    if (m == NULL) {
        return;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            m[i][j] = i * C + j;
            printf("%2d ", m[i][j]);
        }
        printf("\n");
    }

    libererMatrice(m, L);
}


/*
    Exercice 7 - Créer et détruire une structure

    Une structure dont un champ est lui-même alloué.
    - Equipement contient un char *nom alloué dynamiquement.
    - creerEquipement alloue la structure et le nom.
    - detruireEquipement libère tout ; vérifie avec ASan.
*/

Equipement *creerEquipement(const char *nom, uint32_t ip) {

    Equipement *e = malloc(sizeof *e);

    if (e == NULL) {
        return NULL;
    }

    e->nom = dupliquer(nom);
    if (e->nom == NULL) {
        free(e);
        return NULL;
    }

    e->ip = ip;
    return e;
}

void detruireEquipement(Equipement *e) {

    if (e == NULL) {
        return;
    }

    free(e->nom);   // le nom d'abord : après free(e) je n'ai plus le droit de lire e->nom
    free(e);
}

void testEquipement(void) {

    Equipement *e = creerEquipement("rt-core", 0xC0A80101);

    if (e == NULL) {
        return;
    }

    printf("%s -> %u.%u.%u.%u\n", e->nom,
           (unsigned) (e->ip >> 24) & 0xFF, (unsigned) (e->ip >> 16) & 0xFF,
           (unsigned) (e->ip >> 8) & 0xFF, (unsigned) e->ip & 0xFF);

    detruireEquipement(e);
}


/*
    Exercice 8 - Chasse aux bugs mémoire

    Chacun des quatre programmes fournis contient un bug mémoire.
    - Lance chaque programme avec ASan (ou valgrind --leak-check=full).
    - Identifie le type d'erreur : débordement, utilisation après
      libération, double libération ou fuite.
    - Corrige et explique chaque correction en une phrase.

    Code fourni :
        int *t = malloc(5 * sizeof *t);
        for (int i = 0; i <= 5; i++) t[i] = i;   // bug 1
        free(t);
        printf("%d\n", t[0]);                    // bug 2
        free(t);                                 // bug 3
        (bug 4 : char *nom = malloc(32); ... jamais libéré)

    Bug 1 (heap-buffer-overflow) : avec i <= 5 on écrit dans t[5], une case de trop -> i < 5.
    Bug 2 (heap-use-after-free) : t est lu après le free, j'affiche avant de libérer.
    Bug 3 (double-free) : deuxième free sur le même bloc, je le retire et je mets t à NULL.
    Bug 4 (fuite) : nom n'est jamais libéré, j'ai ajouté le free(nom).
*/

void chasseAuxBugs(void) {

    int *t = malloc(5 * sizeof *t);
    char *nom = malloc(32);

    if (t == NULL || nom == NULL) {
        free(t);
        free(nom);
        return;
    }

    for (int i = 0; i < 5; i++) {
        t[i] = i;
    }

    printf("%d\n", t[0]);

    free(t);
    t = NULL;

    strcpy(nom, "srv-web");
    printf("%s\n", nom);
    free(nom);

    printf("Plus aucun rapport ASan.\n");
}


/*
    Exercice 9 - Liste de mots dynamique

    Lire des mots jusqu'à « fin » et les stocker sans gaspiller de mémoire.
    - Un tableau dynamique de char * qui grandit avec realloc.
    - Chaque mot est dupliqué avec ta fonction de l'exercice 3.
    - Affiche les mots en ordre inverse, puis libère tout.
*/

void listeDeMots(void) {

    char **mots = NULL;
    int nb = 0;
    int capacite = 0;
    char buffer[64];

    printf("Mots : ");

    while (scanf("%63s", buffer) == 1 && strcmp(buffer, "fin") != 0) {

        if (nb == capacite) {

            int nouvelleCapacite = capacite == 0 ? 2 : capacite * 2;
            char **tmp = realloc(mots, nouvelleCapacite * sizeof *mots);

            if (tmp == NULL) {
                break;
            }

            mots = tmp;
            capacite = nouvelleCapacite;
        }

        // buffer est écrasé à chaque tour, je garde donc une copie
        mots[nb] = dupliquer(buffer);
        if (mots[nb] == NULL) {
            break;
        }
        nb++;
    }
    viderBuffer();

    printf("Inverse : ");
    for (int i = nb - 1; i >= 0; i--) {
        printf("%s ", mots[i]);
    }
    printf("\n");

    // chaque mot, puis le tableau
    for (int i = 0; i < nb; i++) {
        free(mots[i]);
    }
    free(mots);

    printf("%d mots, 0 fuite.\n", nb);
}
