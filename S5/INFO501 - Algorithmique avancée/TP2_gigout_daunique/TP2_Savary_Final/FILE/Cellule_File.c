#include "Cellule_File.h"
#include <stdlib.h>

void initcellule(cellule* x, int val){
	x->preced=NULL;
	x->cle=val;
	x->succ=NULL;
}