#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>

/*Tailles simulation*/
#define LINES 30
#define COLS 15

/*Clés*/
#define CLE_MSG 1056
#define CLE_SHM 2056
#define CLE_SEM 3056

#endif /*CONSTANTES_H*/