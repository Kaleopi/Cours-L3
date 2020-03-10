#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>



#define M	6
#define N	6
static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct stepOne_t{
	pthread_mutex_t mutex;
    pthread_cond_t cond;
	int **matrice;
	int *vecteur;
	int *vecResultat;
}stepOne_t;

int **matrice;
int *vecteur;
int *vecResultat;

void* stepOne();
void afficherMatrice(int**, int,int);
void afficherVecteur(int*,int);

void *stepOne(void *arg){
	printf("k");
	pthread_mutex_lock(& mutex);
	stepOne_t *element=(stepOne_t*)arg;
for (int i = 0; i < M; i++){
	element->vecResultat[i] = 0;
	for (int j = 0; j < N; j++){
	element->vecResultat[i] = element->vecResultat[i] + element->matrice[i][j] * element->vecteur[j];
}
	afficherVecteur(element->vecResultat, M);
}
        sleep(10);

	pthread_mutex_unlock(& mutex);
	free(element);
	return EXIT_SUCCESS;
}

void afficherMatrice(int** matrice, int m, int n) {
	int i, j;
	printf("Matrice******\n");
	for (i= 0; i < m; i++){
		for (j = 0; j < n; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}
	printf("**************\n");
}

void afficherVecteur(int* vecteur, int taille) {
	int i;
	printf("Vecteur******\n");
	for (i = 0; i < taille; i++)
		printf("%d ", vecteur[i]);
	printf("\n");
	printf("*************\n");
}

int main(int argc, char *argv[]) {
	// pthread th;

	stepOne_t *element;
	element=(stepOne_t*)malloc(sizeof(stepOne_t));
	pthread_t *threads=malloc(sizeof(pthread_t));
    int statut=0;
	int i, j;

	srand(time(NULL));

	matrice = (int **) malloc(sizeof(int *) * M);
	vecteur = (int *) malloc(sizeof(int) * N);
	for (i = 0; i < M; i++) {
		matrice[i] = (int *) malloc(sizeof(int) * N);
		for (j = 0; j < N; j++)
			matrice[i][j] = (rand() % 5) + 1;
	}
	for (i = 0; i < N; i++)
		vecteur[i] = (rand() % 5) + 1;

	vecResultat = (int *) malloc(sizeof(int) * M);
	for (i = 0; i < M; i++)
		vecResultat[i] = -1;

	afficherMatrice(matrice, M, N);
	afficherVecteur(vecteur, N);
	element->matrice=matrice;
	element->vecteur=vecteur;
	element->vecResultat=vecResultat;

    statut= pthread_mutex_init(&element->mutex, NULL);
    if (statut != 0){
        fprintf(stderr, "Problemeinitialisation mutex\n");
    }
    statut= pthread_cond_init(&element->cond, NULL);
	//pthread_mutex_lock(& mutex);
	statut=pthread_create(&threads[0],NULL,stepOne,element);
	//pthread_mutex_unlock(& mutex);
	sleep(2);
	//afficherVecteur(element->vecResultat, M);

	free(vecteur);
	free(vecResultat);
	for (i = 0; i < M; i++)
		free(matrice[i]);
	free(matrice);

	return 0;
}
