#include<stdio.h>
#include<stdlib.h>
#include "sommet_pile.h"

void init_sommet(sommet* s, int id_s){
    s->id_sommet=id_s;
    s->couleur=0; //0=BLANC , 1=GRIS , 2=NOIR
    s->d=99999999;
    s->pere=NULL;
    s->debut=-1;
    s->fin=-1;
}