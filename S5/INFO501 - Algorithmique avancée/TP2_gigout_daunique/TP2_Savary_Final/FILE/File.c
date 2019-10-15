#include "File.h"
#include "graphe_File.h"
#include "Cellule_File.h"
#include <stdlib.h>
#include <stdio.h>
int date =0;
void initialiser_file(file_t* f , int taille)
{
    f->longueur=taille;
    f->tab=malloc(sizeof(sommet)*taille);
    f->tete =0;
    f->queue=0;
}

void detruire_file(file_t* f){
    free(f);
    f=NULL;
}
int file_vide(file_t* f){
    int bool;
    if (f->queue==f->tete)
    {
        bool=1;
    }
    else
    {
        bool=0;
    }
    return bool;
}
int file_pleine(file_t* f){
    int bool;
    if (f->queue==f->tete-1 || (f->queue==f->longueur-1 && f->tete==0))
    {
        bool=1;
    }
    else
    {
        bool=0;
    }
    return bool;
}
void enfiler(file_t* f ,sommet* s){
    if (file_pleine(f)==0)
    {
        f->tab[f->queue]=*s;
        if (f->queue==f->longueur-1)
        {
            f->queue=0;
        }
        else
        {
            f->queue+=1;
        }
    }
    else{
        printf("\nimpossible la file est pleine\n");
    }
}
sommet* defiler(file_t* f){
    if(file_vide(f)==0){
        sommet* temp =malloc(sizeof(sommet));
        *temp= f->tab[f->tete];
        if (f->tete==f->longueur-1)
        {
            f->tete=0;
        }
        else
        {
            f->tete=f->tete+1;
        }

        return temp;
    }
    else
    {
        return NULL;
    }
    
}

void afficher_file(file_t*f){
    int i= f->tete;

    while (i!=f->queue)
   {
      printf("%d ",(&f->tab[i])->id_sommet);
      i++;
      if (i==f->longueur)
      {
          i=0;
      }
   }
       
}


void parcour_largeur(graphe* g , sommet *s){   
    file_t* f = malloc(sizeof(file_t));
    sommet* U= malloc(sizeof(sommet));
    int somorig = s->id_sommet;

    for (int i = 0; i < g->nb_sommet; i++)
    {   
        init_sommet(&g->l_sommet[i],i);
    }

    (&g->l_sommet[somorig])->couleur=1;
    (&g->l_sommet[somorig])->pere=NULL;
    (&g->l_sommet[somorig])->d=0;
    initialiser_file(f,g->nb_sommet);
    enfiler(f,s);

    while (file_vide(f)!=1)
    {
        U=defiler(f); 
        int id_u =U->id_sommet;
        cellule* ok =malloc(sizeof(cellule));
        ok = (&g->l_adj[id_u])->tete;
        while(ok!=NULL){ 
            int id_cle = ok->cle;
            if ((&g->l_sommet[id_cle])->couleur == 0)
            {
                (&g->l_sommet[id_cle])->couleur =1;
                (&g->l_sommet[id_cle])->pere=U;
                (&g->l_sommet[id_cle])->d=(&g->l_sommet[id_u])->d+1;
                enfiler(f,(&g->l_sommet[id_cle]));
            }    
       
       //printf("\nLa couleur du sommet %d est %d et la distance %d\n",id_cle, (&g->l_sommet[id_cle])->couleur, (&g->l_sommet[id_cle])->d);
        ok=ok->succ; 
        }
        
        (&g->l_sommet[id_u])->couleur=2;
        free(ok);

    }
    free(f);
    free(U);
}

void afficher_chemin(graphe* g, sommet* s ,sommet* s2){
    
    if (s->id_sommet==s2->id_sommet)
    {
        printf("%d ", s->id_sommet);
    }
    else
    {
        if (s2->pere==NULL)
        {
            printf("Stop");
        }   
        else {
        
        afficher_chemin(g,s,s2->pere);
        printf("%d ", s2->id_sommet);
        }
    }
    
    return;
    
}

void parcours_profondeur_recur(graphe* g){
    for (int i = 0; i < g->nb_sommet; i++)
    {
      (&g->l_sommet[i])->id_sommet=i;
      (&g->l_sommet[i])->couleur=0;
      (&g->l_sommet[i])->pere=NULL;
    }
    date=0;
    for (int i = 0; i < g->nb_sommet; i++)
    {   
        if ((&g->l_sommet[i])->couleur ==0)
        {
            visiter_pp(g,&g->l_sommet[i]);
            
        }
    }

}

int visiter_pp(graphe* g , sommet* s){
    date++;
    cellule* ok =malloc(sizeof(cellule));
    ok =(&g->l_adj[s->id_sommet])->tete;
    s->debut=date;
    s->couleur=1;
        while(ok!=NULL){ 
            if ((&g->l_sommet[ok->cle])->couleur==0)
            {
                (&g->l_sommet[ok->cle])->pere=s;
                visiter_pp(g,&g->l_sommet[ok->cle]);
            }
            ok=ok->succ;
        }
        
        date++;
        s->fin=date;
        s->couleur=2;
        free(ok);
        return 1;
}

void afficher_parcours_profondeur(graphe* g){
    for (int i = 0; i < g->nb_sommet; i++)
    {
        if ((&g->l_sommet[i])->pere==NULL)
        {
            printf("Sommet : %d, date debut :%d , date fin :%d , pere :-1 \n",(&g->l_sommet[i])->id_sommet,(&g->l_sommet[i])->debut,(&g->l_sommet[i])->fin);
        }
        else{ 
            printf("Sommet : %d, date debut :%d , date fin :%d , pere :%d \n",(&g->l_sommet[i])->id_sommet,(&g->l_sommet[i])->debut,(&g->l_sommet[i])->fin,(&g->l_sommet[i])->pere->id_sommet);
        }
    }

    
}

    
    
