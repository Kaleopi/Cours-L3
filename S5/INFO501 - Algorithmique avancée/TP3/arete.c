#include <stdio.h>
#include <stdlib.h>
#include "arete.h"

void initArete(Arete *a,int x,int y,int poids){
  a->poids=poids;
  a->x=x;
  a->y=y;
}
void afficher_Arete(Arete **a){
for (int i=0;i<23;i++){
  printf("X : %d /",a[i]->x);
  printf("Y : %d /",a[i]->y);
  printf("poids :%d \n",a[i]->poids);
}
}

void triInsertion(Arete **t){
  Arete *cle;
  for (int i=2;i<23;i++){
    cle->poids = t[i]->poids;
    cle->x=t[i]->x;
    cle->y=t[i]->y;
    printf("clef d'origine %d\n", cle->poids);
    while(i>-1 && t[i]->poids>cle->poids){
      printf("yolo\n");
      t[i+1]=t[i];
      i=i-1;
      }
      t[i+1]=cle;
      //printf("yolo\n");
  }
}
