#ifndef CELLULE_H
#define CELLULE_H

typedef struct Cellule Cellule;
struct Cellule{
  int id;
  Cellule* succ;
  Cellule* prec;
};

void initCellule(Cellule *c, int id);

#endif //CELLULE_H
