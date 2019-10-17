#ifndef FILE_H
#define FILE_H
#include "sommet.h"
#include "graphe.h"


typedef struct File File;
struct File{
  Sommet *sommets;
  int tete;
  int queue;
  int longueur;
};

void initialiser_file(File *); //initialise une file vide de capacité maximale fixe
void detruire_file(File*); //détruit une file en libérant ses ressources mémoires
int file_vide(File*); //retourne 0 si vide, 1 si non vide
int file_pleine(File*); //retourne 0 si pleine, 1 sinon
void enfiler(File*, Sommet*); //ajoute un élément en queue de file;
Sommet* defiler(File*); //enlève un élément en tête de file s'il en existe un et retourne sa valeur.

void ParcoursLargeur(Graphe*, Sommet*); // parcours en largeur à partir d'un sommet du graphe
void afficher_chemin(Graphe*, Sommet*, Sommet*);

void parcours_profondeur_recur(Graphe* g);
int visiter_pp(Graphe* g , Sommet* s);
void afficher_parcours_profondeur(Graphe* p);
#endif //FILE_H
