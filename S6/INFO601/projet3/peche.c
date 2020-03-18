#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <ncurses.h>

#define NB_LIGNES_SIM		40				/* Dimensions des fenetres du programme */
#define NB_COL_SIM			80
#define NB_LIGNES_MSG		29
#define NB_COL_MSG			49
#define NB_LIGNES_OUTILS	9
#define NB_COL_OUTILS		49

#define MAX_poissons			1			/* Nombre maximum de poissons de la simulation */

#define VIDE				0				/* Identifiants des elements pouvant etre */
#define OBSTACLE			1				/* places sur la grille de simulation */
#define POISSON				2

typedef struct case_tag {					/* Description d'une case sur la grille de simulation */
	int element;							/* Ce qui est present sur la case */
	pthread_t *poisson;						/* Identifiant du thread de la poisson presente sur la case */
	pthread_mutex_t mutex;					/* Protection de la case */
} case_t;

typedef struct coord_tag {					/* Coordonnees d'une case sur la grille de simulation*/
	int y;
	int x;
} coord_t;

pthread_t *threads_poissons[MAX_poissons];	/* Identifants des threads des poissons de la simulation*/
WINDOW *fen_sim;							/* Fenetre de simulation partagee par les poissons*/
WINDOW *fen_msg;							/* Fenetre de messages partagee par les poissons*/

case_t grille[NB_LIGNES_SIM][NB_COL_SIM];	/* Grille de simulation */

void ncurses_initialiser() {
	initscr();								/* Demarre le mode ncurses */
	cbreak();								/* Pour les saisies clavier (desac. mise en buffer) */
	noecho();								/* Desactive l'affichage des caracteres saisis */
	keypad(stdscr, TRUE);					/* Active les touches specifiques */
	refresh();								/* Met a jour l'affichage */
	curs_set(FALSE);						/* Masque le curseur */
	mousemask(BUTTON1_CLICKED, NULL);		/* Active le clic gauche de la souris*/
}

void ncurses_stopper() {
	endwin();
}

void simulation_initialiser() {
	int i, j;
	
	for (i = 0; i < MAX_poissons; i++)		/* Au depart il n'y a aucune poisson dans la simulation */
		threads_poissons[i] = NULL;
		
	for (i = 0; i < NB_LIGNES_SIM; i++) {	/* Initialisation des cases de la simulation */
		for (j = 0; j < NB_COL_SIM; j++) {
			grille[i][j].element = VIDE;
			grille[i][j].poisson = NULL;
			pthread_mutex_init(&grille[i][j].mutex, NULL);
		}
	}
}

void simulation_stopper() {
	int i;
	
	for (i = 0; i < MAX_poissons; i++) {
		if (threads_poissons[i] != NULL) {
			pthread_cancel(*threads_poissons[i]);
			threads_poissons[i] = NULL;
		}
	}
}

WINDOW *creer_fenetre_box_sim() {
/*Creation de la fenetre de contour de la fenetre de simulation */

	WINDOW *fen_box_sim;
	
	fen_box_sim = newwin(NB_LIGNES_SIM + 2, NB_COL_SIM + 2, 0, 0);
	box(fen_box_sim, 0, 0);
	mvwprintw(fen_box_sim, 0, (NB_COL_SIM + 2) / 2 - 5, "SIMULATION");	
	wrefresh(fen_box_sim);
	
	return fen_box_sim;
}

WINDOW *creer_fenetre_sim() {
/* Creation de la fenetre de simulation dans la fenetre de contour */
/* La simulation est affichee dans cette fenetre */

	WINDOW *fen_sim;
	
	fen_sim = newwin(NB_LIGNES_SIM, NB_COL_SIM, 1, 1);
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	wbkgd(fen_sim,COLOR_PAIR(1));
	return fen_sim;
}

WINDOW *creer_fenetre_box_msg() {
/* Creation de la fenetre de contour de la fenetre de messages */

	WINDOW *fen_box_msg;
	
	fen_box_msg = newwin(NB_LIGNES_MSG + 2, NB_COL_MSG + 2, 0, NB_COL_SIM + 2);
	box(fen_box_msg, 0, 0);
	mvwprintw(fen_box_msg, 0, (NB_COL_MSG + 2) / 2 - 4, "MESSAGES");
	wrefresh(fen_box_msg);
	
	return fen_box_msg;
}

WINDOW *creer_fenetre_msg() {
/* Creation de la fenetre de messages dans la fenetre de contour */
/* Les messages indicatifs des evenements de la simulation et de l'interface */
/* utilisateur sont affiches dans cete fenetre */

	WINDOW *fen_msg;
	
	fen_msg = newwin(NB_LIGNES_MSG, NB_COL_MSG, 1, NB_COL_SIM + 3);
	scrollok(fen_msg, TRUE);
	
	return fen_msg;
}

