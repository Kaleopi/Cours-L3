#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "cellule.h"

int main(){
  Liste l;
  initListe(&l);
  Cellule *c = malloc(sizeof(Cellule));
  initCellule(c,5);
  insererListe(&l,c);
  Cellule *c2 = malloc(sizeof(Cellule));
  initCellule(c2,7);
  insererListe(&l,c2);
  afficherListe(&l);
  supprimerCellule(&l,c);
  afficherListe(&l);
  return 0;
}
