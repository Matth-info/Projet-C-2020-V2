#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAction.h"

void lancementdePartie(ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde *monde, int* tresorRouge, int * tresorBleu)
{
  CreerChateau(JeuRougeVoisin, monde ,Rouge,7,7);
  CreerManant(JeuRougeVoisin->tete,monde,Rouge,7,6,tresorRouge);
  CreerSeigneur(JeuRougeVoisin->tete,monde, Rouge,6,7,tresorRouge);

  CreerChateau(JeuBleuVoisin,monde, Bleu,0,0);
  CreerManant(JeuBleuVoisin->tete,monde, Bleu ,0,1,tresorBleu);
  CreerSeigneur(JeuBleuVoisin->tete,monde, Bleu,1,0,tresorBleu);

  // retablir le tresor à 50 pieces d'or
  *tresorRouge=50;
  *tresorBleu=50;
}

// fonctions suicide des seigneurs et des guerriers

// fonctions productions des manants

void trahisonManant(Personnage* manant, Personnage* Attaquant, Personnage* Perdant){ // attaquant et perdant représente les chateaux affiliés aux manants
  if (manant->typePerso!=Manant){
    printf("le personnage n'est pas un manant");
  }else{
    if (manant->couleur==Rouge){
      // devient à nouvrau mobile MAIS reste sur place lors de la trahison
      manant->dx=manant->px;
      manant->dy=manant->py;
      manant->couleur=Bleu;

      manant->PersoPrecedent->PersoSuivant=NULL;


      printf("\t -Le manant traitre est rouge (%d,%d), il passe dans le camp bleu\n", manant->px,manant->py);
      //trouver le dernier personnage Bleu (attaquant relié au chateau)
      Personnage* dernierperso=Attaquant;
      while(dernierperso->PersoSuivant!=NULL){
        dernierperso=dernierperso->PersoSuivant;
      }
      manant->PersoPrecedent=dernierperso;
      manant->PersoSuivant=NULL;
    }
    else {
      manant->dx=manant->px;
      manant->dy=manant->py;
      manant->couleur=Rouge;

      manant->PersoPrecedent->PersoSuivant=NULL;

      printf("\t - Le manant traitre est bleu (%d,%d), il passe dans le camp rouge\n",manant->px,manant->py);
      Personnage* dernierperso=Attaquant;
      while(dernierperso->PersoSuivant!=NULL){
        dernierperso=dernierperso->PersoSuivant;
      }
      manant->PersoPrecedent=dernierperso;
      manant->PersoSuivant=NULL;
    }
  }
}
// la fonction suicide se produit après la fonction de trahison des manant de la liste
void suicide(Personnage* Harakiri, Monde* monde){

  if (Harakiri->typePerso==Chateau || Harakiri->typePerso==Manant){
    printf("ce type d'agent ne se suicide pas");
  }else {

    if (Harakiri->typePerso==Seigneur){
      printf("\t -suicide d'un Seigneur en case (%d,%d)\n",Harakiri->px, Harakiri->py);
    } else{ printf("\t  -suicide d'un Guerrier en case (%d,%d)\n",Harakiri->px, Harakiri->py);}


    if (Harakiri->PersoSuivant==NULL){ // cas où le harakiri est en bout de chaine
      Harakiri->PersoPrecedent->PersoSuivant=NULL;
    } else {
      Harakiri->PersoPrecedent->PersoSuivant=Harakiri->PersoSuivant;
      Harakiri->PersoSuivant->PersoPrecedent=Harakiri->PersoPrecedent;
      }

      monde->plateau[Harakiri->px][Harakiri->py].perso=NULL;
      free(Harakiri);
    }
}

