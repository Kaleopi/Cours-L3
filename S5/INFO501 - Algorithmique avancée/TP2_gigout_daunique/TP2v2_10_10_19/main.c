#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"
#include "file.h"
#include "sommet.h"


int main(int argc, char* argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  Sommet *s = malloc(sizeof(Sommet));
  initialiser_graphe(g,argv[1]);

  afficher_graphe(g);
  detruire_graphe(g);
  ParcoursLargeur(g,g->l_adj[0]);
  return 0;
}
