#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "cellule.h"
#include "graphe.h"
#include "arete.h"
#define MAX 100

void initialiser_graphe(Graphe *g, char* nomFichier){
  FILE* f=NULL;
  char chaine[MAX]="";
  int sommet, value, oriente, j;
  char char_sommet[MAX];
  char char_poids[MAX];

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

  g->m_adj = malloc(sizeof(int*)*sommet); //allocation matrice carrée
  for(int i=0 ; i<sommet ; i++){
    g->m_adj[i] = malloc(sizeof(int)*sommet);
  }
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
    int i=0;
    while(strcmp(chaine,"FIN_DEF_ARETES")!=0){
      //initialisation cellule et arcs
      Cellule *c = malloc(sizeof(Cellule));
      Cellule *c2 = malloc(sizeof(Cellule));
      Arete *a=malloc(sizeof(Arete));
      Arete **tab=malloc(sizeof(Arete)*MAX);
      //recupération des sommet
      fscanf(f,"%s",char_sommet);
      initCellule(c,atoi(char_sommet));
      j=atoi(chaine);
      insererListe(&g->l_adj[j],c);
      initCellule(c2,atoi(chaine));
      j=atoi(char_sommet);
      insererListe(&g->l_adj[j],c2);

      //création des Arcs
      fscanf(f,"%s",char_poids);
      //printf("%s\n",char_poids);
      j=atoi(char_poids);
      initArete(a,c2->id,c->id,j);
      tab[i]=a;

      afficher_Arete(tab[i]);
      i++;

      //printf("%d",i);
      fscanf(f,"%s",chaine);
      //printf("%s\n",chaine);


    }
    
    printf("\n");
  }
  g->nbSommet=sommet;
  g->oriente=oriente;
  g->value=value;
  fclose(f);

  //Remplissage de la matrice
  for(int i=0; i<sommet ; i++){
    for(int j=0 ; j<sommet ; j++){
      if(rechercherCellule(&g->l_adj[i],j)){
        g->m_adj[i][j] = 1;
      }
      else{
        g->m_adj[i][j] = 0;
      }
    }
  }


}

void afficher_graphe(Graphe *g){
  printf("Nombre de sommets : %d\n", g->nbSommet);

  if(g->oriente==0){printf("Non oriente\n");}
  else{printf("Oriente\n");}

  if(g->value==0){printf("Non value\n");}
  else{printf("Value\n");}

  for(int i=0 ; i<g->nbSommet ; i++){ //Listes d'adjacence
    printf("%d -->",i);
    afficherListe(&g->l_adj[i]);
  }
  printf("\nMatrice d'adjacences : \n");
  for(int i=0 ; i<g->nbSommet ; i++){     //Matrice d'adjacence
    for(int j=0 ; j<g->nbSommet ; j++){
      printf(" %d",g->m_adj[i][j]);
    }
    printf("\n");
  }
}

void detruire_graphe(Graphe *g){
  printf("\n\nDestruction du graphe !\n");
  for(int i=0 ; i<(g->nbSommet) ; i++){
    supprimerListe(&g->l_adj[i]);
    free(g->m_adj[i]);
  }
  free(g->m_adj);
  g->nbSommet = 0;
  g->oriente = 0;
  g->value = 0;
}
