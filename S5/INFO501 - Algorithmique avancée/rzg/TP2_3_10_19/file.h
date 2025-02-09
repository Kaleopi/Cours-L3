#ifndef FILE_H
#define FILE_H
#include "sommet.h"


typedef struct File File;
struct File{
  Sommet *sommet;
};

void initialiser_file(File *); //initialise une file vide de capacité maximale fixe
void detruire_file(File*); //détruit une file en libérant ses ressources mémoires
int file_vide(File*); //retourne 0 si vide, 1 si non vide
int file_pleine(File*); //retourne 0 si pleine, 1 sinon
void enfiler(File*, Sommet*); //ajoute un élément en queue de file;
int defiler(File*); //enlève un élément en tête de file s'il en existe un et retourne sa valeur.
#endif //FILE_H
