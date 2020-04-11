#include "includes.h"
#include "liste.h"

void init_plateau(plateau_t* plateau, liste_t* liste){
  int hauteur, largeur;
  hauteur = plateau->hauteur;
  largeur = plateau->largeur;
  int i,j;
  for(i=0 ; i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
      plateau->cases[i*largeur+j] = M_VIDE;
    }
  }
}

void afficher_plateau(plateau_t* plateau){
  int i,j,hauteur,largeur;
  hauteur = plateau->hauteur;
  largeur = plateau->largeur;
  for(i=0 ; i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
      printf("%d",plateau->cases[i*largeur+j]);
    }
    printf("\n");
  }
}
