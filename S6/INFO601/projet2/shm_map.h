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
    int shmid;
    char *titre;
    carte_t *carte;
    voiture_t *voitures;
    void *addr;
}shmmap_t;


void initialiser_carte(carte_t *);
int creer_segment(shmmap_t*, key_t, char*, size_t, int);
void charger_carte(char *, WINDOW*, WINDOW*, carte_t *, size_t);

#endif /*SHMMAP_H*/

 