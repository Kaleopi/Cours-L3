#include "pile.h"
#include <stdlib.h>
#include <stdio.h>

void initialiser_pile(pile* p ,int taille ){
	p->taillemax=taille;
	p->tableau=malloc(sizeof(int)*(p->taillemax));
	p->sommet=-1;
}

int pile_Vide(pile* p){
	int test;
	if (p->sommet==-1)
	{
		test= 0;
	}
	else{
		test =1;
	}
	return test;
} 
int pile_pleine(pile* p){
	if (p->sommet==p->taillemax)
	{
		return 1;
	}
	else{
		return 0;
	}
}

void empiler(pile* p, sommet* x){
	if (pile_pleine(p) ==1)
	{
		printf("\nPile pleine\n");
	}
	else{
		p->sommet+=1;
		p->tableau[p->sommet]=*x;
	}
}

sommet* depiler(pile *p ){
	if (pile_Vide(p)==0)
	{
		printf("Pile vide\n");
	}
	else{
		p->sommet-=1;
	}

	return (&p->tableau[p->sommet+1]);
}

void afficherPile(pile* p){
	if(pile_Vide(p)==1){	
		for (int i = 0; i <= p->sommet; ++i)
		{
			printf("%d ",(&p->tableau[i])->id_sommet);
		}
		printf("\n");
	}
	else{
		printf("Impossible\n");
	}
}

int sommet_t(pile* p){
	return p->sommet;
}

void parcours_profondeur_iteratif(graphe* g){
	sommet* v= malloc(sizeof(sommet));
	cellule* c =malloc(sizeof(cellule));
	for (int i = 0; i < g->nb_sommet; i++)
	{
		init_sommet((&g->l_sommet[i]),i);
	}
	
	pile* p =malloc(sizeof(pile));
	initialiser_pile(p, g->nb_sommet);

	for (int i = 0; i < g->nb_sommet; i++)
	{
		if ((&g->l_sommet[i])->couleur==0)
		{
			(&g->l_sommet[i])->couleur=1;
			empiler(p,&g->l_sommet[i]);
			while (pile_Vide(p)==1)
			{
				
				v=depiler(p);
				c=(&g->l_adj[v->id_sommet])->tete;
				while (c!=NULL)
				{
					if ((&g->l_sommet[c->cle])->couleur==0)
					{
						(&g->l_sommet[c->cle])->couleur=1;
						(&g->l_sommet[c->cle])->pere=v;
						empiler(p,(&g->l_sommet[c->cle]));
					}
					v->couleur=2;
					c=c->succ;
				}
				
			}

			
		}
		
	}
	
}

void afficher_parcours(graphe* g){
	for (int i = 0; i < g->nb_sommet; i++)
    {
        if ((&g->l_sommet[i])->pere==NULL)
        {
            printf("Sommet : %d, pere :-1 \n",(&g->l_sommet[i])->id_sommet);
        }
        else{ 
            printf("Sommet : %d,  pere :%d \n",(&g->l_sommet[i])->id_sommet,(&g->l_sommet[i])->pere->id_sommet);
        }
    }
}