#include <stdio.h>
#include <stdlib.h>
#include "arete.h"


void entasser_max(Tas tas[],Arete a,int i){
  Arete *g=malloc(sizeof(Arete));
  Arete *d=malloc(sizeof(Arete));
  Arete *temp=malloc(sizeof(Arete));
  int j=(a->poids)*2;
  g=tas[i]->gauche;
  d=tas[i]->droite;
  max=i;
  if ( Tas->gauche>g->gauche){
    max=g->poids;
  }
  if ( Tas->gauche>d->gauche){
    max=d->poids;
  }
  if (max!=i){
    temp=Tas[i];
    Tas[i]=Tas[max];
    Tas[max]=temp;
    entasser_max(Tas,max);
  }
