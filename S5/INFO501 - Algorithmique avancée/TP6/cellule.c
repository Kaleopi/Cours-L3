#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cellule.h"

//initialise la cellule passée en paramètre à NULL
void initCellule(Cellule *c, char chaine[]){
  strcpy(c->chaine, chaine);
  c->succ = NULL;
  c->prec = NULL;
}
