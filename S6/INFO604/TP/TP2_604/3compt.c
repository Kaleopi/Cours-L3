#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define SPIN			1000000
static int compteur = 0;
static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
//int_pelement = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};
typedef struct int_protege{
    pthread_mutex_t mutex; 
    pthread_cond_t cond;
    int valeur; 
    }int_p;


typedef struct Hello_world{
    int n;
    int id;
}Hello_t;

void *compt(void *arg) {
    while (1) {
        pthread_mutex_lock(& mutex);	
        compteur++;
        usleep(100000);
        printf("%d ",compteur);
        pthread_mutex_unlock(& mutex);
    }
}


void *Hello_n(void *arg){
    Hello_t *hello=(Hello_t*)arg;
    printf("\nHello World ! du thread %d de %d !\n ",hello->id,hello->n);
    fflush(stdout);
    free(hello);
    return NULL;
}

int main(int argc,char*argv[]){
    int_p *element;
    int statut=0;
    int n = atoi(argv[1]);
    
    element = (int_p*) malloc(sizeof(int_p));
    Hello_t *hello;
    pthread_t *threads=malloc(sizeof(pthread_t)*n);

    statut= pthread_mutex_init(&element->mutex, NULL);
    if (statut != 0){
        fprintf(stderr, "Problemeinitialisation mutex\n");
    }
    statut= pthread_cond_init(&element->cond, NULL);
  
    pthread_mutex_lock(& mutex);
    statut=pthread_create(&threads[0],NULL,compt,element);
    pthread_mutex_unlock(& mutex);
    /*for(int i=0;i<n;i++){
        hello=(Hello_t*)malloc(sizeof(Hello_t));
        hello->n=n;
        hello->id=i+1;
        statut=pthread_create(&threads[i],NULL,Hello_n,hello);
        if(statut!=0){
            printf("probleme thread create\n");
            return EXIT_FAILURE;
        }
    }

    for(int i=0 ; i<n ; i++){
        statut=pthread_join(threads[i],NULL);
        if(statut!=0){
            fprintf(stderr, "probleme thread join\n");
        }
    }*/
    return EXIT_SUCCESS;
}
