#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Hello_world{
    int n;
    int id;
}Hello_t;

void *Hello_n(void *arg){
    Hello_t *hello=(Hello_t*)arg;

    printf("\nHello World ! du thread %d de %d !\n ",hello->id,hello->n);
    fflush(stdout);
    free(hello);
    return NULL;
}

int main(int argc,char*argv[]){
    int statut=0;
    int n = atoi(argv[1]);
    Hello_t *hello;
    pthread_t *threads=malloc(sizeof(pthread_t)*n);

    for(int i=0;i<n;i++){
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
    }
    return EXIT_SUCCESS;
}