#include <stdio.h> 
#include <stdlib.h> 
#include "file.h"

#define TRUE 1
#define FALSE 0

Cellule_t* creerCellule(int id){
    Cellule_t *tmp = (Cellule_t*)malloc(sizeof(Cellule_t));
    tmp->id = id;
    tmp->suiv = NULL; 
    return tmp;
}

struct File_t* creerFile(){
    struct File_t* f = (File_t*)(malloc(sizeof(File_t)));
    f->tete = NULL;
    f->fin = NULL;
    return f;
}

void enfiler(File_t* file, int id){
    Cellule_t* tmp = creerCellule(id);

    printf("Enfiler %d...\n",id);
    if(file->fin == NULL){
        file->tete = tmp;
        file->fin = tmp;
        return;
    }

    file->fin->suiv = tmp;
    file->fin = tmp;
}

void defiler(File_t* file){
    Cellule_t* tmp; 

    printf("Défile...\n");
    if(file->tete == NULL){
        printf("File vide.\n");
        return;
        free(tmp);
    }
    tmp = file->tete;
    file->tete = file->tete->suiv;
    if(file->tete == NULL){
        file->fin = NULL;
    }
    free(tmp);
}

void supprFile(File_t* file){
    if(file->tete == NULL){
        printf("La file n'existe pas.\n");
        return;
    }
    while(file->tete != NULL){
        defiler(file);
        free(file->tete);
    }
    free(file);
}
