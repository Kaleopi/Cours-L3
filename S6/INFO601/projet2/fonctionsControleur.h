#include "ncurses.h"
#include "shm_map.h"
#include "messages.h"
#include "defines.h"

void charger_carte(char *, WINDOW *, WINDOW *, carte_t *);
void afficher_carte(carte_t *);