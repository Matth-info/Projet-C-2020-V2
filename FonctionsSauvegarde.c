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

  Personnage* fin = chateau;
  while(fin->PersoSuivant != NULL){ //recherche de l'emplacement du dernier agent dans la liste du chateau afin d'y insérer le manant
    fin = fin->PersoSuivant;
  }
  manant->PersoPrecedent=fin;
  manant->PersoSuivant= NULL;// la tete ne change jamais = toujours un chateau en tete de sa liste.
  fin->PersoSuivant=manant;

// placement du manant dans la liste voisin de la case
  if (monde->plateau[px][py].perso==NULL){
    manant->PersoPrecedentVoisin=NULL;
    manant->PersoSuivantVoisin=NULL;
    monde->plateau[px][py].perso=manant;
  }else{ //  il y a déjà des agents sur la case
    Personnage* finVoisin = monde->plateau[px][py].perso;
    while (finVoisin->PersoSuivantVoisin != NULL){ //recherche de l'emplacement du dernier agent dans la liste du chateau afin d'y insérer le manant
          finVoisin = finVoisin->PersoSuivantVoisin;
      }
      manant->PersoPrecedentVoisin=finVoisin;
      manant->PersoSuivantVoisin=NULL;
      finVoisin->PersoSuivantVoisin=manant;
  }

  *tresor=*tresor-1;
  }
}

void CreerSeigneurChargement(Personnage* chateau, Monde* monde,  couleur_t couleur, int px, int py,int dx, int dy, int* tresor){ // un seigneur est rataché à un chateau forcément
  Personnage* seigneur=malloc(sizeof(Personnage));
  if ((seigneur==NULL) || (chateau->typePerso!=Chateau) || (*tresor-20 < 0 )){
      printf("creation du Seigneur impossible\n ");
  }
  else
  {
    seigneur->couleur=couleur;
    seigneur->typePerso=Seigneur;
    seigneur->px=px;
    seigneur->py=py;
    seigneur->dx=dx;
    seigneur->dy=dy;
    seigneur->typeProd=Rien;
    seigneur->tempsProd=-1;


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

    if (monde->plateau[px][py].perso==NULL){
        seigneur->PersoPrecedentVoisin=NULL;
        seigneur->PersoSuivantVoisin=NULL;
        monde->plateau[px][py].perso=seigneur;
    } else {
      // est généré comme le placement du guerrier dans la liste doublement chainée du chateau;
      // placer le seigneur entre des guerriers et des manants
      // on commence par trouver le dernier élément de la liste des voisin
        Personnage * Persotemp=monde->plateau[px][py].perso;
        while(Persotemp->PersoSuivantVoisin!=NULL){
          Persotemp=Persotemp->PersoSuivantVoisin;
        }
        Personnage * finVoisin = Persotemp;

        while ((Persotemp->typePerso==Manant) && (Persotemp->PersoPrecedentVoisin!=NULL)){
          Persotemp= Persotemp->PersoPrecedentVoisin;
        }

        if(Persotemp==finVoisin){ // cas où il n'y a pas de manant dans les voisins;
          if(Persotemp->typePerso==Manant){
            seigneur->PersoSuivantVoisin=Persotemp;
            seigneur->PersoPrecedentVoisin= NULL;
            Persotemp->PersoPrecedentVoisin=seigneur;
            monde->plateau[px][py].perso=seigneur;

          }else{
          seigneur->PersoPrecedentVoisin=finVoisin;
          finVoisin->PersoSuivantVoisin=seigneur;
          seigneur->PersoSuivantVoisin=NULL;
          }
        }
        else {
          seigneur->PersoPrecedentVoisin=Persotemp;
          seigneur->PersoSuivantVoisin = Persotemp->PersoSuivantVoisin;

          Persotemp->PersoSuivantVoisin->PersoPrecedentVoisin=seigneur;
          Persotemp->PersoSuivantVoisin = seigneur;
        }
      }

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

  if (monde->plateau[px][py].perso==NULL){
    guerrier->PersoSuivantVoisin=NULL;
    guerrier->PersoPrecedentVoisin=NULL;
      monde->plateau[px][py].perso=guerrier;
  }else{
      // le guerrier est placé en 1 ère ligne , soit la tete;
      monde->plateau[px][py].perso->PersoPrecedentVoisin=guerrier;
      guerrier->PersoSuivantVoisin=monde->plateau[px][py].perso;
      guerrier->PersoPrecedentVoisin=NULL;
      monde->plateau[px][py].perso=guerrier;
    }

  }
  *tresor=*tresor-5;
}

