#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"

int main(int argc, char *argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);
  afficher_graphe(g);
  printf("\nAretes:\n" );
  afficher_Arete(g->t);
  printf("hello" );
  triInsertion(g->t);
  printf("done");
  afficher_Arete(g->t);
  printf("world" );

  detruire_graphe(g);
  afficher_graphe(g);
  return 0;
}
