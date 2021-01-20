#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAction.h"

void lancementdePartie(ListePerso* JeuRouge, ListePerso* JeuBleu, Monde *monde, int* tresorRouge, int * tresorBleu)
{
  CreerChateau(JeuRouge, monde ,Rouge,7,7);
  CreerManant(JeuRouge,monde,Rouge,7,6,tresorRouge);
  CreerSeigneur(JeuRouge,monde, Rouge,6,7,tresorRouge);

  CreerChateau(JeuBleu,monde, Bleu,0,0);
  CreerManant(JeuBleu,monde, Bleu ,5,5,tresorBleu);
  CreerSeigneur(JeuBleu,monde, Bleu,1,0,tresorBleu);

  // retablir le tresor à 50 pieces d'or
  *tresorRouge=50;
  *tresorBleu=50;
}
// fonctions à créer
// fonctions suicide des seigneurs et des guerriers

// fonctions productions des manants

void trahisonManant(Personnage* manant, ListePerso *Attaquant, ListePerso* Perdant){
  if (manant->typePerso!=Manant){
    printf("le personnage n'est pas un manant");
  }else{
    if (manant->couleur==Rouge){
      // devient à nouvrau mobile MAIS reste sur place lors de la trahison
      manant->dx=manant->px;
      manant->dy=manant->py;
      manant->couleur=Bleu;

      manant->PersoPrecedent->PersoSuivant=NULL;
      Perdant->fin=manant->PersoPrecedent;


      printf("\t -Le manant traitre est rouge (%d,%d), il passe dans le camp bleu\n", manant->px,manant->py);
      manant->PersoPrecedent=Attaquant->fin;
      manant->PersoSuivant=NULL;
      Attaquant->fin->PersoSuivant=manant;
      Attaquant->fin=manant;
    }
    else {
      manant->dx=manant->px;
      manant->dy=manant->py;
      manant->couleur=Rouge;

      manant->PersoPrecedent->PersoSuivant=NULL;
      Perdant->fin=manant->PersoPrecedent;


      printf("\t - Le manant traitre est bleu (%d,%d), il passe dans le camp rouge\n",manant->px,manant->py);
      manant->PersoPrecedent=Attaquant->fin;
      manant->PersoSuivant=NULL;
      Attaquant->fin->PersoSuivant=manant;
      Attaquant->fin=manant;
    }

    Attaquant->nbPerso++;
    Perdant->nbPerso--;
  }
}
// la fonction suicide se produit après la fonction de trahison des manant de la liste
void suicide(Personnage* Harakiri,ListePerso *Perdant, Monde* monde){
  if (Harakiri->typePerso==Chateau || Harakiri->typePerso==Manant){
    printf("ce type d'agent ne se suicide pas");
  }else {

    if (Harakiri->typePerso==Seigneur){
      printf("\t -suicide d'un Seigneur en case (%d,%d)\n",Harakiri->px, Harakiri->py);
    } else{ printf("\t  -suicide d'un Guerrier en case (%d,%d)\n",Harakiri->px, Harakiri->py);}


    if (Harakiri->PersoSuivant==NULL){ // cas où le harakiri est en bout de chaine
      Perdant->fin->PersoPrecedent->PersoSuivant=NULL;
      Perdant->fin = Perdant->fin->PersoPrecedent;
      Perdant->nbPerso--;
    } else {
      Harakiri->PersoPrecedent->PersoSuivant=Harakiri->PersoSuivant;
      Harakiri->PersoSuivant->PersoPrecedent=Harakiri->PersoPrecedent;
      Perdant->nbPerso--;
      }

      monde->plateau[Harakiri->px][Harakiri->py].perso=NULL;
      free(Harakiri);
    }
}

// cette fonction detruit et libere la liste de Jeu lié au chateau qui vient d'être détruit
void destructionChateau(ListePerso* Attaquant, ListePerso* Perdant, Monde* monde){
    //la destruction du chateau soit la tete de la liste Perdant va provoquer le suicide des Seigneurs et des guerriers
    // et la trahison de tout les manants;
    if(Perdant->tete->couleur==Rouge){
      printf("Destruction du chateau Rouge de la case(%d,%d) : \n",Perdant->tete->px,Perdant->tete->py);
    } else {printf("Destruction du chateau Bleu de la case(%d,%d): \n",Perdant->tete->px,Perdant->tete->py);}

      Personnage* persotemp =Perdant->fin;
      while (persotemp->typePerso==Manant){
          trahisonManant(persotemp,Attaquant,Perdant);
          persotemp=Perdant->fin;
        }
        // comme les manants sont obligatoirement à la fin de la liste de Jeu, on les lit et ils trahissent consécutivement;
        // à ce niveau il n' y a plus de manant dans la liste des perdants;
      Personnage* harakiri=Perdant->fin;
      while( (harakiri->typePerso==Seigneur) || (harakiri->typePerso==Guerrier) ){
          suicide(harakiri,Perdant,monde);
          harakiri=Perdant->fin;
        }

      // a ce niveau il n'y a plus que le chateau dans la liste
      if(Perdant->nbPerso==1){
        monde->plateau[Perdant->tete->px][Perdant->tete->py].chateau=NULL;
        if(Perdant->tete->couleur==Rouge){
          monde->CampRouge=NULL;
        }else{monde->CampBleu=NULL;}
        free(Perdant->tete);
        free(Perdant);
        printf("fin du processus de destruction\n");
      }
}


