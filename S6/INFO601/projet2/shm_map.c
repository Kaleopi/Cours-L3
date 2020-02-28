#include "shm_map.h"
#include <semaphore.h>

#define NB_THREAD 4
#define LIMIT 2
#define N 3

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
        //manque les arguments des to something
        //à parametrer 
        //
 
        switch(cardinal){
            case 0:
                if(carte->carte[COLONNE*(v->y)-cardinal+(v->x)]==0){
                    toLeft(WINDOW* simulation, v->x, v->y, int* carte);
                }else{
                    while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+cardinal+(v->x)]==0){
                                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)+(v->x)-cardinal]==0){
                                  toUp(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 2:
                                if(carte->carte[COLONNE*(v->y)+(v->x)+cardinal]==0){
                                     toDown(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                        }
                    }
                }
                break;
            case 1:
                if(carte->carte[COLONNE*(v->y)+cardinal+(v->x)]==0){
                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)-cardinal+(v->x)]==0){
                                    toLeft(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)+(v->x)-cardinal]==0){
                                  toUp(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 2:
                                if(carte->carte[COLONNE*(v->y)+(v->x)+cardinal]==0){
                                     toDown(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                        }
                    }
                    
                }
                break;
            case 2 :
                if(carte->carte[COLONNE*(v->y)+(v->x)-cardinal]==0){
                    toUp(WINDOW* simulation, v.x, v.y, int* carte);
                }
                else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+cardinal+(v->x)]==0){
                                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)-cardinal+(v->x)]==0){
                                  toLeft(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 2:
                                if(carte->carte[COLONNE*(v->y)+(v->x)+cardinal]==0){
                                     toDown(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                        }
                    }
                }
                break;
            case 3 :
                if(carte->carte[COLONNE*(v->y)+(v->x)+cardinal]==0){
                    toDown(WINDOW* simulation, v.x, v.y, int* carte);
                }else{
                     while(booleen!=1){
                        randomValue = rand() % N;
                        switch(randomValue){
                            case 0:
                                if(carte->carte[COLONNE*(v->y)+cardinal+(v->x)]==0){
                                    toRight(WINDOW* simulation, v.x, v.y, int* carte);
                                booleen=1
                                }
                            break;
                            case 1:
                                if(carte->carte[COLONNE*(v->y)+(v->x)-cardinal]==0){
                                  toUp(WINDOW* simulation, v.x, v.y, int* carte);
                                  booleen=1;
                                }
                            break;
                            case 2:
                                if(carte->carte[COLONNE*(v->y)-cardinal+(v->x)]==0){
                                     toLeft(WINDOW* simulation, v.x, v.y, int* carte);
                                     booleen=1;
                                }
                            break;
                        }
                    }
                }
                break;
            default:
                printf("plop");
                break;
            }
        
        //attente
		if(sem_wait(&op) == -1){
         perror("Erreur lors de l'opération wait sur le sémaphore ");
         exit(EXIT_FAILURE);
        }
		// Section critique
		printf("Je suis la voiture [%i] et je vais dormir \n", tid);
		if (sleepnano(tim,time2) == -1) {
         perror("Erreur lors de l'opération sur le sémaphore ");
         exit(EXIT_FAILURE);
        }
		printf("Je suis le voiture [%i] et j'ai fini ma sieste\n", tid);
		// On relache le sémaphore
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

