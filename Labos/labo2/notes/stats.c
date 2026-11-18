#include <stdio.h>
#include "stats.h"


int saisirNotes(double notes[], int max) {

    int n;

    do {
        printf("Nombre de notes (1-%d) : ", max);
        scanf("%d", &n);
    } while (n < 1 || n > max);

    for (int i = 0; i < n; i++) {
        do {
            printf("Note %d : ", i + 1);
            scanf("%lf", &notes[i]);
        } while (notes[i] < 0 || notes[i] > 20);
    }

    return n;
}

double moyenne(const double notes[], int n) {

    double somme = 0;

    for (int i = 0; i < n; i++) {
        somme += notes[i];
    }

    return somme / n;
}

double minimum(const double notes[], int n) {

    double min = notes[0];

    for (int i = 1; i < n; i++) {
        if (notes[i] < min) min = notes[i];
    }

    return min;
}

double maximum(const double notes[], int n) {

    double max = notes[0];

    for (int i = 1; i < n; i++) {
        if (notes[i] > max) max = notes[i];
    }

    return max;
}

void afficherBilan(const double notes[], int n) {

    int reussites = 0;

    for (int i = 0; i < n; i++) {
        if (notes[i] >= 10) reussites++;
    }

    printf("Moyenne : %.2f\n", moyenne(notes, n));
    printf("Min : %.2f   Max : %.2f\n", minimum(notes, n), maximum(notes, n));
    printf("Reussites : %d / %d\n", reussites, n);
}