// cette fonction detruit et libere la liste de Jeu lié au chateau qui vient d'être détruit
void destructionChateau(Personnage* ChateauAttaquant, Personnage* ChateauPerdant, Monde* monde, ListePerso* JeuVoisinPerdant){
    //la destruction du chateau soit la tete de la liste Perdant va provoquer le suicide des Seigneurs et des guerriers
    // et la trahison de tout les manants;
    if(ChateauPerdant->couleur==Rouge){
      printf("Destruction du chateau Rouge de la case(%d,%d) : \n",ChateauPerdant->px,ChateauPerdant->py);
    } else {printf("Destruction du chateau Bleu de la case(%d,%d): \n",ChateauPerdant->px,ChateauPerdant->py);}

      Personnage * dernierperso=ChateauPerdant;
      while (dernierperso->PersoSuivant!=NULL){
        dernierperso=dernierperso->PersoSuivant;
      }

      while (dernierperso->PersoSuivant->typePerso==Manant){
          trahisonManant(dernierperso->PersoSuivant,ChateauAttaquant,ChateauPerdant);
          dernierperso=dernierperso->PersoPrecedent;
        }
        // comme les manants sont obligatoirement à la fin de la liste de Jeu, on les lit et ils trahissent consécutivement;
        // à ce niveau il n' y a plus de manant dans la liste des perdants;

      while( (dernierperso->PersoSuivant->typePerso==Seigneur) || (dernierperso->PersoSuivant->typePerso==Guerrier) ){
          suicide(dernierperso->PersoSuivant,monde);
          dernierperso=dernierperso->PersoPrecedent;
        }

      // a ce niveau il n'y a plus que le chateau dans la liste
      if (JeuVoisinPerdant->tete==ChateauPerdant){ // premier chateau dans la liste voisin;
        ChateauPerdant->PersoSuivantVoisin->PersoPrecedentVoisin=NULL;
        JeuVoisinPerdant->tete=ChateauPerdant->PersoSuivantVoisin;
        JeuVoisinPerdant->nbPerso--;
      }
      if (JeuVoisinPerdant->fin==ChateauPerdant){ // dernier chateau dans la liste voisin
        ChateauPerdant->PersoPrecedentVoisin->PersoSuivantVoisin=NULL;
        JeuVoisinPerdant->fin=ChateauPerdant->PersoPrecedentVoisin;
      }

      if ((ChateauPerdant->PersoSuivant!=NULL) && (ChateauPerdant->PersoPrecedentVoisin!=NULL)){ // si le chateau enlevé n'est ni au début ni à la fin de la liste des chateau voisin
          monde->plateau[ChateauPerdant->px][ChateauPerdant->py].chateau=NULL;
          ChateauPerdant->PersoSuivantVoisin->PersoPrecedent=ChateauPerdant->PersoPrecedentVoisin;
          ChateauPerdant->PersoPrecedentVoisin->PersoSuivantVoisin=ChateauPerdant->PersoSuivantVoisin;
      }
      JeuVoisinPerdant->nbPerso--;
      if (JeuVoisinPerdant->nbPerso==0){
          if(ChateauPerdant->couleur==Rouge){
            monde->CampRouge=NULL;
          }else {monde->CampBleu=NULL;} // tester si CampRouge ou CampBleu pointe vers NULL signifierait que le CampRouge ou Bleu à perdu la partie;
      }
      printf("fin du processus de destruction du chateau (%d,%d)", ChateauPerdant->px, ChateauPerdant->py);
      free(ChateauPerdant);
}



