#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "liste.h"

int main(int argc, char *argv[]){
  FILE* file=NULL;
  char buffer[100]="";
  Liste l;
  initListe(&l);
  Cellule c;


  if(argc == 0){
    printf("Argument manquant...");
    exit(0);
  }
  file = fopen(argv[1],"r");
  if(file == NULL){
    printf("Impossible d'ouvrir le fichier %s\n",argv[1]);
    exit(0);
  }else{
    while(!feof(file)){
      fscanf(file,"%s",buffer);
      // printf("%s ",buffer);
      if(rechercherStr(&l,buffer)==1){
        // printf("%s ",buffer);
        initCellule(&c,buffer);
        insererListe(&l,&c);
        afficherListe(&l);
      }else{
        printf("Existe deja\n");
      }
    }
  }
  afficherListe(&l);
}
