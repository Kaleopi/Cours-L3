#ifndef _FUNCTION_
#define _FUNCTION_

#include <stdlib.h>
#include <ncurses.h>
#include "define.h"

    void ecrire(WINDOW*, const char*);
    void nbFlocons(WINDOW*, int*);
    void placerObstacle(WINDOW*, int, int *);
	void creerFlocons(WINDOW*, int*, int*, int*);
	void updateFlocon(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
	void faitDesFlocon(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
    void versDroite(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*);
    void versGauche(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*);
    int check(int*);
#endif
