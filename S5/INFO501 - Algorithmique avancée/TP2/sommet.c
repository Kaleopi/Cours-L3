#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"

void initSommet(Sommet *s){
  s->pere = malloc(sizeof(Sommet));
  s->distance = 0;
  s->c=BLANC;
  s->id=0;
}

void afficher_sommet(Sommet *s){
  printf("%d ",s->id);
}
