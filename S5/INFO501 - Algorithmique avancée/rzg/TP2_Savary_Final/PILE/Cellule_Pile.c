#include "Cellule_Pile.h"
#include <stdlib.h>

void initcellule(cellule* x, int val){
	x->preced=NULL;
	x->cle=val;
	x->succ=NULL;
}