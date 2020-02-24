#include "ncurses.h"
#include "defines.h"
#include "fonctionsControleur.h"

int main(int argc, char *argv[]){
    /*Initialisation de ncurses*/
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    wbkgd(stdscr, COLOR_PAIR(4));
    refresh();

	/* Vérification des dimensions du terminal */
  	if((COLS < COL+5) || (LINES < LINE+5)) {
        ncurses_stopper();
        fprintf(stderr, "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", COLS, LINES, COL+5, LINE+5);
        exit(EXIT_FAILURE);
    }

    WINDOW *carte, *bordure;
    srand(time(NULL));
    int i=0;

    /*Initialisation des fenêtres*/
    bordure = newwin(COL+2,LINE+2,1,0);
    box(bordure, 0,0);
    carte = subwin(bordure, COL,LINE,2,1);

    wrefresh(bordure);
    wrefresh(carte);
    scrollok(carte,TRUE);
    printw("Pressez F2 pour quitter...");
    while((i = getch()) != KEY_F(2)){

    };
    delwin(carte);
    delwin(bordure);
    ncurses_stopper();

    return EXIT_SUCCESS;
}