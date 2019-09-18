#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

//initialise une liste vide
void initListe(Liste *l){
  l->tete = NULL;
}
//libère si nécessaire les ressources mémoire d'une liste
void supprimerListe(Liste *l){
  printf("Liste supprimee !\n");
  l->tete = NULL;
  free(l);
}
//Prend un paramètre un pointeur sur une cellule et insère cette cellule au début d'une liste
void insererListe(Liste *l, Cellule *x){
  x->succ = l->tete;
  if(l->tete != NULL){
    l->tete->prec = x;
  }
  l->tete = x;
  x->prec = NULL;
}
//affiche les informations relatives à la liste
void afficherListe(Liste *l){
  Cellule *c = malloc(sizeof(Cellule));
  if(l->tete!=NULL){
    c = l->tete;
    while(c!=NULL){
      printf(" %d" ,c->id);
      c = c->succ;
    }
  }
  else{
    printf("Erreur ! La liste que vous essayez d'afficher est vide\n");
  }
  printf("\n");
}
//recherche un sommet dans une liste et retourne soit un pointeur sur la cellule qui contient le sommet, soit NULL
Cellule* rechercherCellule(Liste *l, int v){
  Cellule *c = malloc(sizeof(Cellule));
  if(l->tete!=NULL){
    c = l->tete;
    while((c != NULL) && (c->id != v)){
      c = c->succ;
    }
  }
  return c;
}
//Supprime une cellule dans une liste si elle existe
void supprimerCellule(Liste *l, Cellule *c){
  if(l->tete != NULL){
    if(rechercherCellule(l,c->id)){
      if(c->prec != NULL){
        c->prec->succ = c->succ;
      }
      else{
        l->tete = c->succ;
      }
      if(c->succ != NULL){
        c->succ->prec = c->prec;
      }
    }
  }
}
