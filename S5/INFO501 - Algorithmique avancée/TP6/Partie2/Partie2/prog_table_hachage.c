#include "table_hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

int main(){
  int i, m=MAX;
  table_hachage *tabH = NULL;
  cellule_t *c, *c1;
  c = (cellule_t*)malloc(sizeof(cellule_t));
  c1 = (cellule_t*)malloc(sizeof(cellule_t));
  c->pred = NULL;
  c->succ = NULL;
  initialiser_cellule(c, "Abc");

  tabH = (table_hachage*)malloc(sizeof(table_hachage));


  initialiser_table_hachage(tabH,m);

  printf("Convertir : %llu\n",convertir_ch_entier("Abc"));

  printf("Hachage : %d\n", hachage(tabH,convertir_ch_entier("Abc")));

  inserer_hachage(tabH, c);

  c1 = rechercher_hachage(tabH, "Abc");
  printf("%s", c1->mot);

  afficher_table_hachage(tabH);
  detruire_table_hachage(tabH);

  return 0;
}
