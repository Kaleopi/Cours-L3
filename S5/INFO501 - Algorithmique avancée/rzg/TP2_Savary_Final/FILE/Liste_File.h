#ifndef LISTE
#define LISTE
#include "Cellule_File.h"
typedef struct liste liste;
struct liste
{
	cellule* tete;
};

void initialiser_liste(liste* l);

cellule* rechercher_liste(liste* l , int k);

void inserer_liste(liste* l, cellule* x);

void supprimer_liste(liste* l , cellule* x);

void detruire_liste (liste *l);

void afficher(liste* l);

#endif

