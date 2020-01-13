#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"
#include "arete.h"
#define MAX 100;

Arete** generer_acpm_kruskal_tableau(Arete ** t){
  Arete **tab = malloc(sizeof(Arete)*23);
  int temp=1;
  tab[0]=t[0];
  for (int i=1;i<23;i++){
    for(int j=1;j<temp;j++){
      printf("[%i] [%i]",i,j);
      if(((t[i]->x!=tab[j]->x)&&(t[i]->y!=tab[j]->y))||(j<23)){
        tab[temp]=t[i];
        temp++;
        printf("%d ",tab[temp]->poids);
      }
    }
  }
  return tab;
}
