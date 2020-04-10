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
int nb_poissons=0;

 
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

void update_sim(WINDOW *w, grille_t *etang){
	int i,j;
	for(i=0 ; i<NB_LIGNES_SIM ; i++){
		for(j=0 ; j<NB_COL_SIM ; j++){
			switch(etang->grille[i][j]){
				case VIDE:
					wattron(w, COLOR_PAIR(4));
					mvwprintw(w, i, j, " ", 4);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(4));
					break;
				case POISSON:
					wattron(w, COLOR_PAIR(1));
					mvwprintw(w, i, j, " ", 1);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(1));
				break;
				case POISSONVAL1:
					wattron(w, COLOR_PAIR(1));
					mvwprintw(w, i, j, "1", 1);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(1));
				break;
				case POISSONVAL2:
					wattron(w, COLOR_PAIR(1));
					mvwprintw(w, i, j, "2", 1);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(1));
				break;
				case POISSONVAL3:
					wattron(w, COLOR_PAIR(1));
					mvwprintw(w, i, j, "3", 1);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(1));
				break;
				case HAMMECONS:
					wattron(w, COLOR_PAIR(4));
					mvwprintw(w, i, j, "*", 4);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(4));
				break;
				case PNEU:
					wattron(w, COLOR_PAIR(2));
					mvwprintw(w, i, j, " ", 2);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(2));
				break;
				case DYNA:
					wattron(w, COLOR_PAIR(3));
					mvwprintw(w, i, j, " ", 3);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(3));
				break;
				default:
					wattron(w, COLOR_PAIR(4));
					mvwprintw(w, i, j, " ", 4);
					wrefresh(w);
					wattroff(w, COLOR_PAIR(4));
				break;
			}
			refresh();
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
	init_pair(2, COLOR_WHITE, COLOR_BLACK);/*peuneu*/
	init_pair(3, COLOR_WHITE, COLOR_RED);/*dyna*/
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	 /*eau*/
	init_pair(5, COLOR_WHITE, COLOR_GREEN);/*requin*/
	wbkgd(stdscr, COLOR_PAIR(2));
	refresh();
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

	WINDOW *fen;

	fen = newwin(NB_LIGNES_SIM + 2, NB_COL_SIM + 2, 0, 0);
	box(fen, 0, 0);
	mvwprintw(fen, 0, (NB_COL_SIM + 2) / 2 - 5, "SIMULATION");
	wrefresh(fen);

	return fen;
}

WINDOW *creer_fenetre_sim()
{
	/* Creation de la fenetre de simulation dans la fenetre de contour */
	/* La simulation est affichee dans cette fenetre */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_SIM, NB_COL_SIM, 1, 1);
	wrefresh(fen);
	return fen;
}

WINDOW *creer_fenetre_box_msg()
{
	/* Creation de la fenetre de contour de la fenetre de messages */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_MSG + 2, NB_COL_MSG + 2, NB_LIGNES_POINTS+NB_LIGNES_OUTILS+4, NB_COL_SIM + 2);
	box(fen, 0, 0);
	mvwprintw(fen, 0, (NB_COL_MSG + 2) / 2 - 4, "DEBUG");
	wrefresh(fen);

	return fen;
}

WINDOW *creer_fenetre_msg()
{
	/* Creation de la fenetre de messages dans la fenetre de contour */
	/* Les messages indicatifs des evenements de la simulation et de l'interface */
	/* utilisateur sont affiches dans cete fenetre */

	WINDOW *fen;
	fen = newwin(NB_LIGNES_MSG, NB_COL_MSG, NB_LIGNES_POINTS+NB_LIGNES_OUTILS+5, NB_COL_SIM + 3);
	scrollok(fen, TRUE);

	return fen;
}

WINDOW *creer_fenetre_box_outils()
{
	/* Fenetre de contour de la fenetre des outils */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_OUTILS + 2, NB_COL_OUTILS + 2, NB_LIGNES_POINTS + 2, NB_COL_SIM + 2);
	box(fen, 0, 0);
	mvwprintw(fen, 0, (NB_COL_OUTILS + 2) / 2 - 3, "OUTILS");
	wrefresh(fen);

	return fen;
}

