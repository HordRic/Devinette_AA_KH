#ifndef FONCTIONSEQ_H
#define FONCTIONSEQ_H

#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************
 * STRUCTURE : Utilisateur
 * DESCRIPTION : Stocke les informations d'un joueur
 ******************************************************************************/
typedef struct {
    char pseudo[50];
    char mdp[50];
    int meilleur_score;
    int parties_jouees;
} Utilisateur;

/*******************************************************************************
 * FONCTION : verifierUtilisateur
 * DESCRIPTION : Vérifie l'existence d'un pseudo dans la base de données
 ******************************************************************************/
bool verifierUtilisateur(const char* pseudo);

/*******************************************************************************
 * FONCTION : authentifierUtilisateur
 * DESCRIPTION : Vérifie la correspondance pseudo/mot de passe
 ******************************************************************************/
bool authentifierUtilisateur(const char* pseudo, const char* mdp);

/*******************************************************************************
 * FONCTION : creerUtilisateur
 * DESCRIPTION : Enregistre un nouveau joueur dans le système
 ******************************************************************************/
void creerUtilisateur(const char* pseudo, const char* mdp);

/*******************************************************************************
 * FONCTION : sauvegarderScore
 * DESCRIPTION : Met à jour les statistiques du joueur
 ******************************************************************************/
void sauvegarderScore(const char* pseudo, int score);

/*******************************************************************************
 * FONCTION : afficherStatistiques
 * DESCRIPTION : Affiche l'historique des parties d'un joueur
 ******************************************************************************/
void afficherStatistiques(const char* pseudo);

#endif // FONCTIONSEQ_H
