#include "pile.h"
#include <stdlib.h>
#include <stdio.h>

void initialiser_pile(Pile* p ,int taille ){
	p->taillemax=taille;
	p->tableau=malloc(sizeof(int)*(p->taillemax));
	p->sommet=-1;
}

int pile_Vide(Pile* p){
	int test;
	if (p->sommet==-1){test = 0;}
	else{test = 1;}
	return test;
}
int pile_pleine(pile* p){
	if (p->sommet==p->taillemax){
		return 1;
	}
	else{return 0;}
}

void empiler(Pile* p, Sommet* x){
	if (pile_pleine(p) ==1)
	{
		printf("\nLa pile est pleine\n");
	}
	else{
		p->sommet+=1;
		p->tableau[p->sommet]=*x;
	}
}

Sommet* depiler(Pile *p){
	if (pile_Vide(p)==0){
		printf("La pile est vide\n");
	}
	else{p->sommet-=1;}

	return (&p->tableau[p->sommet+1]);
}

void afficherPile(Pile* p){
	if(pile_Vide(p)==1){
		for (int i=0 ; i <= p->sommet ; ++i){
			printf("%d ",(&p->tableau[i])->id);
		}
		printf("\n");
	}
	else{printf("Impossible d'afficher la pile...\n");
	}
}

int sommet_t(Pile* p){
	return p->sommet;
}

void parcours_profondeur_iteratif(Graphe* g){
	Sommet* v= malloc(sizeof(Sommet));
	Cellule* c =malloc(sizeof(Cellule));
	for (int i=0 ; i < g->nbSommet ; i++){
		init_sommet((&g->l_sommet[i]),i);
	}

	Pile* p =malloc(sizeof(Pile));
	initialiser_pile(p, g->nbSommet);

	for (int i = 0; i < g->nb_sommet; i++){
		if((&g->l_sommet[i])->couleur==BLANC){
			(&g->l_sommet[i])->couleur=GRIS;
			empiler(p,&g->l_sommet[i]);
			while(pile_Vide(p)==1){
				v=depiler(p);
				c=(&g->l_adj[v->id])->tete;
				while (c!=NULL){
					if((&g->l_sommet[c->id])->couleur==BLANC){
						(&g->l_sommet[c->id])->couleur=GRIS;
						(&g->l_sommet[c->id])->pere=v;
						empiler(p,(&g->l_sommet[c->id]));
					}
					v->couleur=NOIR;
					c=c->succ;
				}
			}
		}
	}
}

void afficher_parcours(graphe* g){
	for (int i=0 ; i < g->nbSommet ; i++){
        if ((&g->l_sommet[i])->pere==NULL){
            printf("Sommet : %d, pere :-1 \n",(&g->l_sommet[i])->id);
        }
        else{
            printf("Sommet : %d,  pere :%d \n",(&g->l_sommet[i])->id,(&g->l_sommet[i])->pere->id);
        }
    }
}
