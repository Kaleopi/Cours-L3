#ifndef CELLULE_H
#define CELLULE_H

typedef struct Cellule Cellule;
struct Cellule{
  char chaine[50];
  Cellule* succ;
  Cellule* prec;
};

void initCellule(Cellule *, char[]);

#endif //CELLULE_H
