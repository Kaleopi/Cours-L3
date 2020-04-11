#include "includes.h"

/* liste */
void init_liste(liste_t* l) {
  l->tete = NULL;
}

void ajouter_cellule(liste_t* l, cell_t *c) {
  cell_t* tmp = malloc(sizeof(cell_t));
  if(l->tete==NULL) {
    l->tete = malloc(sizeof(cell_t));
    l->tete->position.x = c->position.x;
    l->tete->position.y = c->position.y;
    l->tete->type = c->type;
    l->tete->succ = NULL;
  }else{
    tmp->position.x = c->position.x;
    tmp->position.y = c->position.y;
    tmp->type = c->type;
    tmp->succ = l->tete;
    l->tete = tmp;
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

/* plateau */
void init_plateau(plateau_t* plateau, liste_t* liste){
  int hauteur, largeur,x,y,type;
  hauteur = plateau->hauteur;
  largeur = plateau->largeur;
  int i,j;
  for(i=0 ; i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
      plateau->cases[j*hauteur+i] = M_VIDE;
    }
  }
  while(liste->tete != NULL){
    x = liste->tete->position.x;
    y = liste->tete->position.y;
    type = liste->tete->type;
    if(plateau->cases[x*largeur+y]!=M_VIDE){
      fprintf(stderr,"Impossible, objet deja present sur la case x:%d y:%d\n",x,y);
    }
    plateau->cases[x*largeur+y]=type;
    liste->tete = liste->tete->succ;
  }
}

void afficher_plateau(plateau_t* plateau){
  int i,j,hauteur,largeur;
  hauteur = plateau->hauteur;
  largeur = plateau->largeur;
  for(i=0 ; i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
      printf("%d",plateau->cases[i*largeur+j]);
    }
    printf("\n");
  }
}
