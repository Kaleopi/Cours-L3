#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cellule.h"
#include "liste.h"

void initialiser_liste(liste_t *l){
	l->tete = 0;
}

void detruire_liste(liste_t *l){
  cellule_t *p;
  while (l->tete != NULL){
    p = l->tete;
    while (p->succ != NULL){
      p = p->succ;
    }
    supprimer(l, p);
  }
}


void inserer(liste_t *l, cellule_t *c){
  c->succ = l->tete;
  if (l->tete != NULL){
    l->tete->pred = c;
  }
  l->tete = c;
  c->pred = NULL;
}

void afficherListe(liste_t *l){
  cellule_t *p;

	p = (cellule_t*)malloc(sizeof(cellule_t));
	p->mot = (char*)malloc(sizeof(char) * 26);

  if (l->tete == NULL){
    printf("La liste est vide\n");
  }
  else {
    p = l->tete;
    while (p->succ != NULL){
      printf("%s 	", p->mot);
			p = p->succ;
		}
		printf("%s\n", p->mot);
  }
}

cellule_t* rechercher(liste_t *l, char *k){
  cellule_t *c;
	c = (cellule_t*)malloc(sizeof(cellule_t));
	c->mot = (char*)malloc(sizeof(char) * 26);
	c = l->tete;
  while (c != NULL && strcmp(c->mot,k) != 0){
    c = c->succ;
  }
	if (strcmp(c->mot,k) == 0){
		return c;
	}
  return NULL;
}

void supprimer(liste_t *l, cellule_t *c){
  if (c->pred != NULL)
    c->pred->succ = c->succ;
  else
    l->tete = c->succ;
  if (c->succ != NULL)
    c->succ->pred = c->pred;
}
