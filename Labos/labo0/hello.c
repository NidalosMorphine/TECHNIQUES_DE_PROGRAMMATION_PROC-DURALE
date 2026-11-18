/*
    Labo 0 - Exercice 1 : Vérifier son installation

    Ouvre un terminal (MSYS2 ou PowerShell) et tape gcc --version.
    Crée hello.c qui affiche « Bonjour ITLG ! ».
    Compile avec gcc -std=c11 -Wall -Wextra hello.c -o hello,
    puis exécute ./hello.
*/

#include <stdio.h>

int main(void) {

    printf("Bonjour ITLG !\n");

    return 0;
}
