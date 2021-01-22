#ifndef FONCTIONCREATION_H
#define FONCTIONCREATION_H
#include<stdio.h>

ListePerso * initJeu(void);

void CreerChateau(ListePerso* JeuVoisinChateau,  Monde* monde, couleur_t couleur,int px, int py);

void CreerSeigneur(Personnage* chateau, Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void CreerManant(Personnage* chateau,Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void CreerGuerrier(Personnage* chateau, Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void ChateauProduction(Personnage* chateau, Monde* monde, int* tresor);

Case** CreerPlateau(int nbcolonne, int nbligne);

Monde* CreerMonde(Case** plateau);
#endif