void productionManant(Personnage* manant, int* tresor){
  if (manant->typePerso!=Manant){
    printf("le personnage n'est pas un manant");
  }else{
    if ((manant->dx!=manant->px || manant->dy !=manant->py ) && (manant->dx!=-1 || manant->dy!=-1)){
      printf(" le manant est en déplacement, il ne peut rien produire");
    }
    if (manant->dx==-1 && manant->dy==-1){ // le manant est immobile
      (*tresor)++;
    }
  }
}

void immobilisation(Personnage* perso){
  if((perso->typePerso==Seigneur) || (perso->typePerso==Manant)){
    perso->dx=-1;
    perso->dy=-1;
    // le personnage est immobilisé; Manant ou seigneur
  } else{
    printf ("ce type de personnage ne peut pas etre immobilise");
    }
}


void nouvelleDestination(Personnage* perso, Monde* monde, int newdx, int newdy){
  if (perso->dx==-1  && perso->dy==-1){
    printf("votre personnage est immobilise, il ne peut pas se déplacer");
  }
  else {
      if ((newdx==perso->px) && (newdy==perso->py)){
          printf("vous avez choisi de rester sur place ?\n Veuillez rentrer de nouveaux coordonnees");

          int newdx1, newdy1;
          printf("nouvelle ligne dx : ");
          scanf("%d",&newdx1);
          printf("nouvelle colonne dy : ");
          scanf("%d",&newdy1);
          nouvelleDestination(perso, monde, newdx1, newdy1);
      }
      else{
        if ( (newdy>=8) || (newdy<0) ||(newdx>=8) || (newdx<0) || (monde->plateau[newdx][newdy].perso!=NULL) || (monde->plateau[newdx][newdy].chateau!=NULL)) { // cas ou la case n'est pas vide
          // traite du cas ou la case de destination n'appartient pas au plateau créé
            printf("la case destination est deja occupee ou n'exite pas, veuillez rentrer de nouvelles coordonnees\n");
            int newdx1, newdy1;
            printf("nouvelle ligne dx : ");
            scanf("%d",&newdx1);
            printf("nouvelle colonne dy : ");
            scanf("%d",&newdy1);
            nouvelleDestination(perso, monde, newdx1, newdy1);
          } else{
            printf("la case a atteindre est vide, l'objectif de destination a bien ete ajoute\n");
            perso->dx=newdx;
            perso->dy=newdy;
            }
      }
  }
}

