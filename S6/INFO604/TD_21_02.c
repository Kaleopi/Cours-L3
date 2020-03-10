#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <ncurses.h>
/*  SERVEUR  */
typedef struct serveurAff{
	int rat; //requete a traiter
	pthread_mutex_t mutex;
	pthread_cond_t termine;
	pthread_cond_t requete
} serveurAff_t;

serveurAff_t serveurAff = {0, PTHREAD mutex initializer, PTHREAD, cond initializer, PTHREAD cond initializer};

void* afficherMatrices(void *args){
	/*---
	---*/
	while(1){
		pthread_mutex_lock(&serveurAff.mutex);
		while(!serveurAff.rat){
			pthread_cond_wait(&serveurAff.requete, &serveurAff.mutex);
		}
		serveurAff.rat = 0;
		/*Afficher matrices*/
		pthread_cond_broadcast(&serveurAff.termine);
		pthread_mutex_unlock(&serveurAff.mutex);
	}
	return NULL;
}

	/*  CLIENT  */
void *afficherInfosClient(void *args){
	pthread_mutex_lock(&serveurAff.mutex);
	while(&serveurAff.rat){
		pthread_cond_wait(&serveurAff.termine, &serveurAff.mutex);
	}
	/*
	*
	*/
	serveurAff.rat = 1;
	pthread_cond_signal(&serveurAff.requete);
	pthread_mutex_unlock(&serveurAff.mutex);
}
