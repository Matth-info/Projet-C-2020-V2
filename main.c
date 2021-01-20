#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include"FonctionsAction.h"



int main(int argc, char const *argv[])
{

  // creation du plateau de Jeu de depart
  ListePerso * JeuRouge=initJeu();
  ListePerso * JeuBleu=initJeu();
  Case** plateau = CreerPlateau(8,8);
  Monde *monde= CreerMonde(plateau);
  int tresorR = 50;
  int tresorB = 50;
  lancementdePartie(JeuRouge,JeuBleu,monde,&tresorR,&tresorB);
  int cmpt_tour=0;

  AffichageJeu(JeuRouge);
  AffichageJeu(JeuBleu);
  AffichagePlateau(monde);

  while ((cmpt_tour!=10) || (monde->CampBleu!=NULL) || (monde->CampRouge!=NULL)){
    for(Personnage* persotemp=JeuRouge->tete; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
      printf("le numero de personnage est %d\n", persotemp->typePerso);
      switch(persotemp->typePerso){
        case 0: TourChateau(JeuRouge, monde,&tresorR);
                break;
        case 1: TourSeigneur(persotemp, JeuRouge, monde);
                break;
        case 2: TourGuerrier(persotemp, JeuRouge, monde);
                break;
        case 3: TourManant(persotemp, JeuRouge, monde,&tresorR);
                break;
      }
      AffichageJeu(JeuRouge);
      AffichagePlateau(monde);

    }
    for(Personnage* persotemp=JeuBleu->tete; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
      printf("le numero de personnage est %d\n", persotemp->typePerso);
      switch (persotemp->typePerso){
        case 0: TourChateau(JeuBleu, monde,&tresorR);
                break;
        case 1: TourSeigneur(persotemp, JeuBleu, monde);
                break;
        case 2: TourGuerrier(persotemp, JeuRouge, monde);
                break;
        case 3: TourManant(persotemp, JeuBleu, monde,&tresorR);
                break;
      }
      AffichageJeu(JeuBleu);
      AffichagePlateau(monde);
    }
    printf("%d tours restants",10 - ++cmpt_tour);
  }
  return 0;
}
