/**
 * Ce programme illustre le fonctionnement de base de ncurses.
 * Le mode ncurses est activé puis l'utilisateur peut tapez sur les touches
 * flèches du clavier pour déplacer un curseur à l'écran.
 * @author Cyril Rabat
 * @version 21/01/2016
 **/

#include <stdlib.h>     /* Pour EXIT_SUCCESS */
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */

#include "ncurses.h"

int main() {
  int ch, posX, posY;

  /* Initialisation de ncurses */
  ncurses_initialiser();
  printw("Pressez F2 pour quitter le programme. Utilisez les flèches pour déplacer le curseur.\n");

  /* Place le curseur à la position de départ */
  posX = COLS / 2 -1;
  posY = LINES / 2 - 1;
  mvaddch(posY, posX, ACS_DIAMOND);
  refresh();

  /* Routine principale */
  while((ch = getch()) != KEY_F(2)) {
    /* On efface le curseur */
    mvaddch(posY, posX, ' ');

    /* On calcule la nouvelle position */
    switch(ch) {
      case KEY_LEFT:
	if(posX > 0) posX--;
	break;
      case KEY_RIGHT:
	if(posX < COLS - 1) posX++;
	break;
      case KEY_UP:
	if(posY > 0) posY--;
	break;
      case KEY_DOWN:
	if(posY < LINES - 1) posY++;
	break;
    }

    /* On affiche le curseur */
    mvaddch(posY, posX, ACS_DIAMOND);
    refresh();
  }

  /* Arrêt de ncurses */
  ncurses_stopper();

  return EXIT_SUCCESS;
}
