#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
}pos_t;

typedef struct cellule {
  pos_t position;
  int type;
  struct cellule* succ;
}cell_t;

typedef struct {
  cell_t* tete;
}liste_t;

/*lites*/
void init_liste(liste_t*);
void ajouter_cellule(liste_t*, cell_t*);
void destroy_liste(liste_t*);
