#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"

int main(int argc, char *argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);
  afficher_graphe(g);
  detruire_graphe(g);
  afficher_graphe(g);
  triInsertion(g->t);
  for(int i=0;i<23;i++){
    afficher_Arete(g->t[i]);
  }
  return 0;
}
