#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "liste.h"

int main(int argc, char *argv[])
{
    Liste *l = NULL;
    Cellule *c = NULL;
    char str[26] = "Chaine";
    initCellule(c,str);
    initListe(l);
    insererListe(l,c);
    afficherListe(l);
    return 0;
}