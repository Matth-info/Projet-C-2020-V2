#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"


ListePerso * initJeu(void){ // creation d'une liste doublement chainee
    ListePerso* Jeu=malloc(sizeof(ListePerso));
    if (Jeu==NULL){
      return NULL;
    }
    Jeu->tete=NULL;
    Jeu->fin=NULL;
    Jeu->nbPerso=0;
    return Jeu;
}


void CreerChateau(ListePerso *Jeu, Monde * monde, couleur_t couleur,int px, int py){ // fonction pour remplir un espace alloué pour un chateau// Tete d'une ListePerso
  Personnage* Castle =malloc(sizeof(Personnage));
  if (Jeu->nbPerso>0){
    printf("la liste de jeu contient déjà un chateau, initialisation de la liste impossible"); // si il y a déjà un personnage dans la double liste chainée alors on ne peut pas rajouter un Chateau car il en exite déjà un forcément
  }
  else
  {
    Castle->couleur = couleur;
    Castle->typePerso=Chateau;
    Castle->px=px;
    Castle->py=py;
    Castle->dx=-1; // les coordonnees negatifs sont là pour empecher le deplacement de ce type de personnage
    Castle->dy=-1; // (les manants immobiles auront egalement ces coordonnees)
    Castle->typeProd=Rien;
    Castle->tempsProd=0;

    Castle->PersoPrecedent=NULL;
    Castle->PersoSuivant=NULL;
    Jeu->tete=Castle;
    Jeu->fin=Castle;
    Jeu->nbPerso++;

    monde->plateau[px][py].chateau=Castle; // ici on accede au plateau de jeu, à la case px, py et on relie le membre chateau au Castle
    switch(couleur){
      case 0: monde->CampRouge=Castle;
              break;
      case 1: monde->CampBleu=Castle;
              break;
    }
  }
}

void CreerSeigneur(ListePerso* Jeu, Monde* monde,  couleur_t couleur, int px, int py, int* tresor){ // un seigneur est rataché à un chateau forcément
  Personnage* seigneur=malloc(sizeof(Personnage));
  if (seigneur==NULL || Jeu->nbPerso==0 || *tresor-20 < 0 ){
      printf("creation du Seigneur impossible\n ");
  }
  else
  {
    seigneur->couleur=couleur;
    seigneur->typePerso=Seigneur;
    seigneur->px=px;
    seigneur->py=py;
    seigneur->dx=px; // à la creation du seigneur sa destination est egale à sa position condition pour effectuer une action autre que le deplacement
    seigneur->dy=py;
    seigneur->typeProd=Rien; // le seigneur ne produit rien mais peut devenir un chateau (il faudra faire une fonction transformation)
    seigneur->tempsProd=-1;


    if (Jeu->nbPerso==1){
      seigneur->PersoSuivant=NULL;
      seigneur->PersoPrecedent=Jeu->tete;
      Jeu->tete->PersoSuivant=seigneur;
      Jeu->fin=seigneur;
    } else{
      seigneur->PersoSuivant=Jeu->tete->PersoSuivant;
      seigneur->PersoPrecedent=Jeu->tete; // la tete ne change jamais = toujours un chateau en tete de sa liste.
      Jeu->tete->PersoSuivant->PersoPrecedent=seigneur;
      Jeu->tete->PersoSuivant=seigneur;
    }
    Jeu->nbPerso++;

    monde->plateau[px][py].perso=seigneur;
    *tresor=*tresor-20;

  }
}

void CreerGuerrier(ListePerso* Jeu,Monde* monde, couleur_t couleur, int px, int py, int * tresor) {
  Personnage* guerrier = malloc(sizeof(Personnage));
  if (guerrier == NULL || Jeu->nbPerso == 0 || *tresor - 5 < 0){
    printf("creation du Guerrier impossible");
  }
  else{
  guerrier->couleur = couleur;
  guerrier->typePerso = Guerrier;
  guerrier->px = px;
  guerrier->py = py;
  guerrier->dx = px;
  guerrier->dy = py;
  guerrier->typeProd = Rien;
  guerrier->tempsProd = -1;

  Personnage* Perso = Jeu->fin;

  while(Perso->typePerso == Manant) {
    Perso = Perso->PersoPrecedent;
  }

  if(Perso == Jeu->fin) {
    guerrier->PersoPrecedent=Jeu->fin;
    Jeu->fin->PersoSuivant = guerrier;
    Jeu->fin = guerrier;
    guerrier->PersoSuivant = NULL;
  }
  else {
    guerrier->PersoPrecedent = Perso; // la tete ne change jamais = toujours un chateau en tete de sa liste.
    guerrier->PersoSuivant = Perso->PersoSuivant;

    Perso->PersoSuivant->PersoPrecedent = guerrier;
    Perso->PersoSuivant = guerrier;
  }

  Jeu->nbPerso++;

  monde->plateau[px][py].perso=guerrier;
  *tresor=*tresor-5;
  }
}

