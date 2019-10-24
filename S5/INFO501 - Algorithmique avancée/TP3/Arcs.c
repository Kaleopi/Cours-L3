#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "Arcs.h"

void initArcs(Arcs *a,Cellule *x,Cellule *y,int poids){
  a->poids=poids;
  a->x=x;
  a->y=y;
}
void afficher_arcs(Arcs *a){

  printf("X : %d /",a->x->id);
  printf("Y : %d /",a->y->id);
  printf("poids :%d \n",a->poids);
}
 void triInsertion(Arcs *tab){
   printf("[1]" );
   int j=1;
   int i=j-1;
   Arcs *cle=malloc(sizeof(Arcs));
   while (j<23){
     *cle = tab[j];
    // afficher_arcs(cle);
     i=j-1;
     j++;
     while((i>-1) && (tab[i].poids>cle->poids)){
       printf("[3]" );
      tab[i+1]=tab[i];
        i=i-1;
       }
     tab[i+1]=*cle;
   }
 }
//TRI-INSERTION(t)pour j= 2 à t.longueurclé= t[j]i= j–1tant que i> 0 et t[i] > clét[i+1] = t[i]i= i–1t[i+1] = clé
