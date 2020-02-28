#include "messages.h"
#include "shm_map.h"
#include "defines.h"

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
/*int sleepnano(struct timespec tim, struct timespec time){
   if(nanosleep(&tim , &time) < 0 ){
      printf("Failed \n");
      return -1;
   }
   printf("Sleep\n");
   return 0;
}*/

int main(int argc, char *argv[]) {
	struct timespec tim;
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
	if((id = msgget(CLE_MSG, 0) == -1)){
		perror("recup file statut :FAILED");
		exit(EXIT_FAILURE);
  	}
	/*envoie de la requête*/
  	requete.type = TYPE_REQUETE;
 	requete.pid = getpid();

	do{
		if(msgsnd(id, &requete, sizeof(requete_t) - sizeof(long), 0) == -1) {
			perror("Requete statut :FAILED");
			exit(EXIT_FAILURE);
		}
		printf("Requete statut :DONE. pid = %d\n", getpid());

		if(msgrcv(id, &reponse, sizeof(reponse_t) - sizeof(long), getpid(), 0) == -1) {
			perror("Reponse statut :FAILED");
			exit(EXIT_FAILURE);    
		}
		
		tim.tv_nsec =rand()%500000000L+500000000L;
		tim.tv_sec = 0;
		nanosleep(&tim,NULL);
		printf("ZzzZZz");
	}while (reponse.cle_sem!=-1 && !sigRecu);
	requete.type = TYPE_REPONSE;
    requete.pid = getpid();

	exit(EXIT_SUCCESS);
}




