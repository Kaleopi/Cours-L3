#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "define.h"

void init_obstacles(WINDOW*, int*);
int finSimulation(int*);
void updateSimulation(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
void createFlocon(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
void toLeft(WINDOW*, int*, int*, int*);
void toRight(WINDOW*, int*, int*, int*);

#endif //FUNCTION_H
