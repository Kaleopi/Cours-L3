#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"

//initialise la cellule passée en paramètre à NULL
void initCellule(Cellule *c, int id){
  c->id = id;
  c->succ = NULL;
  c->prec = NULL;

}
