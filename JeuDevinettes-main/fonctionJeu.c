#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "fonctionJeu.h"

//Listes de fonctions pour controler les entrées de l'utilisateur

int lireEntier() {
    int valeur;
    char buffer[100];
    while (true) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valeur) == 1) {
                return valeur;
            }
        }
        printf("Entr\351e invalide.\nVeuillez entrer un entier : \n");
    }
}


//Fonction qui permet à l'utilisateur de comprendre un peu le jeu
void afficheRegles(){
    printf("R\350gles : \n");
    printf("\tAu d\351but du jeu, vous devez choisir un intervalle. \n");
    printf("\tUn nombre appartenant \340 cet intervalle sera alors g\351n\351r\351.\n");
    printf("\tVotre objectif sera de trouver ce nombre en faisant le \n\tmoins de tentatives possibles.\n\n\n");
}

// Prend en paramètre un intervalle et retourne un nombre aléatoirement
// généré et appartenant à cet intervalle
int getRandomInt(int bornInf, int bornSup){
    int randomInt;
    srand(time(NULL));
    randomInt = (rand() % (bornSup - bornInf + 1)) + bornInf;
    printf("Nombre Random = %d\n", randomInt);
    return randomInt;
}

//Fonction qui lit un intervalle et génère un nombre aléatoire qui appartient à cet intervalle
int lireIntervalle(){
    int bornInf, bornSup, randomInt;
    bool valid = false;
    while(valid == false){
        printf("Entrez la Borne Inf\351rieure de l'intervalle : ");
        bornInf = lireEntier();
        printf("Entrez maintenant la Borne Sup\351rieure : ");
        bornSup = lireEntier();
        if(bornSup - bornInf < 20){
            printf("\tIntervalle Incorrect\nNous allons recommencer.");
        }
        else {
            randomInt = getRandomInt(bornInf,bornSup);
            valid = true;
        }
    }
    return randomInt;
}

// Menu qui affiche les différents intervalles par défaut
void proposeIntervalle(){
    printf("- Intervalle par d\351faut : \n");
    printf("\t1. Facile       : Entre 0 et 20\n");
    printf("\t2. Normale      : Entre 0 et 100\n");
    printf("\t3. Difficile    : Entre 0 et 200\n");
    printf("\t4. Personnalisé : Entre 0 et 200\n");
}

// Procédure qui affiche un message d'orientation pour aider l'utilisateur
// à trouver le nombre généré par la machine
void messageOrientation(int nbreLu, int nbreRandom){
    if (nbreLu < nbreRandom){
        printf("- %d est Plus Petit que le Nombre Secret\n", nbreLu);
    }
    else if(nbreLu > nbreRandom){
        printf("- %d est Plus Grand que le Nombre Secret\n", nbreLu);
    }
    else{
        printf("Entr\251e Invalide ou Non prise en charge\n");
    }
}

// Procédure qui affiche un "grade" au joueur en fonction du nombre
// de tentatives effectuées
void messageFelicitation(int nbreDeTentatives){
    printf("F\351licitations, Vous avez trouv\351 le Nombre Secret apr\350s %d tentatives\n", nbreDeTentatives);
    if (nbreDeTentatives >= 1 && nbreDeTentatives <= 3){
        printf("Vous \352tes un Super Voyant\n");
    }
    else if (nbreDeTentatives >= 4 && nbreDeTentatives <= 6){
        printf("Vous \352tes un Sage Voyant\n");
    }
    else if(nbreDeTentatives >= 7 && nbreDeTentatives <= 9){
        printf("Vous \352tes un Apprenti Voyant\n");
    } else {
        printf("Vous \352tes un Voyant Pusillanime\n");
    }
}




// Cette fonction contiendra tout le jeu proprement dit avec les appels
// des différentes fonctions définies plus haut
void lancerJeu(){
    setlocale(LC_CTYPE, ""); // pour l'encodage en UTF-8
    int choix = -1, cpt = 0, nbreLu, nbreRandom;
    char pseudo[100];
    bool pseudoExiste;
    FILE* file;

    afficheRegles();
    proposeIntervalle();
    printf("Votre choix : ");
    choix = lireEntier();
    while (choix < 1 || choix > 3) { // Correction de la condition de boucle while
        printf("Entr\351e Invalide - R\351essayer : "); // Controle de choix
        scanf("%d", &choix);
    }

    // En fonction du choix, on envoie un intervalle différent à la fonction getRandomInt
    switch (choix){
    case 1:
        nbreRandom = getRandomInt(0, 20);
        break;
    case 2:
        nbreRandom = getRandomInt(0, 100);
        break;
    case 3:
        nbreRandom = getRandomInt(0, 200);
        break;
    case 4:
        nbreRandom = lireIntervalle();
        break;
    default:
        printf("Erreur: Choix non pris en charge\n");
        return;
    }

    printf("\300 vous de jouer : ");
    nbreLu = lireEntier() ;
    while (nbreLu != nbreRandom){
        messageOrientation(nbreLu, nbreRandom);
        nbreLu = lireEntier() ;
        cpt++;
    }
    messageFelicitation(cpt);

    printf("Entrez un pseudo : ");
    scanf("%s", pseudo);
    pseudoExiste = verifiePseudo(pseudo, file);
    if (pseudoExiste) {
        printf("Ce pseudo est déjà enregistré dans score.txt\n");
    } else {
        archivePseudo(pseudo, file);
    }
    printf("Fin du Programme....\n");
}
