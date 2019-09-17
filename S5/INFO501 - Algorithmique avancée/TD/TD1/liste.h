#ifndef LISTE_H
#define LISTE_H

typedef struct Liste{
  Cellule *tete;
  Cellule *queue;
}Liste;

int initListe(Liste *l);
Cellule* rechercherListe(Liste *l, int k);
void insererListe(Liste *l, Cellule x);
void supprimerListe(Liste *l, Cellule **x);
#endif //LISTE_H
