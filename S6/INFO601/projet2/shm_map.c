#include "shm_map.h"
#include <semaphore.h>
#include "defines.h"

#define NB_THREAD 4
#define LIMIT 2
#define N 2

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
            carte->carte[i][j] = 0;
        }
    }
}

/**
 * créer le segment partagé (pour contrôleur)
 * @param cle_shm clé du segment partagé
 * @return id segment partagé
 */
int creer_segment(shmmap_t* segment, key_t cle_shm, char* titre, size_t taille, int nbVoitures){
    int shmid;
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
    segment->titre = malloc(sizeof(char)*taille);
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
void charger_carte(char *nom_fichier, WINDOW * bordure, WINDOW * sim, carte_t *carte, size_t taille){
    int i = 0, fd, j = 0, v = 0;

    char *nom_decor;

    /* ouverture du fichier */
    if((fd = open(nom_fichier, O_RDONLY)) == -1){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\"\n", strerror(errno));
        delwin(sim);
        delwin(bordure);
        ncurses_stopper();
        exit(EXIT_FAILURE);
    }

    /* taille nom décor */
    if((v = read(fd, &taille, sizeof(size_t))) == -1){
        /* Gestion d'erreur */
        fprintf(stderr,"Erreur lors de la lecture taille nom_decor : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if((nom_decor = malloc(sizeof(char)*taille))==NULL){
        fprintf(stderr, "Erreur : allocation nom_decor\n");
    };

    /* nom décor */
    if((v = read(fd, nom_decor, taille*sizeof(char))) == -1){
        /* Gestion d'erreur */
        fprintf(stderr, "Erreur lors de la lecture du nom_decor : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    mvwprintw(bordure,0,1, nom_decor);

    /* matrice */
    if ((v = read(fd, carte->carte, COL*LINE*sizeof(char)+30)) == -1){
        /* Gestion d'erreur */
        printw("Erreur lors de la lecture de la matrice : \"%s\"\n", strerror(errno));
        exit(EXIT_FAILURE);
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

// Création du sémaphore;
//penser à passer la grille en param 
//penser à passer la window
//penser à vérifier les coords
//

int semid;
struct sembuf op;

void * job_voiture(void * args) {
	// Récupération de l'identifiant du thread
    struct timespec tim, time2;
    tim.tv_sec = 0;
    tim.tv_nsec = 500000000L;
	int tid = pthread_self();
	int i = 0;
    if((semid = semget((cle_sem, 0, 0)) == -1) {
        perror("Erreur lors de la récupération du tableau de sémaphores ");
        exit(EXIT_FAILURE);
    }
	while (i < LIMIT) {
        attente(op);
		// On attend la disponibilité du sémaphore
        if(semop(semid, &op, 1) == -1) {
         perror("Erreur lors de l'opération op sur le sémaphore ");
         exit(EXIT_FAILURE);
        }else{
        //choix de la direction  
        int randomValue;
        randomValue = rand() % N;
        // 
        //manque les arguments des to something
        //à parametrer 
        //
        switch(randomValue){
            case 0:
                toLeft(WINDOW* simulation, int *row, int* col, int* carte);
                break;
            case 1:
                toRight(WINDOW* simulation, int* row, int* col, int* carte);
                break;
            case 2 :
                toUp(WINDOW* simulation, int* row, int* col, int* carte);
                break;
            case 3 :
                toDown(WINDOW* simulation, int* row, int* col, int* carte);
                break;
            default:
                printf("plop");
            break;
        }
        /*attente*/
		if(sem_wait(&op)==-1){
            perror("Erreur lors de l'opération wait sur le sémaphore ");
            exit(EXIT_FAILURE);
        }
		/*Section critique*/
		printf("Je suis la voiture [%i] et je vais dormir \n", tid);
		if (sleepnano(tim,time2) == -1) {
            perror("Erreur lors de l'opération sur le sémaphore ");
            exit(EXIT_FAILURE);
        }
		printf("Je suis le voiture [%i] et j'ai fini ma sieste\n", tid);
		/*On relache le sémaphore*/
		if (liberation(op) == -1) {
         perror("Erreur lors de la liberation sur le sémaphore ");
         exit(EXIT_FAILURE);
        };
		i++;
        }
	}
	pthread_exit(EXIT_SUCCESS);
}
//Deplacement a gauche
void toLeft(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*col)--;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation, *row, *col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}
//deplacement a droite
void toRight(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*col)++;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}
//deplacement en haut
void toUp(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*row)++;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}
//deplacement en bas 
void toDown(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*row)--;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}


//libere le semaphore
int  liberation(struct sembuf op){
    int retour;
    printf(" libération du semaphore Sn -> V(Sn)\n");
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
//se met en attente du semaphore puis fait l'action
int attente(vstruct sembuf opoid *arg){
    int retour;
    printf("  attente du sémaphore Sn -> P(Sn)\n");
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

  /* Récupération du tableau de sémaphores */
  if((semid = semget((key_t)CLE, 0, 0)) == -1) {
    perror("Erreur lors de la recuperation du tableau de sémaphores ");
    exit(EXIT_FAILURE);
  }

  /* Suppression du tableau de sémaphores */
  if(semctl(semid, 0, IPC_RMID) == -1) {
    perror("Erreur lors de la suppresion du tableau de sémaphores ");
    exit(EXIT_FAILURE);
  }

  printf("Tableau de semaphores supprimé.\n");

  return EXIT_SUCCESS;
}



// Création du sémaphore;
//penser à passer la grille en param 
//penser à passer la window
//penser à vérifier les coords
//

int semid;
struct sembuf op;

void * job_voiture(voiture_t *v ,carte_t *carte,int *cardinal) {
	// Récupération de l'identifiant du thread
	int i = 0;
    int booleen=-1;
    if((semid = semget((key_t)CLE, 0, 0)) == -1) {
    perror("Erreur lors de la récupération du tableau de sémaphores ");
    exit(EXIT_FAILURE);
    }
	while (i < LIMIT) {
        attente(op);
		// On attend la disponibilité du sémaphore
        if(semop(semid, &op, 1) == -1) {
         perror("Erreur lors de l'opération op sur le sémaphore ");
         exit(EXIT_FAILURE);
        }else{
        //choix de la direction  
        int randomValue;

        // 
        //déplacement
        //
        //
 
        switch(cardinal){
            case 0:
                if(carte->carte[COLONNE*(v->y)-1+(v->x)]==0){
                    toLeft(WINDOW* simulation, v->x, v->y, int* carte);
                }else{
                    while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+(v->x)-1]==0){
                                  toUp(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)+(v->x)+1]==0){
                                     toDown(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                            default:
                            printf("plop");
                            break;
                        }
                    }
                    booleen=-1;
                }
                break;
            case 1:
                if(carte->carte[COLONNE*(v->y)+1+(v->x)]==0){
                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+(v->x)-1]==0){
                                  toUp(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)+(v->x)+1]==0){
                                     toDown(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                            default:
                            printf("plop");
                            break;
                        }
                    }
                     booleen=-1;
                }
                break;
            case 2 :
                if(carte->carte[COLONNE*(v->y)+(v->x)-1]==0){
                    toUp(WINDOW* simulation, v.x, v.y, int* carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+1+(v->x)]==0){
                                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)-1+(v->x)]==0){
                                  toLeft(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            default:
                            printf("plop");
                            break;
                        }
                    }
                     booleen=-1;
                }
                break;
            case 3 :
                if(carte->carte[COLONNE*(v->y)+(v->x)+1]==0){
                    toDown(WINDOW* simulation, v.x, v.y, int* carte);
                }else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+1+(v->x)]==0){
                                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)-1+(v->x)]==0){
                                     toLeft(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                            default:
                            printf("plop");
                            break;
                                    
                            }
                    }
                     booleen=-1;
                }
                break;
            default:
                printf("plop");
                break;
            }
        
      
		// Section critique
		printf(" je vais dormir \n");
		if (sleepnano(tim,time2) == -1) {
         perror("Erreur lors de l'opération sur le sémaphore ");
         exit(EXIT_FAILURE);
        }
		printf(" j'ai fini ma sieste\n");
		// On relache le sémaphore
		if (liberation(op) == -1) {
         perror("Erreur lors de la liberation sur le sémaphore ");
         exit(EXIT_FAILURE);
        }
        }
        
	}
	pthread_exit(EXIT_SUCCESS);

}