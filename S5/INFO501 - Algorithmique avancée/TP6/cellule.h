#ifndef CELLULE_H
#define CELLULE_H

typedef struct Cellule Cellule;
struct Cellule{
  char chaine[26];
  Cellule* succ;
  Cellule* prec;
};

void initCellule(Cellule *c, char[]);

#endif //CELLULE_H
