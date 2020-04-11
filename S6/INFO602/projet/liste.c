#include "liste.h"

void init_liste(liste_t* l) {
  l->tete = NULL;
}

void ajouter_cellule(liste_t* l, cell_t *c) {
  cell_t* tmp1 = malloc(sizeof(cell_t));
  if(l->tete==NULL) {
    l->tete = malloc(sizeof(cell_t));
    l->tete->position.x = c->position.x;
    l->tete->position.y = c->position.y;
    l->tete->type = c->type;
    l->tete->succ = NULL;
  }else{
    tmp1->position.x = c->position.x;
    tmp1->position.y = c->position.y;
    tmp1->type = c->type;
    tmp1->succ = l->tete;
    l->tete = tmp1;
  }
}

void destroy_liste(liste_t* l) {
  cell_t* tmp=malloc(sizeof(cell_t));
  if(l->tete!=NULL) {
    do {
      tmp=l->tete;
      l->tete=tmp->succ;
      free(tmp);
      tmp=NULL;
    }while(l->tete!=NULL);
    free(tmp);
    tmp=NULL;
    free(l->tete);
    l->tete=NULL;
  }
}
