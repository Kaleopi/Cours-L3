#ifndef LISTE_H
#define LISTE_H
#include "cellule.h"

typedef struct Liste Liste;
struct Liste{
  Cellule *tete;
  Cellule *queue;
};

void initListe(Liste *l);
void supprimerListe(Liste *l);
void insererListe(Liste *l, Cellule *x);
void afficherListe(Liste *l);

int rechercherStr(Liste *l, char []);
void supprimerCellule(Liste *l, Cellule *c);
#endif //LISTE_H
