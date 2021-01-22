#ifndef FONCTIONSACTION_H
#define FONCTIONSACTION_H

void lancementdePartie(ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde *monde, int* tresorRouge, int * tresorBleu);
void productionManant(Personnage* manant, int* tresor);
void trahisonManant(Personnage* manant, Personnage*Attaquant, Personnage* Perdant);
void suicide(Personnage* Harakiri, Monde* monde);
void destructionChateau(Personnage* ChateauAttaquant, Personnage* ChateauPerdant, Monde* monde, ListePerso* JeuVoisinPerdant);
void nouvelleDestination(Personnage* perso,Monde* monde, int newdx, int newdy);
void deplacementPerso(Personnage* perso, Monde * monde);
void immobilisation(Personnage* perso);
int* TrouverCaseLibre(Monde* monde, Personnage* chateau, int* tresor);
void TourGuerrier(Personnage * guerrier, Monde *monde);
void TourManant( Personnage* manant, Monde * monde, int * tresor);
void TourSeigneur(Personnage * seigneur, Monde *monde);
void TourChateau(Personnage * chateau,Monde* monde, int* tresor);
void Transformartion(Personnage* Seigneur,ListePerso*JeuVoisin, Monde* monde, int* tresor);
#endif
