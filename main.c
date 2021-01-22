#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include"FonctionsAction.h"
#include"FonctionsSauvegarde.h"




int main(int argc, char const *argv[])
{

  // creation du plateau de Jeu de depart
  ListePerso * JeuRougeVoisin=initJeu();
  ListePerso * JeuBleuVoisin=initJeu();
  Case** plateau = CreerPlateau(8,8);

  Monde *monde= CreerMonde(plateau);
  int tresorR = 50;
  int tresorB = 50;

  lancementdePartie(JeuRougeVoisin,JeuBleuVoisin,monde,&tresorR,&tresorB);
  int cmpt_tour=0;
  AffichageJeuVoisin(JeuBleuVoisin);
  AffichageJeuVoisin(JeuRougeVoisin);
  AffichagePlateau(monde);

  int objTours;
  printf("rentrez le nombre de tours a jouer : "),
  scanf("%d",&objTours);


  while ((cmpt_tour!=objTours) || (monde->CampBleu!=NULL) || (monde->CampRouge!=NULL)){
      // demande à chaque tour si les joueurs veulent sauvegarder la partie
      printf("voulez-vous sauvegarder la partie ? \noui ou non ?: ");
      char str[4];
      char str1[4]="oui";
      scanf("%s",str);
      if(strcmp(str1,str)==0){
          sauvergardeJeu(monde,JeuRougeVoisin,JeuBleuVoisin,&tresorR,&tresorB);
          return 0;
      } else{
        printf("debut du tour du joueur Rouge\n");

        for(Personnage* ChateauR=JeuRougeVoisin->tete; ChateauR!=NULL; ChateauR=ChateauR->PersoSuivantVoisin){
          for(Personnage* persotemp=ChateauR; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
            switch(persotemp->typePerso){
              case 0: TourChateau(persotemp, monde,&tresorR);
                      break;
              case 1: TourSeigneur(persotemp, JeuRougeVoisin, monde, &tresorR);
                      break;
              case 2: TourGuerrier(persotemp, monde);
                      break;
              case 3: TourManant(persotemp,monde,&tresorR);
                      break;
            }
          AffichageJeu(ChateauR);
          AffichagePlateau(monde);
          AffichageTresor(&tresorR,&tresorB);
          }
        }

        printf(" debut du tour du joueur Bleu\n");
        for(Personnage* ChateauB=JeuBleuVoisin->tete; ChateauB!=NULL; ChateauB=ChateauB->PersoSuivantVoisin){
          for(Personnage* persotemp=ChateauB; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
            switch (persotemp->typePerso){
              case 0: TourChateau(persotemp, monde,&tresorB);
                      break;
              case 1: TourSeigneur(persotemp, JeuBleuVoisin, monde,&tresorB);
                      break;
              case 2: TourGuerrier(persotemp, monde);
                      break;
              case 3: TourManant(persotemp, monde,&tresorB);
                      break;
            }
          AffichageJeu(ChateauB);
          AffichagePlateau(monde);
          AffichageTresor(&tresorR,&tresorB);
         }
       }
      printf("%d tours restants\n", objTours - (++cmpt_tour));
      }
    } // sortie du while (fin de partie);
  return 0;
}
