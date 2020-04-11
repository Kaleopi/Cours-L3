#include "structures.h"

int switch_cst(char* s) {
  int res=0;
  if(strcmp(s,"\"HAUT\"")==0) res = HAUT;
  else if(strcmp(s,"\"BAS\"")==0) res = BAS;
  else if(strcmp(s,"\"GAUCHE\"")==0) res = GAUCHE;
  else if(strcmp(s,"\"DROITE\"")==0) res = DROITE;
  return res;
}

case_t strToType(char *s){
  case_t res = 0;
  if(strcmp(s,"\"TROU\"")==0) res = TROU;
  else if(strcmp(s,"\"CAISSE\"")==0) res = CAISSE;
  else if(strcmp(s,"\"OBSTACLE\"")==0) res = OBSTACLE;
  else if(strcmp(s,"\"BILLE\"")==0) res = BILLE;
  return res;
}

void init_grille(grille_t* g) {
  int i, j;
  for(i=0; i<g->largeur; i++) {
    for(j=0; j<g->hauteur; j++) {
      g->cases[i][j] = VIDE;
    }
  }
}

void afficher_grille(grille_t g) {
  int i, j;
  for(i=0; i<g.largeur; i++) {
    for(j=0; j<g.hauteur; j++) {
      if(g.cases[i][j]==VIDE) printf(" . ");
      else printf(" %u ", g.cases[i][j]);
    }
    printf("\n");
  }
}

void alloue_grille(grille_t* g, int hauteur, int largeur){
  int i;
  g->cases = malloc(sizeof(case_t*)*hauteur);
  for(i=0; i<hauteur;i++){
    g->cases[i] = malloc(sizeof(case_t)*largeur);
  }
}

void detruire_grille(grille_t *grille, int hauteur){
  int i;
  for(i=0; i<hauteur; i++){
    free(grille->cases[i]);
    grille->cases[i] = NULL;
  }
  free(grille);
  grille->cases = NULL;
}


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

void copy_grille(grille_t* dest, grille_t src) {
  int i, j;
  alloue_grille(dest, src.hauteur, src.largeur);
  for(i=0; i<dest->largeur; i++) {
    for(j=0; j<dest->hauteur; j++) {
      dest->cases[i][j] = src.cases[i][j];
    }
  }
}
