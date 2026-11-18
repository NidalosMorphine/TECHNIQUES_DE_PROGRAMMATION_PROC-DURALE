/*
    Correctif du labo 4

    gcc -std=c11 -Wall -Wextra main.c -o labo4 -lm
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef struct {
    double x, y;
} Point;

typedef struct {
    int jour, mois, annee;
} Date;

typedef struct {
    char titulaire[32];
    double solde;
} Compte;

typedef enum {
    ROUTEUR,
    SWITCH_RESEAU,
    SERVEUR,
    PC,
    IMPRIMANTE,
    NB_TYPES        // vaut 5, je m'en sers pour boucler sur tous les types
} TypeEquipement;

typedef struct {
    char nom[20];
    int note;
} Etudiant;

typedef struct {
    char rue[40];
    int numero;
    int codePostal;
    char ville[24];
} Adresse;

typedef struct {
    char prenom[20];
    char nom[20];
    Date naissance;
    Adresse adresse;
} Personne;


void viderBuffer(void);

double distance(Point a, Point b);
void testPoints(void);

void afficherDate(Date d);
int comparerDates(Date a, Date b);
void testDates(void);

void deposer(Compte *c, double montant);
int retirer(Compte *c, double montant);
void testCompte(void);

const char *libelleType(TypeEquipement t);
void testTypes(void);

void testClasse(void);

size_t maLongueur(const char *s);
void maCopie(char *dest, const char *src);
void mesMajuscules(char *s);
void testChaines(void);

void testEtiquette(void);

void trierParNom(Etudiant *t, int n);
void testTri(void);

int age(Personne p, Date aujourdhui);
void testPersonne(void);


Etudiant classe[5] = { {"Alice", 15}, {"Bilal", 9}, {"Chloé", 12},
                       {"David", 7}, {"Emma", 17} };


int main(void) {

    int choix;

    do {

        printf("\n===== LABO 4 =====\n");
        printf("1. Points et distance\n");
        printf("2. Dates\n");
        printf("3. Compte\n");
        printf("4. Types d'equipements\n");
        printf("5. Tableau d'etudiants\n");
        printf("6. Chaines a la main\n");
        printf("7. Etiquette\n");
        printf("8. Trier par nom\n");
        printf("9. Structures imbriquees\n");
        printf("0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            choix = -1;
        }
        viderBuffer();

        switch (choix) {
            case 1: testPoints(); break;
            case 2: testDates(); break;
            case 3: testCompte(); break;
            case 4: testTypes(); break;
            case 5: testClasse(); break;
            case 6: testChaines(); break;
            case 7: testEtiquette(); break;
            case 8: testTri(); break;
            case 9: testPersonne(); break;
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
    Exercice 1 - Points et distance

    Représenter un point du plan et calculer une distance.
    - Définis typedef struct { double x, y; } Point;
    - Écris une fonction qui renvoie la distance entre deux points.
    - Compile avec -lm pour la fonction sqrt.
*/

double distance(Point a, Point b) {

    double dx = b.x - a.x;
    double dy = b.y - a.y;

    return sqrt(dx * dx + dy * dy);
}

void testPoints(void) {

    Point a = { 1.0, 2.0 };
    Point b = { 4.0, 6.0 };

    printf("A(%.1f, %.1f)  B(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);
    printf("Distance : %.2f\n", distance(a, b));
}


/*
    Exercice 2 - Dates

    Une structure Date (jour, mois, année) et deux fonctions utilitaires.
    - Affiche une date au format JJ/MM/AAAA.
    - Compare deux dates : renvoie -1, 0 ou 1.
*/

void afficherDate(Date d) {
    printf("%02d/%02d/%04d", d.jour, d.mois, d.annee);
}

int comparerDates(Date a, Date b) {

    // je compare l'année, puis le mois, puis le jour
    if (a.annee != b.annee) return a.annee < b.annee ? -1 : 1;
    if (a.mois != b.mois)   return a.mois < b.mois ? -1 : 1;
    if (a.jour != b.jour)   return a.jour < b.jour ? -1 : 1;

    return 0;
}

void testDates(void) {

    Date a = { 14, 9, 2026 };
    Date b = { 2, 2, 2027 };
    int cmp = comparerDates(a, b);

    afficherDate(a);

    if (cmp < 0) printf(" est avant ");
    else if (cmp > 0) printf(" est apres ");
    else printf(" est le meme jour que ");

    afficherDate(b);
    printf("\n");
}


/*
    Exercice 3 - Modifier une structure

    Une fonction qui reçoit une structure par adresse et la modifie.
    - Structure Compte : titulaire (chaîne), solde.
    - deposer et retirer modifient le solde ; retirer renvoie 0 si le
      solde est insuffisant.
    - Utilise l'opérateur ->.
*/

void deposer(Compte *c, double montant) {
    c->solde += montant;
}

int retirer(Compte *c, double montant) {

    if (montant > c->solde) {
        return 0;
    }

    c->solde -= montant;
    return 1;
}

void testCompte(void) {

    Compte c = { "Alice", 100.0 };

    printf("%s : %.2f\n", c.titulaire, c.solde);

    deposer(&c, 50);
    printf("Depot de 50    -> %.2f\n", c.solde);

    if (!retirer(&c, 200)) {
        printf("Retrait de 200 -> refuse\n");
    }

    if (retirer(&c, 80)) {
        printf("Retrait de 80  -> %.2f\n", c.solde);
    }
}


/*
    Exercice 4 - Types d’équipements avec enum

    Remplacer des nombres magiques par une énumération.
    - Définis typedef enum { ROUTEUR, SWITCH_RESEAU, SERVEUR, PC, IMPRIMANTE } TypeEquipement;
    - Écris une fonction qui renvoie le libellé de chaque type.
    - Affiche tous les types avec une boucle.
*/

const char *libelleType(TypeEquipement t) {

    switch (t) {
        case ROUTEUR: return "Routeur";
        case SWITCH_RESEAU: return "Switch";
        case SERVEUR: return "Serveur";
        case PC: return "PC";
        case IMPRIMANTE: return "Imprimante";
        default: return "Inconnu";
    }
}

void testTypes(void) {

    for (TypeEquipement t = ROUTEUR; t < NB_TYPES; t++) {
        printf("%d %s\n", t, libelleType(t));
    }
}


/*
    Exercice 5 - Tableau d’étudiants

    Gérer une classe de 5 étudiants (nom, note).
    - Initialise le tableau directement dans le code.
    - Affiche la moyenne de la classe et le meilleur étudiant.
    - Affiche la liste des étudiants en échec (< 10).
*/

void testClasse(void) {

    int total = 0;
    int meilleur = 0;
    int premier = 1;

    for (int i = 0; i < 5; i++) {
        total += classe[i].note;
        if (classe[i].note > classe[meilleur].note) {
            meilleur = i;
        }
    }

    printf("Moyenne de la classe : %.2f\n", total / 5.0);
    printf("Meilleur : %s (%d)\n", classe[meilleur].nom, classe[meilleur].note);
    printf("En echec : ");

    for (int i = 0; i < 5; i++) {
        if (classe[i].note < 10) {
            // petite astuce pour ne mettre la virgule qu'entre deux noms
            printf("%s%s", premier ? "" : ", ", classe[i].nom);
            premier = 0;
        }
    }

    printf("\n");
}


/*
    Exercice 6 - Chaînes à la main

    Réécrire trois fonctions de <string.h> pour comprendre le terminateur.
    - maLongueur compte les caractères jusqu'au '\0'.
    - maCopie copie la source dans la destination, '\0' compris.
    - mesMajuscules met la chaîne en majuscules (avec toupper).
*/

size_t maLongueur(const char *s) {

    size_t n = 0;

    while (s[n] != '\0') {
        n++;
    }

    return n;
}

void maCopie(char *dest, const char *src) {

    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';   // sans ça dest n'est pas une vraie chaîne
}

void mesMajuscules(char *s) {

    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = toupper((unsigned char) s[i]);
    }
}

