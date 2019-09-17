#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "liste.h"
#include "graphe.h"

int main(){
  Graphe g;
  initialiser_graphe(&g,"graphe1.txt");
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
