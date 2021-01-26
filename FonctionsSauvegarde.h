#ifndef FONCTIONSSAUVEGARDE_H
#define FONCTIONSSAUVEGARDE_H

void sauvergardeJeu(Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB, int ProchainAJouer);
int Chargementpartie(int argc, char* argv[], Monde* monde,ListePerso * JeuRougeVoisin, ListePerso * JeuBleuVoisin,int* tresorR,int* tresorB);
void CreerManantChargement(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py,int dx, int dy, int* tresor);
void CreerSeigneurChargement(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py,int dx, int dy, int* tresor);
void CreerGuerrierChargement(Personnage* chateau,Monde* monde, couleur_t couleur, int px, int py,int dx, int dy, int * tresor);
int DemandeSauvegarde(Monde* monde, ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin,int * tresorR, int* tresorB,int ProchainAJouer);
void traitementFscore(int argc, char** argv, char *NvVainqueur,int nvscore);
void InsertionNvScore(CoupleNS* tab, int tailletab, CoupleNS nvCoupleNS);
void triInsertionDecroissant(CoupleNS *tab, int tailletab);
void Score(int argc, char** argv,Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB);
#endif
