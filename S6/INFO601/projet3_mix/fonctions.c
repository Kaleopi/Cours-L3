
#include <stdlib.h>		/* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h> /* Pour socket */
#include <arpa/inet.h>	/* Pour sockaddr_in, IPPROTO_TCP */
#include <stdio.h>		/* Pour perror */
#include <unistd.h>		/* Pour close */
#include <string.h>		/* Pour memset */
#include <time.h>
#include <errno.h>

#include "message.h"
#include "includes.h"
#include "fonctions.h"

pthread_t *threads_poissons[MAX_POISSONS]; /* Identifants des threads des poissons de la simulation*/
WINDOW *fen_sim;						   /* Fenetre de simulation partagee par les poissons*/
WINDOW *fen_msg;						   /* Fenetre de messages partagee par les poissons*/
case_t grille[NB_LIGNES_SIM][NB_COL_SIM];  /* Grille de simulation */

void both_send(grille_t *etang, int sock_one, int sock_two)
{
	one_send(etang, sock_one);
	one_send(etang, sock_two);
}

void one_send(grille_t *etang, int sockfd)
{
	if (write(sockfd, etang, sizeof(grille_t)) == -1)
	{
		perror("Erreur lors de l'envoi de la grille");
	}
}

void init_etang(grille_t *etang)
{
	int i, j;
	for (i = 0; i < NB_LIGNES_SIM; i++)
	{
		for (j = 0; j < NB_COL_SIM; j++)
		{
			etang->grille[i][j] = 0;
		}
	}
}

void afficher_etang(grille_t *etang)
{
	int i, j;
	for (i = 0; i < NB_LIGNES_SIM; i++)
	{
		for (j = 0; j < NB_COL_SIM; j++)
		{
			printf("%d", etang->grille[i][j]);
		}
		printf("\n");
	}
}

void init_sim(WINDOW *w, grille_t *etang)
{
	int i, j, val;
	for (i = 0; i < NB_LIGNES_SIM; i++)
	{
		for (j = 0; j < NB_COL_SIM; j++)
		{
			val = etang->grille[i][j];
			if (val == 0)
			{
				val = 4;
			}
			wattron(w, COLOR_PAIR(val));
			mvwprintw(w, i, j, " ", val);
			wrefresh(w);
			wattroff(w, COLOR_PAIR(val));
		}
	}
}

void ncurses_initialiser()
{
	initscr();						  /* Demarre le mode ncurses */
	cbreak();						  /* Pour les saisies clavier (desac. mise en buffer) */
	noecho();						  /* Desactive l'affichage des caracteres saisis */
	keypad(stdscr, TRUE);			  /* Active les touches specifiques */
	refresh();						  /* Met a jour l'affichage */
	curs_set(FALSE);				  /* Masque le curseur */
	mousemask(BUTTON1_CLICKED, NULL); /* Active le clic gauche de la souris*/
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW); /*poisson*/
	init_pair(4, COLOR_BLACK, COLOR_BLUE);	 /*eau*/
	wbkgd(fen_sim, COLOR_PAIR(-1));
}

void ncurses_stopper()
{
	endwin();
}

void simulation_initialiser()
{
	int i, j;

	for (i = 0; i < MAX_POISSONS; i++) /* Au depart il n'y a aucune poisson dans la simulation */
		threads_poissons[i] = NULL;

	for (i = 0; i < NB_LIGNES_SIM; i++)
	{ /* Initialisation des cases de la simulation */
		for (j = 0; j < NB_COL_SIM; j++)
		{
			grille[i][j].element = VIDE;
			grille[i][j].poisson = NULL;
			pthread_mutex_init(&grille[i][j].mutex, NULL);
		}
	}
}

void simulation_stopper()
{
	int i;

	for (i = 0; i < MAX_POISSONS; i++)
	{
		if (threads_poissons[i] != NULL)
		{
			pthread_cancel(*threads_poissons[i]);
			threads_poissons[i] = NULL;
		}
	}
}

WINDOW *creer_fenetre_box_sim()
{
	/*Creation de la fenetre de contour de la fenetre de simulation */

	WINDOW *fen_box_sim;

	fen_box_sim = newwin(NB_LIGNES_SIM + 2, NB_COL_SIM + 2, 0, 0);
	box(fen_box_sim, 0, 0);
	mvwprintw(fen_box_sim, 0, (NB_COL_SIM + 2) / 2 - 5, "SIMULATION");
	wrefresh(fen_box_sim);

	return fen_box_sim;
}

