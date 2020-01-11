#ifndef LISTE_H
#define LISTE_H

#include "cellule.h"

typedef struct {
  cellule_t *tete;
} liste_t;

void initialiser_liste(liste_t*);
void detruire_liste(liste_t*);
void inserer(liste_t*, cellule_t*);
void afficherListe(liste_t*);
cellule_t* rechercher(liste_t*, char*);
void supprimer(liste_t*, cellule_t*);

#endif
