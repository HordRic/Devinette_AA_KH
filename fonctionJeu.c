#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "fonctionJeu.h"
#include "fonctionSeq.h"

/*******************************************************************************
 * FONCTION : genererNombreSecret
 * DESCRIPTION : Génère un nombre aléatoire dans un intervalle donné
 ******************************************************************************/
static int genererNombreSecret(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

/*******************************************************************************
 * FONCTION : choisirDifficulte
 * DESCRIPTION : Permet à l'utilisateur de choisir la difficulté
 ******************************************************************************/
static int choisirDifficulte(int* min, int* max)
{
    int choix;
    printf("\n=== CHOIX DE LA DIFFICULTE ===\n");
    printf("1. Facile (0-%d)\n", FACILE);
    printf("2. Normal (0-%d)\n", NORMAL);
    printf("3. Difficile (0-%d)\n", DIFFICILE);
    printf("4. Personnalise\n");
    printf("Choix : ");
    scanf("%d", &choix);

    *min = 0;
    switch(choix) {
        case 1: *max = FACILE; break;
        case 2: *max = NORMAL; break;
        case 3: *max = DIFFICILE; break;
        case 4:
            printf("Borne minimale : ");
            scanf("%d", min);
            printf("Borne maximale : ");
            scanf("%d", max);
            if(*max - *min < DIFFICILE) {
                printf("Intervalle trop petit! Defaut au mode difficile\n");
                *min = 0;
                *max = DIFFICILE;
            }
            break;
        default:
            printf("Choix invalide! Defaut au mode normal\n");
            *max = NORMAL;
    }
    return choix;
}

/*******************************************************************************
 * FONCTION : jouerPartie
 * DESCRIPTION : Contrôle le déroulement d'une partie
 ******************************************************************************/
static void jouerPartie(const char* pseudo, int min, int max)
{
    int nombreSecret = genererNombreSecret(min, max);
    int tentative, essais = 0;

    printf("\n=== DEBUT DE LA PARTIE ===\n");
    printf("Trouvez le nombre entre %d et %d\n", min, max);

    while(essais < MAX_TENTATIVES) {
        printf("Essai %d/%d > ", essais+1, MAX_TENTATIVES);
        scanf("%d", &tentative);
        essais++;

        if(tentative == nombreSecret) {
            printf("\nBravo %s! Trouve en %d essais!\n", pseudo, essais);
            sauvegarderScore(pseudo, essais);
            return;
        }
        printf("%s\n", (tentative < nombreSecret) ? " Le nombre est Plus grand !" : "Le nombre est Plus petit!");
    }
    printf("\nPerdu! Le nombre etait : %d\n", nombreSecret);
}

void lancerJeu()
{
    srand(time(NULL));
    char pseudo[50];
    int min, max;

    gererAuthentification(pseudo);
    choisirDifficulte(&min, &max);
    jouerPartie(pseudo, min, max);
    afficherStatistiques(pseudo);
}

void gererAuthentification(char* pseudo)
{
    char mdp[50];
    printf("\n=== AUTHENTIFICATION ===\n");

    while(true) {
        printf("Pseudo : ");
        scanf("%49s", pseudo);

        if(verifierUtilisateur(pseudo)) {
            printf("Mot de passe : ");
            scanf("%49s", mdp);
            if(authentifierUtilisateur(pseudo, mdp)) break;
            printf("Mot de passe incorrect!\n");
        } else {
            printf("Nouveau compte - Choisir mot de passe : ");
            scanf("%49s", mdp);
            creerUtilisateur(pseudo, mdp);
            break;
        }
    }
}
