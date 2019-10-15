#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste_Pile.h"
#define TAILLE 100
#include "graphe_Pile.h"
#include "sommet_pile.h"


void initialiser_graphe(graphe* g,char* nom_fichier){
	FILE* fichier= NULL;
	char chaine[TAILLE]="";
	int n_sommet;
	int value;
	int oriente;
    int j;
    char sommetY[TAILLE];

	fichier =fopen(nom_fichier ,"r");
	 if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier");
        return;
    }

    fscanf(fichier , "%s",chaine); 
    fscanf(fichier,"%d",&n_sommet); 
	fscanf(fichier , "%s",chaine);
    fscanf(fichier,"%d",&oriente);
    fscanf(fichier , "%s",chaine);
    fscanf(fichier,"%d",&value);
    fscanf(fichier, "%s",chaine);
    fscanf(fichier,"%s",chaine);

    g->l_sommet=malloc(sizeof(sommet)*n_sommet);

    g->l_adj=malloc(sizeof(liste)*n_sommet);

    for (int i = 0; i < n_sommet; ++i){
        initialiser_liste(&g->l_adj[i]);
    }   


   
    if(oriente==1){
        while(strcmp(chaine,"FIN_DEF_ARC")!=0){
            cellule* x= malloc(sizeof(cellule));
            fscanf(fichier,"%s",sommetY);
            initcellule(x,atoi(sommetY));
            j=atoi(chaine);
            inserer_liste(&g->l_adj[j],x);
            fscanf(fichier,"%s",chaine);
        }
    }
    else{
        while(strcmp(chaine,"FIN_DEF_ARETES")!=0){
            cellule* x= malloc(sizeof(cellule));
            cellule* y =malloc(sizeof(cellule));
            fscanf(fichier,"%s",sommetY);
            initcellule(x,atoi(sommetY));
            j=atoi(chaine);
            inserer_liste(&g->l_adj[j],x);
            initcellule(y,atoi(chaine));
            j=atoi(sommetY);
            inserer_liste(&g->l_adj[j],y);
            fscanf(fichier,"%s",chaine);
        }
    }

	fclose(fichier);

    g->nb_sommet=n_sommet;
    g->oriente=oriente;
    g->value=value;
}
void afficher_graphe(graphe* g){
     
    printf("Nombre de sommets : %d\n", g->nb_sommet); 
    if (g->oriente==0)
       {
           printf("Non oriente\n");
       }
    else{
        printf("Oriente\n");
    } 
    if (g->value==0)
       {
           printf("Non Value\n\n");
       }
    else{
        printf("Value\n\n");
    }     

    printf("Liste d'adjacence\n");
    for (int i = 0; i < g->nb_sommet; ++i)
    {   
        printf("%d--->",i );   
        afficher(&g->l_adj[i]);
    }
    printf("\n");
}

void detruire_graphe(graphe *g){
  for(int i=0 ; i<(g->nb_sommet) ; i++){
    detruire_liste(&g->l_adj[i]);
  }
  g->nb_sommet = 0;
  g->oriente = 0;
  g->value = 0;
}
