/*
    Correctif du labo 1

    gcc -std=c11 -Wall -Wextra main.c -o labo1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOTES 30
#define MAX_TACHES 20


void viderBuffer(void);

void calculatrice(void);
void pairImpairMultiples(void);
void jeuDevinettes(void);

double celsiusVersFahrenheit(double c);
double kmVersMiles(double km);
double kgVersLivres(double kg);
void convertisseur(void);

void analyseNotes(void);
void tablesMultiplication(void);

int montantValide(double montant);
void compteBancaire(void);

int rechercher(const int t[], int n, int valeur);
int compter(const int t[], int n, int valeur);
void rechercheTableau(void);

int manche(int joueur, int ordi);
void pierrePapierCiseaux(void);

void gestionnaireTaches(void);


int main(void) {

    int choix;

    srand(time(NULL));

    do {

        printf("\n===== LABO 1 =====\n");
        printf("1. Calculatrice\n");
        printf("2. Pair / impair / multiples\n");
        printf("3. Jeu de devinettes\n");
        printf("4. Convertisseur\n");
        printf("5. Analyse de notes\n");
        printf("6. Tables de multiplication\n");
        printf("7. Compte bancaire\n");
        printf("8. Recherche dans un tableau\n");
        printf("9. Pierre - Papier - Ciseaux\n");
        printf("10. Gestionnaire de taches\n");
        printf("0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            choix = -1;
        }

        switch (choix) {
            case 1: calculatrice(); break;
            case 2: pairImpairMultiples(); break;
            case 3: jeuDevinettes(); break;
            case 4: convertisseur(); break;
            case 5: analyseNotes(); break;
            case 6: tablesMultiplication(); break;
            case 7: compteBancaire(); break;
            case 8: rechercheTableau(); break;
            case 9: pierrePapierCiseaux(); break;
            case 10: gestionnaireTaches(); break;
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
    Exercice 1 - Calculatrice avec menu

    Une calculatrice qui propose les quatre opérations de base dans un menu.
    - Lis deux réels puis l'opération choisie.
    - Refuse la division par zéro.
    - Le menu se répète jusqu'au choix 0.
*/

void calculatrice(void) {

    int op;
    double a, b;

    do {

        printf("\n1. +  2. -  3. *  4. /  0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &op) != 1) {
            viderBuffer();
            op = -1;
        }

        if (op == 0) {
            break;
        }

        if (op < 1 || op > 4) {
            printf("Operation inconnue.\n");
            continue;
        }

        printf("a = ");
        scanf("%lf", &a);
        printf("b = ");
        scanf("%lf", &b);

        switch (op) {
            case 1: printf("%.2f + %.2f = %.2f\n", a, b, a + b); break;
            case 2: printf("%.2f - %.2f = %.2f\n", a, b, a - b); break;
            case 3: printf("%.2f * %.2f = %.2f\n", a, b, a * b); break;
            case 4:
                if (b == 0) {
                    printf("Division par zero impossible.\n");
                } else {
                    printf("%.2f / %.2f = %.2f\n", a, b, a / b);
                }
                break;
        }

    } while (op != 0);
}


/*
    Exercice 2 - Pair, impair et multiples

    Analyse d'un entier saisi par l'utilisateur.
    - Indique s'il est pair ou impair.
    - Indique s'il est multiple de 3, de 5, des deux ou d'aucun.
*/

void pairImpairMultiples(void) {

    int n;

    printf("Nombre : ");
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("%d est pair.\n", n);
    } else {
        printf("%d est impair.\n", n);
    }

    if (n % 3 == 0 && n % 5 == 0) {
        printf("%d est multiple de 3 et de 5.\n", n);
    } else if (n % 3 == 0) {
        printf("%d est multiple de 3.\n", n);
    } else if (n % 5 == 0) {
        printf("%d est multiple de 5.\n", n);
    } else {
        printf("%d n'est multiple ni de 3 ni de 5.\n", n);
    }
}


/*
    Exercice 3 - Jeu de devinettes

    L'ordinateur choisit un nombre entre 1 et 100 ; le joueur doit le trouver.
    - Utilise srand(time(NULL)) et rand() % 100 + 1.
    - Affiche « plus grand » ou « plus petit » à chaque essai.
    - Affiche le nombre d'essais à la fin.
*/

void jeuDevinettes(void) {

    int secret = rand() % 100 + 1;
    int essai = 0;
    int nbEssais = 0;

    // pas de srand ici, je le fais une seule fois dans le main (sinon même nombre si on rejoue dans la même seconde)

    while (essai != secret) {

        printf("Essai : ");

        if (scanf("%d", &essai) != 1) {
            viderBuffer();
            continue;
        }

        nbEssais++;

        if (essai < secret) {
            printf("Plus grand !\n");
        } else if (essai > secret) {
            printf("Plus petit !\n");
        }
    }

    printf("Bravo, trouve en %d essais.\n", nbEssais);
}


