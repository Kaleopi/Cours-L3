#ifndef ARCS_H
#define ARCS_H
#include "cellule.h"

typedef struct Arcs Arcs;
struct Arcs{
  int poids;
  Cellule* x;
  Cellule* y;
};
void initArcs(Arcs *a,Cellule *x,Cellule *y , int poids);
void afficher_arcs(Arcs *a);
void triInsertion(Arcs **t);
#endif
