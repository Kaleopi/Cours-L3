#include "ncurses.h"
#include "functions.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"

#define LARGEUR 50     /* Largeur de la fenêtre */
#define HAUTEUR 30      /* Hauteur de la fenêtre */
#define POSX    0      /* Position horizontale de la fenêtre */
#define POSY    3       /* Position verticale de la fenêtre */


int main(){
    int i, obstacles, tricheText, tailleMat, col, lignes, flocons;
    int * matrice;
    WINDOW* fenetreInfo, *fenetreSim, *fenetreEtat;
    WINDOW* sous_fenetreInfo, *sous_fenetreSim, *sous_fenetreEtat;

    srand(time(NULL));
    flocons = 0;
    col = 0;
    lignes = 0;
    obstacles = 25;
    tricheText = 0;
    tailleMat = SIMHAUT * SIMLONG;

    matrice = (int*)malloc(sizeof(int) * tailleMat);
    for(i = 0; i < tailleMat; i++){
        matrice[i] = 0;
    }

    /* Initialisation de ncurses */
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs(); 

    /* Vérification des dimensions du terminal */
    if((COLS < POSX + LARGEUR) || (LINES < POSY + HAUTEUR)) {
        ncurses_stopper();
        fprintf(stderr, "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", COLS, LINES, POSX + LARGEUR, POSY + HAUTEUR);
        exit(EXIT_FAILURE);
    }

    /* Creation de la fenêtre */
    fenetreInfo = newwin(5, COLS, 3, 0);
    fenetreSim = newwin(SIMHAUT+2, SIMLONG+2, 8, 0);
    fenetreEtat = newwin((int)((SIMHAUT+2)/2), COLS - SIMLONG+2, 8, SIMLONG+2);
    box(fenetreInfo, 0, 0);
    box(fenetreSim, 0, 0);
    box(fenetreEtat, 0, 0);
    sous_fenetreInfo = subwin(fenetreInfo, 3, COLS - 2, 3 + 1, 0 + 1);
    sous_fenetreSim = subwin(fenetreSim, SIMHAUT, SIMLONG,8+ 1, 1);
    sous_fenetreEtat = subwin(fenetreEtat, (int)13/2, COLS - 34, 8+ 1, 32+ 1);

    wprintw(fenetreInfo, "Infos");
    wprintw(fenetreSim, "Simulation");
    wprintw(fenetreEtat, "Etat");

    /* Création d'un cadre */
    wrefresh(fenetreInfo);
    wrefresh(sous_fenetreInfo);
    wrefresh(fenetreSim);
    wrefresh(sous_fenetreSim);
    wrefresh(fenetreEtat);
    wrefresh(sous_fenetreEtat);

    scrollok(sous_fenetreInfo, TRUE);
    scrollok(sous_fenetreEtat, TRUE);

	placerObstacle(sous_fenetreSim, obstacles, matrice);


    /* Attente d'un clic dans la fenêtre ou de F2 */
    printw("Pressez F2 pour quitter...");
    timeout(50);

    while((i = getch()) != KEY_F(2)) {
    	tricheText++;
    	if(tricheText != 1) wprintw(sous_fenetreInfo, "\n");
        updateFlocon(sous_fenetreSim, sous_fenetreInfo, sous_fenetreEtat, &col, &lignes, &flocons, matrice);
    }

    /* Suppression des fenêtres */
    delwin(sous_fenetreInfo);
    delwin(fenetreInfo);
    delwin(sous_fenetreSim);
    delwin(fenetreSim);
    delwin(sous_fenetreEtat);
    delwin(fenetreEtat);
  
    /* Arrêt de ncurses */
    ncurses_stopper();

    return EXIT_SUCCESS;
}
