#include "Liste_Pile.h"
#include "Cellule_Pile.h"
#include <stdlib.h>
#include <stdio.h>

void initialiser_liste(liste* l){
	l->tete=NULL;
}

cellule* rechercher_liste(liste* l , int k){
	cellule* x= malloc(sizeof(cellule));
	x=l->tete;
	while(x!=NULL && x->cle!=k){
		x=x->succ;
	}
	return x;
}

void inserer_liste(liste* l, cellule* x){
	x->succ=l->tete;
	if (l->tete!=NULL)
	{
		l->tete->preced=x;
	}
	l->tete=x;
	x->preced=NULL;
	
}

void supprimer_liste(liste* l , cellule* x){
	if (x->preced!=NULL)
	{
		x->preced->succ=x->succ;
	}
	else{
		l->tete=x->succ;
	}
	if (x->succ!=NULL)
	{
		x->succ->preced=x->preced;
	}
	free(x);
	x=NULL;

}

void detruire_liste (liste *l){
	while(l->tete!=NULL){
		supprimer_liste(l,l->tete);
	}
	l=NULL;
}

void afficher(liste* l){
	cellule* x= malloc(sizeof(cellule));
	x=l->tete;
	while(x!=NULL){
		if (x->succ==NULL)
		{
			printf("%d",x->cle);
		}
		else{
			printf("%d->",x->cle);
			
		}	
		x=x->succ;
	}
	printf("\n");
}