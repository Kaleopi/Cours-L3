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
    int msqid, shmid, i, voitures_i, nbMaxVoitures;
    char *nom_fichier;
    struct sigaction sa;
    union sigval sigval;
    shmmap_t segment;
    size_t taille_titre;
    key_t cle_msg, cle_sem, cle_shm;
    pid_t *tab_pid;
    requete_t req;
    reponse_t rep;
    WINDOW *sim, *bordure;
    int semid;

    sa.sa_handler = handler;

    sa.sa_flags = 0;
    voitures_i = 0;
    //semaphore
    unsigned short val[2];
    val[0] = 0;
    val[1] = 0;
    struct sembuf op;

  
    sigaction(SIGINT, &sa, NULL);
    
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

    /* Création de la file si elle n'existe pas */
    msqid = creer_file(cle_msg);
    /* Création du segment */
    shmid = creer_segment(&segment, cle_shm, nom_fichier, taille_titre, nbMaxVoitures);

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



    /*Initialisation des fenêtres*/
    bordure = newwin(LINE+2,COL+2,1,0);
    box(bordure, 0,0);
    sim = subwin(bordure,LINE+1,COL,2,1);
    scrollok(sim,TRUE);

    charger_carte(nom_fichier, bordure, sim, &carte, taille_titre);
    /* afficher_carte(&carte);*/

    wrefresh(bordure);
    wrefresh(sim);
    printw("Pressez F2 pour quitter...");
    /*à inverser */
    while((!sigintRecu) && (i=getch()!=KEY_F(2))){
        printf("CONTROLEUR : en attente d'une requête\n");
        if((msgrcv(msqid , &req, sizeof(requete_t)-sizeof(long), -2, 0)==-1) && !sigintRecu){
            perror("Erreur lors de la réception de la requête");
            break;
        }
        if(!sigintRecu && req.type == TYPE_REQUETE){
            tab_pid[voitures_i]=req.pid;
            voitures_i++;
            printf("Voiture %d veut se connecter\n",req.pid);
        }

        /* Envoi de la réponse */
        rep.type = req.pid;
        rep.cle_shm = cle_shm;
        rep.cle_sem = cle_sem;

        if(msgsnd(msqid, &rep, sizeof(reponse_t)-sizeof(long), 0) == -1){
            perror("Erreur lors de l'envoi de la réponse");
            exit(EXIT_FAILURE);
        }
        printf("Réponse envoyée\n");

        if(!sigintRecu && req.type == TYPE_REPONSE){
            printf("mise à jour affichage ncurses");
        }
    }

    /* Kill des voitures après avoir reçu SIGINT */
    for(i=0; i<voitures_i; i++){
        printf("CONTROLEUR : envoie signal arrêt au processus %d\n", tab_pid[i]);
        if(kill(tab_pid[i], SIGRTMIN) == -1){
            if(errno == EINVAL)
                fprintf(stderr, "Erreur lors de la terminaison du kill (pid=%d)\n",tab_pid[i]);
            else if(errno == EPERM)
                fprintf(stderr, "Ce prossessus n'a pas les droits suffisants de kill (pid=%d)\n",tab_pid[i]);
            else if(errno == ESRCH)
                fprintf(stderr, "Ce processus n'existe pas\n");
            else
                fprintf(stderr, "Erreur kill pid\n");
            exit(EXIT_FAILURE);
        };  
    }

    /* Suppression de la file */
    if(msgctl(msqid, IPC_RMID, 0) == -1) {
        perror("CONSTROLEUR : Erreur lors de la suppression de la file ");
        exit(EXIT_FAILURE);
    }
    printf("CONSTROLEUR : File supprimée.\n");

    delwin(sim);
    delwin(bordure);
    ncurses_stopper();

    exit(EXIT_SUCCESS);
}