#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"
#include "arete.h"
#define MAX 100;

Arete** generer_acpm_kruskal_tableau(Arete ** t){
  Arete **tab = malloc(sizeof(Arete)*23);
  int tabint[24];
  int temp=2;
  int val=2;
  int bool=0;
  int j=0;
  tab[0]=t[0];
  tabint[0]=t[0]->x;
  tabint[1]=t[0]->y;
  for (int i=1;i<23;i++){
    //printf("%d/",t[i]->x );
  //
    //printf("%d\n",tabint[temp]);
    //printf("[%i] [%i]",i,j);
      bool=0;
      j=0;
      while(bool!=1&&j<24){


        printf("|%d|",j );
        if((t[i]->x!=tabint[j]&&t[i]->y!=tabint[j])&&(val<24)){
          printf("%d/",t[i]->x );
          printf("%d::",t[i]->y );
            tabint[val]=t[i]->x;
            val++;
            tabint[val]=t[i]->y;
            val++;
          printf("@%d/@",tabint[j] );
          //printf("passer\n" );
          tab[temp-1]=t[i];
          temp++;
          bool=1;
          //printf("%d ",tab[temp]->poids);
      }else{
        bool=0;
      }

      j++;
      printf("%d\n",val );
    }
    printf("\n" );
  }
  return tab;
}
