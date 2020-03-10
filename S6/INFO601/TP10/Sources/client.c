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

#define MAX 1024

int main(int argc, char *argv[]) {
  int fd;
  struct sockaddr_in adresse;
  size_t taille;
  char *msgrecu,*msg;
  char line[MAX];

  /* Vérification des arguments */
  if(argc != 3) {
    fprintf(stderr, "Usage : %s adresseServeur portServeur message\n", argv[0]);
    fprintf(stderr, "Où :\n");
    fprintf(stderr, "  adresseServeur : adresse IPv4 du serveur\n");
    fprintf(stderr, "  portServeur    : numéro de port du serveur\n");
    /*fprintf(stderr, "  message        : le message à envoyer\n");*/
    exit(EXIT_FAILURE);
  }

  /* Création de la socket de connection */
  if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    perror("Erreur lors de la création de la socket ");
    exit(EXIT_FAILURE);
  }

  /* Remplissage de la structure */
  memset(&adresse, 0, sizeof(struct sockaddr_in));
  adresse.sin_family = AF_INET;
  adresse.sin_port = htons(atoi(argv[2]));
  if(inet_pton(AF_INET, argv[1], &adresse.sin_addr.s_addr) != 1) {
    perror("Erreur lors de la conversion de l'adresse ");
    exit(EXIT_FAILURE);
  }

  /* Connexion au serveur */
  if(connect(fd, (struct sockaddr*)&adresse, sizeof(adresse)) == -1) {
    perror("Erreur lors de la connexion ");
    exit(EXIT_FAILURE);
  }
  do{
    printf("Entrez le message à envoyer au serveur : ");
    if((msg = fgets(line, MAX, stdin))==NULL){
     perror("Erreur saisie msg client"); 
    }

    /* Envoi du message au serveur */
    taille = strlen(msg);
    if(msg[taille-1] == '\n')
      msg[taille-1] = '\0';
    if(write(fd, &taille, sizeof(size_t)) == -1) {
      perror("Erreur lors de l'envoi de la taille du message ");
      exit(EXIT_FAILURE);
    }
    if(write(fd, msg, sizeof(char) * taille) == -1) {
      perror("Erreur lors de l'envoi du message ");
      exit(EXIT_FAILURE);
    }
    printf("Client : message envoyé.\n");

    /* Réception de la réponse du serveur */
    if(read(fd, &taille, sizeof(size_t)) == -1) {
      perror("Erreur lors de la lecture de la taille du message ");
      exit(EXIT_FAILURE);
    }
    if((msgrecu = (char*)malloc(sizeof(char) * taille)) == NULL) {
      perror("Erreur lors de l'allocation mémoire pour le message ");
      exit(EXIT_FAILURE);
    }
    if(read(fd, msgrecu, sizeof(char) * taille) == -1) {
      perror("Erreur lors de la lecture de la taille du message ");
      exit(EXIT_FAILURE);
    }
    printf("Client : message recu '%s'.\n", msgrecu);
  }while(strcmp(msgrecu,"Au revoir"));


  /* Fermeture de la socket */
  if(close(fd) == -1) {
    perror("Erreur lors de la fermeture de la socket ");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