void testChaines(void) {

    const char *nom = "routeur-01";
    char copie[32];

    printf("\"%s\" : %zu caracteres\n", nom, maLongueur(nom));

    maCopie(copie, nom);
    printf("Copie : %s\n", copie);

    mesMajuscules(copie);
    printf("Majuscules : %s\n", copie);
}


/*
    Exercice 7 - Saisie de chaînes sécurisée

    Lire un nom d'équipement avec espaces sans risque de débordement.
    - Lis avec fgets dans un tableau de 32 caractères.
    - Retire le \n final avec strcspn.
    - Construis l'étiquette "[nom] - salle" avec snprintf.
*/

void testEtiquette(void) {

    char nom[32];
    char salle[16];
    char etiquette[64];

    printf("Nom : ");
    fgets(nom, sizeof nom, stdin);
    nom[strcspn(nom, "\n")] = '\0';

    printf("Salle : ");
    fgets(salle, sizeof salle, stdin);
    salle[strcspn(salle, "\n")] = '\0';

    // j'utilise snprintf et pas sprintf : il ne dépasse jamais la taille du tableau
    snprintf(etiquette, sizeof etiquette, "[%s] - %s", nom, salle);

    printf("Etiquette : %s\n", etiquette);
}


/*
    Exercice 8 - Trier par nom

    Trier le tableau d'étudiants de l'exercice 5 par ordre alphabétique.
    - Utilise strcmp pour comparer les noms.
    - Échange des structures complètes (une affectation suffit).
*/

void trierParNom(Etudiant *t, int n) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(t[j].nom, t[j + 1].nom) > 0) {
                Etudiant tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
}

void testTri(void) {

    // je trie une copie pour ne pas toucher à la classe de l'exercice 5
    Etudiant copie[5] = { {"Emma", 17}, {"Chloé", 12}, {"Alice", 15},
                          {"David", 7}, {"Bilal", 9} };

    trierParNom(copie, 5);

    for (int i = 0; i < 5; i++) {
        printf("%s %d\n", copie[i].nom, copie[i].note);
    }
}


/*
    Exercice 9 - Structures imbriquées

    Une Personne possède une Date de naissance et une Adresse.
    - Définis les trois structures.
    - Écris une fonction qui calcule l'âge à une date donnée.
    - Affiche une fiche complète.
*/

int age(Personne p, Date aujourdhui) {

    int a = aujourdhui.annee - p.naissance.annee;

    // anniversaire pas encore passé cette année
    if (aujourdhui.mois < p.naissance.mois ||
        (aujourdhui.mois == p.naissance.mois && aujourdhui.jour < p.naissance.jour)) {
        a--;
    }

    return a;
}

void testPersonne(void) {

    Personne p = {
        "Jean", "Dupont",
        { 3, 5, 1998 },
        { "Rue de la Station", 12, 5000, "Namur" }
    };
    Date aujourdhui = { 18, 11, 2026 };

    printf("%s %s\n", p.prenom, p.nom);
    printf("Ne le ");
    afficherDate(p.naissance);
    printf(" - %d ans\n", age(p, aujourdhui));
    printf("%s %d, %d %s\n", p.adresse.rue, p.adresse.numero, p.adresse.codePostal, p.adresse.ville);
}
