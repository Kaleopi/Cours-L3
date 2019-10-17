#include <stdio.h>
#include <stdlib.h>
#include "sommet.h"
#include "file.h"
#define TAILLE 20

// initialise  une  file  vide  de  capacité  maximale  fixe  en  allouant  la  mémoire nécessaire
void initialiser_file(File *f){
  f->sommets = malloc(sizeof(Sommet)*TAILLE);
  f->longueur = TAILLE;
  f->tete = 0;
  t->queue = 0;
}
//détruit une file en libérant ses ressources mémoires
void detruire__file(File *f){
  free(f);
  f = NULL;
}
 //retourne 0 si vide, 1 si non vide
int file_vide(File *f){
  if(f->queue==f->tete){
    return 1;
  }else{return 0;}
}
//retourne 0 si pleine, 1 sinon
int file_pleine(File *f){
  if (f->queue==f->tete-1 || (f->queue==f->longueur-1 && f->tete==0)){
    return 1;
  }
  else{return 0;}
}
//ajoute un élément en queue de file;
void enfiler(File *f, Sommet *s){
  if (file_pleine(f)==0){
      f->sommets[f->queue]=*s;
      if (f->queue==f->longueur-1){
          f->queue=0;
      }
      else{f->queue+=1;}
  }
  else{
      printf("\nImpossible d'enfiler, la file est pleine.\n");
  }
}
//enlève un élément en tête de file s'il en existe un et retourne sa valeur.
Sommet* defiler(File *f){
  if(file_vide(f)==0){
      Sommet* temp =malloc(sizeof(Sommet));
      *temp= f->sommets[f->tete];
      if (f->tete==f->longueur-1){
          f->tete=0;
      }else{
          f->tete=f->tete+1;
      }
      return temp;
  }else{
      return NULL;
  }

//parcours en largeur
void ParcoursLargeur(Graphe* g,Sommet* s){
  File* f = malloc(sizeof(File));
  Sommet* u= malloc(sizeof(Sommet));
  int sid = s->id;

  for (int i = 0; i < g->nbSommet; i++){
      initSommet(&g->l_sommet[i],i);
  }

  (&g->l_sommet[sid])->c=GRIS;
  (&g->l_sommet[sid])->pere=NULL;
  (&g->l_sommet[sid])->d=0;
  initialiser_file(f,g->nbSommet);
  enfiler(f,s);

  while (file_vide(f)!=1)
  {
      u=defiler(f);
      int id_u =u->id;
      cellule* ok =malloc(sizeof(Cellule));
      ok = (&g->l_adj[id_u])->tete;
      while(ok!=NULL){
          int id_cle = ok->cle;
          if ((&g->l_sommet[id_cle])->couleur == BLANC){
              (&g->l_sommet[id_cle])->couleur = GRIS;
              (&g->l_sommet[id_cle])->pere=u;
              (&g->l_sommet[id_cle])->d=(&g->l_sommet[id_u])->d+1;
              enfiler(f,(&g->l_sommet[id_cle]));
          }
     printf("\nLa couleur du sommet %d est %d et la distance %d\n",id_cle, (&g->l_sommet[id_cle])->couleur, (&g->l_sommet[id_cle])->d);
      ok=ok->succ;
      }
      (&g->l_sommet[id_u])->couleur=NOIR;
      free(ok);
  }
  free(f);
  free(u);
  }


//afficher le chemin d'un sommet "s" à "v"
void afficher_chemin(Graphe* g, Sommet* s, Sommet* v){
  if(s==v){
    afficher_sommet(s);
  }
  else{
    if(v->pere == NULL){
      printf("Il n'existe aucun chemin de S à V");
    }
    else{
      afficher_chemin(g,s,v->pere);
      afficher_sommet(v);
    }
  }
}

void parcours_profondeur_recursif(Graphe* g){
    for (int i = 0; i < g->nbSommet; i++){
      (&g->l_sommet[i])->id=i;
      (&g->l_sommet[i])->c=BLANC;
      (&g->l_sommet[i])->pere=NULL;
    }
    int date=0;
    for (int i = 0; i < g->nbSommet; i++){
        if ((&g->l_sommet[i])->c==BLANC){
            visiter_pp(g,&g->l_sommet[i]);
        }
    }
}

int visiter_pp(Graphe* g , Sommet* s){
    date++;
    Cellule* ok =malloc(sizeof(Cellule));
    ok =(&g->l_adj[s->id])->tete;
    s->debut=date;
    s->c=GRIS;
        while(ok!=NULL){
            if ((&g->l_sommet[ok->id])->c==BLANC){
                (&g->l_sommet[ok->id])->pere=s;
                visiter_pp(g,&g->l_sommet[ok->id]);
            }
            ok=ok->succ;
        }

        date++;
        s->fin=date;
        s->c=NOIR;
        free(ok);
        return 1;
}

void afficher_parcours_profondeur(graphe* g){
    for (int i = 0; i < g->nbSommet; i++){
        if((&g->l_sommet[i])->pere==NULL){
            printf("Sommet : %d, date debut :%d , date fin :%d , pere :-1 \n",(&g->l_sommet[i])->id,(&g->l_sommet[i])->debut,(&g->l_sommet[i])->fin);
        }
        else{
            printf("Sommet : %d, date debut :%d , date fin :%d , pere :%d \n",(&g->l_sommet[i])->id,(&g->l_sommet[i])->debut,(&g->l_sommet[i])->fin,(&g->l_sommet[i])->pere->id);
        }
    }
}
