#include "sommet.h"
#include "graphe_File.h"
#ifndef FILE_T
#define FILE_T

typedef struct file_t file_t;
struct file_t{
    int tete;
    sommet* tab;
    int queue;
    int longueur;
};

void initialiser_file(file_t* f , int taille);
void detruire_file(file_t* f);
int file_vide(file_t* f);
int file_pleine(file_t* f);
void enfiler(file_t* f ,sommet* s);
sommet* defiler(file_t* f);
void afficher_file(file_t*f);

void parcour_largeur(graphe* g , sommet *s);
void afficher_chemin(graphe*g ,sommet* s, sommet* s2);

void parcours_profondeur_recur(graphe* g);
int visiter_pp(graphe* g , sommet* s);
void afficher_parcours_profondeur(graphe* p);
#endif