void deplacementPerso(Personnage* perso, Monde * monde){
// Cette fonction ne fait que constater la différence entre la case de la position actuelle et la case destination.
// attention px et dx represente le numéro de ligne et py et dy le numero de colonne
 // dans cette partie le personnage va se deplacer en empruntant le plus court chemin
 // le test d'immobilisation sera testé en amont, on ne pourra se déplacer que si les valeurs dx et dy soient différentes de -1

      int deltaX, deltaY;
      deltaX = perso->dx - perso->px;
      deltaY = perso->dy - perso->py;

      if ((deltaX > 0) && (deltaY> 0)){
        printf("deplacement vers le sud est\n");
        if (monde->plateau[perso->px+1][perso->py+1].perso!=NULL || monde->plateau[perso->px+1][perso->py+1].chateau!=NULL){
          printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
          perso->dx=perso->px;
          perso->dy=perso->py;
        }else{
          monde->plateau[perso->px+1][perso->py+1].perso=perso;
          monde->plateau[perso->px][perso->py].perso=NULL;
          perso->px++;
          perso->py++;
        }
      }

      if((deltaX > 0) && (deltaY < 0)){
        printf("deplacement vers le sud ouest\n");
        if (monde->plateau[perso->px-1][perso->py+1].perso!=NULL || monde->plateau[perso->px-1][perso->py+1].chateau!=NULL){
          printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
          perso->dx=perso->px;
          perso->dy=perso->py;
        }else{
          monde->plateau[perso->px-1][perso->py+1].perso=perso;
          monde->plateau[perso->px][perso->py].perso=NULL;
          perso->px--;
          perso->py++;
        }
      }

      if ((deltaX < 0) && (deltaY > 0)){
        printf("deplacement vers le nord est\n");
        if (monde->plateau[perso->px+1][perso->py-1].perso!=NULL || monde->plateau[perso->px+1][perso->py-1].chateau!=NULL){
          printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
          perso->dx=perso->px;
          perso->dy=perso->py;
        } else{
          monde->plateau[perso->px+1][perso->py-1].perso=perso;
          monde->plateau[perso->px][perso->py].perso=NULL;
          perso->px++;
          perso->py--;
        }
      }

      if ((deltaX < 0) && (deltaY < 0)){
       printf("deplacement vers le nord ouest\n");
       if (monde->plateau[perso->px-1][perso->py-1].perso!=NULL || monde->plateau[perso->px-1][perso->py-1].chateau!=NULL){
         printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
         perso->dx=perso->px;
         perso->dy=perso->py;
       }else{
        monde->plateau[perso->px-1][perso->py-1].perso=perso;
        monde->plateau[perso->px][perso->py].perso=NULL;
        perso->px--;
        perso->py--;
        }
      }

      if ((deltaY==0) && (deltaX<0)){
          printf("deplacement nord\n");
          if (monde->plateau[perso->px-1][perso->py].perso!=NULL || monde->plateau[perso->px-1][perso->py].chateau!=NULL){
            printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
            perso->dx=perso->px;
            perso->dy=perso->py;
          }else {
          monde->plateau[perso->px-1][perso->py].perso=perso;
          monde->plateau[perso->px][perso->py].perso=NULL;
          perso->px--;
          }
        }

      if ((deltaY==0) && (deltaX>0)){
          printf("deplacement sud\n");
          if (monde->plateau[perso->px+1][perso->py].perso!=NULL || monde->plateau[perso->px+1][perso->py].chateau!=NULL){
            printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
            perso->dx=perso->px;
            perso->dy=perso->py;
          } else{
            monde->plateau[perso->px+1][perso->py].perso=perso;
            monde->plateau[perso->px][perso->py].perso=NULL;
            perso->px++;
            }
      }
      if ((deltaX==0) && (deltaY>0)){
          printf("deplacement vers l'Est\n");
          if (monde->plateau[perso->px][perso->py+1].perso!=NULL || monde->plateau[perso->px][perso->py+1].chateau!=NULL){
            printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
            perso->dx=perso->px;
            perso->dy=perso->py;
          }else {
            monde->plateau[perso->px][perso->py+1].perso=perso;
            monde->plateau[perso->px][perso->py].perso=NULL;
            perso->py++;
          }
      }

      if ((deltaX==0) && (deltaY<0)){
          printf("deplacement vers l'Ouest\n");
          if (monde->plateau[perso->px][perso->py-1].perso!=NULL || monde->plateau[perso->px][perso->py-1].chateau!=NULL){
            printf("le personnage a rencontre un case occupee pendant son deplacement \n cela met fin a son deplacement\n");
            perso->dx=perso->px;
            perso->dy=perso->py;
          } else{
            monde->plateau[perso->px][perso->py-1].perso=perso;
            monde->plateau[perso->px][perso->py].perso=NULL;
            perso->py--;
          }
      }

      if ((deltaX==0) && (deltaY==0)){
        printf("votre personnage est reste a la meme position\n");
      } else{
            if  ((perso->dx==perso->px) && (perso->dy==perso->py)){
              switch(perso->typePerso){
              case 0: printf(" impossible, les chateaux ne peuvent pas se deplacer\n");
                      break;
              case 1: printf("le seigneur en case (%d,%d) a fini son deplacement\n",perso->px,perso->py);
                      break;
              case 2: printf("le guerrier en case (%d,%d) a fini son deplacement\n",perso->px,perso->py);
                      break;
              case 3: printf("le manant en case (%d,%d) a fini son deplacement\n", perso->px,perso->py);
                      break;
              }
            }else{
                  switch(perso->typePerso){
                    case 0: printf(" impossible, les chateaux ne peuvent pas se deplacer\n");
                      break;
                    case 1: printf("le seigneur en case (%d,%d) n'a pas fini son deplacement\n",perso->px,perso->py);
                      break;
                    case 2: printf("le guerrier en case (%d,%d) n'a pas fini son deplacement\n",perso->px,perso->py);
                      break;
                    case 3: printf("le manant en case (%d,%d) n'a pas fini son deplacement\n", perso->px,perso->py);
                      break;
                  }
              }
        }
}

int* TrouverCaseLibre(Monde* monde, Personnage* chateau, ListePerso* Jeu, couleur_t couleur, int* tresor){
    // objectif trouver une case libre autour du chateau
    int * T = malloc(2*sizeof(int));
    if(T==NULL){
      return NULL;
    } else{

      int cx=chateau->px;
      int cy=chateau->py;

      for(int i=-1; i<=1; i++){
          for (int j=-1; j<=1;j++){
            if (monde->plateau[cx+i][cy+j].perso==NULL){
              *T= cx+i;
              *(T+1)=cy+j;
              return T;
            }
          }
      }

      for(int i=-2; i<=2; i++){
          for (int j=-2; j<=2;j++){
            if((i==2) || (j==2)){
              if (monde->plateau[cx+i][cy+j].perso==NULL){
                *T= cx+i;
                *(T+1)=cy+j;
                 return T;
              }
            }
          }
      }
      return NULL; 

    }
}