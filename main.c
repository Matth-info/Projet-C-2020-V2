#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include"FonctionsAction.h"
#include"FonctionsSauvegarde.h"
#define T_MAX 256

int main(int argc, char **argv)
{
  // creation du plateau de Jeu de depart
  ListePerso * JeuRougeVoisin=initJeu();
  ListePerso * JeuBleuVoisin=initJeu();
  Case** plateau = CreerPlateau(8,8);

  Monde *monde= CreerMonde(plateau);
  int tresorR = 50;
  int tresorB = 50;
  int ProchainAJouer;

  if(argv[1]!=NULL){
      printf("chargement de la partie du fichier %s\n",argv[1]);
      ProchainAJouer=Chargementpartie(argc,argv,monde, JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB);
      if (ProchainAJouer==0){
        printf("le joueur rouge commencera a jouer\n");
      }
      if (ProchainAJouer==1){
        printf("le joueur bleu commencera a jouer\n");
      }
      printf("fin du chargement de la partie\n");
    }
  else{
    printf("pas de fichier rentre en sauvegarde\n lancement automatique d'une nouvelle partie\n");
    lancementdePartie(JeuRougeVoisin,JeuBleuVoisin,monde,&tresorR,&tresorB);
  }


  AffichageTresor(&tresorR,&tresorB);
  AffichageJeuVoisin(JeuBleuVoisin);
  AffichageJeuVoisin(JeuRougeVoisin);
  AffichagePlateau(monde);

  int cmpt_tour=0;
  while ((monde->CampBleu!=NULL) && (monde->CampRouge!=NULL)){

      if ((ProchainAJouer==0) || (argc==1)){ //tour commencant par le joueur Rouge (cas de chargement et nouvelle partie)
          if (DemandeSauvegarde(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB,0)==0){
              return 0;
          }
          printf("debut du tour du joueur Rouge\n");
          TourDeJeu(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR);

          if (DemandeSauvegarde(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB,1)==0){
              return 0;
          }
          printf(" debut du tour du joueur Bleu\n");
          TourDeJeu(monde,JeuBleuVoisin,JeuRougeVoisin,&tresorB);

          printf("%d tours \n",++cmpt_tour);
      } // sortie du while (fin de partie);
      else{
          if (DemandeSauvegarde(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB,1)==0){
              return 0;
          }
          printf(" debut du tour du joueur Bleu\n");
          TourDeJeu(monde,JeuBleuVoisin, JeuRougeVoisin, &tresorB);

          if (DemandeSauvegarde(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB,0)==0){
              return 0;
          }
          printf("debut du tour du joueur Rouge\n");
          TourDeJeu(monde,JeuRougeVoisin, JeuBleuVoisin, &tresorR);

          printf("%d tours\n",++cmpt_tour);
      } // sortie du while (fin de partie);
    }
    Score(argc,argv,monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB);
  return 0;
}
