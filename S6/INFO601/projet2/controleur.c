#define _POSIX_C_SOURCE 199309L

#include "shm_map.h"
#include "ncurses.h"
#include "messages.h"
#include "fonctionsControleur.h"
#include "defines.h"

static carte_t carte;
short sigintRecu = 0;

void handler(int signum){
  if(signum == SIGINT) sigintRecu = 1;
}

int main(int argc, char *argv[]){
    /*declarations de variables*/
    int msqid;
    int i;
    int voitures_i = 0;

    key_t cle_msg = CLE_MSG;
    key_t cle_sem = CLE_SEM;
    key_t cle_shm = CLE_SHM;
    pid_t tab_pid[MAX_VOITURES];
    message_t msg;
    reponse_t rep;

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    /* Création de la file si elle n'existe pas */
    msqid = creer_file();

    initialiser_carte(&carte);
    /*Initialisation de ncurses*/
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    wbkgd(stdscr, COLOR_PAIR(3));
    refresh();

	/* Vérification des dimensions du terminal */
  	if((COLS < COL+5) || (LINES < LINE+5)) {
        ncurses_stopper();
        fprintf(stderr, "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", COLS, LINES, COL+5, LINE+5);
        exit(EXIT_FAILURE);
    }

    WINDOW *sim, *bordure;

    /*Initialisation des fenêtres*/
    bordure = newwin(LINE+2,COL+2,1,0);
    box(bordure, 0,0);
    sim = subwin(bordure,LINE+1,COL,2,1);
    scrollok(sim,TRUE);

    charger_carte("reims.bin", bordure, sim, &carte);
    /* afficher_carte(&carte);*/

    wrefresh(bordure);
    wrefresh(sim);
    printw("Pressez F2 pour quitter...");
    while((i = getch()) != KEY_F(2)){
        
    };
    delwin(sim);
    delwin(bordure);
    ncurses_stopper();

    exit(EXIT_SUCCESS);
}