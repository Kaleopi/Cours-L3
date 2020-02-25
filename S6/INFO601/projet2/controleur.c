#include "shm_map.h"
#include "ncurses.h"
#include "messages.h"
#include "fonctionsControleur.h"
#include "defines.h"

static carte_t carte;

int main(int argc, char *argv[]){
    int msqid;
    message_t msg;
    reponse_t rep;
    /* Création de la file si elle n'existe pas */
    if((msqid = msgget((key_t)CLE_MSG, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
            fprintf(stderr, "Erreur : file (cle=%d) existante\n", CLE_MSG);
        else
           perror("Erreur lors de la creation de la file ");
    exit(EXIT_FAILURE);
  }

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
    srand(time(NULL));
    int i=0;

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
        if(msgrcv(msqid, &msg, sizeof(message_t) - sizeof(long), IPC_NOWAIT)){

        }
    };
    delwin(sim);
    delwin(bordure);
    ncurses_stopper();

    exit(EXIT_SUCCESS);
}