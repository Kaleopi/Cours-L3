#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"

#define MAX 100

void initialiser_graphe(Graphe *g, char* nomFichier){
  FILE* f=NULL;
  char chaine[MAX]="";
  int sommet, val, oriente, j;

  f=fopen(nomFichier,"r+");
  // if(f==NULL){
  //   printf("[ERREUR] Impossible d'ouvrir le fichier.");
  //   return;
  // }
  //else
  //récupération nb sommets
  fscanf(f,"%s",chaine); printf("%s ",chaine);
  fscanf(f,"%d",&sommet); printf("%d ",sommet);
  //récupération orienté
  fscanf(f,"%s",chaine); printf(" %s ",chaine);
  fscanf(f,"%d",&oriente); printf("%d ",oriente);
  //récupération value
  fscanf(f,"%s",chaine); printf(" %s ",chaine);
  fscanf(f,"%d",&val); printf("%d ",val);
  //récupération "DEBUT_DEF_ARETES"
  fscanf(f,"%s",chaine); printf(" %s ",chaine);

  g->l_adj = malloc(sizeof(Liste)*sommet); //allocation liste / nombre de sommet
  for(int i=0 ; i<sommet ; ++i){
    initListe(&g->l_adj[i]);
  }
}
