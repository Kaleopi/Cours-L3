/**
 * Ce programme illustre l'utilisation de la souris dans un environnement
 * ncurses. Lorsque l'utlisateur clique sur la souris, un message est affiché
 * à l'écran avec les coordonnées du caractère cliqué.
 * @author Cyril Rabat
 * @version 21/01/2016
 **/

#include <stdlib.h>     /* Pour EXIT_SUCCESS */
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */

#include "ncurses.h"

int main() {
  int sourisX, sourisY, bouton, ch;

  /* Initialisation de ncurses */
  ncurses_initialiser();
  ncurses_souris();
  scrollok(stdscr, TRUE);
  printw("Pressez F2 pour quitter. Cliquez avec la souris sur le terminal...\n");

  /* Routine principale */
  while((ch = getch()) != KEY_F(2)) {
    switch(ch) {
      case KEY_MOUSE:
        if(souris_getpos(&sourisX, &sourisY, &bouton) == OK) {
	  if(bouton & BUTTON1_CLICKED)
	    printw("Clic bouton 1 a la position (%d, %d)\n", sourisX, sourisY);
	  if(bouton & BUTTON2_CLICKED)
	    printw("Clic bouton 2 a la position (%d, %d)\n", sourisX, sourisY);
	  if(bouton & BUTTON1_DOUBLE_CLICKED)
	    printw("Double-clic bouton 1 a la position (%d, %d)\n", sourisX, sourisY);
	  if(bouton & BUTTON2_DOUBLE_CLICKED)
	    printw("Double-clic bouton 2 a la position (%d, %d)\n", sourisX, sourisY);
	  refresh();
	}
    }
  }

  /* Arrêt de ncurses */
  ncurses_stopper();

  return EXIT_SUCCESS;
}
