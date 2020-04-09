#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int hauteur;
  int largeur;
  int* plateau;
}plateau_t;

typedef struct{
  int x;
  int y;
  int direction;
}robot_t;
#endif /*INCLUDES_H*/
