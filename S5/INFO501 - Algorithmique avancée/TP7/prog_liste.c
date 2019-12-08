#include <stdio.h>
#include <stdlib.h>
#include "prim.h"
#include "graphe.h"
#include "cellule.h"
#include "liste.h"
#include "arete.h"
#include "tas.h"
#include "kruskal.h"

int main(int argc, char *argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);
  afficher_graphe(g);
  printf("\nAretes:\n" );
  afficher_Arete(g->t);
  triInsertion(g->t,23);
  afficher_Arete(g->t);
  Arete **tab = malloc(sizeof(Arete)*23);
  tab=generer_acpm_kruskal_tableau(g->t);
  printf("kek\n" );
  afficher_Arete(tab);
  Tas *tas=malloc(sizeof(Tas));
  tas =initialiser_tas(g->t,23);
  // prim_tri(g);
  //afficher_tas(tas);
  detruire_graphe(g);
  afficher_graphe(g);

}
