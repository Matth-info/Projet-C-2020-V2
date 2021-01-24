#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"FonctionsCreation.h"
#include"FonctionsAffichage.h"
#include"FonctionsAction.h"
#include"FonctionsSauvegarde.h"

#define T_MAX 256

void CreerManantChargement(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py,int dx, int dy, int* tresor) {
  Personnage* manant = malloc(sizeof(Personnage));
  if ((manant == NULL) || (chateau->typePerso!=Chateau) || (*tresor-1 < 0) ){
    printf("creation du manant impossible");
  }
  else
  {
  manant->couleur = couleur;
  manant->typePerso = Manant;
  manant->px = px;
  manant->py = py;
  manant->dx = dx;
  manant->dy = dy;
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

void CreerSeigneurChargement(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py,int dx, int dy, int* tresor){ // un seigneur est rataché à un chateau forcément
  Personnage* seigneur=malloc(sizeof(Personnage));
  if (seigneur==NULL || chateau->typePerso!=Chateau || *tresor-20 < 0 ){
      printf("creation du Seigneur impossible\n ");
  }
  else
  {
    seigneur->couleur=couleur;
    seigneur->typePerso=Seigneur;
    seigneur->px=px;
    seigneur->py=py;
    seigneur->dx=dx; // à la creation du seigneur sa destination est egale à sa position condition pour effectuer une action autre que le deplacement
    seigneur->dy=dy;
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
void CreerGuerrierChargement(Personnage* chateau,Monde* monde, couleur_t couleur, int px, int py, int dx, int dy, int * tresor) {
  Personnage* guerrier = malloc(sizeof(Personnage));
  if ((guerrier == NULL) || (chateau->typePerso != Chateau) || (*tresor - 5 < 0)){
    printf("creation du Guerrier impossible");
  }
  else{
  guerrier->couleur = couleur;
  guerrier->typePerso = Guerrier;
  guerrier->px = px;
  guerrier->py = py;
  guerrier->dx = dx;
  guerrier->dy = dy;
  guerrier->typeProd = Rien;
  guerrier->tempsProd = -1;

  guerrier->PersoSuivantVoisin=NULL;
  guerrier->PersoPrecedentVoisin=NULL; // à modifier lorsque l'on sera au niveau 4;

  Personnage* Persotemp = chateau;

  while(Persotemp->PersoSuivant!= NULL) {
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

//objectif créer un fichier de sauvegarde .got qui respecte les critères de sauvegardes afin de pouvoir facilement le récupérer et rétablir le jeu.
void sauvergardeJeu(Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB, int ProchainAJouer){
  FILE* fichier =NULL;
  printf("entrer le nom du fichier avec l'extension .got :");
  char str[T_MAX]="";
  scanf("%s",str);
  fichier=fopen(str,"w");
  if (fichier==NULL){
    printf("erreur lors de la creation du fichier");
  }
  if (ProchainAJouer==0){
  fprintf(fichier,"R  %d\n",*tresorR);
  fprintf(fichier,"B  %d\n",*tresorB);
  }else{
  fprintf(fichier,"B  %d\n",*tresorB);
  fprintf(fichier,"R  %d\n",*tresorR);
  }

  for(Personnage* ChateauR=JeuRougeVoisin->tete; ChateauR!=NULL; ChateauR=ChateauR->PersoSuivantVoisin){
    for(Personnage* persotemp=ChateauR; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
          if(persotemp->couleur==Rouge){
            fprintf(fichier,"R ");
          }
          switch(persotemp->typePerso){
              case 0: fprintf(fichier,"c ");
                      break;
              case 1: fprintf(fichier,"s ");
                      break;
              case 2: fprintf(fichier,"g ");
                      break;
              case 3: fprintf(fichier,"m ");
                      break;
          }
          fprintf(fichier,"%d %d",persotemp->px,persotemp->py);
          if (persotemp->typePerso!=Chateau){
            fprintf(fichier,"%d %d",persotemp->dx,persotemp->dy);
          }else {
            switch(persotemp->typeProd){
                case 0: fprintf(fichier,"s ");
                        break;
                case 1: fprintf(fichier,"g ");
                        break;
                case 2: fprintf(fichier,"m ");
                        break;
                case 3: fprintf(fichier,"r ");// r pour rien, pas de production;
                        break;
              }
              fprintf(fichier,"%d",persotemp->tempsProd);
            }fprintf(fichier,"\n");
      }
    }
  for(Personnage* ChateauB=JeuBleuVoisin->tete; ChateauB!=NULL; ChateauB=ChateauB->PersoSuivantVoisin){
      for(Personnage* persotemp=ChateauB; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
            if(persotemp->couleur==Bleu){
              fprintf(fichier,"B ");
            }
            switch(persotemp->typePerso){
                case 0: fprintf(fichier,"c ");
                        break;
                case 1: fprintf(fichier,"s ");
                        break;
                case 2: fprintf(fichier,"g ");
                        break;
                case 3: fprintf(fichier,"m ");
                        break;
            }
            fprintf(fichier,"%d %d",persotemp->px,persotemp->py);
            if (persotemp->typePerso!=Chateau){
              fprintf(fichier,"%d %d",persotemp->dx,persotemp->dy);
            }else {
              switch(persotemp->typeProd){
                case 0: fprintf(fichier,"s ");
                        break;
                case 1: fprintf(fichier,"g ");
                        break;
                case 2: fprintf(fichier,"m ");
                        break;
                case 3: fprintf(fichier,"r ");// r pour rien, pas de production;
                        break;
                }
                fprintf(fichier,"%d",persotemp->tempsProd);
              }
               fprintf(fichier,"\n");
        }
      }
    fclose(fichier);
// fin du fichier de sauvegarde
}

int Chargementpartie(int argc, char** argv, Monde* monde,ListePerso * JeuRougeVoisin, ListePerso * JeuBleuVoisin, int* tresorR, int* tresorB){
  // les fichiers à compiler sont FonctionsCreation.c FonctionsAffichage.c,
  // FonctionsAction.c FonctionsCombat.c FonctionsSauvegarde.c main.c
  // si argc==7 alors on a la présence d'un fichier de sauvegarde .got;
  // la fonction récupère les trésors bleu et rouge (initialisé à 50 dans le main(), puis les modifie en fonction des 2 premières lignes du fichier Sauvegarde)
  // (Problème resolu)noter que la récupération du premier tresor en tête de fichier sauvegarde fonctionne bien mais pas celle du deuxieme trésor (ex ci dessous)
  // 10 pieces d'or dans le coffre Rouge
  //1965968678 pieces d'or dans le coffre Bleu
  int ProchainAJouer=3;
  if (argc==2){
    FILE* fichier=fopen(argv[argc-1],"r");
    if (fichier==NULL){
      return 2;
    }else{
      //generation du monde avec les deux listes JeuVoisin Bleue et Rouge
      int tresor1;
      int tresor2;

      int tresorRsave;
      int tresorBsave;
      char lignePerso[T_MAX]="";
      char Tresor1[T_MAX]="";
      char Tresor2[T_MAX]="";
      int i;

      fgets(lignePerso,T_MAX,fichier);
      if(lignePerso[0]=='R'){
        ProchainAJouer=0; // le prochain à jouer est le joueur Rouge;
        //tresorRsave=tresor1;
        i=2;
        while(lignePerso[i]!='\0'){
          Tresor1[i-2]=lignePerso[i];
          i++;
        }Tresor1[i-2]='\0';
        tresor1=atoi(Tresor1);
        //printf("tresor1: %d\n", tresor1);
        tresorRsave=tresor1;

        fgets(lignePerso,T_MAX,fichier); // on passe à la deuxième ligne;
        i=2;
        while(lignePerso[i]!='\0'){
          Tresor2[i-2]=lignePerso[i];
          i++;
        }Tresor2[i-2]='\0';
        tresor2=atoi(Tresor2);
        //printf("tresor 2: %d\n",tresor2);
        tresorBsave=tresor2;
      } else {

        i=2;
        ProchainAJouer=1;
        while(lignePerso[i]!='\0'){
          Tresor1[i-2]=lignePerso[i];
          i++;
        }Tresor1[i-2]='\0';
        tresor1=atoi(Tresor1);
        //printf("tresor1: %d\n", tresor1);
        tresorBsave=tresor1;

        fgets(lignePerso,T_MAX,fichier); // on passe à la deuxième ligne;
        i=2;
        while(lignePerso[i]!='\0'){
          Tresor2[i-2]=lignePerso[i];
          i++;
        } Tresor2[i-2]='\0';
        tresor2=atoi(Tresor2);
        //printf("tresor 2 :%d\n",tresor2);
        tresorRsave=tresor2;
      }
      // fin de la récupération et du traitement des deux premières lignes

      Personnage* chateauRougeTemp=NULL;
      Personnage* chateauBleuTemp=NULL;

      while (fgets(lignePerso,T_MAX,fichier)!=NULL){
          // printf("%s",lignePerso); // verification de la lecture de l'ensemble des lignes du fichier sauvegarde; YES

          char strpx[2]={lignePerso[4],'\0'};
          char strpy[2]={lignePerso[6],'\0'};
          int px=atoi(strpx); // récupération des positions du personnage
          int py=atoi(strpy);

          if(lignePerso[0]=='R'){ //perso rouge
            char strdx[2]={lignePerso[8],'\0'};
            char strdy[2]={lignePerso[10],'\0'};
            switch(lignePerso[2]){
              case 'c': CreerChateau(JeuRougeVoisin,monde,Rouge,px,py);
                        if (JeuRougeVoisin->nbPerso==1){
                          chateauRougeTemp=JeuRougeVoisin->tete;
                        }else{
                          chateauRougeTemp=chateauRougeTemp->PersoSuivantVoisin;
                        }

                        switch(lignePerso[8]){
                          case 's': chateauRougeTemp->typeProd=seigneur;
                                    break;
                          case 'g': chateauRougeTemp->typeProd=guerrier;
                                    break;
                          case 'm': chateauRougeTemp->typeProd=manant;
                                    break;
                          case 'r': chateauRougeTemp->typeProd=Rien;
                                    break;
                        }
                        char strtempProd[2]={lignePerso[10],'\0'};
                        chateauRougeTemp->tempsProd=atoi(strtempProd);
                        break;

              case 's': if(lignePerso[8]=='-'){
                            CreerSeigneurChargement(chateauRougeTemp,monde,Rouge,px,py,-1,-1,tresorR);
                        }
                        else{ CreerSeigneurChargement(chateauRougeTemp,monde,Rouge,px,py,atoi(strdx),atoi(strdy),tresorR);
                        }
                        *tresorR=50;
                        break;
              case 'g': CreerGuerrierChargement(chateauRougeTemp,monde,Rouge,px,py,atoi(strdx),atoi(strdy),tresorR);
                        *tresorR=50;
                        break;
              case 'm': if(lignePerso[8]=='-'){
                              CreerManantChargement(chateauRougeTemp,monde,Rouge,px,py,-1,-1,tresorR);
                        } else {CreerManantChargement(chateauRougeTemp,monde,Rouge,px,py,atoi(strdx),atoi(strdy),tresorR);}
                        *tresorR=50;
                        break;
            }

          } else { // perso bleu;
            char strdx[2]={lignePerso[8],'\0'};
            char strdy[2]={lignePerso[10],'\0'};
            switch(lignePerso[2]){
              case 'c': CreerChateau(JeuBleuVoisin,monde,Bleu,px,py);
                        if (JeuBleuVoisin->nbPerso==1){
                          chateauBleuTemp=JeuBleuVoisin->tete;
                        }else{
                          chateauBleuTemp=chateauBleuTemp->PersoSuivantVoisin;
                        }

                        switch(lignePerso[8]){
                          case 's': chateauBleuTemp->typeProd=seigneur;
                                    break;
                          case 'g': chateauBleuTemp->typeProd=guerrier;
                                    break;
                          case 'm': chateauBleuTemp->typeProd=manant;
                                    break;
                          case 'r': chateauBleuTemp->typeProd=Rien;
                                    break;
                        }
                        char strtempProd[2]={lignePerso[10],'\0'};
                        chateauBleuTemp->tempsProd=atoi(strtempProd);
                        break;

              case 's': if(lignePerso[8]=='-'){
                            CreerSeigneurChargement(chateauBleuTemp,monde,Bleu,px,py,-1,-1,tresorB);// le seigneur est immobile
                        }
                        else{ CreerSeigneurChargement(chateauBleuTemp,monde,Bleu,px,py,atoi(strdx),atoi(strdy),tresorB);
                        }
                        *tresorB=50;
                        break;
              case 'g': CreerGuerrierChargement(chateauBleuTemp,monde,Bleu,px,py,atoi(strdx),atoi(strdy),tresorB);
                        *tresorB=50;
                        break;
              case 'm': if(lignePerso[8]=='-'){
                        CreerManantChargement(chateauBleuTemp,monde,Bleu,px,py,-1,-1,tresorB);}//le manant est immobile
                        else {CreerManantChargement(chateauBleuTemp,monde,Bleu,px,py,atoi(strdx),atoi(strdy),tresorB);}
                        *tresorB=50;
                        break;
            }
          }
      } // fin du while
      *tresorR=tresorRsave;
      *tresorB=tresorBsave;
    }
  fclose(fichier);
  return ProchainAJouer;
  }
  else{ return 2;// cas ou il n'y a pas de fichier en entrée}
  }
}

int DemandeSauvegarde(Monde* monde, ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin,int * tresorR, int* tresorB,int ProchainAJouer){
    printf("voulez-vous sauvegarder la partie ? \noui ou non ?: ");
    char str[4];
    char str1[4]="oui";
    scanf("%s",str);
    if(strcmp(str1,str)==0){
        sauvergardeJeu(monde,JeuRougeVoisin,JeuBleuVoisin,tresorR,tresorB,ProchainAJouer);
        return 0;
    }else{return 1;}
}
