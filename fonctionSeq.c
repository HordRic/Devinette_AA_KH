#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fonctionSeq.h"

#define FICHIER_DONNEES "joueurs.dat"
#define MAX_UTILISATEURS 100

/*******************************************************************************
 * FONCTION : chargerUtilisateurs
 * DESCRIPTION : Charge les utilisateurs depuis le fichier binaire
 ******************************************************************************/
static int chargerUtilisateurs(Utilisateur* utilisateurs)
{
    FILE* fichier = fopen(FICHIER_DONNEES, "rb");
    if(!fichier) return 0;

    int count = 0;
    while(fread(&utilisateurs[count], sizeof(Utilisateur), 1, fichier)) {
        count++;
    }
    fclose(fichier);
    return count;
}

/*******************************************************************************
 * FONCTION : sauvegarderUtilisateurs
 * DESCRIPTION : Écrit les utilisateurs dans le fichier binaire
 ******************************************************************************/
static void sauvegarderUtilisateurs(Utilisateur* utilisateurs, int count)
{
    FILE* fichier = fopen(FICHIER_DONNEES, "wb");
    if(!fichier) return;

    for(int i=0; i<count; i++) {
        fwrite(&utilisateurs[i], sizeof(Utilisateur), 1, fichier);
    }
    fclose(fichier);
}

bool verifierUtilisateur(const char* pseudo)
{
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int count = chargerUtilisateurs(utilisateurs);

    for(int i=0; i<count; i++) {
        if(strcmp(utilisateurs[i].pseudo, pseudo) == 0) return true;
    }
    return false;
}

bool authentifierUtilisateur(const char* pseudo, const char* mdp)
{
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int count = chargerUtilisateurs(utilisateurs);

    for(int i=0; i<count; i++) {
        if(strcmp(utilisateurs[i].pseudo, pseudo) == 0 &&
           strcmp(utilisateurs[i].mdp, mdp) == 0) return true;
    }
    return false;
}

void creerUtilisateur(const char* pseudo, const char* mdp)
{
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int count = chargerUtilisateurs(utilisateurs);

    strncpy(utilisateurs[count].pseudo, pseudo, 49);
    strncpy(utilisateurs[count].mdp, mdp, 49);
    utilisateurs[count].meilleur_score = 0;
    utilisateurs[count].parties_jouees = 0;

    sauvegarderUtilisateurs(utilisateurs, count+1);
}

void sauvegarderScore(const char* pseudo, int score)
{
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int count = chargerUtilisateurs(utilisateurs);

    for(int i=0; i<count; i++) {
        if(strcmp(utilisateurs[i].pseudo, pseudo) == 0) {
            if(score < utilisateurs[i].meilleur_score || utilisateurs[i].meilleur_score == 0) {
                utilisateurs[i].meilleur_score = score;
            }
            utilisateurs[i].parties_jouees++;
            break;
        }
    }
    sauvegarderUtilisateurs(utilisateurs, count);
}

void afficherStatistiques(const char* pseudo)
{
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int count = chargerUtilisateurs(utilisateurs);

    for(int i=0; i<count; i++) {
        if(strcmp(utilisateurs[i].pseudo, pseudo) == 0) {
            printf("\n=== STATISTIQUES ===\n");
            printf("Meilleur score : %d\n", utilisateurs[i].meilleur_score);
            printf("Parties jouees : %d\n", utilisateurs[i].parties_jouees);
            return;
        }
    }
    printf("Aucune statistique disponible\n");
}
