#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

#define M_VIDE 0
#define M_BLOC 1
#define M_CAISSE 2
#define M_TROU 3
#define M_BILLE 4
#define M_ROBOT 5

#define M_HAUT 1
#define M_BAS 2
#define M_GAUCHE 3
#define M_DROITE 4

typedef struct{
  int hauteur;
  int largeur;
  int *cases;
}plateau_t;

typedef struct{
  int x;
  int y;
  int direction;
}robot_t;

void init_plateau(plateau_t*, liste_t*);
void afficher_plateau(plateau_t*);

#endif /*INCLUDES_H*/
