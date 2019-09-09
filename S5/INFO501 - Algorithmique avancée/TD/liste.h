#ifndef LISTE_H
#define LISTE_H

struct Liste{
  Cellule *tete;
  Cellule *queue;
}

Cellule* rechercherListe(Liste l, int k);
void insererListe(Liste l, Cellule x);
void supprimerListe(Liste l, Cellule x);
#endif //LISTE_H
