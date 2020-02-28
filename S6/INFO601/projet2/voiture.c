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
	int msqid;
	key_t cle_msg;
 	requete_t requete;
 	reponse_t reponse;
	struct sigaction sa;
	srand(time(NULL));
	sa.sa_handler = handler;
  	sa.sa_flags = 0;
	
 	sigaction(SIGINT, &sa, NULL);
  	sigaction(SIGRTMIN, &sa, NULL);
	cle_msg = 1056;
	/*init file message et récup*/

	if((msqid = msgget(cle_msg, 0) == -1)){
		perror("recup file statut :FAILED");
		exit(EXIT_FAILURE);
  	}
	printf("voiture : file de message ouverte ");
	/*envoie de la requête*/
  	requete.type = TYPE_REQUETE;
 	requete.pid = getpid();
	printf("msqid %d\n",msqid);
	if(msgsnd(msqid, &requete, sizeof(requete_t) - sizeof(long), 0) == -1) {
		perror("Requete statut 1:FAILED");
		exit(EXIT_FAILURE);
	}
	printf("Requete statut :DONE. pid = %d\n", getpid());

	if(msgrcv(msqid, &reponse, sizeof(reponse_t) - sizeof(long), getpid(), 0) == -1) {
		perror("Reponse statut :FAILED");
		exit(EXIT_FAILURE);    
	}
		
	tim.tv_nsec =rand()%500000000L+500000000L;
	tim.tv_sec = 0;
	do{
		nanosleep(&tim,NULL);
		/*DEPLCAMENENT*/
		requete.type = TYPE_REPONSE;
 		requete.pid = getpid();
		if(msgsnd(msqid, &requete, sizeof(requete_t) - sizeof(long), 0) == -1) {
			perror("Requete statut 2:FAILED");
			exit(EXIT_FAILURE);
		}
		printf("ZzzZZz");
	}while (reponse.cle_sem!=-1 && !sigRecu);
	requete.type = TYPE_REPONSE;
    requete.pid = getpid();

	exit(EXIT_SUCCESS);
}




