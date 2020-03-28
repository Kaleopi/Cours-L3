#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#define NB_MSG 5
#define SIZE_MAX_MSG 256
#define MAX_PLAYERS 2
#define MAX 1024

#define NB_LIGNES_SIM		40				/* Dimensions des fenetres du programme */
#define NB_COL_SIM			80
#define NB_LIGNES_MSG		29
#define NB_COL_MSG			49
#define NB_LIGNES_OUTILS	9
#define NB_COL_OUTILS		49

#define MAX_HAMMECONS 		1
#define MAX_POISSONS		10				/* Nombre maximum de poissons de la simulation */

#define VIDE				0				/* Identifiants des elements pouvant etre */
#define HAMMECONS			1				/* places sur la grille de simulation */
#define POISSON				2

pthread_t *threads_poissons[MAX_POISSONS];	/* Identifants des threads des poissons de la simulation*/
WINDOW *fen_sim;							/* Fenetre de simulation partagee par les poissons*/
WINDOW *fen_msg;							/* Fenetre de messages partagee par les poissons*/

case_t grille[NB_LIGNES_SIM][NB_COL_SIM];	/* Grille de simulation */

#endif
