#ifndef SHMMAP_H
#define SHMMAP_H
#include "defines.h"

typedef struct{
    unsigned char carte[LINE][COL];
}carte_t;

typedef struct{
    int x;
    int y;
}coords_t;

typedef struct{
    carte_t *carte;
    coords_t *coords;
}shmmap_t;

#endif /*SHMMAP_H*/
 