#ifndef CELLULE
#define CELLULE
typedef struct cellule cellule;
struct cellule
{
	struct cellule* preced;
	int cle;
	struct cellule* succ;
};

void initcellule(cellule* x, int val);

#endif