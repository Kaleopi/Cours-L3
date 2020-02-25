#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>     /* Pour exit, EXIT_FAILURE, EXIT_SUCCESS */
#include <stdio.h>      /* Pour printf, perror */
#include <sys/msg.h>    /* Pour msgget, msgsnd, msgrcv */
#include <errno.h>      /* Pour errno */
#include <sys/stat.h>   /* Pour S_IRUSR, S_IWUSR */
#include <signal.h>

#include "structures.h"
#include "constantes.h"

short sigintRecu = 0;

void handler(int signum){
  printf("CONTROLEUR : signal SIGINT recu\n");
  if(signum == SIGINT) sigintRecu = 1;
}

int main() {
  int idMsg, i;
  requete_t requete;
  reponse_t reponse;
  struct sigaction sa;
  int cle_sem = KEY_SEM;
  int cle_shm = KEY_SHM;
  int cpt_voitures = 0;
  pid_t pids[MAX_V];
  union sigval messageArret;

  sa.sa_handler = handler;
  sa.sa_flags = 0;

  sigaction(SIGINT, &sa, NULL);

  /* Création de la file si elle n'existe pas */
  if((idMsg = msgget((key_t)CLE, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
    if(errno == EEXIST)
      fprintf(stderr, "CONSTROLEUR : Erreur : file (cle=%d) existante\n", CLE);
    else
      perror("CONSTROLEUR : Erreur lors de la creation de la file ");
    exit(EXIT_FAILURE);
  }

  /* Attente d'une requête */
  while(!sigintRecu) {
    printf("CONSTROLEUR : en attente d'une requête...\n");
    if((msgrcv(idMsg, &requete, sizeof(requete_t) - sizeof(long), -2, 0) == -1)&&!sigintRecu) {
      perror("CONSTROLEUR : Erreur lors de la réception d'une requête ");
      exit(EXIT_FAILURE);
    }
    if(!sigintRecu && requete.type==TYPE_CONFIG) {
      pids[cpt_voitures]=requete.pid;
      cpt_voitures++;
      printf("CONSTROLEUR : voiture %d veut se connecter\n", requete.pid);

      /* Envoi de la réponse */
      reponse.type = requete.pid;
      reponse.cleSem = cle_sem;
      reponse.cleShm = cle_shm;

      if(msgsnd(idMsg, &reponse, sizeof(reponse_t) - sizeof(long), 0) == -1) {
        perror("CONSTROLEUR : Erreur lors de l'envoi de la reponse ");
        exit(EXIT_FAILURE);
      }
      printf("CONSTROLEUR : réponse envoyée.\n");
    }
    if(!sigintRecu && requete.type==TYPE_DEPL) {
      /*mettre a jour ncurses*/
      printf("CONTROLEUR : mise a jour affichage ncurses\n");
    }
  }

  for(i=0; i<cpt_voitures; i++){
    printf("CONTROLEUR : envoie signal arrêt au processus %d\n", pids[i]);
    sigqueue(pids[i], SIGRTMIN, messageArret)
    /*kill(pid_t, int signal)*/
  }

  /* Suppression de la file */
  if(msgctl(idMsg, IPC_RMID, 0) == -1) {
    perror("CONSTROLEUR : Erreur lors de la suppression de la file ");
    exit(EXIT_FAILURE);
  }
  printf("CONSTROLEUR : File supprimée.\n");

  return EXIT_SUCCESS;
}
