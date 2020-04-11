#include "includes.h"

void init_plateau(plateau_t* plateau){
  int hauteur, largeur;
  hauteur = plateau->hauteur;
  largeur = plateau->largeur;
  plateau->cases = malloc(sizeof(int)*hauteur*largeur);
  int i,j;
  for(i=0 ; i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
      plateau->cases[j*largeur+i] = 0;
    }
  }
  // plateau->cases[0*hauteur+1] = 1;
}

void afficher_plateau(plateau_t* plateau){
  int i,j;
  for(i=0 ; i<plateau->hauteur ; i++){
    for(j=0 ; j<plateau->largeur ; j++){
      printf("%d",plateau->cases[j*plateau->largeur+i]);
    }
    printf("\n");
  }

}
