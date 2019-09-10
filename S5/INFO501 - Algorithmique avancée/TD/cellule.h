#ifndef CELLULE_H
#define CELLULE_H

typedef struct Cellule{
  int idSommet;
  Cellule *succ;
  Cellule *prec;
}Cellule;

int initCellule(Cellule *c, int id);

#endif //CELLULE_H
