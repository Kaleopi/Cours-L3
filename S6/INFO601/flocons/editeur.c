#include "ncurses.h"
#include "functions.h"
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */
#include <stdlib.h>     /* Pour EXIT_FAILURE */
#include <time.h>
#include "define.h"

int main(int argc, char* argv[]){
    /* Initialisation de ncurses */
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs(); 
    wbkgd(stdscr, COLOR_PAIR(4));
    refresh();

	/* Vérification des dimensions du terminal */
  	if((COLS < POSX + COLONNE) || (LINES < POSY + HAUTEUR)) {
    	ncurses_stopper();
    	fprintf(stderr, 
        	"Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
            COLS, LINES, POSX + COLONNE, POSY + HAUTEUR);
      exit(EXIT_FAILURE);
    }
    WINDOW *info, *sous_info, *simulation, *sous_simulation, *etat, *sous_etat;
    srand(time(NULL));
    int i=0, taille=LIGNE*COLONNE, sourisX, sourisY, bouton;
    int *mat;
    mat = (int*)malloc(sizeof(int)*taille);
    for(i=0 ; i<taille ; i++){
        mat[i]=0;
    }

    /*Initialisation des fenêtres principales*/
	info = newwin(H_INFO+2, COLONNE+30, POSY, POSX);
  	simulation = newwin(LIGNE+2, COLONNE+2, POSY+5, POSX);
  	etat = newwin(H_ETAT+2, COLONNE-2, POSY+5, POSX+32);
	box(info, 0, 0);
  	box(simulation, 0, 0);
  	box(etat, 0, 0);

    /*Création des sous fenêtres*/
  	sous_info = subwin(info, H_INFO, COLONNE +28, POSY + 1, POSX + 1);
  	sous_simulation = subwin(simulation,LIGNE, COLONNE , POSY + 6, POSX + 1);
  	sous_etat = subwin(etat,H_ETAT, COLONNE - 2, POSY + 6, POSX + 32);
  	

    /* Écriture légendes */
    wattron(sous_etat,COLOR_PAIR(2));
    mvwprintw(sous_etat,3,1," ");
    wattroff(sous_etat,COLOR_PAIR(2));
    wattron(sous_etat,COLOR_PAIR(1));
    mvwprintw(sous_etat,4,1," ");
    wattroff(sous_etat,COLOR_PAIR(1));
    mvwprintw(sous_etat,3,2,"   Obstacle ");
    mvwprintw(sous_etat,4,2,"   Flocon ");

    /* Création des cadres */
    wrefresh(info);
    wrefresh(sous_info);
    wrefresh(simulation);
    wrefresh(sous_simulation);
    wrefresh(etat);
    wrefresh(sous_etat);

    /*Lock molette*/
	scrollok(sous_info, TRUE);
    scrollok(sous_etat, TRUE);

    /* Attente d'un clic dans la fenêtre ou de F2 */
    printw("Cliquez dans la info ; pressez F2 pour quitter...");

    init_obstacles(sous_simulation,mat);
    timeout(5);
    while((i = getch()) != KEY_F(2)) {
        if(i==KEY_MOUSE && souris_getpos(&sourisX, &sourisY, &bouton)==OK) {
            if(bouton & BUTTON1_CLICKED){
                int col = sourisX-21;
                int row = sourisY-11;
                if((col>=0)&&(col<30)&&(row>=0)&&(row<15)){
                    mvwprintw(sous_info,2,0,"Clic bouton 1 a la position (%d, %d)\n", sourisX-21, sourisY-11);
                    wrefresh(sous_info);
                    clickObstacles(sous_simulation,&col,&row,mat);
                }
            }
        }
    }
    free(mat);

    /* Suppression des fenêtres */
    delwin(sous_info);
    delwin(info);
    delwin(sous_simulation);
    delwin(simulation);
    delwin(sous_etat);
    delwin(etat);
  
    /* Arrêt de ncurses */
    ncurses_stopper();

    return EXIT_SUCCESS;
}