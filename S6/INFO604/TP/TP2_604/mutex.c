#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
pthread_t tid[3];
int counter;
int compteur=0;
pthread_mutex_t lock;


void* compt3(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d commencé\n", counter);

    if(compteur==9){
        compteur=0;
         printf("\n RESET\n");
    }
   
    printf("\n Job %d finit\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

void* compt2(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d commencé\n", counter);


    
    if(compteur%2==0){
         printf("\n GG module de 2\n");
         sleep(2);
    }
    printf("\n Job %d finit\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

void* compt(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d commencé\n", counter);

    compteur++;
    sleep(3);
    printf("\n compt= %d\n", compteur);
    printf("\n Job %d finit\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init rater\n");
        return 1;
    }

    while(i < 30)
    {
        err = pthread_create(&(tid[i]), NULL, &compt, NULL);
        err = pthread_create(&(tid[i+1]), NULL, &compt2, NULL);
        err = pthread_create(&(tid[i+2]), NULL, &compt3, NULL);

        if (err != 0){
            printf("\nERROR :[%s]", strerror(err));
        }
        i=i+3;
    }

   // pthread_join(tid[0], NULL);
    //pthread_join(tid[1], NULL);

    for(int i=0 ; i<30 ; i++){
        int statut =pthread_join(tid[i],NULL);
        if(statut!=0){
            fprintf(stderr, "probleme thread join\n");
        }
    }
    pthread_mutex_destroy(&lock);

    return 0;
}