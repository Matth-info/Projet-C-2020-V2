#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAction.h"


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


void CreerChateau(ListePerso *Jeu, ListePerso* JeuVoisinChateau, Monde * monde, couleur_t couleur,int px, int py){ // fonction pour remplir un espace alloué pour un chateau// Tete d'une ListePerso
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

    if (JeuVoisinChateau->nbPerso==0){ // si le nombre de personnage dans la liste Jeu voisin n'est pas nul, alors il y a déjà d'autres chateau initiallisaer;
        switch(couleur){
          case 0: monde->CampRouge=Castle;
                  JeuVoisinChateau->tete=Castle;
                  JeuVoisinChateau->fin=Castle;
                  break;
          case 1: monde->CampBleu=Castle;
                  JeuVoisinChateau->tete=Castle;
                  JeuVoisinChateau->fin=Castle;
                  break;
        }
    }
    Castle->PersoPrecedentVoisin=JeuVoisinChateau->fin;
    Castle->PersoSuivantVoisin= NULL;// la tete ne change jamais = toujours un chateau en tete de sa liste.

    JeuVoisinChateau->fin->PersoSuivant=Castle;
    JeuVoisinChateau->fin=Castle;

    JeuVoisinChateau->nbPerso++;
  }
}

void CreerSeigneur(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py, int* tresor){ // un seigneur est rataché à un chateau forcément
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

    seigneur->PersoPrecedentVoisin=NULL; // à modifier au niveau 4
    seigneur->PersoSuivantVoisin=NULL;


    if (chateau->PersoSuivant == NULL){
      seigneur->PersoSuivant=NULL;
      seigneur->PersoPrecedent=chateau;
      chateau->PersoSuivant=seigneur;
    } else{
      seigneur->PersoSuivant=chateau->PersoSuivant;
      seigneur->PersoPrecedent=chateau; // la tete ne change jamais = toujours un chateau en tete de sa liste.
      chateau->PersoSuivant->PersoPrecedent=seigneur;
      chateau->PersoSuivant=seigneur;
    }

    monde->plateau[px][py].perso=seigneur;
    *tresor=*tresor-20;

  }
}

void CreerGuerrier(Personnage* chateau,Monde* monde, couleur_t couleur, int px, int py, int * tresor) {
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

  guerrier->PersoSuivantVoisin=NULL;
  guerrier->PersoPrecedentVoisin=NULL; // à modifier lorsque l'on sera au niveau 4;

  Personnage* Persotemp = chateau;

  while(Persotemp->suivant != NULL) {
    Persotemp = Persotemp->PersoSuivant;
  }

  Personnage* fin = Persotemp;

  while(Persotemp->typePerso == Manant) {
    Persotemp = Persotemp->PersoPrecedent;
  }

  if(Persotemp == fin) {
    guerrier->PersoPrecedent=fin;
    fin->PersoSuivant = guerrier;
    fin = guerrier;
    guerrier->PersoSuivant = NULL;
  }
  else {
    guerrier->PersoPrecedent = Persotemp; // la tete ne change jamais = toujours un chateau en tete de sa liste.
    guerrier->PersoSuivant = Persotemp->PersoSuivant;

    Persotemp->PersoSuivant->PersoPrecedent = guerrier;
    Persotemp->PersoSuivant = guerrier;
  }


  monde->plateau[px][py].perso=guerrier;
  *tresor=*tresor-5;
  }
}

void CreerManant(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py, int* tresor) {
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

  manant->PersoPrecedentVoisin=NULL;
  manant->PersoSuivantVoisin=NULL;
  Personnage* fin = chateau;
  while(fin->PersoSuivant != NULL)
    fin = fin->PersoSuivant;
  manant->PersoPrecedent=fin;
  manant->PersoSuivant= NULL;// la tete ne change jamais = toujours un chateau en tete de sa liste.

  fin->PersoSuivant=manant;

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


void ChateauProduction(Personnage* chateau, Monde* monde, int* tresor) {
  if(chateau->tempsProd != 0) {
    printf("le chateau est deja en production\n");
  }
  else {
    int* T;
    T= TrouverCaseLibre(monde, chateau, Jeu, tresor);
    if (T == NULL) {
      printf("Aucune case libre trouvee au tour du chateau (%d,%d)\n", chateau->px, chateau->py);
    }
    else {
      int i;
      printf("Rentrer le numero  du personnage: \n \t 1: un Seigneur en (%d,%d) pour 20 pieces d'or \n \t 2: un Guerrier en (%d,%d) pour 5 pieces d'or  \n \t 3: un Manant en (%d,%d) pour 1 piece d'or \n \t 4: Rien \n",T[0],T[1],T[0],T[1],T[0],T[1]);
      scanf("%d", &i);
      int savetresor = *tresor; // comparer le trésor d'avant et d'après l'appel à la fonction permettra de savoir si la création du nouveau personnage a bien eu lieu;

      switch(i) {
        case 1: CreerSeigneur(chateau, monde, chateau->couleur, T[0], T[1], tresor);
          if(savetresor == *tresor){
            printf("avec un tresor de %d pieces d'or, vous n'avez pas assez pour creer un Seigneur", *tresor);
            ChateauProduction(Castle, monde, tresor);
          }else{
              chateau->typeProd = Seigneur;
              chateau->tempsProd = 6;
          }
          break;
        case 2: CreerGuerrier(chateau, monde, chateau->couleur, T[0], T[1], tresor);
          if(savetresor == *tresor) {
              ChateauProduction(chateau, monde, tresor);
              printf("avec un tresor de %d pieces d'or, vous n'avez pas assez pour créer un Guerrier", *tresor);
          } else{
            chateau->typeProd = Guerrier;
            chateau->tempsProd = 4;
          }
          break;
        case 3: CreerManant(chateau, monde, chateau->couleur, T[0], T[1], tresor);
          if(savetresor == *tresor){
            printf("avec un tresor de %d pieces d'or, vous n'avez pas assez pour créer un Manant", *tresor);
            ChateauProduction(chateau, monde, tresor);
          }else{
          chateau->typeProd = Manant;
          chateau->tempsProd = 2;
          }
          break;
        case 4: chateau->typeProd = Rien;
                break;
        default: printf("Valeur rentree incorrect\n");
                ChateauProduction(chateau, monde, tresor);
      }

    }
    free(T);
  }
}
