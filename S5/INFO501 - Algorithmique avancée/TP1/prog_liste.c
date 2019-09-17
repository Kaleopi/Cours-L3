#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "cellule.h"
#include "liste.h"

int main(int argc, char *argv[]){
  Graphe *g = malloc(sizeof(Graphe));
  initialiser_graphe(g,argv[1]);
  printf("test");
  afficher_graphe(g);
  return 0;
}

//MAIN de test pour les listes et cellules
/*
int main(){
  Liste l;
  Liste l2;
  initListe(&l);
  initListe(&l2);
  Cellule *c = malloc(sizeof(Cellule));
  initCellule(c,5);
  insererListe(&l,c);
  Cellule *c2 = malloc(sizeof(Cellule));
  initCellule(c2,7);
  insererListe(&l,c2);
  afficherListe(&l);
  supprimerCellule(&l,c);
  afficherListe(&l);
  afficherListe(&l2);
  supprimerListe(&l2);
  afficherListe(&l2);

  return 0;
}*/
