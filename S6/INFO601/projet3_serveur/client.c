/**
 * Ce programme permet d'envoyer un message au serveur via une socket TCP.
 * Le message, passé en argument du programme, est envoyé en deux temps :
 * sa taille, puis le contenu du message. L'adresse IP et le port du serveur
 * sont passés en arguments du programme.
 * @author Cyril Rabat
 **/
#include <stdlib.h>     /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h> /* Pour socket */
#include <arpa/inet.h>  /* Pour IPPROTO_TCP */
#include <stdio.h>      /* Pour perror */
#include <unistd.h>     /* Pour close */
#include <string.h>     /* Pour memset */

#include "includes.h"
#include "message.h"

int main(int argc, char *argv[]) {
  int sockfd;
  struct sockaddr_in adresse;
  requete_t requete;
  reponse_t reponse;
  /*size_t taille;
  char *msgrecu,*msg;
  char line[MAX];*/

  /* Vérification des arguments */
  if(argc != 3) {
    fprintf(stderr, "Usage : %s adresse portServeur\n", argv[0]);
    fprintf(stderr, "Où :\n");
    fprintf(stderr, "  adresse : adresse IPv4 du serveur\n");
    fprintf(stderr, "  portServeur    : numéro de port du serveur\n");
    /*fprintf(stderr, "  message        : le message à envoyer\n");*/
    exit(EXIT_FAILURE);
  }
  /*
   * PARTIE UDP
   */
   /* Création de la socket */
   if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
     perror("Erreur lors de la création de la socket ");
     exit(EXIT_FAILURE);
   }

   /* Création de l'adresse du serveur */
   memset(&adresse, 0, sizeof(struct sockaddr_in));
   adresse.sin_family = AF_INET;
   adresse.sin_port = htons(atoi(argv[2]));
   if(inet_pton(AF_INET, argv[1], &adresse.sin_addr) != 1) {
     perror("Erreur lors de la conversion de l'adresse ");
     exit(EXIT_FAILURE);
   }

   /* Préparation du message */
   memset(&requete, 0, sizeof(requete_t));
   requete.type = TYPE_CONNEXION;

   /* Envoi du message */
   if(sendto(sockfd, &requete, sizeof(requete), 0, (struct sockaddr*)&adresse, sizeof(struct sockaddr_in)) == -1) {
     perror("Erreur lors de la connexion au serveur ");
     exit(EXIT_FAILURE);
   }
   /* Réception confirmation de connexion */
   if(recvfrom(sockfd, &reponse, sizeof(reponse), 0, NULL, NULL) == -1) {
     perror("Erreur lors de la réception du message ");
     exit(EXIT_FAILURE);
   }
   printf("reponse.type : %ld\n",reponse.type);
   printf("reponse.port : %d\n",reponse.port);

   /* Fermeture de la socket */
   if(close(sockfd) == -1) {
     perror("Erreur lors de la fermeture de la socket ");
     exit(EXIT_FAILURE);
   }
   printf("connecté UDP\n");

  /*
   * PARTIE TCP
   */

  /* Création de la socket de connection */
  if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    perror("Erreur lors de la création de la socket ");
    exit(EXIT_FAILURE);
  }

  /* Remplissage de la structure */
  memset(&adresse, 0, sizeof(struct sockaddr_in));
  adresse.sin_family = AF_INET;
  adresse.sin_port = htons(reponse.port);
  if(inet_pton(AF_INET, argv[1], &adresse.sin_addr.s_addr) != 1) {
    perror("Erreur lors de la conversion de l'adresse ");
    exit(EXIT_FAILURE);
  }

  /* Connexion au serveur */
  if(connect(sockfd, (struct sockaddr*)&adresse, sizeof(adresse)) == -1) {
    perror("Erreur lors de la connexion ");
    exit(EXIT_FAILURE);
  }
  printf("Connecté au serveur en TCP !\n");
  /*
  do{
    printf("Entrez le message à envoyer au serveur : ");
    if((msg = fgets(line, MAX, stdin))==NULL){
     perror("Erreur saisie msg client");
    }


    taille = strlen(msg);
    if(msg[taille-1] == '\n')
      msg[taille-1] = '\0';
    if(write(sockfd, &taille, sizeof(size_t)) == -1) {
      perror("Erreur lors de l'envoi de la taille du message ");
      exit(EXIT_FAILURE);
    }
    if(write(sockfd, msg, sizeof(char) * taille) == -1) {
      perror("Erreur lors de l'envoi du message ");
      exit(EXIT_FAILURE);
    }
    printf("Client : message envoyé.\n");

    if(read(sockfd, &taille, sizeof(size_t)) == -1) {
      perror("Erreur lors de la lecture de la taille du message ");
      exit(EXIT_FAILURE);
    }
    if((msgrecu = (char*)malloc(sizeof(char) * taille)) == NULL) {
      perror("Erreur lors de l'allocation mémoire pour le message ");
      exit(EXIT_FAILURE);
    }
    if(read(sockfd, msgrecu, sizeof(char) * taille) == -1) {
      perror("Erreur lors de la lecture de la taille du message ");
      exit(EXIT_FAILURE);
    }
    printf("Client : message recu '%s'.\n", msgrecu);
  }while(strcmp(msgrecu,"Au revoir"));*/


  /* Fermeture de la socket */
  if(close(sockfd) == -1) {
    perror("Erreur lors de la fermeture de la socket ");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
