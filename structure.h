#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<stdio.h>
#define T_MAX 256

typedef enum typePerso {Chateau, Seigneur, Guerrier, Manant} typePerso_t;
typedef enum typeProd {seigneur,guerrier,manant,Rien} typeProd_t;
typedef enum couleur{Rouge, Bleu} couleur_t;

typedef enum direction{Nord,Sud,Est,Ouest,NordEst, NordOuest, SudEst, SudOuest } direction_t;

typedef struct mouvement{
  direction_t direction;
  int dx;
  int dy;
}mouvement_t;

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

  struct Personnage* PersoPrecedentVoisin; // chateau voisin pour les chateaux et agents sur la même case pour les agents
  struct Personnage* PersoSuivantVoisin; // les voisins de case pour les agents seront initilisés à NULL , pas possible avant le niveau 4 d'avoir plusieur personnage sur la case.

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

typedef struct CoupleNS{
  char nomVainqueur[T_MAX];
  int score;
}CoupleNS;

#endif
