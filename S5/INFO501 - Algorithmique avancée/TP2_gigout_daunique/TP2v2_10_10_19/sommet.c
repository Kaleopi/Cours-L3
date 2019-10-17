#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"

void initSommet(Sommet *s){
  s->id=0;
  s->c=BLANC;
  s->pere = NULL;
  s->distance = 999999;
  s->debut = -1;
  s->fin = -1;
}

void afficher_sommet(Sommet *s){
  printf("%d ",s->id);
}
