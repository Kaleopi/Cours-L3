#include "File.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    printf("Les test en commentaire");
    // Zone de test de la file
   /* int nb_sommet;
    file_t* f =malloc(sizeof(file_t));
    sommet* s;
    sommet* s2=malloc(sizeof(sommet));
    sommet* s3=malloc(sizeof(sommet));
    
    nb_sommet=atoi(argv[1]);
    if(nb_sommet<=0){
        printf("taille trop petite");
        return 0;
    }

    initialiser_file(f,nb_sommet);
    s=malloc(sizeof(sommet)*nb_sommet);

    for (int i = 0; i < nb_sommet-1; i++)
    {
        init_sommet(&s[i],i);
        enfiler(f,&s[i]);
    }
    printf("on va afficher\n");
    afficher_file(f);
    init_sommet(s2,25);
    enfiler(f,s2);
    s3=defiler(f);
    enfiler(f,s2);
    printf("une suite de defilement et d'enfilement");
    for (int i = 0; i < 5; i++)
    {
        printf("Indice de tete : %d\nIndice de queue : %d\n",f->tete,f->queue);
        afficher_file(f);
        printf("\n");
        s3=defiler(f);
        enfiler(f,s3);
        printf("\n");
    }
      
        
    afficher_file(f);
    free(f);

    free(s);
    free(s2);
    free(s3);

   */
   /* parcour en largeurgraphe* 
   g=malloc(sizeof(graphe));
   initialiser_graphe(g,argv[1]);
   afficher_graphe(g);
   sommet* s= malloc(sizeof(sommet));
   init_sommet(s,0);
   printf("on va dans le parcour\n");
   printf("\nOn affiche le parcour\n");
   parcour_largeur(g,s);
   
   for (int i = 0; i < g->nb_sommet; i++)
   {
       afficher_chemin(g,&g->l_sommet[0],&g->l_sommet[i]);
       printf("\n");
   }
   free(g);
   free(s);
   
    */

   //Parcour profondeur recursif

    /*graphe* g =malloc(sizeof(graphe));
    initialiser_graphe(g,argv[1]);
    afficher_graphe(g);
    parcours_profondeur_recur(g);
    afficher_parcours_profondeur(g);
    free(g);*/
    return 0;
}
