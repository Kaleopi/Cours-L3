#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <stdio.h>
#include <stdlib.h>

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

#define M_VIDE 0
#define M_BLOC 1
#define M_CAISSE 2
#define M_TROU 3
#define M_BILLE 4

#endif /*INCLUDES_H*/
