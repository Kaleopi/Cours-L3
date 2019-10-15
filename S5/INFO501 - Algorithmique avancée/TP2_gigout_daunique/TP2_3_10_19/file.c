#include <stdio.h>
#include <stdlib.h>
#include "sommet.h"
#include "file.h"
#define TAILLE 20

// initialise  une  file  vide  de  capacité  maximale  fixe  en  allouant  la  mémoire nécessaire
void initialiser_file(File *f){
  f = malloc(sizeof(Sommet)*TAILLE);
}
//détruit une file en libérant ses ressources mémoires
void detruire__file(File *f){
  free(f);
}
 //retourne 0 si vide, 1 si non vide
int file_vide(File *f){
  if(f==NULL){
    return 0;
  }else{1;}
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
  if(file_pleine(f)){
    printf("File pleine, impossible d'ajouter\n");
  }
  if(file_vide(f)==1){
    while(f->sommet==NULL){
      f->sommet = f->sommet->pere;
    }
    f->sommet = s;
  }else{
    f->sommet=s;
  }
}
//enlève un élément en tête de file s'il en existe un et retourne sa valeur.
int defiler(File *f)
{
  int nb;
    if (file_vide(f));{exit(EXIT_FAILURE);}

    //On vérifie s'il y a quelque chose à défiler
    if (f->sommet != NULL)
    {
      Sommet *elementDefile = f->sommet;

      nb = elementDefile->id;
      f->sommet = elementDefile->pere;
      free(elementDefile);
    }

    return nb;
}
//parcours en largeur
void ParcoursLargeur(Graphe* g,Sommet* s ){
    File *f;
    initialiser_file(f);
    enfiler(f,s);
    for(int i=0;i<g->nbSommet;i++){
      s->c=0
      s->pere=NULL;
    }
    s.c=1;
    s.pere=NULL;
    s.d=0;
    while(file_vide!=0){
      sommet *u=defiler(f);
      for(int i=0;i<g->nbSommet;i++){
          if(s->c=0){
            s->c=1;
            s->pere=u;
            s->distance=u->distance+1;
            enfiler(f,s);
          }
          s->c=2;
      }
      }
    }

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
      afficher_chemin(g,s,v->pere);
      afficher_sommet(v);
    }
  }
}

//parcours en profondeur récursif
void parcours_profondeur_recursif(Graphe *g){
  File *f =
  for(int i=0 ; i<g->nbSommet ; i++){

  }
}