WINDOW *creer_fenetre_box_outils() {
/* Fenetre de contour de la fenetre des outils */

	WINDOW *fen_box_outils;
	
	fen_box_outils = newwin(NB_LIGNES_OUTILS + 2, NB_COL_OUTILS + 2, NB_LIGNES_MSG + 2 , NB_COL_SIM + 2);
	box(fen_box_outils, 0, 0);
	mvwprintw(fen_box_outils, 0, (NB_COL_OUTILS + 2) / 2 - 3, "OUTILS");
	wrefresh(fen_box_outils);
	
	return fen_box_outils;
}

WINDOW *creer_fenetre_outils() {
/* Creation de la fenetre des outils a l'interieur de la fenetre de contour */
/* Les outils dans cette fenetre sont clickables, l'outil actif etant indique par un X */

	WINDOW *fen_outils;
	
	fen_outils = newwin(NB_LIGNES_OUTILS, NB_COL_OUTILS, NB_LIGNES_MSG + 3, NB_COL_SIM + 3);
	mvwprintw(fen_outils, 0, 3, "# : Obstacle\n");
	mvwprintw(fen_outils, 1, 3, "@ : poisson");
	mvwprintw(fen_outils, 0, 1, "X");
	wrefresh(fen_outils);
	
	return fen_outils;
}


void toUp(WINDOW* simulation, int row, int col){
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	grille[col][row].element = VIDE;
	row--;
	grille[col][row].element = POISSON;
	mvwprintw(simulation,row, col,"@");
	wrefresh(simulation);


}
void toDown(WINDOW* simulation, int row ,int col){
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	grille[col][row].element = VIDE;
	row++;
	grille[col][row].element=POISSON;
	mvwprintw(simulation,row, col,"@");
	wrefresh(simulation);

}
void toLeft(WINDOW* simulation, int row, int col){
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	grille[col][row].element = VIDE;
	col--;
	grille[col][row].element = POISSON;
	mvwprintw(simulation,row,col,"@");
	wrefresh(simulation);
}
void toRight(WINDOW* simulation, int row, int col){
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	grille[col][row].element = VIDE;
	col++;
	grille[col][row].element = POISSON;
	mvwprintw(simulation,row,col,"@");
	wrefresh(simulation);
}

void *routine_poisson(void *arg) {
	coord_t *coord = (coord_t *) arg;
	int random=0;
	srand(time(NULL));
	while (1) {		
		/*Que feront les poissons ?!?!?!*/
		random=rand()%5;
		switch (random){
			case 1:
				if(coord->y>0){
					if(grille[coord->y-1][coord->x].element==VIDE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y-1][coord->x].element = POISSON;
							mvwprintw(fen_sim,coord->y-1,coord->x,"@");
							wrefresh(fen_sim);
							coord->y--;
					}
					else if(grille[coord->y-1][coord->x].element==OBSTACLE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y-1][coord->x].element = POISSON;
							mvwprintw(fen_sim,coord->y-1,coord->x,"@");
							wrefresh(fen_sim);
							coord->y--;
					}
				}
			break;
			case 2:
				if(coord->y<40){
					if(grille[coord->y+1][coord->x].element==VIDE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y+1][coord->x].element = POISSON;
							mvwprintw(fen_sim,coord->y+1,coord->x,"@");
							wrefresh(fen_sim);
								coord->y++;
					}
					else if(grille[coord->y+1][coord->x].element==OBSTACLE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y+1][coord->x].element = POISSON;
							mvwprintw(fen_sim,coord->y+1,coord->x,"@");
							wrefresh(fen_sim);
								coord->y++;
					}
				}
			break;
			case 3:
				if(coord->x>0){
					if(grille[coord->y][coord->x-1].element==VIDE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y][coord->x-1].element = POISSON;
							mvwprintw(fen_sim,coord->y,coord->x-1,"@");
							wrefresh(fen_sim);
							coord->x--;
					}
					else if(grille[coord->y][coord->x-1].element==OBSTACLE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y][coord->x-1].element = POISSON;
							mvwprintw(fen_sim,coord->y,coord->x-1,"@");
							wrefresh(fen_sim);
							coord->x--;
					}
				}
			break;
			case 4:
				if(coord->x<80){
					if(grille[coord->y][coord->x+1].element==VIDE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y][coord->x+1].element = POISSON;
							mvwprintw(fen_sim,coord->y,coord->x+1,"@");
							wrefresh(fen_sim);
								coord->x++;
					}
				}
				else if(coord->x<80){
					if(grille[coord->y][coord->x+1].element==OBSTACLE){
							mvwprintw(fen_sim,coord->y,coord->x," ");
							wrefresh(fen_sim);
							grille[coord->y][coord->x].element = VIDE;
							grille[coord->y][coord->x+1].element = POISSON;
							mvwprintw(fen_sim,coord->y,coord->x+1,"@");
							wrefresh(fen_sim);
								coord->x++;
					}
				}
			break;
			default: ;
		}
		
		sleep(1);
		
	}

	free(coord);
	return NULL;
}


