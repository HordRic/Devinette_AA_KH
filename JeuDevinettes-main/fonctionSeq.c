/**

    Dans ce fichier source se trouve la définition
    de toutes les fonctions utilisées dans le jeu
    (main.c)

*/

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include "fonctionSeq.h"

// Fonction booléenne qui renvoie true si le pseudo existe déjà et false sinon
bool verifiePseudo(const char* pseudo, FILE* file) {
    file = fopen("score.txt", "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return false;
    }
    char ligne[300];
    while (fgets(ligne, sizeof(ligne), file)) {
        printf("Ligne lue: %s", ligne);
        // Utilisation de strcmp pour comparer les chaînes de caractères
        if (strcmp(ligne, pseudo) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void archivePseudo(const char* pseudo, FILE* file) {
    file = fopen("score.txt", "a");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    fprintf(file, "%s\n", pseudo); // Correction de fprintf pour inclure file
    fclose(file);
    printf("%s, ton pseudo vient d'\250tre enregistré avec succès !\n", pseudo);
}
