#include <stdio.h>
#include "pile.h"
int main(int argc, char *argv[])
{
    //Test de la pile
    /*pile* p =malloc(sizeof(pile));
    sommet* s = malloc(sizeof(sommet));
    init_sommet(s,5);
    initialiser_pile(p,5);
    if(pile_Vide(p)==0){
        printf("Pile vide");
    }
    else{
        printf("Pile vide");
    }
    empiler(p,s);
    afficherPile(p);
    */

    graphe* g =malloc(sizeof(graphe));
    pile* p =malloc(sizeof(pile));

    initialiser_graphe(g,argv[1]);
    initialiser_pile(p,g->nb_sommet);
    parcours_profondeur_iteratif(g);
    printf("\n");
    afficher_parcours(g);
    return 0;
}
