#include <stdio.h>
#include <stdlib.h>
#include "tas.h"
#include "arete.h"

Tas* initialiser_tas(Arete **t,int size){
  Tas *tas = malloc(sizeof (Tas)*size);
  //int i=0;
  for (int j=0 ; j<size/2 ; j++){
    tas->parent=t[j/2];
    tas->gauche=t[2*j];
    tas->droite=t[2*j+1];


    }
    return tas;

}
void detruire_tas(Tas *tas,int size){
  printf("\n\nDestruction du tas !\n");
  for(int i=size/2 ; i>=0 ; i--){
    free(tas[i].gauche);
    free(tas[i].droite);
  }
free(tas);
}

void entasser_max(Tas *tas,int i){
  Arete *g=malloc(sizeof(Arete));
  Arete *d=malloc(sizeof(Arete));
  Arete *temp=malloc(sizeof(Arete));
  int max = i;
  g=tas[i].gauche;
  d=tas[i].droite;
  if ( tas->gauche>g){
    max=g->poids;
  }
  if ( tas->droite>d){
    max=d->poids;
  }
  if (max!=i){
    temp=tas[i].parent;
    tas[i]=tas[max];
    tas[max].parent=temp;
    entasser_max(tas,max);
  }
}
void tri(Tas *tas, int n)
{
	if (n <= 1) return;

	for (int i = n/2; i>=0;i--)
	{
		entasser_max(tas,i);
	}

}

void afficher_tas(Tas * tas){
    for(int i=0;i<12;i++){
    printf("%d",tas[i].parent->poids);
    printf("%d",tas[i].gauche->poids);
    printf("%d",tas[i].droite->poids);
  }
    }
