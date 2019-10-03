#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "sommet.h"
#define TAILLE 20

// initialise  une  file  vide  de  capacité  maximale  fixe  en  allouant  la  mémoire nécessaire
File initialiser_file(){
  File f = malloc(sizeof(Sommet)*TAILLE);
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
  while(f[cpt]!=NULL){
      cpt++;
  }
  if(cpt==TAILLE){return 0;}
  else{return 1;}
}
//ajoute un élément en queue de file;
void enfiler(File *f, Sommet *s){
  if(file_pleine(f)){
    printf("File pleine, impossible d'ajouter\n");
    return(EXIT_FAILURE);
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
int defiler(File *file)
{
  int nombreDefile;
    if (file_vide(file));{exit(EXIT_FAILURE);}

    //On vérifie s'il y a quelque chose à défiler
    if (file->sommet != NULL)
    {
      Sommet *elementDefile = f->sommet;

      nombreDefile = elementDefile->id;
      f->sommet = elementDefile->pere;
      free(elementDefile);
    }

    return nombreDefile;
}