/*
    Exercice 4 - Convertisseur d’unités

    Convertir des températures, des distances et des masses.
    - Une fonction par conversion : °C -> °F, km -> miles, kg -> livres.
    - Un menu permet de choisir la conversion.
*/

double celsiusVersFahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

double kmVersMiles(double km) {
    return km * 0.621371;
}

double kgVersLivres(double kg) {
    return kg * 2.20462;
}

void convertisseur(void) {

    int choix;
    double valeur;

    printf("1. Celsius -> Fahrenheit\n");
    printf("2. Km -> Miles\n");
    printf("3. Kg -> Livres\n");
    printf("Conversion (1-3) : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > 3) {
        printf("Conversion inconnue.\n");
        return;
    }

    printf("Valeur : ");
    scanf("%lf", &valeur);

    switch (choix) {
        case 1: printf("%.2f C = %.2f F\n", valeur, celsiusVersFahrenheit(valeur)); break;
        case 2: printf("%.2f km = %.2f miles\n", valeur, kmVersMiles(valeur)); break;
        case 3: printf("%.2f kg = %.2f livres\n", valeur, kgVersLivres(valeur)); break;
    }
}


/*
    Exercice 5 - Analyse d’une série de notes

    L'utilisateur encode n notes sur 20 (n <= 30).
    - Refuse toute note hors de 0 à 20.
    - Affiche la moyenne, la note minimale, la note maximale et le
      nombre de réussites (>= 10).
*/

void analyseNotes(void) {

    double notes[MAX_NOTES];
    int n;
    double somme = 0;
    double min, max;
    int reussites = 0;

    do {
        printf("Nombre de notes (1-%d) : ", MAX_NOTES);
        scanf("%d", &n);
    } while (n < 1 || n > MAX_NOTES);

    printf("Notes : ");

    for (int i = 0; i < n; i++) {

        scanf("%lf", &notes[i]);

        // je redemande juste la note fausse, pas toute la série
        while (notes[i] < 0 || notes[i] > 20) {
            printf("Note %d invalide, recommence : ", i + 1);
            scanf("%lf", &notes[i]);
        }
    }

    min = notes[0];
    max = notes[0];

    for (int i = 0; i < n; i++) {

        somme += notes[i];

        if (notes[i] < min) min = notes[i];
        if (notes[i] > max) max = notes[i];
        if (notes[i] >= 10) reussites++;
    }

    printf("Moyenne : %.2f\n", somme / n);
    printf("Min : %.0f   Max : %.0f\n", min, max);
    printf("Reussites : %d / %d\n", reussites, n);
}


/*
    Exercice 6 - Tables de multiplication

    Afficher une table, puis le tableau complet de 1 à 10.
    - Option 1 : afficher la table d'un nombre saisi.
    - Option 2 : afficher la grille 10 x 10 bien alignée.
*/

void tablesMultiplication(void) {

    int option, n;

    printf("1. Une table\n2. Grille complete\nOption : ");
    scanf("%d", &option);

    if (option == 1) {

        printf("Table de : ");
        scanf("%d", &n);

        for (int i = 1; i <= 10; i++) {
            printf("%2d x %d = %d\n", i, n, i * n);
        }

    } else if (option == 2) {

        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                printf("%4d", i * j);
            }
            printf("\n");
        }

    } else {
        printf("Option invalide.\n");
    }
}


/*
    Exercice 7 - Gestion d’un compte bancaire

    Simuler un compte : dépôt, retrait, consultation du solde.
    - Un retrait supérieur au solde est refusé.
    - Un montant négatif ou nul est refusé.
    - Garde un compteur du nombre d'opérations réussies.
*/

int montantValide(double montant) {
    return montant > 0;
}

void compteBancaire(void) {

    double solde = 150.0;
    double montant;
    int nbOperations = 0;
    int choix;

    do {

        printf("\nSolde : %.2f EUR\n", solde);
        printf("1. Depot\n2. Retrait\n0. Retour\nChoix : ");

        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            choix = -1;
        }

        if (choix == 1 || choix == 2) {

            printf("Montant : ");
            scanf("%lf", &montant);

            if (!montantValide(montant)) {
                printf("Refuse : montant invalide.\n");
            } else if (choix == 2 && montant > solde) {
                printf("Refuse : solde insuffisant.\n");
            } else {
                solde += (choix == 1) ? montant : -montant;
                nbOperations++;
            }

        } else if (choix != 0) {
            printf("Choix invalide.\n");
        }

    } while (choix != 0);

    printf("Operations reussies : %d\n", nbOperations);
}


/*
    Exercice 8 - Recherche dans un tableau

    Rechercher une valeur dans un tableau de 10 entiers.
    - Écris une fonction qui renvoie l'indice de la première
      occurrence, ou -1.
    - Compte ensuite le nombre total d'occurrences.
*/

int rechercher(const int t[], int n, int valeur) {

    for (int i = 0; i < n; i++) {
        if (t[i] == valeur) {
            return i;
        }
    }

    return -1;
}

