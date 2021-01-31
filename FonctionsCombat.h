#ifndef FONCTIONSCOMBATS_H
#define FONCTIONSCOMBATS_H

void killdefenseur(Personnage* perdant, Monde* monde);
void killattaquant(Personnage* perdant, Monde* monde);
void CombatMemePerso(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatSeigneurGuerrier(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatSeigneurManant(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatGuerrierSeigneur(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatGuerrierManant(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatManantSeigneur(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void CombatManantGuerrier(Personnage* attaquant, Personnage* defenseur, Monde* monde);
void combat(Personnage* attaquant, Personnage* defenseur, ListePerso* JeuvoisinRouge, ListePerso* Jeuvoisinbleu, Monde* monde);
void CombatChateau(Personnage* attaquant, Personnage* defenseur, ListePerso* JeuvoisinRouge, ListePerso* JeuvoisinBleu, Monde* monde);
#endif
