#ifndef SOMMET_H
#define SOMMET_H
#include "cellule.h"
#include "COULEUR.h"

typedef struct Sommet Sommet;
struct Sommet{
  COULEUR c;
  int distance;
  Cellule *pere;
};

#endif //SOMMET_H