WINDOW *creer_fenetre_outils()
{
	/* Creation de la fenetre des outils a l'interieur de la fenetre de contour */
	/* Les outils dans cette fenetre sont clickables, l'outil actif etant indique par un X */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_OUTILS, NB_COL_OUTILS, NB_LIGNES_POINTS + 3, NB_COL_SIM + 3);
	mvwprintw(fen, 0, 1, " : Hammecon\n");
	mvwprintw(fen, 1, 1, " : Pneu (150)\n");
	mvwprintw(fen, 2, 1, " : Dynamite (200)\n");
	mvwprintw(fen, 3, 1, " : Requin (300)\n");
	mvwprintw(fen, 4, 1, " : Furtif (500)\n");
	mvwprintw(fen, 0, 0, "X");
	wrefresh(fen);

	return fen;
}

WINDOW *creer_fenetre_box_points()
{
	/* Fenetre de contour de la fenetre des outils */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_POINTS + 2, NB_COL_POINTS + 2, 0, NB_COL_SIM + 2);
	box(fen, 0, 0);
	mvwprintw(fen, 0, (NB_COL_OUTILS + 2) / 2 - 3, "POINTS");
	wrefresh(fen);

	return fen;
}

WINDOW *creer_fenetre_points()
{
	/* Creation de la fenetre des outils a l'interieur de la fenetre de contour */
	/* Les outils dans cette fenetre sont clickables, l'outil actif etant indique par un X */

	WINDOW *fen;

	fen = newwin(NB_LIGNES_POINTS, NB_COL_POINTS, 1, NB_COL_SIM + 3);
	mvwprintw(fen, 0, 0, "Points : x");
	mvwprintw(fen, 1, 0, "Poireaus : x");
	wrefresh(fen);

	return fen;
}
/*thread*/
	/*routine des poissons*/
void *routine_poisson(void *arg)
{
	
	
	/*int j;*/
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
					coord->etang->grille[coord->y + 1][coord->x]= coord->poisson->val;
					coord->etang->grille[coord->y ][coord->x]= VIDE;
					grille[coord->y + 1][coord->x].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->y++;
				}

			}
			break;
		case 1:
			if (coord->x + 1 < NB_COL_SIM)
			{
				if (grille[coord->y][coord->x + 1].element == VIDE)
				{
						coord->etang->grille[coord->y][coord->x+1]= coord->poisson->val;
					coord->etang->grille[coord->y ][coord->x]= VIDE;
					grille[coord->y][coord->x + 1].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->x++;
				}

			}
			break;
		case 2:
			if (coord->y - 1 > 0)
			{
				if (grille[coord->y - 1][coord->x].element == VIDE)
				{
						coord->etang->grille[coord->y -1 ][coord->x]= coord->poisson->val;
					coord->etang->grille[coord->y ][coord->x]= VIDE;
					grille[coord->y - 1][coord->x].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->y--;
				}

			}
			break;
		case 3:
			if (coord->x - 1 > 0)
			{
				if (grille[coord->y][coord->x - 1].element == VIDE)
				{
					coord->etang->grille[coord->y ][coord->x-1]= coord->poisson->val;
					coord->etang->grille[coord->y ][coord->x]= VIDE;
					grille[coord->y][coord->x - 1].element = POISSON;
					grille[coord->y][coord->x].element = VIDE;
					coord->x--;
				}
			}
			break;
		}
	sleep(1);
		wrefresh(fen_sim);
		
	}
	pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
	update_sim(fen_sim,coord->etang);
	free(coord);
	return NULL;
}
/*recupere la grille*/
void recuperation(grille_t *etang){
	int i,j;
	for(i=0;i<NB_LIGNES_SIM;i++){
		for( j=0;j<NB_COL_SIM;j++){
			etang->grille[i][j]=grille[i][j].element;
		}
	}
}
/*recupere l'etang*/
void recuperation_grille(grille_t *etang){
	int i,j;
	for(i=0;i<NB_LIGNES_SIM;i++){
		for( j=0;j<NB_COL_SIM;j++){
			grille[i][j].element=etang->grille[i][j];
		}
	}
}
/*crée les stats des poissons*/
void creer_poisson(int id, int posx, int posy,poisson_t *poisson,int random,int nb_poissons)
{

	
	
				if (random < 20)
				{
					poisson[nb_poissons].val = 300;
				}
				if (random > 20&& random <40 )
				{
					poisson[nb_poissons].val = 200;
				}
				if(random>40&&random<100)
				{
					poisson[nb_poissons].val = 100;
				}
	
	poisson[nb_poissons].id = nb_poissons;
	poisson[nb_poissons].posx = posx;
	poisson[nb_poissons].posy = posy;
	

}
/*thread*/
	/*creer les thread etles poissons*/