void CreerManant(ListePerso* Jeu, Monde* monde,  couleur_t couleur, int px, int py, int* tresor) {
  Personnage* manant = malloc(sizeof(Personnage));
  if (manant == NULL || Jeu->nbPerso == 0 || *tresor-1 < 0){
    printf("creation du manant impossible");
  }
  else
  {
  manant->couleur = couleur;
  manant->typePerso = Manant;
  manant->px = px;
  manant->py = py;
  manant->dx = px;
  manant->dy = py;
  manant->typeProd = Rien;
  manant->tempsProd = -1;

  manant->PersoPrecedent=Jeu->fin;
  manant->PersoSuivant= NULL;// la tete ne change jamais = toujours un chateau en tete de sa liste.

  Jeu->fin->PersoSuivant=manant;
  Jeu->fin=manant;

  Jeu->nbPerso++;
  monde->plateau[px][py].perso=manant;
  *tresor=*tresor-1;
  }
}

Case** CreerPlateau(int nbcolonne, int nbligne){// fonction creation d'un plateau de jeu commpose de nbcolonne * nbligne case
  if (nbcolonne<4 || nbligne<4){
    printf("dimension du plateau trop petite, veuillez rentrer de nouvelle dimension du plateau de jeu");
    return NULL; // si le plateau ne peut pas se creer, on renvoie un pointeur NULL;
  } else {
      Case** plateau= malloc(nbligne*sizeof(Case)); // creation du plateau de jeu
      for (int i=0;i<nbligne;i++){
        plateau[i]=malloc(nbcolonne*sizeof(Case));
      }
      // initialisation du plateau de jeu dont toute les cases sont composees par des pointeurs NULL,
      for (int i=0; i<nbligne; i++){
        for (int j=0; j<nbcolonne; j++){
          plateau[i][j].chateau=NULL;
          plateau[i][j].perso=NULL;
        }
      } // on retourne le plateau

    return plateau;
    }
}

Monde *CreerMonde(Case ** Land){
      Monde *monde=malloc(sizeof(Monde)); // les 1er chateaux construits seront ceux qui se lieront aux pointeurs Camps Rouge et Bleu
      monde->CampRouge=NULL;
      monde->CampBleu=NULL;
      monde->plateau=Land;
      return monde;
}


void ChateauProduction(ListePerso* Jeu, Monde* monde,  couleur_t couleur, int* tresor) {
  if(Jeu->tete->tempsProd != 0) {
    printf("le chateau est déjà en production");
  }
  else {
    int * T = TrouverCaseLibre(monde, Jeu->tete, Jeu, couleur, tresor);
    if (T == NULL) {
      printf("Aucune case libre trouvee");
    }
    else {
      int i;
      printf("Rentrer le numero  du personnage: \n \t 1:Seigneur, 20 pieces d'or \n \t 2:Guerrier, 5 pieces d'or  \n \t 3:Manant, 1 piece d'or \n \t 4:Rien \n");
      scanf("%d", &i);
      int savetresor = *tresor;


      switch(i) {
        case 1: CreerSeigneur(Jeu, monde, couleur, T[0], T[1], tresor);
          if(savetresor == *tresor) ChateauProduction(Jeu, monde, couleur, tresor);
          Jeu->tete->typeProd = Seigneur;
          Jeu->tete->tempsProd = 6;
          break;
        case 2: CreerGuerrier(Jeu, monde, couleur, T[0], T[1], tresor); 
          if(savetresor == *tresor) ChateauProduction(Jeu, monde, couleur, tresor);
          Jeu->tete->typeProd = Guerrier;
          Jeu->tete->tempsProd = 4;
          break;
        case 3: CreerManant(Jeu, monde, couleur, T[0], T[1], tresor); 
          if(savetresor == *tresor) ChateauProduction(Jeu, monde, couleur, tresor);
          Jeu->tete->typeProd = Manant;
          Jeu->tete->tempsProd = 2;
          break;
        case 4: Jeu->tete->typeProd = Rien; break;
      }


    }
  }
}