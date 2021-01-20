#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<stdio.h>

typedef enum typePerso {Chateau, Seigneur, Guerrier, Manant} typePerso_t;
typedef enum typeProd {seigneur,guerrier,manant,Rien} typeProd_t;
typedef enum couleur{Rouge, Bleu} couleur_t;

typedef struct Personnage{ //equivalent du maillon dans les TD/TPs
  couleur_t couleur;
  typePerso_t typePerso;
  // position
  int px,py; // tant que p!=d pas de deplacement supplementaire possible
  //si agent
  int dx,dy;
  //si chateau
  typeProd_t typeProd; // le chateau peut produire uniquement des guerriers, des manants et des seigneurs
  int tempsProd;

  struct Personnage* PersoPrecedent; // dans le ListePerso
  struct Personnage* PersoSuivant;
}Personnage;


typedef struct ListePerso{ //Liste doublement chainee
  Personnage* tete;
  Personnage* fin;
  int nbPerso;
}ListePerso;

typedef struct Case{
  Personnage* chateau; // si il y a un chateau sur la case
  Personnage* perso; //reserver aux autres personnages
}Case;

typedef struct {
  Case** plateau;
  Personnage* CampRouge;
  Personnage* CampBleu;
}Monde;

#endif
