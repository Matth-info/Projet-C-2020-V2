#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include"FonctionsAction.h"
#include"FonctionsSauvegarde.h"

#define T_MAX 256

//objectif créer un fichier de sauvegarde .got qui respecte les critères de sauvegardes afin de pouvoir facilement le récupérer et rétablir le jeu.
void sauvergardeJeu(Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB){
  FILE* fichier =NULL;
  printf("entrer le nom du fichier avec l'extension .got :");
  char str[T_MAX]="";
  scanf("%s",str);
  fichier=fopen(str,"w");
  if (fichier==NULL){
    printf("erreur lors de la creation du fichier");
  }
  fprintf(fichier,"R  %d\n",*tresorR);
  fprintf(fichier,"B  %d\n",*tresorB);


  for(Personnage* ChateauR=JeuRougeVoisin->tete; ChateauR!=NULL; ChateauR=ChateauR->PersoSuivantVoisin){
    for(Personnage* persotemp=ChateauR; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
          if(persotemp->couleur==Rouge){
            fprintf(fichier,"R ");
          }
          switch(persotemp->typePerso){
              case 0: fprintf(fichier,"c ");
                      break;
              case 1: fprintf(fichier,"s ");
                      break;
              case 2: fprintf(fichier,"g ");
                      break;
              case 3: fprintf(fichier,"m ");
                      break;
          }
          fprintf(fichier,"(%d,%d) ",persotemp->px,persotemp->py);
          if (persotemp->typePerso!=Chateau){
            fprintf(fichier,"(%d,%d) ",persotemp->dx,persotemp->dy);
          }else {
            switch(persotemp->typeProd){
                case 0: fprintf(fichier,"s ");
                        break;
                case 1: fprintf(fichier,"g ");
                        break;
                case 2: fprintf(fichier,"m ");
                        break;
                case 3: fprintf(fichier,"r ");// r pour rien, pas de production;
                        break;
              }
              fprintf(fichier,"%d",persotemp->tempsProd);
            }fprintf(fichier,"\n");
      }
    }
  for(Personnage* ChateauB=JeuBleuVoisin->tete; ChateauB!=NULL; ChateauB=ChateauB->PersoSuivantVoisin){
      for(Personnage* persotemp=ChateauB; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
            if(persotemp->couleur==Bleu){
              fprintf(fichier,"B ");
            }
            switch(persotemp->typePerso){
                case 0: fprintf(fichier,"c ");
                        break;
                case 1: fprintf(fichier,"s ");
                        break;
                case 2: fprintf(fichier,"g ");
                        break;
                case 3: fprintf(fichier,"m ");
                        break;
            }
            fprintf(fichier,"(%d,%d) ",persotemp->px,persotemp->py);
            if (persotemp->typePerso!=Chateau){
              fprintf(fichier,"(%d,%d) ",persotemp->dx,persotemp->dy);
            }else {
              switch(persotemp->typeProd){
                case 0: fprintf(fichier,"s ");
                        break;
                case 1: fprintf(fichier,"g ");
                        break;
                case 2: fprintf(fichier,"m ");
                        break;
                case 3: fprintf(fichier,"r ");// r pour rien, pas de production;
                        break;
                }
                fprintf(fichier,"%d",persotemp->tempsProd);
              }
               fprintf(fichier,"\n");
        }
      }
    fclose(fichier);
// fin du fichier de sauvegarde
}
