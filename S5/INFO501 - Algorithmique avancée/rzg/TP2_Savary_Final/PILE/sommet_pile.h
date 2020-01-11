#ifndef SOMMET
#define SOMMET value
typedef struct sommet sommet;
struct sommet
{
	int id_sommet;
	int couleur;
	int d;
	int debut;
	int fin;
	sommet* pere;
};

void init_sommet(sommet* s , int id_s);
#endif