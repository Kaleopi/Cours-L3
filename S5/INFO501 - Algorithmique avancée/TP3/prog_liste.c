#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"
#include "arete.h"

int main(int argc, char *argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);
  afficher_graphe(g);
  printf("\nAretes:\n" );
  afficher_Arete(g->t);
  triInsertion(g->t);
  afficher_Arete(g->t);
  detruire_graphe(g);
  afficher_graphe(g);


}
