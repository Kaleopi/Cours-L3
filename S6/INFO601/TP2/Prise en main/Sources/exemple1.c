/**
 * Ce programme illustre le fonctionnement de base de ncurses.
 * Le mode ncurses est activé et plusieurs messages sont affichés de couleurs
 * différentes.
 * @author Cyril Rabat
 * @version 21/01/2016
 **/

#include <stdlib.h>     /* Pour EXIT_SUCCESS */
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */

#include "ncurses.h"

int main() {
  int i;

  /* Initialisation de ncurses */
  ncurses_initialiser();
  ncurses_couleurs();

  /* Exemple d'affichage */
  for(i = 1; i <= 3; i++) {
    attron(COLOR_PAIR(i));
    printw("Bonjour (dans la couleur %d).\n", i);
    attroff(COLOR_PAIR(i));
  }

  /* Attente d'une touche */
  printw("Pressez une touche...");
  getch();

  /* Arrêt de ncurses */
  ncurses_stopper();

  return EXIT_SUCCESS;
}
