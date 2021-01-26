#ifndef FONCTIONSACTION_H
#define FONCTIONSACTION_H

void lancementdePartie(ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde *monde, int* tresorRouge, int * tresorBleu);
void productionManant(Personnage* manant, int* tresor);
void trahisonManant(Personnage* manant, Personnage*Attaquant, Personnage* Perdant);
void suicide(Personnage* Harakiri, Monde* monde);
void destructionChateau(Personnage* ChateauAttaquant, Personnage* ChateauPerdant, Monde* monde, ListePerso* JeuVoisinPerdant);
void nouvelleDestination(Personnage* perso, ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde* monde, int newdx, int newdy);
void deplacementPerso(Personnage* perso,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde * monde);
void immobilisation(Personnage* perso);
int* TrouverCaseLibre(Monde* monde, Personnage* chateau, int* tresor);
void TourGuerrier(Personnage * guerrier, ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde *monde);
void TourManant(Personnage* manant,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, Monde * monde, int * tresor);
void TourSeigneur(Personnage * seigneur,ListePerso* JeuVoisin, ListePerso* JeuVoisinAdverse, Monde *monde, int* tresor);
void TourChateau(Personnage * chateau,Monde* monde, int* tresor);
void Transformartion(Personnage* Seigneur,ListePerso*JeuVoisin, Monde* monde, int* tresor);
void TourDeJeu(Monde* monde,ListePerso* JeuVoisin, ListePerso* JeuVoisinAdverse, int*tresor);
#endif