//objectif créer un fichier de sauvegarde .got qui respecte les critères de sauvegardes afin de pouvoir facilement le récupérer et rétablir le jeu.
void sauvergardeJeu(Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB, int ProchainAJouer){
  FILE* fichier =NULL;
  printf("entrer le nom du fichier avec l'extension .got :");
  char str[T_MAX]="";
  scanf("%s",str);
  fichier=fopen(str,"w");
  if (fichier==NULL){
    printf("erreur lors de la creation du fichier\n");
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
          fprintf(fichier,"%d %d ",persotemp->px,persotemp->py);
          if (persotemp->typePerso!=Chateau){
            fprintf(fichier,"%d %d ",persotemp->dx,persotemp->dy);
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
            fprintf(fichier,"%d %d ",persotemp->px,persotemp->py);
            if (persotemp->typePerso!=Chateau){
              fprintf(fichier,"%d %d ",persotemp->dx,persotemp->dy);
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
                fprintf(fichier,"%d ",persotemp->tempsProd);
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
  // si argc==2 alors on a la présence d'un fichier de sauvegarde .got;
  // la fonction récupère les trésors bleu et rouge (initialisé à 50 dans le main(), puis les modifie en fonction des 2 premières lignes du fichier Sauvegarde)
  // (Problème resolu) noter que la récupération du premier tresor en tête de fichier sauvegarde fonctionne bien mais pas celle du deuxieme trésor (ex ci dessous)
  // 10 pieces d'or dans le coffre Rouge
  //1965968678 pieces d'or dans le coffre Bleu
  int ProchainAJouer=3;
  if (argv[1]!=NULL){
    FILE* fichier=fopen(argv[1],"r");
    if (fichier==NULL){
      return 2;
    }else {

      if (strcmp(argv[1],"ScoreParties.got")!=0){ // on vérifie que le premier nom de fichier à l'emplacement de la sauvegarde n'est pas ScoreParties.got
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
            i=2;
            while(lignePerso[i]!='\0'){
              Tresor1[i-2]=lignePerso[i];
              i++;
            }Tresor1[i-2]='\0';
            tresor1=atoi(Tresor1);
            tresorRsave=tresor1;

            fgets(lignePerso,T_MAX,fichier); // on passe à la deuxième ligne;
            i=2;
            while(lignePerso[i]!='\0'){
              Tresor2[i-2]=lignePerso[i];
              i++;
            }Tresor2[i-2]='\0';
            tresor2=atoi(Tresor2);
            tresorBsave=tresor2;
          } else {

            i=2;
            ProchainAJouer=1;
            while(lignePerso[i]!='\0'){
              Tresor1[i-2]=lignePerso[i];
              i++;
            }Tresor1[i-2]='\0';
            tresor1=atoi(Tresor1);
            tresorBsave=tresor1;

            fgets(lignePerso,T_MAX,fichier); // on passe à la deuxième ligne;
            i=2;
            while(lignePerso[i]!='\0'){
              Tresor2[i-2]=lignePerso[i];
              i++;
            } Tresor2[i-2]='\0';
            tresor2=atoi(Tresor2);
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
        } else{printf("pas de fichier sauvegarde, nouvelle partie\n"); return 2;}
  }
  fclose(fichier);
  return ProchainAJouer;
  } else{ return 2; }// cas ou il n'y a pas de fichier en entrée;
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

void triInsertionDecroissant(CoupleNS *tab, int tailletab)
{
    int i,j;
    CoupleNS tmp;
    int n=tailletab;
    for (i=1; i < n; i++)
    {
      tmp =tab[i];
      j=i-1;
      while ((j>=0) && (tab[j].score < tmp.score))
      {
        tab[j+1] = tab[j];
        j--;
      }
      tab[j+1]=tmp;
    }
}

void InsertionNvScore(CoupleNS* tab, int tailletab, CoupleNS nvCoupleNS){
  tab[10].score=nvCoupleNS.score;
  strcpy(tab[10].nomVainqueur,nvCoupleNS.nomVainqueur);
  triInsertionDecroissant(tab,11);
}

void traitementFscore(int argc, char** argv, char *NvVainqueur,int nvscore){
  CoupleNS nvCoupleNS;
  strcpy(nvCoupleNS.nomVainqueur,NvVainqueur);
  nvCoupleNS.score=nvscore;
  CoupleNS* tab =malloc(11*sizeof(CoupleNS)); // tableau de 11 couples de valeurs que l'on initialise (nv,0)
  char nv[3]="nv";
  for (int i=0; i<11; i++){
    tab[i].score=0;
    strcpy(tab[i].nomVainqueur,nv);
  }
  int m=0; // indice du tableau de CoupleNS
  char str[T_MAX]="";
  char nomVainqueur[T_MAX]="";
  char scoreT[T_MAX]="";
  int score;

  char nomFichierScore[T_MAX]="";
  if (strcmp(argv[1],"ScoreParties.got")==0){
    strcpy(nomFichierScore,argv[1]);
  }
  if (strcmp(argv[2],"ScoreParties.got")==0){
    strcpy(nomFichierScore,argv[2]);
  }

  if (argv[2]!=NULL){
    FILE* fscore=NULL;
    fscore=fopen(nomFichierScore,"r+");
    if (fscore==NULL){
      printf("erreur lors de l'ouverture du fichier Score\n");
    }
    fseek(fscore,0,SEEK_SET); // revenir au début du fichier texte
    while(fgets(str,T_MAX,fscore)!=NULL){
        //str est une chaine contenant une ligne : nomVainqueur scoreVainqueur
        int i;
        int j;
        for(i=0; str[i]!=' ';i++){
          nomVainqueur[i]=str[i];
        }
        nomVainqueur[i]='\0'; // nomVainqueur est bien une chaine de caractère;
        j=++i;
        while(str[i] != '\0'){
          scoreT[i-j]=str[i];
          i++;
        } scoreT[i-j]='\0'; // score est bien une chaine de caractère
        score=atoi(scoreT); // récupération de la chaine scoreT pour en récupérer la valeur décimale;
        strcpy(tab[m].nomVainqueur,nomVainqueur);
        tab[m].score=score;
        printf("%s %d\n",tab[m].nomVainqueur, tab[m].score);
        m++;
    }
    // a ce niveau, on a recupere l'integralité des au plus 10 scores dans le tableau tab;
    // procedons a un tri sur les cles pour être sûr que le prochain score soit bien trié.

    triInsertionDecroissant(tab,11); // m est le nombre de score dans le fichier de score, m+1 après l'ajout de ce score si m<10;
    // a ce niveau, le tab de couple NS est trié par ordre décroissant

    InsertionNvScore(tab,11,nvCoupleNS);

    // reinscription dans le fichier score des scores actualisé
    //affichage fichier mis à jour
    fseek(fscore,0,SEEK_SET); // revenir au début du fichier texte
    for(int i=0; i<10;i++){
      printf("%s %d\n",tab[i].nomVainqueur,tab[i].score);
      fprintf(fscore,"%s %d\n",tab[i].nomVainqueur,tab[i].score);
    }
    fclose(fscore);
    free(tab);

  }else{
    printf("Pas de fichier score rentre\n");
  }
}



void Score(int argc, char** argv,Monde* monde,ListePerso* JeuRougeVoisin, ListePerso* JeuBleuVoisin, int* tresorR, int* tresorB){
  // compter les points de victoire
  int victorieux;
  int pointdevictoire = 0;
  ListePerso* Vainqueur=NULL;

  if (monde->CampRouge==NULL){
    printf("\nVictoire du joueur Bleu, Felicitation !\n");
    printf("%d pieces d'or\n",*tresorB);
    victorieux=1;
  }else{
    printf("\nVictoire du joueur Rouge, Felicitation !\n");
    printf("%d pieces d'or\n",*tresorR);
    victorieux=0;
  }

  if (victorieux==0){
    Vainqueur=JeuRougeVoisin;
    pointdevictoire = *tresorR;
  }else
  { Vainqueur=JeuBleuVoisin;
    pointdevictoire = *tresorB;
  }

  for(Personnage* Chateau=Vainqueur->tete; Chateau!=NULL; Chateau=Chateau->PersoSuivantVoisin){
      for(Personnage* persotemp=Chateau; persotemp!=NULL; persotemp=persotemp->PersoSuivant){
        switch(persotemp->typePerso){
            case 0: printf("un chateau rapporte 30 points\n");
                      pointdevictoire+=30;
                      break;
            case 1: printf("un seigneur rapporte 20 points\n");
                      pointdevictoire+=20;
                      break;
            case 2: printf("un guerrier rapporte 5 points\n");
                      pointdevictoire+=5;
                      break;
            case 3: printf("un manant rapporte 1 points\n");
                      pointdevictoire+=1;
                      break;
      }
    }
  }
  printf("nombre de point de victoire du gagnant : %d\n",pointdevictoire);
  char nomVainqueur[T_MAX]="";
  if ((strcmp(argv[2],"ScoreParties.got")==0) || (strcmp(argv[1],"ScoreParties.got")==0)) { // attention les scores doivent etre triés par ordres decroissant, manipulation d'une structure dictionnaire
    printf("recuperation d'un fichier ScoreParties.got\n");
    printf("rentrez le nom du Vainqueur: ");
    scanf("%s",nomVainqueur);
    printf("ajout de %s %d dans le fichier score\n",nomVainqueur,pointdevictoire);
    traitementFscore(argc,argv, nomVainqueur,pointdevictoire);

  }else{
     printf("creation d'un fichier ScoreParties.got\n");
     FILE* fnewscore=NULL;
     fnewscore=fopen("ScoreParties.got","w");
     if (fnewscore==NULL){
       printf("erreur lors de la creation du fichier score");
     }
     printf("rentrez le nom du Vainqueur: ");
     scanf("%s",nomVainqueur);
     fprintf(fnewscore,"%s %d",nomVainqueur,pointdevictoire);

     fclose(fnewscore);
 }
}
