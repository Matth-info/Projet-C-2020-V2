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
  // initialisation  entiers comptant le trésor disponible de chaque trésors
  // la création d'agent par le chateau coûte
  // seigneur = 20 + 6 tours de jeu
  // guerrier = 5 + 4 tours de jeu
  // manant = 1 + 2 tours de jeu
  int tresorB = 50;
  int tresorR = 50;

  lancementdePartie(JeuRouge,JeuBleu,monde,&tresorR,&tresorB);
  /*CreerGuerrier(JeuRouge,monde,Rouge, 3, 4, &tresorR);
  CreerManant(JeuRouge,monde,Rouge, 3, 4, &tresorR);
  CreerGuerrier(JeuRouge,monde,Rouge, 3, 4, &tresorR);
  CreerSeigneur(JeuRouge,monde,Rouge, 3, 4, &tresorR);*/

  AffichageTresor(&tresorR, &tresorB);
  AffichageJeu(JeuRouge);
  printf("\n");
  AffichageJeu(JeuBleu);
  AffichagePlateau(monde);
  printf("\n");

  *int newdx, newdy;
  printf("entrer les coordonnees de la nouvelle destination de l'agent Seigneur Rouge\n");
  printf("nouvelle ligne dx : ");
  scanf("%d",&newdx);
  printf("nouvelle colonne dy : ");
  scanf("%d",&newdy);


  nouvelleDestination(JeuRouge->tete->PersoSuivant, monde, newdx, newdy);
  do {
    deplacementPerso(JeuRouge->tete->PersoSuivant, monde);
    AffichagePlateau(monde);
  }
  while ((JeuRouge->tete->PersoSuivant->px != JeuRouge->tete->PersoSuivant->dx) || (JeuRouge->tete->PersoSuivant->py != JeuRouge->tete->PersoSuivant->dy));
  return 0;
}
