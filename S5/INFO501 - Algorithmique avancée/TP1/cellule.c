#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"

void initCellule(Cellule *c, int id){
  c->id = id;
  c->succ = NULL;
  c->prec = NULL;
}
