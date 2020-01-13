#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"
#include "arete.h"
#define MAX 100;

arete_t** generer_acpm_kruskal_tableau(graphe_t *g){
  // DECLARATIONS
  arete_t **a = NULL;
  int i, j, u, v, w, iCC;
  int *CC;
  arete_t **E;
  int cpt = 0;

  // INITIALISATIONS
  E = (arete_t**)malloc(sizeof(arete_t*) * g->n_sommets * g->n_sommets);
  for (i = 0 ; i < g->n_sommets * g->n_sommets ; i++){
    E[i] = (arete_t*)malloc(sizeof(arete_t));
  }
  a = (arete_t**)malloc(sizeof(arete_t*) * g->n_sommets * g->n_sommets);
  for (i = 0 ; i < g->n_sommets * g->n_sommets ; i++){
    a[i] = (arete_t*)malloc(sizeof(arete_t));
  }
  CC = (int*)malloc(sizeof(int) * g->n_sommets);

  // KRUSKAL
  //recuperer_aretes(g,a);
  //tri_insertion(a);
  printf("\n");
  for (i = 0 ; i < g->n_sommets ; i++){
    CC[i] = i;
  }
  printf("\n");
  for (i = 0 ; a[i]->poids > 0 ; i++){
    u = a[i]->x;
    v = a[i]->y;
    w = a[i]->poids;
    if (CC[u] != CC[v]){
      E[cpt]->x = u;
      E[cpt]->y = v;
      E[cpt]->poids = w;
      cpt++;
      iCC = CC[v];
      for (j = 0 ; j < g->n_sommets ; j++){
        if (CC[j] == iCC){
          CC[j] = CC[u];
        }
      }
    }
  }
  return E;
}
Arete** generer_acpm_kruskal_tableauv1(Arete ** t){
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
      //printf("%d\n",val );
    }
    printf("\n" );
  }
  return tab;
}
