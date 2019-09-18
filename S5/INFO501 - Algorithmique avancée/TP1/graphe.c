#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "cellule.h"
#include "graphe.h"

#define MAX 100

void initialiser_graphe(Graphe *g, char* nomFichier){
  FILE* f=NULL;
  char chaine[MAX]="";
  int sommet, value, oriente, j;
  char char_sommet[MAX];

  f=fopen(nomFichier,"r+");
  if(f==NULL){
    printf("[ERREUR] Impossible d'ouvrir le fichier.");
    return;
  }
  //else
  //récupération nb sommets
  fscanf(f,"%s",chaine);
  fscanf(f,"%d",&sommet);
  //récupération orienté
  fscanf(f,"%s",chaine);
  fscanf(f,"%d",&oriente);
  //récupération value
  fscanf(f,"%s",chaine);
  fscanf(f,"%d",&value);
  //récupération "DEBUT_DEF_ARETES"
  fscanf(f,"%s",chaine);
  fscanf(f,"%s",chaine);

  g->l_adj = malloc(sizeof(Liste)*sommet); //allocation liste / nombre de sommet
  for(int i=0 ; i<sommet ; ++i){
    initListe(&g->l_adj[i]);
  }

  if(oriente!=0){
    while(strcmp(chaine,"FIN_DEF_ARETES")!=0){
      Cellule *c = malloc(sizeof(Cellule));
      fscanf(f,"%s",char_sommet);
      initCellule(c,atoi(char_sommet));
      j=atoi(chaine);
      insererListe(&g->l_adj[j],c);
      fscanf(f,"%s",chaine);
    }
  }
  else{
    while(strcmp(chaine,"FIN_DEF_ARETES")!=0){
      Cellule *c = malloc(sizeof(Cellule));
      Cellule *c2 = malloc(sizeof(Cellule));
      fscanf(f,"%s",char_sommet);
      initCellule(c,atoi(char_sommet));
      j=atoi(chaine);
      insererListe(&g->l_adj[j],c);
      initCellule(c2,atoi(chaine));
      j=atoi(char_sommet);
      insererListe(&g->l_adj[j],c2);
      fscanf(f,"%s",chaine);
    }
  }
  g->nbSommet=sommet;
  g->oriente=oriente;
  g->value=value;
  fclose(f);
  afficher_graphe(g);
}

void afficher_graphe(Graphe *g){
  printf("Nombre de sommets : %d\n", g->nbSommet);

  if(g->oriente==0){printf("Non oriente\n");}
  else{printf("Oriente\n");}

  if(g->value==0){printf("Non value\n");}
  else{printf("Value\n");}

  for(int i=0 ; i<g->nbSommet ; i++){
    printf("%d -->",i);
    afficherListe(&g->l_adj[i]);
  }

}
