#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"
#include "file.h"
#include "sommet.h"

int main(int argc, char* argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);

  File *f ;
  initialiser_file(f);

  afficher_graphe(g);
  detruire_graphe(g);
  return 0;
}
