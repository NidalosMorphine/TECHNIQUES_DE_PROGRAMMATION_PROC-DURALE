/*
    Correctif du labo 0

    Exercices 4 à 10 : le profil du développeur.
    gcc -std=c11 -Wall -Wextra main.c -o profil
*/

#include <stdio.h>

#define MAX_COMPETENCES 10
#define NB_PROJETS 4


const char *nom = "Romain Chariot";
const char *formation = "Informatique de gestion";
const char *presentation = "Dev C, Java et Angular";
const char *depot = "github.com/NidalosMorphine";

const char *techno[MAX_COMPETENCES] = { "C", "Python", "SQL", "Java", "Git", "Angular" };
int niveau[MAX_COMPETENCES] = { 5, 4, 4, 3, 3, 2 };
int nbCompetences = 6;

const char *projetNom[NB_PROJETS] = { "Gestion de stock", "Portfolio", "Bot Discord", "Site du club" };
const char *projetTechno[NB_PROJETS] = { "Java", "Angular", "Python", "PHP" };
int projetAnnee[NB_PROJETS] = { 2024, 2025, 2025, 2026 };
int projetStatut[NB_PROJETS] = { 0, 1, 2, 1 };


void afficherProfil(void);
void afficherJauge(const char *nomTechno, int niv);
void afficherToutesCompetences(void);
void afficherCompetences(const char *techno[], const int niveau[], int n, int seuil);
void filtrerParNiveau(void);
const char *libelleStatut(int statut);
void afficherProjets(void);
void afficherStatistiques(void);


/*
    Exercice 9 - Le menu du profil / Exercice 10 - Livrer proprement

    Assemble toutes les briques derrière un menu en ligne de commande.
    - Affiche le menu, lis le choix, appelle la bonne fonction.
    - Le menu se répète jusqu'au choix 0.
    - Un choix invalide affiche un message d'erreur sans quitter.

    Découpe le main : il ne doit plus contenir que le menu.
*/

int main(void) {

    int choix;

    do {

        printf("\n=== MON PROFIL ===\n");
        printf("1. Profil\n");
        printf("2. Competences\n");
        printf("3. Filtrer les competences\n");
        printf("4. Projets\n");
        printf("5. Statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) {
            // si l'utilisateur tape des lettres, scanf ne lit rien et les laisse dans le buffer -> je vide la ligne sinon boucle infinie
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choix = -1;
        }

        switch (choix) {
            case 1: afficherProfil(); break;
            case 2: afficherToutesCompetences(); break;
            case 3: filtrerParNiveau(); break;
            case 4: afficherProjets(); break;
            case 5: afficherStatistiques(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}


/*
    Exercice 4 - Afficher son profil

    Déclare des variables pour le nom, la formation, une présentation
    courte et le lien du dépôt. Affiche-les dans un encadré lisible.
*/

void afficherProfil(void) {

    printf("+--------------------------------------------+\n");
    printf("| %-42s |\n", nom);
    printf("| Formation : %-30s |\n", formation);
    printf("| Profil    : %-30s |\n", presentation);
    printf("| Depot     : %-30s |\n", depot);
    printf("+--------------------------------------------+\n");
}


/*
    Exercice 5 - Les compétences techniques

    On mémorise jusqu'à 10 compétences avec leur niveau (de 1 à 5).
    - Deux tableaux parallèles : const char *techno[10] et int niveau[10].
    - Remplis 6 compétences et affiche-les avec une jauge d'étoiles.
*/

void afficherJauge(const char *nomTechno, int niv) {

    printf("%-10s ", nomTechno);

    for (int k = 1; k <= 5; k++) {
        printf("%c", k <= niv ? '*' : '.');
    }

    printf("\n");
}

void afficherToutesCompetences(void) {

    for (int i = 0; i < nbCompetences; i++) {
        afficherJauge(techno[i], niveau[i]);
    }
}


/*
    Exercice 6 - Filtrer par niveau

    On ne veut afficher que les compétences au-dessus d'un seuil
    saisi par l'utilisateur.
    - Une fonction affiche les compétences dont le niveau est >= au seuil.
    - Lis le seuil avec scanf et refuse une valeur hors de 1 à 5.
*/

void afficherCompetences(const char *techno[], const int niveau[], int n, int seuil) {

    for (int i = 0; i < n; i++) {
        if (niveau[i] >= seuil) {
            afficherJauge(techno[i], niveau[i]);
        }
    }
}

void filtrerParNiveau(void) {

    int seuil;

    printf("Seuil minimum (1-5) : ");

    if (scanf("%d", &seuil) != 1 || seuil < 1 || seuil > 5) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Seuil invalide.\n");
        return;
    }

    afficherCompetences(techno, niveau, nbCompetences, seuil);
}


/*
    Exercice 7 - Les projets réalisés

    Chaque projet possède un nom, une technologie, une année et un
    statut (0 = terminé, 1 = en cours, 2 = abandonné).
    - Stocke au moins 4 projets dans des tableaux parallèles.
    - Affiche le statut en toutes lettres grâce à un switch.
*/

const char *libelleStatut(int statut) {

    switch (statut) {
        case 0: return "termine";
        case 1: return "en cours";
        case 2: return "abandonne";
        default: return "inconnu";
    }
}

void afficherProjets(void) {

    for (int i = 0; i < NB_PROJETS; i++) {
        printf("%d  %-20s  %-8s %s\n",
               projetAnnee[i],
               projetNom[i],
               projetTechno[i],
               libelleStatut(projetStatut[i]));
    }
}


/*
    Exercice 8 - Quelques statistiques

    - Nombre de technologies connues et niveau moyen (2 décimales).
    - Pourcentage de projets terminés.
    - Technologie la plus maîtrisée (la première en cas d'égalité).
*/

void afficherStatistiques(void) {

    int total = 0;
    int meilleur = 0;
    int termines = 0;

    for (int i = 0; i < nbCompetences; i++) {

        total += niveau[i];

        // j'utilise > et pas >= pour garder la première en cas d'égalité
        if (niveau[i] > niveau[meilleur]) {
            meilleur = i;
        }
    }

    for (int i = 0; i < NB_PROJETS; i++) {
        if (projetStatut[i] == 0) {
            termines++;
        }
    }

    printf("Technologies connues : %d\n", nbCompetences);
    printf("Niveau moyen         : %.2f\n", (double) total / nbCompetences);
    printf("Projets termines     : %.1f %%\n", 100.0 * termines / NB_PROJETS);
    printf("Point fort           : %s\n", techno[meilleur]);
}
