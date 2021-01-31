#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include<stdio.h>
#include<math.h>


int MaxNbPerso(Monde* monde){ // fonction ayant pour but de trouver le nombre de personnage maximal dans une case afin de
  // permettre à l'affichage de cette case au complet tout en conservant un plateau carré.
  int nbPerso[64]={0};
  int m=0;
  int compteur;
  for(int i=0; i<8; i++){
    for(int j=0; j<8;j++){
      compteur=0;
      if (monde->plateau[i][j].chateau!=NULL){
        compteur++;
      }
      if (monde->plateau[i][j].perso!=NULL){
        for(Personnage* persotemp=monde->plateau[i][j].perso; persotemp!=NULL ;persotemp=persotemp->PersoSuivantVoisin){
            compteur++;
        }
      }
      nbPerso[m++]=compteur;
    }
  }
  int max=0;
  for(int i=0;i<64;i++){
    if (nbPerso[i]> max){
      max=nbPerso[i];
    }
  }
  //printf("max : %d\n", max); 
  return max;
}

void AffichageJeu(Personnage* Castle)
{
    printf("\n");

    if (Castle->couleur== Rouge){
      printf("\nPersonnages dans la liste Rouge du Chateau Cr(%d,%d):\n",Castle->px,Castle->py);
    }
    else {
      printf("\nPersonnages dans la liste Bleue du Chateau Cb(%d,%d):\n",Castle->px,Castle->py);
    }
    for (Personnage * persotemp=Castle ; persotemp!=NULL ; persotemp=persotemp->PersoSuivant)
    {
      switch(persotemp->typePerso){
        case 0: printf("chateau");
                break;
        case 1: printf("\tseigneur");
                break;
        case 2 : printf("\tguerrier");
                break;
        case 3 : printf("\tmanant");
                break;
        default : printf("Type de Personnage inconnu\n");
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
    printf("L'initialisation du Monde n'a pas fonctionnee\n");
  }
  printf("\nPlateau de jeu actuellement\n");
  int max=MaxNbPerso(monde);

  printf("0");
  for(int j=1; j<8; j++){ // affichage des numéro de colonne
    for (int i=0; i < 3*max;i++){ // distance entre ces numéros
      printf(" ");
    }
    printf("%d",j);
  }

  for(int i=0; i<8; i++){
    printf("\n");
    for (int l=0; l<8; l++){
      for (int m=0; m< 3*max+1; m++){
        printf("_"); // affichage de ligne de sepatation entre les lignes (effet cadrillage)
        }
    }
    printf("\n");
    for (int j=0; j<8; j++){
      int cmp_perso_case=0;
      if (monde->plateau[i][j].chateau!=NULL){
          switch (monde->plateau[i][j].chateau->couleur) {
              case 0: printf("Cr ");
                      break;
              case 1: printf("Cb ");
          }
      cmp_perso_case++;
      }
      if (monde->plateau[i][j].perso!=NULL){
          for(Personnage * persotemp=monde->plateau[i][j].perso; persotemp!=NULL; persotemp=persotemp->PersoSuivantVoisin){
              cmp_perso_case++;
              if(persotemp->couleur==Rouge){
                switch (persotemp->typePerso) {
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
                switch (persotemp->typePerso) {
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
        }
      }
      if (cmp_perso_case==max){
        printf("|");
      }
      if (cmp_perso_case < max){
        for(int j=cmp_perso_case; j<max;j++){
          printf("   ");
        }
        printf("|");
      }
    }
  printf("%d", i);
  } // fin boucle for

 printf("\n"); // passage à la ligne suivante
}

void AffichageTresor(int* tresorRouge, int* tresorBleu){
  printf("%d pieces d'or dans le coffre Rouge\n", *tresorRouge);
  printf("%d pieces d'or dans le coffre Bleu\n\n", *tresorBleu);
}
