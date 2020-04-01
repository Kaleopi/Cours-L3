#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include <ncurses.h>
#include <pthread.h>

#define NB_MSG 5
#define SIZE_MAX_MSG 256
#define MAX_PLAYERS 2
#define MAX 1024

#define NB_LIGNES_SIM		20				/* Dimensions des fenetres du programme */
#define NB_COL_SIM			40
#define NB_LIGNES_MSG		14
#define NB_COL_MSG			40
#define NB_LIGNES_OUTILS	4
#define NB_COL_OUTILS		24

#define MAX_HAMMECONS 		1
#define MAX_POISSONS		10				/* Nombre maximum de poissons de la simulation */

#define VIDE				0				/* Identifiants des elements pouvant etre */
#define HAMMECONS			1				/* places sur la grille de simulation */
#define POISSON				2
#define COOL                1
#define FUITE               0
#endif