void generer_poisson(grille_t *etang)
{
	int randomx, randomy;
	int randomP;
	
	poisson_t *poisson;
	coord_t *coord;
	poisson = (poisson_t *)malloc(sizeof(poisson_t)*MAX_POISSONS);
	
		while (nb_poissons < MAX_POISSONS)
		{
			randomx = rand() % NB_COL_SIM/1.5+1;
			randomy = rand() % NB_LIGNES_SIM/1.5+1;
			srand(time(NULL)+randomx*randomy*randomx*randomx);
			if (etang->grille[randomy][randomx] ==0)

				{

				nb_poissons++;
				randomP = rand() % 100;
				
				creer_poisson(nb_poissons,randomx,randomy,poisson, randomP,nb_poissons);
				threads_poissons[nb_poissons] = (pthread_t *)malloc(sizeof(pthread_t));
				grille[randomy][randomx].element = POISSON;
				
			

				etang->grille[randomy][randomx]=poisson->val;
				grille[randomy][randomx].poisson = threads_poissons[nb_poissons];
				coord = (coord_t *)malloc(sizeof(coord_t));
				coord->y = randomy;
				coord->x = randomx;
				coord->etang=etang;
				
				coord->poisson=&poisson[nb_poissons];
				pthread_create(threads_poissons[nb_poissons], NULL, routine_poisson, (void *)coord);
				/* wprintw(fen_msg, "Ajout d'une poisson a la position %d %d\n", randomy - 1, randomx - 1);*/

				pthread_mutex_unlock(&grille[randomy][randomx].mutex);

				
				wrefresh(fen_sim);
				wprintw(fen_msg, "%d %d\n", randomy, randomx);
			
				}
			}
			sleep(0.75);

}
/*change d'items*/
int switchUp(int item_actif,WINDOW *fen){
	switch(item_actif){
		case HAMMECONS:
			mvwprintw(fen, 0, 0, " ");
			mvwprintw(fen, 4, 0, "X");
			return FURTIF;
		break;
		case PNEU:
			mvwprintw(fen, 1, 0, " ");
			mvwprintw(fen, 0, 0, "X");
			return HAMMECONS;
		break;
		case DYNA:
			mvwprintw(fen, 2, 0, " ");
			mvwprintw(fen, 1, 0, "X");
			return PNEU;
		break;
		case FURTIF:
			mvwprintw(fen, 4, 0, " ");
			mvwprintw(fen, 3, 0, "X");
			return REQUIN;
		break;
		case REQUIN:
			mvwprintw(fen, 3, 0, " ");
			mvwprintw(fen, 2, 0, "X");
			return DYNA;
	}
	return item_actif;
}
/*change d'items*/
int  switchDown(int item_actif,WINDOW *fen){
		switch(item_actif){

		case HAMMECONS:
			mvwprintw(fen, 0, 0, " ");
			mvwprintw(fen, 1, 0, "X");
			return PNEU;
		break;
		case PNEU:
			mvwprintw(fen, 1, 0, " ");
			mvwprintw(fen, 2, 0, "X");
			return DYNA;
		break;
		case DYNA:
			mvwprintw(fen, 2, 0, " ");
			mvwprintw(fen, 3, 0, "X");
			return REQUIN;
		break;
		case REQUIN:
			mvwprintw(fen, 3, 0, " ");
			mvwprintw(fen, 4, 0, "X");
			return FURTIF;
		break;
		case FURTIF:
			mvwprintw(fen, 4, 0, " ");
			mvwprintw(fen, 0, 0, "X");
			return HAMMECONS;
			break;
	}
	return item_actif;
}
/*fusionne les étang cote serveur */
void fusion_etang(grille_t *etang,grille_t* etangj1,grille_t *etangj2){
	int i=0,j=0;
		for(i=0;i<20;i++){
				for (j=0;j<40;j++){
						if(etang->grille[i][j]==0){
										if (etangj1->grille[i][j]==0){
												etang->grille[i][j]=etangj2->grille[i][j];
												}else{
													etang->grille[i][j]=etangj1->grille[i][j];
												}
											}
					}
	}
}
/*lance un items*/
void lancerTruc(int item_actif,WINDOW *fen_sim,WINDOW *fen_msg,int* tab, grille_t* etang,int sockfd){
	MEVENT event;
	int nb_hammecon=tab[0];
	int tempx = tab[1], tempy = tab[2];
	if (getmouse(&event) == OK)
			{
				wprintw(fen_msg, "Clic a la position %d %d de l'ecran\n", event.y, event.x);
				wrefresh(fen_msg);

				if (event.y > 0 && event.y < NB_LIGNES_SIM + 1 && event.x > 0 && event.x < NB_COL_SIM + 1)
				{
					switch (item_actif)
					{
					case HAMMECONS:

						if (nb_hammecon < MAX_HAMMECONS)
						{
							if (etang->grille[event.y - 1][event.x - 1] == VIDE)
							{
								etang->grille[event.y - 1][event.x - 1] = HAMMECONS;
								wattron(fen_sim, COLOR_PAIR(4));
								mvwprintw(fen_sim, event.y - 1, event.x - 1, "*");
								wattroff(fen_sim, COLOR_PAIR(4));
								tempx = event.x - 1;
								tempy = event.y - 1;
								nb_hammecon++;
								wprintw(fen_msg, "Ajout d'un Hammecon \n");
							}
						}
						else
						{
							etang->grille[tempy][tempx] = VIDE;
							wattron(fen_sim, COLOR_PAIR(4));
							mvwprintw(fen_sim, tempy, tempx, " ");
							wattroff(fen_sim, COLOR_PAIR(4));
							tempx = event.x - 1;
							tempy = event.y - 1;
							nb_hammecon = 0;
							wprintw(fen_msg, "retrait\n");
						}

						wrefresh(fen_sim);
						wrefresh(fen_msg);
						/*pthread_mutex_unlock(&grille[event.y - 1][event.x - 1].element ,mutex);*/

					break;

				case PNEU:
							if ((etang->grille[event.y - 1][event.x - 1] == VIDE)
								&& (etang->grille[event.y  ][event.x - 1] == VIDE)
								&&(etang->grille[event.y +1][event.x - 1] == VIDE) )
							{
								etang->grille[event.y - 1][event.x - 1] = PNEU;
								etang->grille[event.y ][event.x - 1] = PNEU;
								etang->grille[event.y +1][event.x - 1] = PNEU;
								wattron(fen_sim, COLOR_PAIR(2));
								mvwprintw(fen_sim, event.y - 1, event.x - 1, " ");
								mvwprintw(fen_sim, event.y , event.x - 1, " ");
								mvwprintw(fen_sim, event.y +1 , event.x - 1, " ");
								wattroff(fen_sim, COLOR_PAIR(2));
								wprintw(fen_msg, "Ajout d'un pneu \n");
							}
					break;
				case DYNA:
								etang->grille[event.y-3 ][event.x - 3] = VIDE;
								etang->grille[event.y - 2][event.x - 3] = VIDE;
								etang->grille[event.y -1][event.x - 3] = VIDE;
								etang->grille[event.y ][event.x - 3] = VIDE;
								etang->grille[event.y +1][event.x - 3]=VIDE;

								etang->grille[event.y-3 ][event.x - 2] = VIDE;
								etang->grille[event.y - 2][event.x - 2] = VIDE;
								etang->grille[event.y -1][event.x - 2] = VIDE;
								etang->grille[event.y ][event.x - 2] = VIDE;
								etang->grille[event.y +1][event.x - 2] = VIDE;

								etang->grille[event.y-3 ][event.x - 1] = VIDE;
								etang->grille[event.y - 2][event.x - 1] = VIDE;
								etang->grille[event.y -1][event.x - 1] = VIDE;
								etang->grille[event.y ][event.x - 1] = VIDE;
								etang->grille[event.y +1][event.x - 1]=VIDE;

								etang->grille[event.y-3 ][event.x] = VIDE;
								etang->grille[event.y - 2][event.x] = VIDE;
								etang->grille[event.y -1][event.x] = VIDE;
								etang->grille[event.y ][event.x] = VIDE;
								etang->grille[event.y +1][event.x ]=VIDE;

								etang->grille[event.y-3 ][event.x+1] = VIDE;
								etang->grille[event.y - 2][event.x+1] = VIDE;
								etang->grille[event.y -1][event.x+1] = VIDE;
								etang->grille[event.y ][event.x+1] = VIDE;
								etang->grille[event.y +1][event.x+1 ]=VIDE;



								wattron(fen_sim, COLOR_PAIR(3));
								mvwprintw(fen_sim, event.y -3, event.x - 3, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 3, " ");
								mvwprintw(fen_sim, event.y -1, event.x -3, " ");
								mvwprintw(fen_sim, event.y , event.x - 3, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 3, " ");

								mvwprintw(fen_sim, event.y -3, event.x - 2, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 2, " ");
								mvwprintw(fen_sim, event.y -1, event.x -2, " ");
								mvwprintw(fen_sim, event.y , event.x - 2, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 2, " ");

								mvwprintw(fen_sim, event.y -3, event.x - 1, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 1, " ");
								mvwprintw(fen_sim, event.y -1, event.x -1, " ");
								mvwprintw(fen_sim, event.y , event.x - 1, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 1, " ");

								mvwprintw(fen_sim, event.y -3, event.x , " ");
								mvwprintw(fen_sim, event.y - 2, event.x , " ");
								mvwprintw(fen_sim, event.y -1, event.x , " ");
								mvwprintw(fen_sim, event.y , event.x , " ");
								mvwprintw(fen_sim, event.y + 1, event.x , " ");

								mvwprintw(fen_sim, event.y -3, event.x +1, " ");
								mvwprintw(fen_sim, event.y - 2, event.x +1, " ");
								mvwprintw(fen_sim, event.y -1, event.x +1, " ");
								mvwprintw(fen_sim, event.y , event.x +1, " ");
								mvwprintw(fen_sim, event.y + 1, event.x +1, " ");
								wattroff(fen_sim, COLOR_PAIR(3));


								wrefresh(fen_sim);
								sleep(1);




								wprintw(fen_msg, "EXPLOSION \n");
								wattron(fen_sim, COLOR_PAIR(4));
								mvwprintw(fen_sim, event.y -3, event.x - 3, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 3, " ");
								mvwprintw(fen_sim, event.y -1, event.x -3, " ");
								mvwprintw(fen_sim, event.y , event.x - 3, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 3, " ");

								mvwprintw(fen_sim, event.y -3, event.x - 2, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 2, " ");
								mvwprintw(fen_sim, event.y -1, event.x -2, " ");
								mvwprintw(fen_sim, event.y , event.x - 2, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 2, " ");

								mvwprintw(fen_sim, event.y -3, event.x - 1, " ");
								mvwprintw(fen_sim, event.y - 2, event.x - 1, " ");
								mvwprintw(fen_sim, event.y -1, event.x -1, " ");
								mvwprintw(fen_sim, event.y , event.x - 1, " ");
								mvwprintw(fen_sim, event.y + 1, event.x - 1, " ");

								mvwprintw(fen_sim, event.y -3, event.x , " ");
								mvwprintw(fen_sim, event.y - 2, event.x , " ");
								mvwprintw(fen_sim, event.y -1, event.x , " ");
								mvwprintw(fen_sim, event.y , event.x , " ");
								mvwprintw(fen_sim, event.y + 1, event.x , " ");

								mvwprintw(fen_sim, event.y -3, event.x +1, " ");
								mvwprintw(fen_sim, event.y - 2, event.x +1, " ");
								mvwprintw(fen_sim, event.y -1, event.x +1, " ");
								mvwprintw(fen_sim, event.y , event.x +1, " ");
								mvwprintw(fen_sim, event.y + 1, event.x +1, " ");
								wattroff(fen_sim, COLOR_PAIR(4));
				}
			}
			}
			update_sim(fen_sim,etang);
 
			tab[0]=nb_hammecon;
			tab[2]=tempy;
			tab[1]=tempx;
			/*return tab;*/
}
