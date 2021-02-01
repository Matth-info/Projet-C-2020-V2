#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "FonctionsCreation.h"
#include "FonctionsAction.h"
#include "FonctionsAffichage.h"
#include "FonctionsCombat.h"

void combat(Personnage* attaquant, Personnage* defenseur, ListePerso* JeuVoisin, ListePerso* JeuVoisinAdverse, Monde* monde) {
    if(attaquant->typePerso == defenseur->typePerso) {
        //si deux personnage du meme type s'affrontent
        CombatMemePerso(attaquant,defenseur,monde);
    }
    else{
        switch(attaquant->typePerso) { // disjonction en fonction du type de l'attaquant
            case 0: break;

            case 1: switch(defenseur->typePerso) { // disjonction en fonction du type du défenseur
                case 0: printf("Un seigneur en (%d,%d) attaque un Chateau en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatChateau(attaquant, defenseur, JeuVoisin, JeuVoisinAdverse, monde);
                        break;
                case 2: printf("Un seigneur en (%d,%d) attaque un Guerrier en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatSeigneurGuerrier(attaquant,defenseur,monde);
                        break;
                case 3: printf("Un seigneur en (%d,%d) attaque un Manant en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatSeigneurManant(attaquant,defenseur,monde);
                        break;
                default:
                        break;
            } break;

            case 2: switch(defenseur->typePerso) { // disjonction en fonction du type du défenseur
                case 0: printf("Un Guerrier en (%d,%d) attaque un Chateau en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatChateau(attaquant, defenseur, JeuVoisin, JeuVoisinAdverse, monde);
                        break;
                case 1: printf("Un Guerrier en (%d,%d) attaque un Seigneur en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatGuerrierSeigneur(attaquant,defenseur,monde);
                        break;
                case 3: printf("Un Guerrier en (%d,%d) attaque un Manant en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatGuerrierManant(attaquant,defenseur,monde);
                        break;
                default:
                        break;
            } break;

            case 3: switch(defenseur->typePerso) { // disjonction en fonction du type du défenseur
                case 0: printf("Un Manant en (%d,%d) attaque un Chateau en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatChateau(attaquant, defenseur, JeuVoisin, JeuVoisinAdverse, monde);
                        break;
                case 1: printf("Un Manant en (%d,%d) attaque un Seigneur en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatManantSeigneur(attaquant,defenseur,monde);
                        break;
                case 2: printf("Un Manant en (%d,%d) attaque un Guerrier en (%d,%d)\n", attaquant->px, attaquant->py, defenseur->px, defenseur->py);
                        CombatManantGuerrier(attaquant,defenseur,monde);
                        break;
                default:
                        break;
            } break;
        }
    }
}



void killdefenseur(Personnage* perdant, Monde* monde) { // fonction qui annonce la mort d'un agent lors d'une defense et rétablit la liste doublement chainée du château

    switch(perdant->typePerso){
        case 1: if(perdant->couleur == 0)
                    printf("Le Seigneur rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Seigneur bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        case 2: if(perdant->couleur == 0)
                    printf("Le Guerrier rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Guerrier bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        case 3: if(perdant->couleur == 0)
                    printf("Le Manant rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Manant bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        default: printf("erreur sur le type de personnage (fonction kill)");
                break;
    }

    if (perdant->PersoSuivant==NULL) { // si le personnage décédé est dernier dans la liste double du chateau
        perdant->PersoPrecedent->PersoSuivant=NULL;
    }
    else {
      perdant->PersoPrecedent->PersoSuivant=perdant->PersoSuivant;
      perdant->PersoSuivant->PersoPrecedent=perdant->PersoPrecedent;
    }

    if((monde->plateau[perdant->px][perdant->py].perso == perdant) && (perdant->PersoSuivantVoisin == NULL)){
        monde->plateau[perdant->px][perdant->py].perso = NULL;
    }
    else {
        if(perdant->PersoSuivantVoisin == NULL) {
            perdant->PersoPrecedentVoisin->PersoSuivantVoisin = NULL;
        }
        else {
          perdant->PersoSuivantVoisin->PersoPrecedentVoisin = NULL;
          monde->plateau[perdant->px][perdant->py].perso = monde->plateau[perdant->px][perdant->py].perso->PersoSuivantVoisin;
        }
    }
    free(perdant);
}

void killattaquant(Personnage* perdant, Monde* monde) { // fonction qui annonce la mort d'un agent lors d'une attaque et rétablit la liste doublement chainée du château
    switch(perdant->typePerso){
        case 1: if(perdant->couleur == 0)
                    printf("Le Seigneur rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Seigneur bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        case 2: if(perdant->couleur == 0)
                    printf("Le Guerrier rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Guerrier bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        case 3: if(perdant->couleur == 0)
                    printf("Le Manant rouge en case (%d,%d) est mort\n",perdant->px, perdant->py);
                else
                    printf("Le Manant bleu en case (%d,%d) est mort\n",perdant->px, perdant->py);
                break;
        default: printf("erreur sur le type de personnage (fonction kill)");
                break;
    }

    if (perdant->PersoSuivant==NULL) { // si le personnage décédé est dernier dans la liste double du chateau
        perdant->PersoPrecedent->PersoSuivant=NULL;
    }
    else {
      perdant->PersoPrecedent->PersoSuivant=perdant->PersoSuivant;
      perdant->PersoSuivant->PersoPrecedent=perdant->PersoPrecedent;
    }
    free(perdant);
}

void CombatMemePerso(Personnage* attaquant, Personnage* defenseur, Monde* monde) { 
    // combat opposant 2 personnages de meme type
    int nb = 0;
    int const MIN = 1, MAX = 100;
    srand(time(NULL));

    switch(attaquant->typePerso){
      case 0: break;
      case 1: printf("Duel de Seigneur\n"); break;
      case 2: printf("Duel de Guerrier\n"); break;
      case 3: printf("Duel de Manant\n"); break;
      default : printf("Erreur type Perso (fct CombatMemePerso)\n");
    }

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb <= 50) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatSeigneurGuerrier(Personnage* attaquant, Personnage* defenseur, Monde* monde) { 
    // combat opposant un seigneur en attaque et un guerrier en défense 
    int nb = 0;
    const int MIN = 1, MAX = 25;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN; 
    if(nb >= 5) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatSeigneurManant(Personnage* attaquant, Personnage* defenseur, Monde* monde) {
    // combat opposant un seigneur en attaque et un manant en defense 
    int nb = 0;
    const int MIN = 1, MAX = 21;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb >= 2) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatGuerrierSeigneur(Personnage* attaquant, Personnage* defenseur, Monde* monde) {
    // combat opposant un guerrier en attaque et un seigneur en defense 
    int nb = 0;
    const int MIN = 1, MAX = 25;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb <= 6) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatGuerrierManant(Personnage* attaquant, Personnage* defenseur, Monde* monde) {
    // combat opposant un guerrier en attaque et un manant en defense 
    int nb = 0;
    const int MIN = 1, MAX = 6;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb >= 2) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatManantSeigneur(Personnage* attaquant, Personnage* defenseur, Monde* monde) {
    // combat opposant un manant en attaque et un seigneur en defense 
    int nb = 0;
    const int MIN = 1, MAX = 21;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb <= 1) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}

void CombatManantGuerrier(Personnage* attaquant, Personnage* defenseur, Monde* monde) {
    // combat opposant un manant en attaque et un guerrier en defense 
    int nb = 0;
    const int MIN = 1, MAX = 6;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;
    if(nb <= 1) {
        killdefenseur(defenseur,monde);
    }
    else {
        killattaquant(attaquant,monde);
    }
}


void CombatChateau(Personnage* attaquant, Personnage* defenseur, ListePerso* JeuVoisin, ListePerso* JeuVoisinAdverse, Monde* monde) {
    // combat impliquant un chateau, le chateau est toujours en défense
    int nb = 0;
    int MIN = 1, MAX = 50;
    srand(time(NULL));

    nb = (rand()%(MAX+1-MIN))+MIN;

    switch(attaquant->typePerso) {
        case 0: break;

        case 1: nb = (rand()%(MAX+1-MIN))+MIN;
                if(nb >= 21) {
                    printf("Le Chateau en (%d,%d) a reussi a survivre a l'assaut et tue le seigneur\n", defenseur->px,defenseur->py);
                    killattaquant(attaquant,monde);
                }
                else {
                   destructionChateau(attaquant,defenseur, monde,JeuVoisinAdverse, JeuVoisin);
                }
                break;

        case 2: MAX = 35;
                nb = (rand()%(MAX+1-MIN))+MIN;
                if(nb >= 35) { // si le chateau parvient à se défendre et à tuer son attaquant
                    printf("Le Chateau en (%d,%d) a reussi a survivre a l'assaut et tue le guerrier\n", defenseur->px,defenseur->py);
                    killattaquant(attaquant,monde);
                }
                else {
                    destructionChateau(attaquant,defenseur, monde,JeuVoisinAdverse, JeuVoisin);
                }
                break;

        case 3: MAX = 31;
                nb = (rand()%(MAX+1-MIN))+MIN;
                if(nb >= 2) {
                    printf("Le Chateau en (%d,%d) a reussi a survivre a l'assaut et tue le manant\n", defenseur->px,defenseur->py);
                    killattaquant(attaquant,monde);
                }
                else {
                  destructionChateau(attaquant,defenseur, monde,JeuVoisinAdverse, JeuVoisin);
                }
        }
}
