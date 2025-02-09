#ifndef MESFONCTIONS_H
#define MESFONCTIONS_H

void afficheRegles();
int getRandomInt(int bornInf, int bornSup);
void proposeIntervalle();
void messageOrientation(int nbreLu, int nbreRandom);
void messageFelicitation(int nbreDeTentatives);
bool verifiePseudo(char pseudo, FILE* file);
void archivePseudo(char pseudo, FILE* file);
void lancerJeu();
//void archiveScore(FILE* file);


#endif // MESFONCTIONS_H
