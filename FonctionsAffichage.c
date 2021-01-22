#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include<stdio.h>

void AffichageJeu(Personnage* Castle)
{
    printf("\n");
    int couleur= Castle->couleur;
    if (couleur== 0){
      printf("Personnages dans la liste Rouge du Chateau Cr (%d,%d):\n",Castle->px,Castle->py);
    }
    else {
      printf("Personnages dans la liste Bleue du Chateau Cb(%d,%d):\n",Castle->px,Castle->py);
    }
    for (Personnage * persotemp=Castle ; persotemp!=NULL ; persotemp=persotemp->PersoSuivant)
    {
      switch(persotemp->typePerso){
        case 0: printf("chateau");
                break;
        case 1: printf("seigneur");
                break;
        case 2 : printf("guerrier");
                break;
        case 3 : printf("manant");
                break;
        default : printf("type de Personnage inconnu");
      }

      switch(persotemp->couleur){
        case 0: printf(" Rouge \n");
                break;
        case 1: printf(" Bleu \n");
                break;
        default : printf(" couleur non reconnue\n");
      }
    }

  printf("\n");
}

void AffichageJeuVoisin(ListePerso * JeuVoisin) {
  for(Personnage* castletemp = JeuVoisin->tete; castletemp!=NULL; castletemp = castletemp->PersoSuivantVoisin) {
    AffichageJeu(castletemp);
  }
}



void AffichagePlateau(Monde* monde){
  if (monde==NULL){
    printf("L'initialisation du Monde n'a pas fonctionnée");
  }
  printf("\nPlateau de jeu actuellement\n");
  for(int i=0; i<8; i++){
    printf("\n");
    for (int l=0; l<8; l++){
      for (int m=0; m<8; m++){
      printf("_"); // affichage de ligne de sepatation entre les lignes (effet cadrillage)
      }
    }
    printf("\n");
    for (int j=0; j<8; j++){
      if (monde->plateau[i][j].chateau!=NULL){
          switch (monde->plateau[i][j].chateau->couleur) {
              case 0: printf("Cr ");
                      break;
              case 1: printf("Cb ");
          }
      }
      if (monde->plateau[i][j].perso!=NULL){
          if(monde->plateau[i][j].perso->couleur==Rouge){
            switch (monde->plateau[i][j].perso->typePerso) {
              case 0: printf("Affiche un chateau en doublon"); // cas normalement impossible
                      break;
              case 1: printf("Sr ");
                      break;
              case 2: printf("Gr ");
                      break;
              case 3: printf("Mr ");
                      break;
              default : printf("type de personnage invalide");
            }
          }
          else{
            switch (monde->plateau[i][j].perso->typePerso) {
              case 0: printf("Affiche un chateau en doublon"); // cas normalement impossible
                      break;
              case 1: printf("Sb ");
                      break;
              case 2: printf("Gb ");
                      break;
              case 3: printf("Mb ");
                      break;
              default : printf("type de personnage invalide");
            }
          }
      } printf("\t|");
  }
} printf("\n");
}

void AffichageTresor(int* tresorRouge, int* tresorBleu){
  printf("%d pieces d'or dans le coffre Rouge\n", *tresorRouge);
  printf("%d pieces d'or dans le coffre Bleu\n\n", *tresorBleu);
}
