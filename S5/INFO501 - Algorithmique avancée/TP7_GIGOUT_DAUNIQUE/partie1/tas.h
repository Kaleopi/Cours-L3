#ifndef TAS_H
#define TAS_H
#include "arete.h"

typedef struct Tas Tas;
struct Tas{
  Arete *parent;
  Arete *gauche;
  Arete *droite;

};
Tas* initialiser_tas(Arete **t, int size);
//entasser_max: entasse l’élément d’indice iafin de rétablir la propriété de tas ;
void entasser_max(Tas *tas,int i);
void detruire_tas(Tas *tas, int size);
void tri(Tas *tas, int n);
void afficher_tas(Tas *tas);
#endif
 