void productionManant(Personnage* manant, int* tresor){
  if (manant->typePerso!=Manant){
    printf("le personnage n'est pas un manant\n");
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
  if ((perso->typePerso==Manant) || (perso->typePerso==Seigneur)){
    perso->dx=-1;
    perso->dy=-1;
    // le personnage est immobilisé; Manant ou seigneur
  } else{
    printf ("ce type de personnage ne peut pas etre immobilise\n");
    }
}


void nouvelleDestination(Personnage* perso, Monde* monde, int newdx, int newdy){
  if (perso->dx==-1  && perso->dy==-1){
    printf("votre personnage est immobilise, il ne peut pas se déplacer\n");
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

int* TrouverCaseLibre(Monde* monde, Personnage* chateau,int* tresor){
    // objectif trouver une case libre autour du chateau
    int *T = malloc(2*sizeof(int));
    if(T==NULL){
      return T;
    } else{
      int* Tp=T;
      int cx=chateau->px;
      int cy=chateau->py;

      for(int i=-1; i<=1; i++){
          for (int j=-1; j<=1;j++){
            if ((monde->plateau[cx+i][cy+j].perso==NULL) && (monde->plateau[cx+i][cy+j].chateau==NULL)){
              *Tp= cx+i;
              *(Tp+1)=cy+j;
              return T;
            }
          }
      }

      for(int i=-2; i<=2; i++){
          for (int j=-2; j<=2;j++){
            if((i==2) || (i==2) || (j==-2) || (j==2)){
              if ((monde->plateau[cx+i][cy+j].perso==NULL) && (monde->plateau[cx+i][cy+j].chateau==NULL)){
                *Tp= cx+i;
                *(Tp+1)=cy+j;
                 return T;
              }
            }
          }
      }
      return NULL;

    }
}

void TourManant( Personnage* manant, Monde * monde, int * tresor){

    if((manant->dx!=-1) && (manant->dy!=-1)){
      char str[4];
      char str1[4]="oui";
      printf("souhaitez-vous immobilise le manant sur la case (%d,%d) \n oui ou non ?\n", manant->px, manant->py);
      scanf("%s",str);
      if(strcmp(str,str1)==0){
        immobilisation(manant);
      }else{
        if ((manant->px!=manant->dx) && (manant->py!=manant->dy)){
            printf("votre personnage est en déplacement\n");
            deplacementPerso(manant,monde);
        } else{
          int newdx, newdy;
          printf("entrer les coordonnees de la nouvelle destination du manant (%d,%d)\n", manant->px, manant->py);
          printf("nouvelle ligne dx : ");
          scanf("%d",&newdx);
          printf("nouvelle colonne dy : ");
          scanf("%d",&newdy);
          nouvelleDestination(manant, monde, newdx, newdy);
          deplacementPerso(manant,monde);
          }
        }
    }else {
        printf("le manat (%d,%d) produit 1 piece d'or\n",manant->px,manant->py);
        productionManant(manant, tresor);
    }
}

void TourGuerrier(Personnage * guerrier, Monde *monde){
  if ((guerrier->px!=guerrier->dx) && (guerrier->py!=guerrier->dy)){
      printf("votre personnage est en cours en déplacement\n");
      deplacementPerso(guerrier,monde);
  } else {
      printf("souhaitez-vous deplacer le guerrier de la case (%d,%d) \n oui ou non\n : ",guerrier->px,guerrier->py);
      char str[4];
      char str1[4]="oui";
      scanf("%s",str);
      if (strcmp(str1,str)==0) {
        int newdx, newdy;
        printf("nouvelle ligne dx : ");
        scanf("%d",&newdx);
        printf("nouvelle colonne dy : ");
        scanf("%d",&newdy);
        nouvelleDestination(guerrier,monde,newdx,newdy);
        deplacementPerso(guerrier,monde);
      }
      else{
        printf("souhaitez-vous que votre guerrier se fasse hara-kiri \n oui ou non : \n");
        scanf("%s",str);
        if (strcmp(str1,str)==0){
          suicide(guerrier,monde);
        }
        else
        { printf("votre guerrier en case(%d,%d) n'a pas joue !\n",guerrier->px,guerrier->py); }
      }
   }
}
void TourSeigneur(Personnage *seigneur,ListePerso*JeuVoisin, Monde *monde, int*tresor){
  if ((seigneur->px!=seigneur->dx) && (seigneur->py!=seigneur->dy)){
      printf("votre personnage est en cours en déplacement\n");
      deplacementPerso(seigneur,monde);
  } else {
      char str[4];
      char str1[4]="oui";
      printf("souhaitez-vous deplacer le seigneur de la case (%d,%d) \n oui ou non : \n",seigneur->px,seigneur->py);
      scanf("%s", str);
      if (strcmp(str1,str)==0) {
        int newdx, newdy;
        printf("nouvelle ligne dx : ");
        scanf("%d",&newdx);
        printf("nouvelle colonne dy : ");
        scanf("%d",&newdy);
        nouvelleDestination(seigneur,monde,newdx,newdy);
        deplacementPerso(seigneur,monde);

      } else{
          printf("souhaitez-vous que votre seigneur se fasse hara-kiri \n oui ou non : \n");
          scanf("%s",str);
          if (strcmp(str1,str)==0){
            suicide(seigneur,monde);
          }
          else
          { char str[4];
            printf("souhaitez-vous immobiliser le seigneur de la case (%d,%d) \n oui ou non : \n",seigneur->px,seigneur->py);
            scanf("%s", str);
            if (strcmp(str1,str)==0) {
              immobilisation(seigneur);
              Transformartion(seigneur,JeuVoisin, monde, tresor);
            } else { printf("votre seigneur en case (%d,%d) n'a pas joue !\n ", seigneur->px, seigneur->py);}
          }

      }
   }
}
void TourChateau(Personnage* chateau, Monde* monde, int* tresor){
    if ((chateau->tempsProd!=0) || (chateau->typeProd!=Rien)){
        printf("le chateau est en cours de production d'un ");
        switch(chateau->typeProd){
          case 1: printf("Seigneur pour encore %d tours\n",chateau->tempsProd); break;
          case 2: printf("Guerrier pour encore %d tours\n",chateau->tempsProd); break;
          case 3: printf("Manant pour encore %d tours\n", chateau->tempsProd); break;
          default : printf("pas de type de production définie\n");
        }
        chateau->tempsProd--;
        if (chateau->tempsProd==0){
          chateau->typeProd=Rien;
        }
    }
    else { // partie où le chateau ne produit rien, le temps de production est bien revenue à 0 et la production Rien;
      printf("souhaitez-vous que votre chateau en case (%d,%d) produise ? \n oui ou non ?",chateau->px,chateau->py);
      char str[4];
      char str1[4]="oui";
      scanf("%s",str);
      if(strcmp(str1,str)==0){
          ChateauProduction(chateau,monde,tresor);
      }else{
        printf(" vous avez repondu non, vous passez donc le tour de votre chateau\n");
      }
    }
}


void Transformartion(Personnage* Seigneur,ListePerso *JeuVoisin, Monde* monde, int* tresor) {
  if(Seigneur->dx !=-1 || Seigneur->dy!=-1)
    printf("Le seigneur n'est pas immobile, il ne peut pas se transformer");
  else {
    printf("Souhaitez vous transfrormer votre seigneur en (%d,%d) en chateau pour 30 piece d'or? \n oui ou non?",Seigneur->px,Seigneur->py );
    char str[4];
    char str1[4]="oui";
    scanf("%s",str);
    if(strcmp(str1,str)==0){
      if( *tresor < 30)
        printf("vous n'avez pas assez de pièce d'or");
      else {
        int x = Seigneur->px;
        int y = Seigneur->py;
        couleur_t couleur_seigneur= Seigneur->couleur;
        suicide(Seigneur, monde);
        CreerChateau(JeuVoisin, monde,couleur_seigneur, x, y);
        printf("Le Seigneur s'est transforme en chateau en (%d,%d)",x,y);
        *tresor-=30;
      }
    }
  }
}