WINDOW *creer_fenetre_sim()
{
	/* Creation de la fenetre de simulation dans la fenetre de contour */
	/* La simulation est affichee dans cette fenetre */

	WINDOW *fen_sim;

	fen_sim = newwin(NB_LIGNES_SIM, NB_COL_SIM, 1, 1);
	wrefresh(fen_sim);
	return fen_sim;
}

WINDOW *creer_fenetre_box_msg()
{
	/* Creation de la fenetre de contour de la fenetre de messages */

	WINDOW *fen_box_msg;

	fen_box_msg = newwin(NB_LIGNES_MSG + 2, NB_COL_MSG + 2, 0, NB_COL_SIM + 2);
	box(fen_box_msg, 0, 0);
	mvwprintw(fen_box_msg, 0, (NB_COL_MSG + 2) / 2 - 4, "MESSAGES");
	wrefresh(fen_box_msg);

	return fen_box_msg;
}

WINDOW *creer_fenetre_msg()
{
	/* Creation de la fenetre de messages dans la fenetre de contour */
	/* Les messages indicatifs des evenements de la simulation et de l'interface */
	/* utilisateur sont affiches dans cete fenetre */

	WINDOW *fen_msg;
	fen_msg = newwin(NB_LIGNES_MSG, NB_COL_MSG, 1, NB_COL_SIM + 3);
	scrollok(fen_msg, TRUE);

	return fen_msg;
}

WINDOW *creer_fenetre_box_outils()
{
	/* Fenetre de contour de la fenetre des outils */

	WINDOW *fen_box_outils;

	fen_box_outils = newwin(NB_LIGNES_OUTILS + 2, NB_COL_OUTILS + 2, NB_LIGNES_MSG + 2, NB_COL_SIM + 2);
	box(fen_box_outils, 0, 0);
	mvwprintw(fen_box_outils, 0, (NB_COL_OUTILS + 2) / 2 - 3, "OUTILS");
	wrefresh(fen_box_outils);

	return fen_box_outils;
}

WINDOW *creer_fenetre_outils()
{
	/* Creation de la fenetre des outils a l'interieur de la fenetre de contour */
	/* Les outils dans cette fenetre sont clickables, l'outil actif etant indique par un X */

	WINDOW *fen_outils;

	fen_outils = newwin(NB_LIGNES_OUTILS, NB_COL_OUTILS, NB_LIGNES_MSG + 3, NB_COL_SIM + 3);
	mvwprintw(fen_outils, 0, 3, "# : Hammecons\n");
	mvwprintw(fen_outils, 1, 3, "@ : Poisson");
	mvwprintw(fen_outils, 0, 1, "X");
	wrefresh(fen_outils);

	return fen_outils;
}

