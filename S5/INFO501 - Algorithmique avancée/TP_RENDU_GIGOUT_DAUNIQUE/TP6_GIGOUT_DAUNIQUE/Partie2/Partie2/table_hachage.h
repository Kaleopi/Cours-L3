#ifndef TABLE_HACHAGE_H
#define TABLE_HACHAGE_H

#include "liste.h"

typedef struct {
  int m;
  liste_t** t;
} table_hachage;

void initialiser_table_hachage(table_hachage *tabH, int m);
void detruire_table_hachage(table_hachage *tabH);
void afficher_table_hachage(table_hachage *tabH);
unsigned long long convertir_ch_entier(char *c);
int hachage(table_hachage *tabH, unsigned long long k);
void inserer_hachage(table_hachage *tabH, cellule_t *k);
cellule_t* rechercher_hachage(table_hachage *tabH, char *c);
void supprimer_hachage(table_hachage *tabh ,cellule_t* c);


#endif
