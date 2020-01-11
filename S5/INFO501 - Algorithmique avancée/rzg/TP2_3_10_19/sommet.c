#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"

void initSommet(Sommet *s){
  s->pere = malloc(sizeof(Cellule));
  s->distance = 0;
  s->c=0;
  s->id=0;
}

void afficher_sommet(Sommet *s){
  printf("%d ",s->id);
}
