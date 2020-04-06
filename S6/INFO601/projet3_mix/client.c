#include <stdlib.h>     /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h> /* Pour socket */
#include <arpa/inet.h>  /* Pour IPPROTO_TCP */
#include <stdio.h>      /* Pour perror */
#include <unistd.h>     /* Pour close */
#include <string.h>     /* Pour memset */

#include "includes.h"
#include "message.h"
#include "fonctions.h"
WINDOW *fen_box_sim, *fen_box_msg, *fen_box_outils, *fen_box_points ,*fen_sim, *fen_msg, *fen_outils, *fen_points;
int tab[3];
int verif;
int main(int argc, char *argv[]) {
  struct sockaddr_in adresse;
  int item_actif;
  grille_t *etang;
  int sockfd, ch;
  requete_t requete;
  reponse_t reponse;

  /* Vérification des arguments */
  if(argc != 3) {
    fprintf(stderr, "Usage : %s adresse portServeur\n", argv[0]);
    fprintf(stderr, "Où :\n");
    fprintf(stderr, "  adresse : adresse IPv4 du serveur\n");
    fprintf(stderr, "  portServeur    : numéro de port du serveur\n");
    /*fprintf(stderr, "  message        : le message à envoyer\n");*/
    exit(EXIT_FAILURE);
  }
  etang = malloc(sizeof(grille_t));
  init_etang(etang);
  item_actif = HAMMECONS;
  verif = 0;

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
  if(read(sockfd, etang, sizeof(grille_t))==-1){
    perror("Erreur lors de la réception de la grille");
  }

  ncurses_initialiser();
  fen_box_sim = creer_fenetre_box_sim();
  fen_box_points = creer_fenetre_box_points();
  fen_box_outils = creer_fenetre_box_outils();
  fen_box_msg = creer_fenetre_box_msg();
  fen_sim = creer_fenetre_sim();
  fen_points = creer_fenetre_points();
  fen_outils = creer_fenetre_outils();
  fen_msg = creer_fenetre_msg();
  mvprintw(LINES - 1, 0, "Tapez F2 pour quitter");
  wprintw(fen_msg,"initialisation client verif = %d\n",verif);
  wrefresh(stdscr);
  wrefresh(fen_box_sim);
  wrefresh(fen_box_points);
  wrefresh(fen_box_outils);
  wrefresh(fen_box_msg);
  wrefresh(fen_sim);
  wrefresh(fen_points);
  wrefresh(fen_outils);
  wrefresh(fen_msg);
  init_sim(fen_sim, etang);
  while((ch = getch()) != KEY_F(2)) {
    verif = read(sockfd, etang, sizeof(grille_t));
    if(verif ==-1){
      perror("Erreur lors de la réception de la grille");
    }
    else if(verif>=0){

      wprintw(fen_msg, "verif = %d\n", verif);
      wrefresh(fen_msg);
      update_sim(fen_sim,etang);
      wrefresh(fen_sim);
      /*generer_poisson(etang);*/
      switch (ch)
      {
        case KEY_MOUSE:
        lancerTruc(item_actif,fen_sim,fen_msg,tab);

        break;
        case KEY_DOWN:
        wprintw(fen_msg, "Switch Item down\n");
        wrefresh(fen_msg);
        item_actif=switchDown(item_actif,fen_outils);
        break;
        case KEY_UP:
        wprintw(fen_msg, "Switch item Up\n");
        wrefresh(fen_msg);
        item_actif=switchUp(item_actif,fen_outils);
        break;
      }
      wrefresh(fen_sim);
      wrefresh(fen_outils);
      wrefresh(fen_msg);
      wrefresh(fen_points);
    }
    verif=0;
  }

  simulation_stopper();
  delwin(fen_box_sim);
  delwin(fen_sim);
  delwin(fen_box_msg);
  delwin(fen_msg);
  delwin(fen_box_outils);
  delwin(fen_outils);
  delwin(fen_box_points);
  delwin(fen_points);
  ncurses_stopper();
  /* Fermeture de la socket TCP*/
  if(close(sockfd) == -1) {
    perror("Erreur lors de la fermeture de la socket ");
    exit(EXIT_FAILURE);
  }

  free(etang);
  return EXIT_SUCCESS;
}
