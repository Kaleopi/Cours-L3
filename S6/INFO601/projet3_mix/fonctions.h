#include "message.h"
#include "includes.h"

/*ncurses*/
    void ncurses_initialiser() ;/*initialise toute les fenetre*/
    void ncurses_stopper(); /*ferme la fenetre*/

    /* Création des fenetre*/
    WINDOW *creer_fenetre_box_sim();
    WINDOW *creer_fenetre_sim();
    WINDOW *creer_fenetre_box_msg() ;
    WINDOW *creer_fenetre_msg() ;
    WINDOW *creer_fenetre_box_outils();
    WINDOW *creer_fenetre_outils() ;
    WINDOW *creer_fenetre_box_points();
    WINDOW *creer_fenetre_points() ;

/*thread*/
    void simulation_initialiser();/*initailise la matrice pour les routines*/
    void simulation_stopper() ;/*termine la simulation/cancel les thread*/
    void *routine_poisson(void *);/*routine des poissons*/

/*fonctions*/
void fusion_etang(grille_t *,grille_t*,grille_t*);/*fusionne létang du j1 et j2*/
void init_etang(grille_t*);/*initialise l'étang*/
void update_sim(WINDOW*,grille_t*);/*raffraichis la simulation*/
void afficher_etang(grille_t*);/*affiche l'étang dans la console*/
void recuperation(grille_t*);/*recupère l'étang via la grille*/
void recuperation_grille(grille_t *);/*recupere la grille via l'étang*/
void both_send(grille_t*, int, int);/*envoie du serveur au client de l'étang*/
void one_send(grille_t*, int);/*envoie à l'un des clients de l'étang*/
void init_sim(WINDOW* w, grille_t* etang);/*initialise la simulation /créaetion étang grille ect...*/
int switchUp(int,WINDOW*);/* change d'items fleche du haut*/
int switchDown(int,WINDOW*);/*change d'items fleche du bas */
void lancerTruc(int,WINDOW*,WINDOW*,int*,grille_t*,int);/*lance l'items*/
void creer_poisson(int id, int posx, int posy,poisson_t *poisson,int random,int nb_poissons);/*creer les valeur du poisson*/
void generer_poisson(grille_t*);/*creer le threads poisson*/

