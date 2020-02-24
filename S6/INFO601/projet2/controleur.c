#include "ncurses.h"
#include "constantes.h"
#include "fonctionsControleur.h"

int main(int argc, char *argv[]){
    /*Initialisation de ncurses*/
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    wbkgd(stdscr, COLOR_PAIR(4));
    refresh();

	/* Vérification des dimensions du terminal */
  	if((COLS < POSX) || (LINES < POSY)) {
        ncurses_stopper();
        fprintf(stderr, "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", COLS, LINES, POSX, POSY);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}