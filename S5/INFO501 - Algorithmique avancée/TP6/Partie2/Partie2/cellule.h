#ifndef CELLULE_H
#define CELLULE_H

typedef struct cellule_type{
  char *mot;
  struct cellule_type *pred;
  struct cellule_type *succ;
} cellule_t;

void initialiser_cellule(cellule_t*, char*);

#endif
