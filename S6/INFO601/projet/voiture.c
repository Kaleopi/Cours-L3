#define _POSIX_C_SOURCE 199309L

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

#include "structures.h"

short sigRecu = 0;

void handler(int signum){
  if(signum==SIGINT || signum==SIGRTMIN) sigRecu = 1;
  printf("VOITURE %d : recu signal, %d\n", getpid(), sigRecu);
}

/*
void handlerRT(int signum, siginfo_t *info, void *rien) {
  if(signum==SIGRTMIN) {
    sigRecu=info->si_value.sival_int;
  }
}
*/

int main() {
  int idMsg, r;
  requete_t requete;
  reponse_t reponse;

  struct sigaction sa;

  srand(time(NULL));

  sa.sa_handler = handler;
  sa.sa_flags = 0;

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGRTMIN, &sa, NULL);

  /* Récupération de la file */
  if((idMsg = msgget((key_t)CLE, 0)) == -1) {
    perror("VOITURE : Erreur lors de la récupération de la file ");
    exit(EXIT_FAILURE);
  }

  /* Envoi d'une requête */
  requete.type = TYPE_CONFIG;
  requete.pid = getpid();

  if(msgsnd(idMsg, &requete, sizeof(requete_t) - sizeof(long), 0) == -1) {
    perror("VOITURE : Erreur lors de l'envoi de la requête ");
    exit(EXIT_FAILURE);
  }
  printf("VOITURE %d : envoi d'une requête.\n", getpid());

  /* Réception de la réponse */
  printf("VOITURE %d : attente de la reponse...\n", getpid());
  if(msgrcv(idMsg, &reponse, sizeof(reponse_t) - sizeof(long), getpid(), 0) == -1) {
    perror("VOITURE : Erreur lors de la réception de la réponse ");
    exit(EXIT_FAILURE);    
  }

  printf("VOITURE %d : sem = %d, shm = %d\n", getpid(), reponse.cleSem, reponse.cleShm);

  while(reponse.cleSem!=-1 && !sigRecu) {
    r=rand()%5;
    sleep(r);
    printf("sleep\n");
    /*se deplacer*/
    requete.type = TYPE_DEPL;
    requete.pid = getpid();
    if((msgsnd(idMsg, &requete, sizeof(requete_t) - sizeof(long), 0) == -1)&&!sigRecu) {
      perror("VOITURE : Erreur lors de l'envoi de la requête ");
      exit(EXIT_FAILURE);
    }
  }

  printf("VOITURE %d : Recu signal arret\n", getpid());
  
  return EXIT_SUCCESS;
}
