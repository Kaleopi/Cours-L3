#include "shm_map.h"
#include <semaphore.h>

#define NB_THREAD 4
#define LIMIT 2
#define N 4

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

int semid;
struct sembuf op;

void * job_voiture(void * args) {
	// Récupération de l'identifiant du thread
    struct timespec tim, time2;
    tim.tv_sec = 0;
    tim.tv_nsec = 500000000L;
	int tid = pthread_self();
	int i = 0;
    if((semid = semget((key_t)CLE, 0, 0)) == -1) {
    perror("Erreur lors de la récupération du tableau de sémaphores ");
    exit(EXIT_FAILURE);
    }
	while (i < LIMIT) {
        attente(op);
		// On attend la disponibilité du sémaphore
        if(semop(semid, &op, 1) == -1) {
         perror("Erreur lors de l'opération sur le sémaphore ");
         exit(EXIT_FAILURE);
        }else{
        //choix de la direction  
        int randomValue;
        randomValue = rand() % N;
        // 
        //manque les arguments des to something
        //à parametrer 
        //
        switch( randomValue ){
            case 0:
                toLeft(WINDOW* simulation, int* row, int* col, int* carte);
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
        //attente
		sem_wait(&op);
		// Section critique
		printf("Je suis la voiture [%i] et je vais dormir \n", tid);
		sleepnano(tim,time2);
		printf("Je suis le voiture [%i] et j'ai fini ma sieste\n", tid);
		// On relache le sémaphore
		liberation(op);
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

//initialise le tableau de semaphore du serveur
void *semaphore_serveur(void*arg){
    int semid;
    unsigned short val[2] = {0, 0};
    struct sembuf op;

  /* Création du tableau de sémaphore */
  if((semid = semget((key_t)CLE, 2, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
    if(errno == EEXIST)
      fprintf(stderr, "Tableau de sémaphores (cle=%d) existant\n", CLE);
    else
      perror("Erreur lors de la création du tableau de sémaphores ");
    exit(EXIT_FAILURE);
  }
    if(semctl(semid, 0, SETALL, val) == -1) {
    perror("Erreur lors de l'initialisation des sémaphores ");
    exit(EXIT_FAILURE);
  }

}
//libere le semaphore
int  liberation(void *arg){
    int retour;
    printf("Serveur : libération du semaphore Sn -> V(Sn)\n");
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
int attente(void *arg){
    int retour;
    printf("Serveur : attente du sémaphore Sn -> P(Sn)\n");
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

void* suppression(void *arg){
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

int sleepnano(timespec tim, timespec time){
   if(nanosleep(&tim , &time) < 0 )   
   {
      printf("Failed \n");
      return -1;
   }

   printf("Sleep\n");

   return 0;
}

// int main() {
// 	// Création d'un tableau de thread
// 	pthread_t threads[NB_THREAD];
// 	// Initialisation du sémaphore
// 	sem_init(&semaphore, PTHREAD_PROCESS_SHARED, 1);
// 	for (int i = 0; i < NB_THREAD; i++) {
// 		int err;
// 		if ((err = pthread_create(&threads[i], NULL, job_semaphore, NULL)) != 0) {
// 			printf("Echec de la création du thread: [%s]", strerror(err));
// 			return EXIT_FAILURE;;
// 		}
// 		printf("Création du thread numéro %i\n", i);
// 	}
// 	for (int i = 0; i < NB_THREAD; i++) {
// 		pthread_join(threads[i], NULL);
// 	}
// 	sem_destroy(&semaphore);
// 	return EXIT_SUCCESS;
// }