void *routine_poisson(void *arg)
{
	int j;
	coord_t *coord = (coord_t *)arg;
	srand(time(NULL));

	pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
	while (1)
	{
		int pos = rand() % 4;
		switch (pos)
		{
		case 0:
			if (coord->y + 1 < NB_LIGNES_SIM)
			{
				if (grille[coord->y + 1][coord->x].element == VIDE)
				{
					grille[coord->y + 1][coord->x].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->y++;
				}
				/*else if(grille[coord->y+1][coord->x].element==HAMMECONS){
						grille[coord->y+1][coord->x].element = VIDE;
						mvwprintw(fen_sim, coord->y+1, coord->x, " ");
					}*/
				else if (grille[coord->y + 1][coord->x].element == POISSON)
				{
					grille[coord->y + 1][coord->x].element = VIDE;
					pthread_mutex_lock(&grille[coord->y + 1][coord->x].mutex);
					pthread_cancel((pthread_t)grille[coord->y + 1][coord->x].poisson);
					for (j = 0; j < MAX_POISSONS; j++)
					{
						if (grille[coord->y + 1][coord->x].poisson == threads_poissons[j])
						{
							pthread_cancel((pthread_t)threads_poissons[j]);
						}
					}
					pthread_mutex_unlock(&grille[coord->y + 1][coord->x].mutex);
				}
			}
			break;
		case 1:
			if (coord->x + 1 < NB_COL_SIM)
			{
				if (grille[coord->y][coord->x + 1].element == VIDE)
				{
					grille[coord->y][coord->x + 1].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->x++;
				}
				/*else if(grille[coord->y][coord->x+1].element==HAMMECONS){
						grille[coord->y][coord->x+1].element = VIDE;
						mvwprintw(fen_sim, coord->y, coord->x+1, " ");
					}*/
				else if (grille[coord->y][coord->x + 1].element == POISSON)
				{
					grille[coord->y][coord->x + 1].element = VIDE;
					pthread_mutex_lock(&grille[coord->y][coord->x + 1].mutex);
					pthread_cancel((pthread_t)grille[coord->y][coord->x + 1].poisson);
					for (j = 0; j < MAX_POISSONS; j++)
					{
						if (grille[coord->y][coord->x + 1].poisson == threads_poissons[j])
						{
							pthread_mutex_lock(&grille[coord->y + 1][coord->x].mutex);
							pthread_cancel((pthread_t)threads_poissons[j]);
						}
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x + 1].mutex);
				}
			}
			break;
		case 2:
			if (coord->y - 1 > 0)
			{
				if (grille[coord->y - 1][coord->x].element == VIDE)
				{
					grille[coord->y - 1][coord->x].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->y--;
				}
				/*else if(grille[coord->y-1][coord->x].element==HAMMECONS){
						grille[coord->y-1][coord->x].element = VIDE;
						mvwprintw(fen_sim, coord->y-1, coord->x, " ");
					}*/
				else if (grille[coord->y - 1][coord->x].element == POISSON)
				{
					grille[coord->y - 1][coord->x].element = VIDE;
					pthread_mutex_lock(&grille[coord->y - 1][coord->x].mutex);
					pthread_cancel((pthread_t)grille[coord->y - 1][coord->x].poisson);
					for (j = 0; j < MAX_POISSONS; j++)
					{
						if (grille[coord->y - 1][coord->x].poisson == threads_poissons[j])
						{
							pthread_cancel((pthread_t)threads_poissons[j]);
						}
					}
					pthread_mutex_unlock(&grille[coord->y - 1][coord->x].mutex);
				}
			}
			break;
		case 3:
			if (coord->x - 1 > 0)
			{
				if (grille[coord->y][coord->x - 1].element == VIDE)
				{
					grille[coord->y][coord->x - 1].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->x--;
				}
				/*else if(grille[coord->y][coord->x-1].element==HAMMECONS){
						grille[coord->y][coord->x-1].element = VIDE;
						mvwprintw(fen_sim, coord->y, coord->x-1, " ");
					}*/
				else if (grille[coord->y][coord->x - 1].element == POISSON)
				{
					grille[coord->y][coord->x - 1].element = VIDE;
					pthread_mutex_lock(&grille[coord->y][coord->x - 1].mutex);
					pthread_cancel((pthread_t)grille[coord->y][coord->x - 1].poisson);
					for (j = 0; j < MAX_POISSONS; j++)
					{
						if (grille[coord->y][coord->x - 1].poisson == threads_poissons[j])
						{
							pthread_cancel((pthread_t)threads_poissons[j]);
						}
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x - 1].mutex);
				}
			}
			break;
		}

		wrefresh(fen_sim);
		sleep(1);
	}
	pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);

	free(coord);
	return NULL;
}

poisson_t creer_poisson(int id, int posx, int posy)
{
	int random;
	poisson_t *poisson;

poisson = (poisson_t *)malloc(sizeof(poisson_t));
	random = rand() % 100;
	if (random < 15)
	{
		poisson->val = 3;
	}
	if (random > 15 && random < 40)
	{
		poisson->val = 2;
	}
	else
	{
		poisson->val = 1;
	}
	poisson->id = id;
	poisson->posx = posx;
	poisson->posy = posy;
	return *poisson;
}

void generer_poisson(grille_t *etang)
{
	int randomx, randomy;
	int nb_poissons;
	coord_t *coord;
	nb_poissons=0;
		while (nb_poissons < MAX_POISSONS-2)
		{	
			randomx = rand() % NB_COL_SIM;
			randomy = rand() % NB_LIGNES_SIM;
			if (etang->grille[randomy][randomx] ==0)
				
				{

				nb_poissons++;

				threads_poissons[nb_poissons] = (pthread_t *)malloc(sizeof(pthread_t));
				grille[randomy][randomx].element = POISSON;
				grille[randomy][randomx].poisson = threads_poissons[nb_poissons];
				coord = (coord_t *)malloc(sizeof(coord_t));
				coord->y = randomy;
				coord->x = randomx;
				pthread_create(threads_poissons[nb_poissons], NULL, routine_poisson, (void *)coord);
				mvwprintw(fen_sim, randomy, randomx, "@");
				/* wprintw(fen_msg, "Ajout d'une poisson a la position %d %d\n", randomy - 1, randomx - 1);*/

				pthread_mutex_unlock(&grille[randomy][randomx].mutex);

				sleep(3);
				wrefresh(fen_sim);
				wprintw(fen_msg, "%d %d\n", randomy, randomx);
				}
			}
	
}

