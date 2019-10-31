#ifndef ARCS_H
#define ARCS_H
#include "cellule.h"

typedef struct Arete Arete;
struct Arete{
  int poids;
  int x;
  int y;
};
void initArete(Arete *a,int x,int y , int poids);
void afficher_Arete(Arete **a);
void triInsertion(Arete **t);
#endif
