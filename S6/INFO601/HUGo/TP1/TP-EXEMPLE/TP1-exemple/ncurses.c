#include "ncurses.h"

#include <ncurses.h>   /* Pour toutes les fonctions/constantes ncurses */
#include <stdlib.h>    /* Pour exit, EXIT_FAILURE */

/**
 * Initialisation de ncurses.
 */
void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}

/**
 * Fin de ncurses.
 */
void ncurses_stopper() {
  endwin();
}

/**
 * Initialisation des couleurs.
 */
void ncurses_couleurs() {
  /* Verification du support de la couleur */
  if(has_colors() == FALSE) {
    ncurses_stopper();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  /* Activation des couleurs */
  start_color();

  /* Definition de la palette */
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
}
