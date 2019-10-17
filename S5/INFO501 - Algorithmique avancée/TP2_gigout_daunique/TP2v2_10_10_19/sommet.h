#ifndef SOMMET_H
#define SOMMET_H
#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "COULEUR.h"

typedef struct Sommet Sommet;
struct Sommet{
  COULEUR c;
  Sommet *pere;
  int id;
  int distance;
  int debut;
  int fin;
};

void initSommet(Sommet*);
void afficher_sommet(Sommet*);

#endif //SOMMET_H
