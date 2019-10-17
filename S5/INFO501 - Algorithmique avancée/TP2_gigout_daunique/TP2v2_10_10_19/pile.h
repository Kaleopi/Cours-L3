#ifndef PILE_H
#define PILE_H
#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include "sommet.h"

typedef struct Pile Pile;
struct Pile{
	Sommet* tableau;
	int sommet;
	int taillemax;
};

void initialiser_pile(Pile* p ,int taille);
int pile_Vide(Pile* p);
int pile_pleine(Pile* p);
void empiler(Pile* p, Sommet* x);
sommet* depiler(Pile *p);
void afficherPile(Pile* p);
void parcours_profondeur_iteratif(graphe* g);
void parcours_profondeur_iteratif2(graphe* g);
void afficher_parcours(graphe* g);

#endif //PILE_H
