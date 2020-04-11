#include "ncurses.h"
#include "includes.h"
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
  ncurses_souris();
  ncurses_couleurs();
  wbkgd(stdscr, COLOR_PAIR(1));
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
  init_pair(1, COLOR_BLACK, COLOR_CYAN); /* Background */
  init_pair(2, COLOR_BLACK, COLOR_WHITE); /* Vide */
  init_pair(3, COLOR_WHITE, COLOR_RED); /* Bloc */
  init_pair(4, COLOR_WHITE, COLOR_GREEN); /* Robot */
  init_pair(5, COLOR_WHITE, COLOR_BLACK); /* Caisse */
  init_pair(6, COLOR_BLACK, COLOR_YELLOW); /* Bille */
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA); /* Trou */
}

/**
* Initialisation de la souris.
*/
void ncurses_souris() {
  if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
    ncurses_stopper();
    fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    exit(EXIT_FAILURE);
  }

  if(has_mouse() != TRUE) {
    ncurses_stopper();
    fprintf(stderr, "Aucune souris n'est détectée.\n");
    exit(EXIT_FAILURE);
  }
}

/**
* Recupere la position x et y de la souris.
* @param[out] x la position en x
* @param[out] y la position en y
* @param[out] bouton l'évenement associé au clic (ou NULL)
* @return OK si reussite
*/
int souris_getpos(int *x, int *y, int *bouton) {
  MEVENT event;
  int resultat = getmouse(&event);

  if(resultat == OK) {
    *x = event.x;
    *y = event.y;
    if(bouton != NULL) *bouton = event.bstate;
  }
  return resultat;
}

WINDOW *creer_fenetre(int hauteur, int largeur){
  /* Creation de la fenetre de simulation dans la fenetre de contour */
  /* La simulation est affichee dans cette fenetre */

  WINDOW *fen;

  fen = newwin(hauteur, largeur, 5 , 5);
  wrefresh(fen);
  return fen;
}

void update(WINDOW* w, plateau_t *p, robot_t* r){
  int i,j,height,witdh;
  height = p->hauteur;
  witdh = p->largeur;
  for(i=0 ; i<height ; i++){
    for(j=0 ; j<witdh ; j++){
      switch(p->cases[j*witdh+i]){
        case M_VIDE:
          wattron(w, COLOR_PAIR(2));
          mvwprintw(w,i,j,"0",1);
          wattroff(w,COLOR_PAIR(2));
        break;
        case M_BLOC:
          wattron(w, COLOR_PAIR(3));
          mvwprintw(w,i,j,"B",1);
          wattroff(w,COLOR_PAIR(3));
        break;
        case M_CAISSE:
          wattron(w, COLOR_PAIR(5));
          mvwprintw(w,i,j,"C",1);
          wattroff(w,COLOR_PAIR(5));
        break;
        case M_TROU:
          wattron(w, COLOR_PAIR(7));
          mvwprintw(w,i,j,"T",1);
          wattroff(w,COLOR_PAIR(7));
        break;
        case M_BILLE:
          wattron(w, COLOR_PAIR(6));
          mvwprintw(w,i,j,"o",1);
          wattroff(w,COLOR_PAIR(6));
        break;
        case M_ROBOT:
          wattron(w, COLOR_PAIR(4));
          mvwprintw(w,i,j,"r",1);
          wattroff(w,COLOR_PAIR(4));
        break;
        default:
          wattron(w, COLOR_PAIR(2));
          mvwprintw(w,i,j,M_VIDE,1);
          wattroff(w,COLOR_PAIR(2));
      }
    }
  }
  refresh();
}
