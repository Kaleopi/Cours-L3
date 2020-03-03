#include <stdlib.h>
#include <stdio.h>
#include "include.h"

typedef struct Cellule_t{ 
	int id; 
    char data[TAILLE_MAX];
	struct Cellule_t* suiv; 
}Cellule_t; 

typedef struct File_t{
    struct Cellule_t* tete;
    struct Cellule_t* fin;
}File_t;

/* Fonctions Cellule_t */
Cellule_t* creerCellule(int);

/* Fonctions File_t */
File_t* creerFile();
void enfiler(File_t*, int);
void defiler(File_t*);
void supprFile(File_t*);