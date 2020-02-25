#ifndef SHMMAP_H
#define SHMMAP_H
#include "defines.h"

typedef struct{
    unsigned char carte[LINE][COL];
}carte_t;

typedef struct{
    int num_voiture;
    int x;
    int y;
}voiture_t;

typedef struct{
    unsigned char *L;
    unsigned char *H;
    carte_t *carte;
    voiture_t *voitures;
}shmmap_t;

/*
 * Initialise la carte passée en paramètre à '0'
 */
void initialiser_carte(carte_t *);

#endif /*SHMMAP_H*/

 