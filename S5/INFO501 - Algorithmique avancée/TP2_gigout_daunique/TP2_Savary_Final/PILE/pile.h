#include <stdlib.h>
#include <stdio.h>
#include "graphe_Pile.h"
#include "sommet_pile.h"
#ifndef PILE
#define PILE

typedef struct pile pile;
struct pile {
	sommet* tableau;
	int sommet;
	int taillemax;
};

void initialiser_pile(pile* p ,int taille);
int pile_Vide(pile* p);
int pile_pleine(pile* p);
void empiler(pile* p, sommet* x);
sommet* depiler(pile *p);
void afficherPile(pile* p);
void parcours_profondeur_iteratif(graphe* g);
void parcours_profondeur_iteratif2(graphe* g);
void afficher_parcours(graphe* g);

#endif