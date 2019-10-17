#include <stdio.h>
#include <stdlib.h>
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

void triInsertion(Arcs **t){
  int i=2;
  Arcs *cle;
  while (t!=NULL){
    cle = t[i];
    while(i>0 && t[i]->poids>cle->poids){
      t[i+1]=t[i];
      i=i-1;
      }
      t[i+1]=cle;
  }
}
