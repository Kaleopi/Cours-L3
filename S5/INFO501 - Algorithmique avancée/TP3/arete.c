#include <stdio.h>
#include <stdlib.h>
#include "arete.h"

void initArete(Arete *a,int x,int y,int poids){
  a->poids=poids;
  a->x=x;
  a->y=y;
}
void afficher_Arete(Arete *a){

  printf("X : %d /",a->x);
  printf("Y : %d /",a->y);
  printf("poids :%d \n",a->poids);
}

void triInsertion(Arete **t){
  int i=2;
  Arete *cle;
  while (t!=NULL){
    cle = t[i];
    while(i>0 && t[i]->poids>cle->poids){
      t[i+1]=t[i];
      i=i-1;
      }
      t[i+1]=cle;
  }
}