int main(int argc, char *argv[]) {
	WINDOW *fen_box_sim, *fen_box_msg, *fen_box_outils, *fen_outils;
	MEVENT event;

	int ch, i, item_actif = OBSTACLE;
	int randomx,randomy;
	coord_t *coord;

	ncurses_initialiser();
	simulation_initialiser();

	fen_box_sim = creer_fenetre_box_sim();
	fen_sim = creer_fenetre_sim();
	fen_box_msg = creer_fenetre_box_msg();
	fen_msg = creer_fenetre_msg();
	fen_box_outils = creer_fenetre_box_outils();
	fen_outils = creer_fenetre_outils();


	mvprintw(LINES - 1, 0, "Tapez F2 pour quitter");
	wrefresh(stdscr);
	srand( time( NULL ) );

	
	while((ch = getch()) != KEY_F(2)) {
	while(i<MAX_poissons){
		
		randomx=rand()%NB_COL_SIM;
		randomy=rand()%NB_LIGNES_SIM;
		pthread_mutex_lock(&grille[randomy- 1][randomx - 1].mutex);
			if (grille[randomy - 1][randomx- 1].element == VIDE) {
				i = 0;
				while (i < MAX_poissons && threads_poissons[i] != NULL)
					i++;
					if (i < MAX_poissons) {
						threads_poissons[i] = (pthread_t *) malloc(sizeof(pthread_t));
						grille[randomy - 1][randomx - 1].element = POISSON;
						grille[randomy - 1][randomx- 1].poisson = threads_poissons[i];
						coord = (coord_t *) malloc(sizeof(coord_t));
						coord->y = randomy - 1;
						coord->x = randomx- 1;
						pthread_create(threads_poissons[i], NULL, routine_poisson, (void *) coord);
						mvwprintw(fen_sim, randomy - 1, randomx- 1, "@");
						/*wprintw(fen_msg, "Ajout d'une poisson a la position %d %d\n", randomy - 1, randomx - 1);*/
						}
						else {
							wprintw(fen_msg, "Nombre maximum de poissons atteint\n");
				}
			}
	
		/*switch(ch) {
			case KEY_MOUSE :
				if (getmouse(&event) == OK) {
					wprintw(fen_msg, "Clic a la position %d %d de l'ecran\n", event.y, event.x);
					wrefresh(fen_msg);
					if (event.y == 32 && event.x >= 82 && event.x <= 98) {
						item_actif = OBSTACLE;
						mvwprintw(fen_outils, 0, 1, "X");
						mvwprintw(fen_outils, 1, 1, " ");
						wrefresh(fen_outils);
						wprintw(fen_msg, "Outil obstacle active\n");
						wrefresh(fen_msg);
					}
					else if (event.y == 33 && event.x >=82 && event.x <= 98) {
						item_actif = POISSON;
						mvwprintw(fen_outils, 0, 1, " ");
						mvwprintw(fen_outils, 1, 1, "X");
						wrefresh(fen_outils);
						wprintw(fen_msg, "Outil poisson active\n");
						wrefresh(fen_msg);
					}
					else if (event.y > 0 && event.y < NB_LIGNES_SIM + 1 && event.x > 0 && event.x < NB_COL_SIM + 1) {
						switch (item_actif) {
							case OBSTACLE :
								pthread_mutex_lock(&grille[event.y - 1][event.x - 1].mutex);
								if (grille[event.y - 1][event.x - 1].element == VIDE) {
									grille[event.y - 1][event.x - 1].element = OBSTACLE;
									mvwprintw(fen_sim, event.y - 1, event.x - 1, "#");
									wprintw(fen_msg, "Ajout d'un obstacle a la position %d %d\n", event.y - 1, event.x - 1);
								}
								wrefresh(fen_sim);
								wrefresh(fen_msg);
								pthread_mutex_unlock(&grille[event.y - 1][event.x - 1].mutex);
								break;
							case POISSON :
								pthread_mutex_lock(&grille[event.y - 1][event.x - 1].mutex);
								if (grille[event.y - 1][event.x - 1].element == VIDE) {
									i = 0;
									while (i < MAX_poissons && threads_poissons[i] != NULL)
										i++;
									if (i < MAX_poissons) {
										threads_poissons[i] = (pthread_t *) malloc(sizeof(pthread_t));
										grille[event.y - 1][event.x - 1].element = POISSON;
										grille[event.y - 1][event.x - 1].poisson = threads_poissons[i];
										coord = (coord_t *) malloc(sizeof(coord_t));
										coord->y = event.y - 1;
										coord->x = event.x - 1;
										pthread_create(threads_poissons[i], NULL, routine_poisson, (void *) coord);
										mvwprintw(fen_sim, event.y - 1, event.x - 1, "@");
										wprintw(fen_msg, "Ajout d'une poisson a la position %d %d\n", event.y - 1, event.x - 1);
									}
									else {
										wprintw(fen_msg, "Nombre maximum de poissons atteint\n");
									}
								}	*/				
								wrefresh(fen_sim);
								wrefresh(fen_msg);
								pthread_mutex_unlock(&grille[randomy - 1][randomx- 1].mutex);
								/*break;
						}
					}
				}
			break;*/
		}
	}

	delwin(fen_box_sim);
	delwin(fen_sim);
	delwin(fen_box_msg);
	delwin(fen_msg);
	delwin(fen_box_outils);
	delwin(fen_outils);
	simulation_stopper();
	ncurses_stopper();

	return 0;
}
