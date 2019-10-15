#ifndef GRAPHE
#define GRAPHE
#include "Liste_Pile.h"
#include "sommet_pile.h"
typedef struct graphe graphe;
struct graphe
{
	int nb_sommet;
	int oriente; //0=non oriente 1=oriente
	int value; //0=non value 1=value
	liste* l_adj;
	sommet* l_sommet;
};

void initialiser_graphe(graphe* g ,char* nom_fichier);
void afficher_graphe(graphe* g);
void detruire_graphe(graphe* g);

#endif