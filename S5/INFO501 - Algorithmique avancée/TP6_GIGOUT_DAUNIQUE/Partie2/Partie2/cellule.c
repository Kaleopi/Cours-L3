#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"

void initialiser_cellule(cellule_t *c, char *mot){
  c->pred = NULL;
  c->succ = NULL;
  c->mot = mot;
}
