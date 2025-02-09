#ifndef FONCTIONJEU_H
#define FONCTIONJEU_H

#include <stdbool.h>

/*******************************************************************************
 * CONSTANTES : Définition des niveaux de difficulté
 ******************************************************************************/
#define FACILE 20
#define NORMAL 100
#define DIFFICILE 200
#define MAX_TENTATIVES 10

/*******************************************************************************
 * FONCTION : lancerJeu
 * DESCRIPTION : Point d'entrée principal du jeu
 ******************************************************************************/
void lancerJeu();

/*******************************************************************************
 * FONCTION : gererAuthentification
 * DESCRIPTION : Gère le processus de connexion/inscription
 ******************************************************************************/
void gererAuthentification(char* pseudo);

#endif // FONCTIONJEU_H
