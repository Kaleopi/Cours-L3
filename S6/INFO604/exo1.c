#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define M 12
#define NCLES 100

typedef struct c {
    int cle;
    struct c *succ;
}cellule_t;

typedef struct args{
    int arg1;
    int arg2;
}args_t;

cellule_t *table[M];
int cles[NCLES];
pthread_mutex_t *mutex[M];
pthread_mutex_t mutex_perdus = PTHREAD_MUTEX_INITIALIZER;
int nbPerdus = 0;

void routine_rechercher(void *args) {
    int i, cle, ind, trouve;
    cellule_t *c;
    int *debut=(int*)args[0];
    int *fin=(int*)args[1];

    for (i = debut; i < fin; i++){
        cle = cles[i];
        ind = cle % M;
        c = table[ind];
        trouve = 0;
        while (c != NULL && !trouve) {
            if (c->cle == cle) {
                trouve = 1;
            }else{
                c = c->succ;
            }
            if(!trouve) {
                pthread_mutex_lock(&mutex_perdus);
                nbPerdus++;
                pthread_mutex_unlock(&mutex_perdus);
            }
        }
    }
    printf("Nombre de cles perdues : %d\n", nbPerdus);
}

void recherche() {
    int i, cle, ind, trouve, nbPerdus;
    cellule_t *c;

    nbPerdus = 0;
    for (i = 0; i < NCLES; i++){
        cle = cles[i];
        ind = cle % M;
        c = table[ind];
        trouve = 0;
        while (c != NULL && !trouve) {
            if (c->cle == cle) {
                trouve = 1;
            }else{
                c = c->succ;
            }
            if(!trouve) nbPerdus++;
        }
    }
    printf("Nombre de cles perdues : %d\n", nbPerdus);
}

void routine_ajouter(void *args) {
    int i, cle, ind;
    cellule_t c;
    int *debut=(int*)args[0];
    int *fin=(int*)args[1];

    for(i=debut; i<fin; i++) {
        cle = cles[i];
        ind= cle%M;
        c = (cellule_t*)malloc(sizeof(cellule_t));
        c->cle = cle;
        //lock
        pthread_mutex_lock(&mutex[ind]);
        c->succ = table[ind];
        table[ind] = c;
        //unlock
        pthread_mutex_unlock(&mutex[ind]);
    }
}

void ajout() {
    int i, cle, ind;
    cellule_t *c;

    for(i=0; i<NCLES; i++) {
        cle = cles[i];
        ind = cle%M;
        c = (cellule_t*)malloc(sizeof(cellule_t));
        c->cle = cle;
        c->succ = table[ind];
        table[ind] = c;
    }
}

int main(int argc, char *argv[]){
    int i;
    pthread_t threads[10];
    int arg1, arg2;
    args_t a;

    //initialiser tout les mutex
    for(i=0; i<M; i++) {
        mutex[i] = PTHREAD_MUTEX_INITIALIZER;
        
    }
    for(i=0 ; i<M ; i++){
        table[i] = NULL;
    }
    srand(time(NULL));
    for(i=0 ; i<NCLES ; i++){
        cles[i] = rand()%30;
        printf("[%d] %d\n",i,cles[i]);
    }

    //creer tout les threads
    for(i=0; i<5; i++) {
        a.arg1 = i*i;
        a.arg2 = i+(i*20);
        status = pthread_create(&threads[i], NULL, routine_ajouter, (void*) &a);
    }

    //creer tout les threads
    for(i=0; i<5; i++) {
        a.arg1 = i*i;
        a.arg2 = i+(i*20);
        status = pthread_create(&threads[i+5], NULL, routine_rechercher, (void*) &a);
    }



    ajout();
    recherche();

    return 0;
}
