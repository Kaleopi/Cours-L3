#include <semaphore.h>
#include "shm_map.h"
#include "ncurses.h"
#include "defines.h"


#define N 2

    int semid;
    int booleen;
    struct sembuf op;
/**
 * initialise la carte du segment partagé à '0'
 * @param carte carte_t du segment
 * @return void
 */
void initialiser_carte(carte_t *carte){
    int i;
    int j;
    for(i=0 ; i<LINE ; i++){
        for(j=0 ; j<COL ; j++){
            carte->carte[i][j]= 0;
        }
    }
}

/**
 * créer le segment partagé (pour contrôleur)
 * @param segment segment de mémoire partagée
 * @param cle_shm clé du segment partagé
 * @param titre titre de la carte
 * @param taille taille du titre
 * @param nbVoitures nombre de voiture maximum
 * @return id segment partagé
 */
int creer_segment(shmmap_t* segment, key_t cle_shm, char* titre, size_t taille, int nbVoitures){
    int shmid;
    /*printw("SIZE  = %ld\n", sizeof(int)+(sizeof(char)*(*taille+1))+sizeof(carte_t)+(sizeof(voiture_t)*nbVoitures));*/
    printw("TAILLE = %ld\n", taille+1);
    printw("taille carte = %ld\n",sizeof(carte_t));
    printw("taille voitures = %ld\n",sizeof(voiture_t)*nbVoitures);
    if((shmid = shmget(cle_shm, sizeof(int)+(sizeof(char)*taille+1)+sizeof(carte_t)+(sizeof(voiture_t)*nbVoitures), S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
            fprintf(stderr, "Segment (cle=%d) existant\n", cle_shm);
        else if(errno == EINVAL)
            fprintf(stderr, "Erreur : segment trop petit ou trop grand (cle=%d)",cle_shm);
        else if(errno == ENOENT)
            fprintf(stderr, "Erreur : pas de segment associé à la clé (cle=%d)",cle_shm);
        else if(errno == ENOSPC)
            fprintf(stderr, "Erreur : nombre maximal de segments atteints / mémoire maximale atteinte");
        else
            perror("Erreur inconnue lors de la creation du segment ");
        exit(EXIT_FAILURE);
    }
    if((segment->titre = malloc(sizeof(char)*taille))==NULL){
        printw("Erreur allocation segment->titre\n");
    };
    strcpy(segment->titre, titre);
    segment->shmid = shmid;
    segment->addr = shmat(shmid, NULL,0);
    return shmid;
}

/**
 * Ouvre la carte passée en paramètres pour l'appliquer au ncurses
 * @param nom_fichier nom du fichier .bin qui contient les infos de la carte
 * @param bordure WINDOW ncurses de la bordure (pour le titre)
 * @param sim WINDOW ncurses pour la fenêtre en elle même
 * @param carte carte du segment partagé à remplir avec les infos du fichier
 * @return void
 */
void charger_carte(char *nom_fichier, carte_t *carte, size_t *taille){
    int fd, v = 0;
    char *nom_decor;

    /* ouverture du fichier */
    if((fd = open(nom_fichier, O_RDONLY)) == -1){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\"\n", strerror(errno));
        /*delwin(sim);
        delwin(bordure);
        ncurses_stopper();*/
        exit(EXIT_FAILURE);
    }
    printw("fd : %d\n",fd);

    /* taille nom décor */
    if((v = read(fd, taille, sizeof(size_t))) == -1){
        /* Gestion d'erreur */
        fprintf(stderr,"Erreur lors de la lecture taille nom_decor : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printw("taille : %ld\n",*taille);
    if((nom_decor = malloc(sizeof(char)*(*taille)))==NULL){
        fprintf(stderr, "Erreur : allocation nom_decor\n");
    };

    /* nom décor */
    if((v = read(fd, nom_decor, (*taille)*sizeof(char))) == -1){
        /* Gestion d'erreur */
        fprintf(stderr, "Erreur lors de la lecture du nom_decor : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    /*mvwprintw(bordure,0,1, nom_decor);*/

    /* matrice */
    if ((v = read(fd, carte->carte, COL*LINE*sizeof(char))) == -1){
        /* Gestion d'erreur */
        fprintf(stderr, "Erreur lors de la lecture de la matrice : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
void affiche_carte(WINDOW* sim,carte_t *carte){
    int i,j;
    for(i = 0; i<LINE; i++){
        for(j = 0; j<COL; j++){
            printw("%d",carte->carte[i][j]);
        }
        printw("\n");
     }
    /* Affichage matrice */
    for(i = 0; i<LINE; i++){
        for(j = 0; j<COL; j++){
            if((carte->carte[i][j]) == 0){
                wattron(sim, COLOR_PAIR(0));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(0));
            }
            else if((carte->carte[i][j]) == 1){
                wattron(sim, COLOR_PAIR(1));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(1));
            }
            else{
                wattron(sim, COLOR_PAIR(2));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(2));
            }
        }
    }
}

void toLeft(WINDOW* simulation, int row, int col, carte_t *carte){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	carte->carte[row][col]=0;
	(col)--;
	carte->carte[row][col]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation, row, col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}

void toRight(WINDOW* simulation, int row, int col, carte_t *carte){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	carte->carte[row][col]=0;
	(col)++;
	carte->carte[row][col]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}

void toUp(WINDOW* simulation, int row, int col, carte_t *carte){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	carte->carte[row][col]=0;
	(row)++;
	carte->carte[row][col]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}

void toDown(WINDOW* simulation, int row, int col, carte_t *carte){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	carte->carte[row][col]=0;
	(row)--;
	carte->carte[row][col]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,row,col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}

int  liberation(struct sembuf op){
    int retour;
    printw(" libération du semaphore Sn -> V(Sn)\n");
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    if(semop(semid, &op, 1) == -1) {
        perror("Erreur lors de l'opération sur le sémaphore ");
        exit(EXIT_FAILURE);
    }
    retour =semop(semid, &op, 1);
    return retour;
}

int attente(struct sembuf op){
    int retour;
    printw("  attente du sémaphore Sn -> P(Sn)\n");
    op.sem_num = 1;
    op.sem_op = -1;
    op.sem_flg = 0;
    if(semop(semid, &op, 1) == -1) {
        perror("Erreur lors de l'opération sur le sémaphore ");
        exit(EXIT_FAILURE);
    }
    retour =semop(semid, &op, 1);
    return retour;
}

void* suppression(struct sembuf op){
     int semid;


  if((semid = semget((key_t)CLE_MSG, 0, 0)) == -1) {
    perror("Erreur lors de la recuperation du tableau de sémaphores ");
    exit(EXIT_FAILURE);
  }


  if(semctl(semid, 0, IPC_RMID) == -1) {
    perror("Erreur lors de la suppresion du tableau de sémaphores ");
    exit(EXIT_FAILURE);
  }

  printw("Tableau de semaphores supprimé.\n");

  return EXIT_SUCCESS;
}



void * job_voiture(voiture_t *v ,carte_t *carte,int cardinal,WINDOW*simulation) {

    int semid;
    struct sembuf op;
    int booleen=-1;
    if((semid = semget((key_t)CLE_MSG, 0, 0)) == -1) {
    perror("Erreur lors de la récupération du tableau de sémaphores ");
    exit(EXIT_FAILURE);
    }
	while (attente(op)<0) {
        if(semop(semid, &op, 1) == -1) {
         perror("Erreur lors de l'opération op sur le sémaphore ");
         exit(EXIT_FAILURE);
        }else{
        int randomValue;

        switch(cardinal){
            case 0:
                if(carte->carte[COL*(v->y )-1+(v->x)]==0){
                    toLeft( simulation, v->x, v->y , carte);
                }else{
                    while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COL*(v->y )+(v->x)-1]==0){
                                  toUp( simulation, v->x, v->y ,carte);
                                  booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COL*(v->y )+(v->x)+1]==0){
                                     toDown(simulation, v->x, v->y ,  carte);
                                     booleen=1;
                                }
                            break;
                            default:
                            printw("plop");
                            break;
                        }
                    }
                    booleen=-1;
                }
                break;
            case 1:
                if(carte->carte[COL*(v->y )+1+(v->x)]==0){
                    toRight( simulation, v->x, v->y , carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COL*(v->y )+(v->x)-1]==0){
                                  toUp( simulation, v->x, v->y , carte);
                                  booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COL*(v->y )+(v->x)+1]==0){
                                     toDown(simulation, v->x, v->y ,  carte);
                                     booleen=1;
                                }
                            break;
                            default:
                            printw("plop");
                            break;
                        }
                         booleen=-1;
                    }
                    
                }
                break;
            case 2 :
                if(carte->carte[COL*(v->y )+(v->x)-1]==0){
                    toUp( simulation, v->x, v->y , carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COL*(v->y )+1+(v->x)]==0){
                                    toRight( simulation, v->x, v->y ,  carte);
                                booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COL*(v->y )-1+(v->x)]==0){
                                  toLeft( simulation, v->x, v->y ,carte);
                                  booleen=1;
                                }
                            break;
                            default:
                            printw("plop");
                            break;
                        }
                    }
                     booleen=-1;
                }
                break;
            case 3 :
                if(carte->carte[COL*(v->y )+(v->x)+1]==0){
                    toDown(simulation, v->x, v->y ,  carte);
                }else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COL*(v->y )+1+(v->x)]==0){
                                    toRight( simulation, v->x, v->y ,  carte);
                                booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COL*(v->y )-1+(v->x)]==0){
                                     toLeft(simulation, v->x, v->y , carte);
                                booleen=1;
                                }
                            break;
                            default:
                            printw("plop");
                            break;

                            }
                    }
                     booleen=-1;
                }
                break;
            default:
                printw("plop");
                break;
            }
        }
	}
    return 0;
}


