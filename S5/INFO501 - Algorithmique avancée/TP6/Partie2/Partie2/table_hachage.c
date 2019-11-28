#include <stdio.h>
#include <stdlib.h>
#include "table_hachage.h"
#include "liste.h"
#include <math.h>

void initialiser_table_hachage(table_hachage *tabH, int m){
  int i;
  tabH->m = m;

  tabH->t = (liste_t**)malloc(sizeof(liste_t*) * m);
  for (i = 0 ; i < m ; i++){
    tabH->t[i] = (liste_t*)malloc(sizeof(liste_t));
    initialiser_liste(tabH->t[i]);
  }
}

void detruire_table_hachage(table_hachage *tabH){
  int i;
  for (i = 0 ; i < tabH->m ; i++){
    detruire_liste(tabH->t);
  }
}

void afficher_table_hachage(table_hachage *tabH){
  int i;
  for (i = 0 ; i < tabH->m ; i++){
    afficherListe(tabH->t[i]);
  }
}

unsigned long long convertir_ch_entier(char *c){
  int i;
  int cpt = strlen(c);
  unsigned long long k = 0;
  for (i = 0 ; i < strlen(c) ; i++){
    cpt--;
    k += (int)c[i] * pow(128, cpt);
  }
  return k;
}

int hachage(table_hachage *tabH, unsigned long long k){
  return k%(tabH->m);
}

void inserer_hachage(table_hachage *tabH, cellule_t *cell){
  unsigned long long k;
  int position;

  k = convertir_ch_entier(cell->mot);
  position = hachage(tabH, k);

  inserer(tabH->t[position], cell);
}

cellule_t* rechercher_hachage(table_hachage *tabH, char *c){
  int i;
  cellule_t *cell;
  cell = (cellule_t*)malloc(sizeof(cellule_t));

  for (i = 0 ; i < tabH->m ; i++){
    if (rechercher(tabH->t[i], c) != NULL){
      cell = rechercher(tabH->t[i], c);
    }
  }
  return cell;
}
void supprimer_hachage(table_hachage *tabh ,cellule_t* c){
  free(c);
}