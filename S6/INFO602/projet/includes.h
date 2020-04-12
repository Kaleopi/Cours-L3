#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct {
  int x;
  int y;
}pos_t;

typedef struct cellule {
  pos_t position;
  int type;
  struct cellule* succ;
}cell_t;

typedef struct cellule_hachage{
  char str[50];
  struct cellule_hachage* succ;
}cell_hachage_t;

/*typedef struct{
  int type;
  union{
    liste_t l;
    liste_hachage_t lh;
  }liste;
}listes_t;*/

typedef struct {
  cell_t* tete;
}liste_t;

typedef struct {
  cell_hachage_t* tete;
}liste_hachage_t;

/* listes */
void init_liste(liste_t*);
void ajouter_cellule(liste_t*, cell_t*);
void destroy_liste(liste_t*);

/* plateau */
void init_plateau(plateau_t*, liste_t*);
void afficher_plateau(plateau_t*);

/* liste hachage */
void hach_init_liste(liste_hachage_t* l);
void hach_ajouter_cellule(liste_hachage_t* l, cell_hachage_t *c);
void hach_destroy_liste(liste_hachage_t* l);

#endif /*INCLUDES_H*/
