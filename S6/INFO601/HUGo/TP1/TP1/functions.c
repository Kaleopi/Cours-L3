#include "functions.h"
#include <math.h>
#include <stdio.h>

void ecrire(WINDOW *fenetre, const char* texte){
    wprintw(fenetre, texte);
    wrefresh(fenetre);
}

void nbFlocons(WINDOW *fenetre, int* nbFlocons){
    *nbFlocons = *nbFlocons + 1;
    wmove(fenetre, 0, 0);
    wprintw(fenetre, "Flocons : %d", *nbFlocons);
    wrefresh(fenetre);
}

void placerObstacle(WINDOW* fenetre, int nbObstacle, int * matrice){
	int i = 0;
	for(i = 0; i < nbObstacle; i++){
		int x = rand()%(SIMLONG), y = rand()%SIMHAUT;
		matrice[y * SIMLONG + x] = 1;
		wmove(fenetre, y, x);
		wattron(fenetre, COLOR_PAIR(1));
		ecrire(fenetre, " ");
		wattroff(fenetre, COLOR_PAIR(1));
	}
}

void creerFlocons(WINDOW* fenetre, int* col, int* ligne, int* mat){
	do{
		*col = (rand()%(SIMLONG));
		printf("%d", check(mat));
		*ligne = 0;
		wmove(fenetre, *ligne, *col);
		wattron(fenetre, COLOR_PAIR(2));
		ecrire(fenetre, " ");
		mat[SIMLONG * (*ligne) + (*col)] = 0;
		wattroff(fenetre, COLOR_PAIR(2));
	} while(check(mat) == 1 && mat[*col] != 0);
}

int check(int* mat){
	int i, j = 0;
	for(i = 0; i < SIMLONG - 1; i++){
		if(mat[i] == 0){
			j = 1;
		}
	}
	return j;
}

void updateFlocon(WINDOW* fenetreSim, WINDOW*fenetreInfo, WINDOW* fenetreEtat, int* col, int* ligne, int* nbFloc, int * matrice){
	int dir;
	if(*ligne < SIMHAUT-1){
		if(*ligne<SIMHAUT && matrice[SIMLONG * (*ligne + 1) + (*col)] == 0){/* en bas */
			matrice[SIMLONG * (*ligne) + (*col)] = 0;
			wmove(fenetreSim, *ligne, *col);
			wattron(fenetreSim, COLOR_PAIR(4));
			ecrire(fenetreSim, " ");
			wattroff(fenetreSim, COLOR_PAIR(4));
			*ligne=*ligne + 1;
			*col = *col;
			matrice[SIMLONG * (*ligne) + (*col)] = 2;
			wmove(fenetreSim, *ligne, *col);
			wattron(fenetreSim, COLOR_PAIR(2));
			ecrire(fenetreSim, " ");
			wattroff(fenetreSim, COLOR_PAIR(2));
		}else{ /* Soit à droite soit à gauche */
			if(*col < SIMLONG && *col > 0 && *ligne < SIMHAUT && matrice[SIMLONG * (*ligne) + (*col + 1)] == 0 && matrice[SIMLONG * (*ligne + 1) + (*col + 1)] == 0 && matrice[SIMLONG * (*ligne+1) + (*col - 1)] == 0 && matrice[SIMLONG * (*ligne) + (*col - 1)] == 0){
				dir =rand()%2;
				/*ecrire(fenetreEtat, "multiple ");*/
				if(dir==0){ /* là c'est la droite*/
					versDroite(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice);
				}else{
					/* là c'est la gauche*/
					versGauche(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice);
				}
			}else{
				if(*col > 0 && *ligne<SIMHAUT && matrice[SIMLONG * (*ligne+1) + (*col - 1)] == 0 && matrice[SIMLONG * (*ligne) + (*col - 1)] == 0){
					/* là c'est à gauche */
					versGauche(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice);
				}else if(*col < SIMLONG && *ligne < SIMHAUT && matrice[SIMLONG * (*ligne) + (*col + 1)] == 0 && matrice[SIMLONG * (*ligne + 1) + (*col + 1)] == 0){
						/* là c'est la droite */
						versDroite(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice);
				}else{
					/* là c'est bloquer */
					faitDesFlocon(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice, nbFloc);
				}
				
			}
		}
	} else {
		faitDesFlocon(fenetreSim, fenetreEtat, fenetreInfo, ligne, col, matrice, nbFloc);
	}
}

void faitDesFlocon(WINDOW* fenetreSim, WINDOW* fenetreEtat, WINDOW* fenetreInfo, int* ligne, int* col, int*matrice, int*nbFloc){
	creerFlocons(fenetreSim,col,ligne,matrice);
	nbFlocons(fenetreInfo,nbFloc);
	wmove(fenetreEtat, 0, 0);
	wprintw(fenetreEtat, "Nouveau flocon colonne : %d", *col);
	wrefresh(fenetreEtat);
}

void versDroite(WINDOW* fenetreSim, WINDOW* fenetreEtat, WINDOW* fenetreInfo, int* ligne, int* col, int*matrice){
	/*ecrire(fenetreEtat, "droite\n");*/
	wmove(fenetreSim, *ligne, *col);
	wattron(fenetreSim, COLOR_PAIR(4));
	ecrire(fenetreSim, " ");
	wattroff(fenetreSim, COLOR_PAIR(4));
	matrice[SIMLONG * (*ligne) + (*col)] = 0;
	*col = *col+1;
	*ligne=*ligne+1;
	matrice[SIMLONG * (*ligne) + (*col)] = 2;
	wmove(fenetreSim, *ligne, *col);
	wattron(fenetreSim, COLOR_PAIR(2));
	ecrire(fenetreSim, " ");
	wattroff(fenetreSim, COLOR_PAIR(2));
}

void versGauche(WINDOW* fenetreSim, WINDOW* fenetreEtat, WINDOW* fenetreInfo, int* ligne, int* col, int*matrice){
	/*ecrire(fenetreEtat, "gauche\n");*/
	wmove(fenetreSim, *ligne, *col);
	matrice[SIMLONG * (*ligne) + (*col)] = 0;
	wattron(fenetreSim, COLOR_PAIR(4));
	ecrire(fenetreSim, " ");
	wattroff(fenetreSim, COLOR_PAIR(4));
	*col = *col-1;
	*ligne=*ligne+1;
	matrice[SIMLONG * (*ligne) + (*col)] = 2;
	wmove(fenetreSim, *ligne, *col);
	wattron(fenetreSim, COLOR_PAIR(2));
	ecrire(fenetreSim, " ");
	wattroff(fenetreSim, COLOR_PAIR(2));
}
