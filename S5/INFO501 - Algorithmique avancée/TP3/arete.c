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
  Arete *cle=malloc(sizeof(Arete));
  for (int i=2;i<23;i++){
    cle = t[i];
  
    while(i>-1 && t[i]->poids>cle->poids){
      printf("yolo\n");
      t[i+1]=t[i];
      i=i-1;
      }
      t[i+1]=cle;
      //printf("yolo\n");
  }
}
