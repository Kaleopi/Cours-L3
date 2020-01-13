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

void triInsertion(Arete **t,int size){
  Arete *cle=malloc(sizeof(Arete));
  int j;
  printf("Apres tri:\n");
  for (int i=0;i<size;i++){
    cle=t[i];
    //printf("poids clef %d\n", cle->poids);
    j=i-1;
    while(j>-1 && t[j]->poids>cle->poids){
      t[j+1]=t[j];
      j=j-1;
      }
      t[j+1]=cle;
      //printf("yolo\n");
  }
}
