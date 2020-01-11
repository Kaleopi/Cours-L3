#include <stdio.h>
#include <stdlib.h>
#include "sommet.h"
#include "file.h"
#define TAILLE 20

// initialise  une  file  vide  de  capacité  maximale  fixe  en  allouant  la  mémoire nécessaire
void initialiser_file(File *f){
  f = malloc(sizeof(Sommet)*TAILLE);
  f->tete =-1;
  f->queue=-1;
}
//détruit une file en libérant ses ressources mémoires
void detruire__file(File *f){
  free(f);
}
 //retourne 0 si vide, 1 si non vide
int file_vide(File *f){
  if(f==NULL){
    return 0;
  }else{return 1;}
}
//retourne 0 si pleine, 1 sinon
int file_pleine(File *f){
  int cpt = 0;
  while(f!=NULL){
      f++;
      cpt++;
  }
  if(cpt==TAILLE){return 0;}
  else{return 1;}
}
//ajoute un élément en queue de file;
void enfiler(File *f, Sommet *s){
  Sommet *elementDefile = f->sommet;
  if(file_pleine(f)){
    printf("File pleine, impossible d'ajouter\n");
  }
  if(file_vide(f)==1){
    while(f->sommet==NULL){
      f->sommet->pere = elementDefile->pere;
    }
    f->sommet = s;
  }else{
    f->sommet=s;
  }
}
//enlève un élément en tête de file s'il en existe un et retourne sa valeur.
Sommet* defiler(File *f){
  int nb;
    if (file_vide(f));{exit(EXIT_FAILURE);}

    //On vérifie s'il y a quelque chose à défiler
    if (f->sommet != NULL)
    {
      Sommet *elementDefile = f->sommet;
      f->sommet->pere = elementDefile->pere;
      return elementDefile;
      free(elementDefile);
    }
}
//parcours en largeur
void ParcoursLargeur(Graphe* g,Sommet* s){
  printf("test");
    File *f;
    printf("test");
    initialiser_file(f);
    printf("test");
    enfiler(f,s);
    printf("test");
    for(int i=0;i<g->nbSommet;i++){
      s->c=BLANC;
      s->pere=NULL;
      s++;
    }
    s->c=GRIS;
    s->pere=NULL;
    s->id=0;
    while(file_vide!=0){
      Sommet *u=defiler(f);
      for(int i=0;i<g->nbSommet;i++){
        printf("%d",s->id);
          if(s->c=BLANC){
            s->c=GRIS;
            s->pere=u->pere;
            s->distance=u->distance+1;
            enfiler(f,s);
          }
          if(s->c=GRIS){
            s->c=NOIR;
            s->pere=u->pere;
            s->distance=u->distance+1;
          }

      }
    }
    printf("testfin");
  }


//afficher le chemin d'un sommet "s" à "v"
void afficher_chemin(Graphe* g, Sommet* s, Sommet* v){
  if(s==v){
    afficher_sommet(s);
  }
  else{
    if(v->pere == NULL){
      printf("Il n'existe aucun chemin de S à V");
    }
    else{
      afficher_chemin(g,s,v);
      afficher_sommet(v);
    }
  }
}

//parcours en profondeur récursif
void parcours_profondeur_recursif(Graphe *g){
  File *f = NULL;
  for(int i=0 ; i<g->nbSommet ; i++){

  }
}
