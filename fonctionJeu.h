#ifndef FONCTIONJEU_H
#define FONCTIONJEU_H

#include <stdbool.h>

/*******************************************************************************
 * CONSTANTES : D�finition des niveaux de difficult�
 ******************************************************************************/
#define FACILE 20
#define NORMAL 100
#define DIFFICILE 200
#define MAX_TENTATIVES 10

/*******************************************************************************
 * FONCTION : lancerJeu
 * DESCRIPTION : Point d'entr�e principal du jeu
 ******************************************************************************/
void lancerJeu();

/*******************************************************************************
 * FONCTION : gererAuthentification
 * DESCRIPTION : G�re le processus de connexion/inscription
 ******************************************************************************/
void gererAuthentification(char* pseudo);

#endif // FONCTIONJEU_H
