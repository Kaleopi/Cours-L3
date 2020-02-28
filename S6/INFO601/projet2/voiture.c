#include "fonctionsVoiture.h"
#include "messages.h"
#include "defines.h"
#include "shm_map.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define LIMIT 2




/*Création du sémaphore*/

int semid;
struct sembuf op;
short sigRecu = 0;

void handler(int signum){
  if(signum==SIGINT || signum==SIGRTMIN) sigRecu = 1;
  printf("VOITURE %d :signal recu, %d\n", getpid(), sigRecu);
}
/*sleep*/
int sleepnano(timespec tim, timespec time){
   if(nanosleep(&tim , &time) < 0 ){
      printf("Failed \n");
      return -1;
   }
   printf("Sleep\n");
   return 0;
}

int main() {
	struct timespec tim, time2;
	tim.tv_sec = 0;
    tim.tv_nsec = 500000000L;
	int id;

 	requete_t requete;
 	reponse_t reponse;
	struct sigaction sa;
	srand(time(NULL));
	sa.sa_handler = handler;
  	sa.sa_flags = 0;

 	sigaction(SIGINT, &sa, NULL);
  	sigaction(SIGRTMIN, &sa, NULL);
	/*init file message et récup*/
	if((id = msgget((key_t)CLE, 0)) == -1) {
		perror("recup file statut :FAILED");
		exit(EXIT_FAILURE);
  	}
	/*envoie de la requête*/
  	requete.type = CONFIG;
 	requete.pid = getpid();

	do{
		if(msgsnd(id, &requete, sizeof(requete_t) - sizeof(long), 0) == -1) {
			perror("Requete statut :FAILED");
			exit(EXIT_FAILURE);
		}
		printf("Requete statut :DONE.\n", getpid());

		if(msgrcv(id, &reponse, sizeof(reponse_t) - sizeof(long), getpid(), 0) == -1) {
			perror("Reponse statut :FAILED");
			exit(EXIT_FAILURE);    
		}
		
		tim.tv_nsec =rand() %500000000L ;
		sleepnano(tim,time2);
		printf("ZzzZZz");
		}while (reponse.cle!=-1 && !sigRecu);
		requete.type = DEPLACEMENT;
    	requete.pid = getpid();
}




