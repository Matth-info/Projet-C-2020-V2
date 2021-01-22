#ifndef FONCTIONCREATION_H
#define FONCTIONCREATION_H
#include<stdio.h>

ListePerso * initJeu(void);

void CreerChateau(ListePerso* Jeu,ListePerso* JeuVoisinChateau,  Monde* monde, couleur_t couleur,int px, int py);

void CreerSeigneur(ListePerso* Jeu, Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void CreerManant(Personnage* Castle,Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void CreerGuerrier(Personnage* Castle, Monde* monde, couleur_t couleur, int px, int py, int* tresor);

void ChateauProduction(ListePerso* Jeu, Monde* monde, int* tresor);

Case** CreerPlateau(int nbcolonne, int nbligne);

Monde* CreerMonde(Case** plateau);
#endif
