/*
    Labo 2 - Exercice 5 : Les gardes d’inclusion

    - Crée point.h qui définit typedef struct { int x, y; } Point; SANS garde.
    - Inclus-le deux fois (directement et via geo.h) et lis l'erreur.
    - Ajoute les gardes #ifndef POINT_H / #define / #endif et recompile.

    Sans les gardes j'obtiens : point.h:1:30: error: conflicting types for 'Point'
    main.c inclut point.h, puis geo.h qui l'inclut une deuxième fois, donc Point est défini deux fois.
*/

#ifndef POINT_H
#define POINT_H

typedef struct { int x, y; } Point;

#endif
