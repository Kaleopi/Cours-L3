#define _POSIX_C_SOURCE 199309L

#include "shm_map.h"
#include "ncurses.h"
#include "messages.h"
#include "fonctionsControleur.h"
#include "defines.h"

static carte_t carte;
short sigintRecu = 0;

/**
 * Écoute la réception d'un signal
 * @param signum le signal à écouter
 * @return void
 */
void handler(int signum){
  if(signum == SIGINT) sigintRecu = 1;
}

/**
 * Programme principal du contrôleur 
 * @param argv[1] nom_fichier.bin
 * @param argv[2] nombre maximum de voitures
 * @param argv[3] cle file de message
 * @param argv[4] cle mémoire partagée
 * @param argv[5] cle tableau de sémaphore
 */
int main(int argc, char *argv[]){
    /*declarations de variables*/
    int msqid;
    int i;
    int voitures_i;
    int nbMaxVoitures;
    char *nom_fichier;
    key_t cle_msg;
    key_t cle_sem;
    key_t cle_shm;
    pid_t *tab_pid;
    requete_t req;
    reponse_t rep;

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    //semaphore
    int semid;
    unsigned short val[2] = {0, 0};
     struct sembuf op;

  
    sigaction(SIGINT, &sa, NULL);
    
    /* Création du tableau de sémaphore */
    if((semid = semget((key_t)CLE, 2, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
        fprintf(stderr, "Tableau de sémaphores (cle=%d) existant\n", CLE);
        else
        perror("Erreur lors de la création du tableau de sémaphores ");
        exit(EXIT_FAILURE);
    }

    /* Initialisation des sémaphores */
    if(semctl(semid, 0, SETALL, val) == -1) {
        perror("Erreur lors de l'initialisation des sémaphores ");
        exit(EXIT_FAILURE);
    }
    
    voitures_i = 0;
    if(argc==6){
        nom_fichier = argv[1];
        nbMaxVoitures = atoi(argv[2]);
        cle_msg = atoi(argv[3]);
        cle_shm = atoi(argv[4]);
        cle_sem = atoi(argv[5]);
    }
    else{
        error_args();
        exit(EXIT_FAILURE);
    }

    /* Création de la file si elle n'existe pas */
    msqid = creer_file(cle_msg);

    initialiser_carte(&carte);
    /*Initialisation de ncurses*/
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    wbkgd(stdscr, COLOR_PAIR(3));
    refresh();

	/* Vérification des dimensions du terminal */
  	if((COLS < COL+5) || (LINES < LINE+5)) {
        ncurses_stopper();
        fprintf(stderr, "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", COLS, LINES, COL+5, LINE+5);
        exit(EXIT_FAILURE);
    }

    WINDOW *sim, *bordure;

    /*Initialisation des fenêtres*/
    bordure = newwin(LINE+2,COL+2,1,0);
    box(bordure, 0,0);
    sim = subwin(bordure,LINE+1,COL,2,1);
    scrollok(sim,TRUE);

    charger_carte(nom_fichier, bordure, sim, &carte);
    /* afficher_carte(&carte);*/

    wrefresh(bordure);
    wrefresh(sim);
    printw("Pressez F2 pour quitter...");
    /*à inverser */
    while((i = getch()) != KEY_F(2)){
        while(!sigintRecu){
            
        }
    };
    delwin(sim);
    delwin(bordure);
    ncurses_stopper();

    exit(EXIT_SUCCESS);
}