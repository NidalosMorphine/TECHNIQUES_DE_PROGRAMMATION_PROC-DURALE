#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* ---------------------------------------------------------
   PROTOTYPES DES FONCTIONS
   --------------------------------------------------------- */

void calculatrice(void);
void pairImpairMultiples(void);
void jeuDevinettes(void);
void convertisseur(void);
void analyseNotes(void);
void tablesMultiplication(void);
void compteBancaire(void);
void rechercheTableau(void);
void pierrePapierCiseaux(void);
void gestionnaireTaches(void);


/* ---------------------------------------------------------
   PROGRAMME PRINCIPAL
   --------------------------------------------------------- */

int main(void) {

    int choix;

    /* Initialisation du générateur de nombres aléatoires */
    srand(time(NULL));

    do {

        printf("\n====================================\n");
        printf("          EXERCICES EN C\n");
        printf("====================================\n");

        printf("1. Calculatrice\n");
        printf("2. Pair, impair et multiples\n");
        printf("3. Jeu de devinettes\n");
        printf("4. Convertisseur d'unites\n");
        printf("5. Analyse d'une serie de notes\n");
        printf("6. Tables de multiplication\n");
        printf("7. Gestion d'un compte bancaire\n");
        printf("8. Recherche dans un tableau\n");
        printf("9. Pierre - Papier - Ciseaux\n");
        printf("10. Mini gestionnaire de taches\n");

        printf("0. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {

            case 1:
                calculatrice();
                break;

            case 2:
                pairImpairMultiples();
                break;

            case 3:
                jeuDevinettes();
                break;

            case 4:
                convertisseur();
                break;

            case 5:
                analyseNotes();
                break;

            case 6:
                tablesMultiplication();
                break;

            case 7:
                compteBancaire();
                break;

            case 8:
                rechercheTableau();
                break;

            case 9:
                pierrePapierCiseaux();
                break;

            case 10:
                gestionnaireTaches();
                break;

            case 0:
                printf("\nAu revoir !\n");
                break;

            default:
                printf("\nChoix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}


/* =========================================================
   EXERCICE 1
   CALCULATRICE
   ========================================================= */

void calculatrice(void) {

    int choix;
    float a;
    float b;
    float resultat;

    do {

        printf("\n=== CALCULATRICE ===\n");

        printf("1. Addition\n");
        printf("2. Soustraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Pythagore\n");
        printf("0. Retour\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 5) {

            printf("Premier nombre : ");
            scanf("%f", &a);

            printf("Deuxieme nombre : ");
            scanf("%f", &b);
        }

        switch (choix) {

            case 1:
                resultat = a + b;
                printf("Resultat : %.2f\n", resultat);
                break;

            case 2:
                resultat = a - b;
                printf("Resultat : %.2f\n", resultat);
                break;

            case 3:
                resultat = a * b;
                printf("Resultat : %.2f\n", resultat);
                break;

            case 4:

                if (b != 0) {
                    resultat = a / b;
                    printf("Resultat : %.2f\n", resultat);
                } else {
                    printf("Division par zero impossible.\n");
                }

                break;

            case 5:

                resultat = sqrt((a * a) + (b * b));

                printf("Hypotenuse : %.2f\n", resultat);

                break;
        }

    } while (choix != 0);
}


/* =========================================================
   EXERCICE 2
   PAIR, IMPAIR ET MULTIPLES
   ========================================================= */

void pairImpairMultiples(void) {

    int nombre;

    printf("\n=== PAIR / IMPAIR / MULTIPLES ===\n");

    printf("Entrez un nombre : ");
    scanf("%d", &nombre);

    if (nombre % 2 == 0) {
        printf("%d est pair.\n", nombre);
    } else {
        printf("%d est impair.\n", nombre);
    }

    if (nombre % 3 == 0) {
        printf("%d est un multiple de 3.\n", nombre);
    }

    if (nombre % 5 == 0) {
        printf("%d est un multiple de 5.\n", nombre);
    }

    if (nombre % 10 == 0) {
        printf("%d est un multiple de 10.\n", nombre);
    }
}


/* =========================================================
   EXERCICE 3
   JEU DE DEVINETTES
   ========================================================= */

void jeuDevinettes(void) {

    int nombreSecret;
    int proposition;
    int nombreTentatives = 0;

    /* Nombre aleatoire entre 1 et 100 */
    nombreSecret = rand() % 100 + 1;

    printf("\n=== JEU DE DEVINETTES ===\n");
    printf("Trouvez un nombre entre 1 et 100.\n");

    do {

        printf("Votre proposition : ");
        scanf("%d", &proposition);

        nombreTentatives++;

        if (proposition < nombreSecret) {
            printf("Trop petit !\n");
        }

        else if (proposition > nombreSecret) {
            printf("Trop grand !\n");
        }

        else {
            printf("Bravo !\n");
        }

    } while (proposition != nombreSecret);

    printf("Nombre de tentatives : %d\n", nombreTentatives);
}


/* =========================================================
   EXERCICE 4
   CONVERTISSEUR
   ========================================================= */

void convertisseur(void) {

    int choix;
    float valeur;
    float resultat;

    do {

        printf("\n=== CONVERTISSEUR ===\n");

        printf("1. Celsius vers Fahrenheit\n");
        printf("2. Fahrenheit vers Celsius\n");
        printf("3. Kilometres vers Miles\n");
        printf("4. Metres vers Pieds\n");
        printf("0. Retour\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 4) {

            printf("Valeur : ");
            scanf("%f", &valeur);
        }

        switch (choix) {

            case 1:

                resultat = valeur * 9 / 5 + 32;

                printf("%.2f C = %.2f F\n",
                       valeur,
                       resultat);

                break;

            case 2:

                resultat = (valeur - 32) * 5 / 9;

                printf("%.2f F = %.2f C\n",
                       valeur,
                       resultat);

                break;

            case 3:

                resultat = valeur * 0.621371f;

                printf("%.2f km = %.2f miles\n",
                       valeur,
                       resultat);

                break;

            case 4:

                resultat = valeur * 3.28084f;

                printf("%.2f m = %.2f pieds\n",
                       valeur,
                       resultat);

                break;
        }

    } while (choix != 0);
}


/* =========================================================
   EXERCICE 5
   ANALYSE D'UNE SERIE DE NOTES
   ========================================================= */

void analyseNotes(void) {

    int notes[5];

    int total = 0;
    int minimum;
    int maximum;
    int reussites = 0;

    float moyenne;

    printf("\n=== ANALYSE DES NOTES ===\n");

    /* Encodage des notes */

    for (int i = 0; i < 5; i++) {

        printf("Note %d : ", i + 1);

        scanf("%d", &notes[i]);
    }

    minimum = notes[0];
    maximum = notes[0];

    /* Analyse du tableau */

    for (int i = 0; i < 5; i++) {

        total = total + notes[i];

        if (notes[i] < minimum) {
            minimum = notes[i];
        }

        if (notes[i] > maximum) {
            maximum = notes[i];
        }

        if (notes[i] >= 10) {
            reussites++;
        }
    }

    moyenne = (float) total / 5;

    printf("\nMoyenne : %.2f\n", moyenne);

    printf("Minimum : %d\n", minimum);

    printf("Maximum : %d\n", maximum);

    printf("Reussites : %d / 5\n", reussites);
}


/* =========================================================
   EXERCICE 6
   TABLES DE MULTIPLICATION
   ========================================================= */

void tablesMultiplication(void) {

    int nombre;

    printf("\n=== TABLE DE MULTIPLICATION ===\n");

    printf("Entrez un nombre : ");
    scanf("%d", &nombre);

    for (int i = 1; i <= 10; i++) {

        printf("%d x %d = %d\n",
               nombre,
               i,
               nombre * i);
    }
}


/* =========================================================
   EXERCICE 7
   COMPTE BANCAIRE
   ========================================================= */

void compteBancaire(void) {

    float solde = 500.0f;
    float montant;

    int choix;

    do {

        printf("\n=== COMPTE BANCAIRE ===\n");

        printf("Solde actuel : %.2f EUR\n", solde);

        printf("\n1. Depot\n");
        printf("2. Retrait\n");
        printf("3. Afficher le solde\n");
        printf("0. Retour\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {

            case 1:

                printf("Montant du depot : ");

                scanf("%f", &montant);

                if (montant > 0) {

                    solde = solde + montant;

                    printf("Depot effectue.\n");
                }

                break;

            case 2:

                printf("Montant du retrait : ");

                scanf("%f", &montant);

                if (montant <= solde && montant > 0) {

                    solde = solde - montant;

                    printf("Retrait effectue.\n");

                } else {

                    printf("Retrait impossible.\n");
                }

                break;

            case 3:

                printf("Votre solde est de %.2f EUR\n",
                       solde);

                break;
        }

    } while (choix != 0);
}


/* =========================================================
   EXERCICE 8
   RECHERCHE DANS UN TABLEAU
   ========================================================= */

void rechercheTableau(void) {

    int nombres[] = {
        12,
        45,
        7,
        23,
        56,
        18,
        9
    };

    int taille = 7;

    int valeurRecherchee;

    bool trouve = false;

    printf("\n=== RECHERCHE ===\n");

    printf("Nombre recherche : ");

    scanf("%d", &valeurRecherchee);

    for (int i = 0; i < taille; i++) {

        if (nombres[i] == valeurRecherchee) {

            printf("%d trouve a la position %d.\n",
                   valeurRecherchee,
                   i + 1);

            trouve = true;
        }
    }

    if (trouve == false) {

        printf("%d n'est pas present dans le tableau.\n",
               valeurRecherchee);
    }
}


/* =========================================================
   EXERCICE 9
   PIERRE - PAPIER - CISEAUX
   ========================================================= */

void pierrePapierCiseaux(void) {

    int joueur;
    int ordinateur;

    printf("\n=== PIERRE PAPIER CISEAUX ===\n");

    printf("1. Pierre\n");
    printf("2. Papier\n");
    printf("3. Ciseaux\n");

    printf("\nVotre choix : ");

    scanf("%d", &joueur);

    ordinateur = rand() % 3 + 1;

    printf("Choix de l'ordinateur : ");

    if (ordinateur == 1) {
        printf("Pierre\n");
    }

    else if (ordinateur == 2) {
        printf("Papier\n");
    }

    else {
        printf("Ciseaux\n");
    }


    /* Egalite */

    if (joueur == ordinateur) {

        printf("Egalite !\n");
    }

    /* Victoire du joueur */

    else if (
        (joueur == 1 && ordinateur == 3)
        ||
        (joueur == 2 && ordinateur == 1)
        ||
        (joueur == 3 && ordinateur == 2)
    ) {

        printf("Vous gagnez !\n");
    }

    /* Sinon l'ordinateur gagne */

    else {

        printf("L'ordinateur gagne !\n");
    }
}


/* =========================================================
   EXERCICE 10
   MINI GESTIONNAIRE DE TACHES
   ========================================================= */

void gestionnaireTaches(void) {

    /*
        false = tache non terminee
        true  = tache terminee
    */

    bool taches[5] = {
        false,
        false,
        false,
        false,
        false
    };

    int choix;
    int numeroTache;

    do {

        printf("\n=== GESTIONNAIRE DE TACHES ===\n");

        /* Affichage des taches */

        printf("1. [%c] Installer CLion\n",
               taches[0] ? 'X' : ' ');

        printf("2. [%c] Creer le repository Git\n",
               taches[1] ? 'X' : ' ');

        printf("3. [%c] Terminer le labo\n",
               taches[2] ? 'X' : ' ');

        printf("4. [%c] Commit et Push\n",
               taches[3] ? 'X' : ' ');

        printf("5. [%c] Relire le cours\n",
               taches[4] ? 'X' : ' ');


        printf("\n1. Terminer une tache\n");
        printf("2. Afficher la progression\n");
        printf("0. Retour\n");

        printf("\nVotre choix : ");

        scanf("%d", &choix);


        if (choix == 1) {

            printf("Numero de la tache : ");

            scanf("%d", &numeroTache);

            if (numeroTache >= 1 && numeroTache <= 5) {

                taches[numeroTache - 1] = true;

                printf("Tache terminee !\n");

            } else {

                printf("Numero incorrect.\n");
            }
        }


        else if (choix == 2) {

            int nombreTerminees = 0;

            /* Compter les taches terminees */

            for (int i = 0; i < 5; i++) {

                if (taches[i] == true) {

                    nombreTerminees++;
                }
            }


            float progression;

            progression =
                ((float) nombreTerminees / 5) * 100;


            printf("Taches terminees : %d / 5\n",
                   nombreTerminees);

            printf("Progression : %.2f %%\n",
                   progression);
        }

    } while (choix != 0);
}