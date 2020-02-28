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
    int msqid, shmid, i, voitures_i, nbMaxVoitures;
    char *nom_fichier;
    struct sigaction sa;
    shmmap_t segment;
    size_t taille_titre;
    key_t cle_msg, cle_sem, cle_shm;
    pid_t *tab_pid;
    requete_t req;
    reponse_t rep;
    WINDOW *sim, *bordure, *etat;
    int semid;
    unsigned short val[2];
    /*struct sembuf op;*/

    sa.sa_handler = handler;

    sa.sa_flags = 0;
    voitures_i = 0;
    val[0] = 0;
    val[1] = 0;

    sigaction(SIGINT, &sa, NULL);
    voitures_i = 0;
    if(argc==6){
        nom_fichier = argv[1];
        nbMaxVoitures = atoi(argv[2]);
        cle_msg = atoi(argv[3]);
        cle_shm = atoi(argv[4]);
        cle_sem = atoi(argv[5]);
        if((tab_pid = malloc(sizeof(pid_t)*nbMaxVoitures))==NULL){
            fprintf(stderr, "Erreur : allocation tableau de pids\n");
            exit(EXIT_FAILURE);
        };
    }
    else{
        error_args();
        exit(EXIT_FAILURE);
    }

    /* Création du tableau de sémaphore */
    if((semid = semget(cle_sem, 2, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
        fprintf(stderr, "Tableau de sémaphores (cle=%d) existant\n", cle_sem);
        else
        perror("Erreur lors de la création du tableau de sémaphores ");
        exit(EXIT_FAILURE);
    }

    /* Initialisation des sémaphores */
    if(semctl(semid, 0, SETALL, val) == -1) {
        perror("Erreur lors de l'initialisation des sémaphores ");
        exit(EXIT_FAILURE);
    }
    printw("LES SEMAPHONRES SONT CREE ET INITIALISES\n");
    printw("cc\n");

    initialiser_carte(&carte);
    printw("dd\n");
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

    /*Initialisation des fenêtres*/
    /*fen princ*/
    bordure = newwin(LINE+2,COL+2,10,0);
    etat = newwin(LINE,COL,COL-3,0);
    box(bordure, 0,0);
    box(etat,0,0);
    sim = subwin(bordure,LINE+1,COL,2,1);
    scrollok(sim,TRUE);
  

    charger_carte(nom_fichier, &carte, &taille_titre);

    /* Création de la file si elle n'existe pas */
    msqid = creer_file(cle_msg);
    mvwprintw(etat,COL-2,0,"LA FILE DE MESSAGE CREE ET INITIALISES MSQID : %d //",msqid);
    printw("LA FILE DE MESSAGE CREE ET INITIALISES MSQID : %d \n//",msqid);
    /* Création du segment */
    printw("DANS CONTROLEUR TAILLE = %ld \n//", taille_titre);
    shmid = creer_segment(&segment, cle_shm, nom_fichier, taille_titre, nbMaxVoitures);
    printw("SEGMENT CREE ET INITIALISES \n//");
    printw("%d\n",shmid);
    /*afficher_carte(&carte);*/

    wrefresh(bordure);
    wrefresh(sim);
    wrefresh(etat);
    printw("Pressez F2 pour quitter...");
    while((!sigintRecu) && (i=getch()!=KEY_F(2))){
        printw("CONTROLEUR : en attente d'une requête\n");
        if((msgrcv(msqid , &req, sizeof(requete_t)-sizeof(long), -2, 0)==-1) && !sigintRecu){
            perror("Erreur lors de la réception de la requête");
            exit(EXIT_FAILURE);
        }
        if(!sigintRecu && req.type == TYPE_REQUETE){
            tab_pid[voitures_i]=req.pid;
            voitures_i++;
            printw("Voiture %d veut se connecter\ncpt voiture : %d\n",req.pid, voitures_i);
        }

        /* Envoi de la réponse */
        rep.type = req.pid;
        rep.cle_shm = cle_shm;
        rep.cle_sem = cle_sem;

        if(msgsnd(msqid, &rep, sizeof(reponse_t)-sizeof(long), 0) == -1){
            perror("controleur : Erreur lors de l'envoi de la réponse");
            exit(EXIT_FAILURE);
        }
        printw("Réponse envoyée\n");

        if(!sigintRecu && req.type == TYPE_REPONSE){
            printw("mise à jour affichage ncurses");
        }
    }

    /* Kill des voitures après avoir reçu SIGINT */
    for(i=0; i<voitures_i; i++){
        printw("CONTROLEUR : envoie signal arrêt au processus %d\n", tab_pid[i]);
        if(kill(tab_pid[i], SIGRTMIN) == -1){
            if(errno == EINVAL)
                fprintf(stderr, "Erreur lors de la terminaison du kill (pid=%d)\n",tab_pid[i]);
            else if(errno == EPERM)
                fprintf(stderr, "Ce prossessus n'a pas les droits suffisants de kill (pid=%d)\n",tab_pid[i]);
            else if(errno == ESRCH)
                fprintf(stderr, "Ce processus n'existe pas\n");
            else
                fprintf(stderr, "Erreur kill pid\n");
        };
    }

    /* Suppression de la file */
    if(msgctl(msqid, IPC_RMID, 0) == -1) {
        perror("CONSTROLEUR : Erreur lors de la suppression de la file ");
        exit(EXIT_FAILURE);
    }
    printw("CONSTROLEUR : File supprimée.\n");

    if(semctl(semid, IPC_RMID, 0) == -1) {
        perror("CONSTROLEUR : Erreur lors de la suppression des semaphores ");
        exit(EXIT_FAILURE);
    }
     printw("CONSTROLEUR : Semaphores supprimés.\n");

    /*Suppression de la memoire partagee */
    if(shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("CONSTROLEUR : Erreur lors de la suppression de la memoire partagee ");
        exit(EXIT_FAILURE);
    }
    printw("CONSTROLEUR : Memoire partagee supprimée.\n");

    printw("CONSTROLEUR : Fini.\n");

    delwin(sim);
    delwin(bordure);
    delwin(etat);
    ncurses_stopper();

    exit(EXIT_SUCCESS);
}
