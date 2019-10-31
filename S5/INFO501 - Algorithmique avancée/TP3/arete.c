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
  Arete *cle=malloc(sizeof(Arete));
  Arete *tmp=malloc(sizeof(Arete));

  for (int i=0;i<22;i++){
    cle->poids = t[i]->poids;
    cle->x=t[i]->x;
    cle->y=t[i]->y;
    printf("poids clef %d\n", cle->poids);
    int j=i;
    while(j>-1 && t[j]->poids>=cle->poids){
      //printf("%d /",t[j]->poids);
      //printf("%d /",t[j+1]->poids);
      //printf("%d\n",j);
      tmp=t[j+1];
      t[j+1]=t[j];
      t[j]=tmp;
      j=j-1;
      }
      t[j+1]=cle;
      //printf("yolo\n");
  }
}
