#include "table_hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128


int main(int argc, char *argv[]){
  int m=MAX;
  char chaine[MAX]="";
  table_hachage *tabH = NULL;
  cellule_t *c, *c1;
  c = (cellule_t*)malloc(sizeof(cellule_t));
  //c1 = (cellule_t*)malloc(sizeof(cellule_t));
  c->pred = NULL;
  c->succ = NULL;
  FILE* fichier=NULL;
  fichier =fopen(argv[1],"r+");
  tabH = (table_hachage*)malloc(sizeof(table_hachage));
  initialiser_table_hachage(tabH,m);
   printf("START");
  
  int ch = getc(fichier); 
  while (ch != EOF)  
  { 
    putchar(ch);  
  
    ch = getc(fichier); 
  //printf("fine");
  fscanf(fichier,"%s",chaine);//lecture 
  printf("%s",chaine);
  initialiser_cellule(c,chaine);//init la cellule contenant la chaine
  long long unsigned kek=convertir_ch_entier(c);//converti la chaine pour h(k);
  hachage(tabH,kek);
  inserer_hachage(tabH, c);//insert;
}
if (feof(fichier)) 
     printf("\n End of file reached."); 
  else 
     printf("\n Something went wrong."); 
  fclose(fichier); 

afficher_table_hachage(tabH);
detruire_table_hachage(tabH);



  //printf("Convertir : %llu\n",convertir_ch_entier("Abc"));

  //printf("Hachage : %d\n", hachage(tabH,convertir_ch_entier("Abc")));

  

  //c1 = rechercher_hachage(tabH, "Abc");
  //printf("%s", c1->mot);

 

  return 0;
}