void simulation()
{
	WINDOW *fen_box_sim, *fen_box_msg, *fen_box_outils, *fen_outils;
	MEVENT event;
	int ch, i, item_actif = HAMMECONS;
	/*int randomx, randomy;*/
		int tempx = 0, tempy = 0;
	int nb_hammecon = 0;
	/*int nb_poissons = 0;*/
	coord_t *coord;
	srand(time(NULL));

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

	while ((ch = getch()) != KEY_F(2))
	{

		switch (ch)
		{
		case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				/* wprintw(fen_msg, "Clic a la position %d %d de l'ecran\n", event.y, event.x);*/
				wrefresh(fen_msg);
				if (event.y == 32 && event.x >= 82 && event.x <= 98)
				{
					item_actif = HAMMECONS;
					mvwprintw(fen_outils, 0, 1, "X");
					mvwprintw(fen_outils, 1, 1, " ");
					wrefresh(fen_outils);
					wprintw(fen_msg, "Outil Hammecon active\n");
					wrefresh(fen_msg);
				}
				else if (event.y == 33 && event.x >= 82 && event.x <= 98)
				{
					item_actif = POISSON;
					mvwprintw(fen_outils, 0, 1, " ");
					mvwprintw(fen_outils, 1, 1, "X");
					wrefresh(fen_outils);
					wprintw(fen_msg, "Outil poisson active\n");
					wrefresh(fen_msg);
				}
				else if (event.y > 0 && event.y < NB_LIGNES_SIM + 1 && event.x > 0 && event.x < NB_COL_SIM + 1)
				{
					switch (item_actif)
					{
					case HAMMECONS:

						if (nb_hammecon < MAX_HAMMECONS)
						{
							if (grille[event.y - 1][event.x - 1].element == VIDE)
							{
								grille[event.y - 1][event.x - 1].element = HAMMECONS;
								mvwprintw(fen_sim, event.y - 1, event.x - 1, "#");
								tempx = event.x - 1;
								tempy = event.y - 1;
								nb_hammecon++;
								wprintw(fen_msg, "Ajout d'un Hammecon ");
							}
						}
						else
						{
							grille[tempy][tempx].element = VIDE;
							mvwprintw(fen_sim, tempy, tempx, " ");
							tempx = event.x - 1;
							tempy = event.y - 1;
							nb_hammecon = 0;
							wprintw(fen_msg, "retrait ");
						}

						wrefresh(fen_sim);
						wrefresh(fen_msg);
						pthread_mutex_unlock(&grille[event.y - 1][event.x - 1].mutex);

						break;
					case POISSON:
						pthread_mutex_lock(&grille[event.y - 1][event.x - 1].mutex);
						if (grille[event.y - 1][event.x - 1].element == VIDE)
						{
							i = 0;
							while (i < MAX_POISSONS && threads_poissons[i] != NULL)
								i++;
							if (i < MAX_POISSONS)
							{
								threads_poissons[i] = (pthread_t *)malloc(sizeof(pthread_t));
								grille[event.y - 1][event.x - 1].element = POISSON;
								grille[event.y - 1][event.x - 1].poisson = threads_poissons[i];
								coord = (coord_t *)malloc(sizeof(coord_t));
								coord->y = event.y - 1;
								coord->x = event.x - 1;
								pthread_create(threads_poissons[i], NULL, routine_poisson, (void *)coord);
								mvwprintw(fen_sim, event.y - 1, event.x - 1, "@");
								/* wprintw(fen_msg, "Ajout d'une poisson a la position %d %d\n", event.y - 1, event.x - 1);*/
							}
							else
							{
								/*wprintw(fen_msg, "Nombre maximum de poissons atteint\n");*/
							}
						}
						wrefresh(fen_sim);
						wrefresh(fen_msg);
						pthread_mutex_unlock(&grille[event.y - 1][event.x - 1].mutex);
						break;
					}
				}
			}
			break;
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

	/*return 0;*/
}
