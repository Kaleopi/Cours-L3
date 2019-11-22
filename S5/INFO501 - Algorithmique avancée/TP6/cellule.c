#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cellule.h"

//initialise la cellule passée en paramètre à NULL
void initCellule(Cellule *c, char chaine[26]){
  printf("1: %s",chaine);
  strcpy(c->chaine, chaine);
  printf("2: %s",c->chaine);
  c->succ = NULL;
  c->prec = NULL;
}