int compter(const int t[], int n, int valeur) {

    int nb = 0;

    for (int i = 0; i < n; i++) {
        if (t[i] == valeur) {
            nb++;
        }
    }

    return nb;
}

void rechercheTableau(void) {

    int t[10] = { 4, 8, 15, 16, 23, 42, 8, 4, 8, 1 };
    int valeur, indice;

    printf("Tableau :");
    for (int i = 0; i < 10; i++) {
        printf(" %d", t[i]);
    }

    printf("\nValeur : ");
    scanf("%d", &valeur);

    indice = rechercher(t, 10, valeur);

    if (indice == -1) {
        printf("Valeur absente.\n");
    } else {
        printf("Premiere occurrence : indice %d\n", indice);
        printf("Occurrences : %d\n", compter(t, 10, valeur));
    }
}


/*
    Exercice 9 - Pierre – Papier – Ciseaux

    Une partie en 3 manches gagnantes contre l'ordinateur.
    - Code les coups par 0, 1, 2 et affiche-les en toutes lettres.
    - Écris une fonction qui renvoie 1 si le joueur gagne, -1 s'il
      perd, 0 en cas d'égalité.
    - Affiche le score après chaque manche.
*/

int manche(int joueur, int ordi) {

    if (joueur == ordi) {
        return 0;
    }

    // 0 pierre, 1 papier, 2 ciseaux : chaque coup bat celui juste avant lui, le modulo me permet de boucler (pierre bat ciseaux)
    if ((joueur - ordi + 3) % 3 == 1) {
        return 1;
    }

    return -1;
}

void pierrePapierCiseaux(void) {

    const char *coups[3] = { "pierre", "papier", "ciseaux" };
    int scoreJoueur = 0, scoreOrdi = 0;
    int joueur, ordi, resultat;

    while (scoreJoueur < 3 && scoreOrdi < 3) {

        printf("Ton coup (0 pierre, 1 papier, 2 ciseaux) : ");

        if (scanf("%d", &joueur) != 1 || joueur < 0 || joueur > 2) {
            viderBuffer();
            printf("Coup invalide.\n");
            continue;
        }

        ordi = rand() % 3;
        printf("Ordinateur : %s\n", coups[ordi]);

        resultat = manche(joueur, ordi);

        if (resultat == 1) {
            scoreJoueur++;
            printf("Gagne ! ");
        } else if (resultat == -1) {
            scoreOrdi++;
            printf("Perdu ! ");
        } else {
            printf("Egalite. ");
        }

        printf("Score %d - %d\n", scoreJoueur, scoreOrdi);
    }

    printf(scoreJoueur == 3 ? "Tu remportes la partie !\n" : "L'ordinateur gagne la partie.\n");
}


/*
    Exercice 10 - Mini gestionnaire de tâches

    Gérer une liste de 20 tâches maximum.
    - Ajouter une tâche (texte de 60 caractères maximum).
    - Marquer une tâche comme faite, afficher la liste avec [x] ou [ ].
    - Supprimer une tâche en décalant les suivantes.

    char taches[20][61];
    int faite[20];
    int nb = 0;
*/

char taches[MAX_TACHES][61];
int faite[MAX_TACHES];
int nb = 0;

void gestionnaireTaches(void) {

    int choix, num;

    do {

        printf("\n");
        for (int i = 0; i < nb; i++) {
            printf("%d. [%c] %s\n", i + 1, faite[i] ? 'x' : ' ', taches[i]);
        }

        printf("\n1. Ajouter\n2. Marquer comme faite\n3. Supprimer\n0. Retour\nChoix : ");

        if (scanf("%d", &choix) != 1) {
            choix = -1;
        }
        viderBuffer();   // j'enlève le \n laissé par scanf, sinon fgets lit directement une ligne vide

        switch (choix) {

            case 1:
                if (nb == MAX_TACHES) {
                    printf("Liste pleine.\n");
                    break;
                }

                printf("Tache : ");
                fgets(taches[nb], sizeof taches[nb], stdin);

                if (strchr(taches[nb], '\n') == NULL) {
                    viderBuffer();   // texte trop long : je jette la fin
                }
                taches[nb][strcspn(taches[nb], "\n")] = '\0';

                faite[nb] = 0;
                nb++;
                break;

            case 2:
                printf("Numero : ");
                scanf("%d", &num);
                viderBuffer();

                if (num >= 1 && num <= nb) {
                    faite[num - 1] = 1;
                } else {
                    printf("Numero invalide.\n");
                }
                break;

            case 3:
                printf("Numero : ");
                scanf("%d", &num);
                viderBuffer();

                if (num < 1 || num > nb) {
                    printf("Numero invalide.\n");
                    break;
                }

                // je décale tout d'une case vers la gauche pour boucher le trou
                for (int i = num - 1; i < nb - 1; i++) {
                    strcpy(taches[i], taches[i + 1]);
                    faite[i] = faite[i + 1];
                }
                nb--;
                break;

            case 0:
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);
}
