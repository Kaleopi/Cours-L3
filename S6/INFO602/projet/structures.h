#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIDE      0
#define CAISSE    1
#define OBSTACLE  2
#define BILLE     3
#define TROU      4
#define ROBOT     5

#define HAUT    1
#define BAS    -1
#define GAUCHE  2
#define DROITE -2

typedef unsigned char case_t;

typedef struct {
  case_t **cases;
  int hauteur;
  int largeur;
}grille_t;

typedef struct {
  int x;
  int y;
}pos_t;

typedef struct {
  pos_t position;
  int direction;
}robot_t;

typedef struct cellule {
  pos_t position;
  case_t type;
  struct cellule* succ;
}cell_t;

typedef struct {
  cell_t* tete;
}liste_t;

/*general*/
void alloue_grille(grille_t*, int, int);
/*replir la grille a vide*/
void init_grille(grille_t*);
/*ajouter bille, caisse etc a la grille*/
void ajouter_grille(grille_t*, pos_t, int type);
void afficher_grille(grille_t);
void detruire_grille(grille_t*, int);

int switch_cst(char*);

/*lites*/
void init_liste(liste_t*);
void ajouter_cellule(liste_t*, cell_t*);
void destroy_liste(liste_t*);
case_t strToType(char *s);
void copy_grille(grille_t* dest, grille_t src);

#endif
