#ifndef FONCTIONSACTION_H
#define FONCTIONSACTION_H

void lancementdePartie(ListePerso* JeuRouge, ListePerso* JeuBleu, Monde *monde, int* tresorRouge, int * tresorBleu);
void productionManant(Personnage* manant, int* tresor);
void trahisonManant(Personnage* manant, ListePerso *Attaquant, ListePerso* Perdant);
void suicide(Personnage* Harakiri,ListePerso *Perdant, Monde* monde);
void destructionChateau(ListePerso* Attaquant, ListePerso* Perdant, Monde* monde);
void nouvelleDestination(Personnage* perso,Monde* monde, int newdx, int newdy);
void deplacementPerso(Personnage* perso, Monde * monde);
void immobilisation(Personnage* perso);
int* TrouverCaseLibre(Monde* monde, Personnage* chateau, ListePerso* Jeu, couleur_t couleur, int* tresor);

#endif
