#include <stdio.h>
#include <stdlib.h>
#include "arete.h"

void initialiser_tas(Arete **t,int size){
  Tas *tas = malloc(sizeof (Tas)*size);
  int i=0;
  for (int j;j<size/2;j=j){
    tas->parent=t[j];
    tas->gauche=t[j+1];
    tas->droite=t[j+2];
    tas->tas[j]=t[i]->poids;
    }

}
void detruire_tas(Tas *tas,int Size){
  printf("\n\nDestruction du tas !\n");
  for(int i=size/2 ; i>=0 ; i--){
    free(tas[i]->gauche);
    free(tas[i]->droite);
  }

}

void entasser_max(Tas *tas[],int i){
  Arete *g=malloc(sizeof(Arete));
  Arete *d=malloc(sizeof(Arete));
  Arete *temp=malloc(sizeof(Arete));
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
}
void tri(int tab[], int n)
{
	if (n <= 1) return;

	for (int i = n/2; i>=0;i--)
	{
		entasser_max(tas,i);
	}

}
