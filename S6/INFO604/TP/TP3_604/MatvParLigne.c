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
	int i;
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
	int calcul=M/2;
	stepOne_t *element=(stepOne_t*)arg;
	//printf("%d",element->i);
	int i=element->i;
	element->vecResultat[i] = 0;
	for (int j = 0; j < calcul; j++){
	element->vecResultat[i] = element->vecResultat[i] + element->matrice[i][j] * element->vecteur[j];
}
	afficherVecteur(element->vecResultat, M);

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
	for (i = 0; i < N; i++)for (int i = 0; i < M; i++){
		vecteur[i] = (rand()for (int i = 0; i < M; i++){ % 5) + 1;
for (int i = 0; i < M; i++){
	vecResultat = (int *) mafor (int i = 0; i < M; i++){lloc(sizeof(int) * M);
	for (i = 0; i < M; i++)for (int i = 0; i < M; i++){
		vecResultat[i] = -1;for (int i = 0; i < M; i++){	
for (int i = 0; i < M; i++){
	afficherMatrice(matrice,for (int i = 0; i < M; i++){ M, N);
	afficherVecteur(vecteur,for (int i = 0; i < M; i++){ N);for (int i = 0; i < M; i++){
	element->matrice=matricefor (int i = 0; i < M; i++){;
	element->vecteur=vecteurfor (int i = 0; i < M; i++){;
	element->vecResultat=vecResultat;

    statut= pthread_mutex_init(&element->mutex, NULL);
    if (statut != 0){
        fprintf(stderr, "Problemeinitialisation mutex\n");
    }
    statut= pthread_cond_init(&element->cond, NULL);
	//pthread_mutex_lock(& mutex);
	for(int i=0;i<M/2;i++){
	element->i=i;
	statut=pthread_create(&threads[i],NULL,stepOne,element);
	}
	for(int i=0 ; i<M/2 ; i++){
        statut=pthread_join(threads[i],NULL);
        if(statut!=0){
            fprintf(stderr, "probleme thread join\n");
        }
    }
	//pthread_mutex_unlock(& mutex);
	//sleep(2);
	//afficherVecteur(element->vecResultat, M);

	free(vecteur);
	free(vecResultat);
	for (i = 0; i < M; i++)
		free(matrice[i]);
	free(matrice);

	return 0;
}


