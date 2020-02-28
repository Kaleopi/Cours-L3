#include "segment.h"

/*carte*/
void print_carte(carte_t carte) {
	/*Section critique = sémaphores*/
	int i, j;
	for(i=0; i<COL; i++) {
		for(j=0; j<LI; j++) {
			if(carte.grille[(i*LI)+j]==0) printf("X");
			else if (carte.grille[(i*LI)+j]==1) printf("_");
			else printf("?");
		}
		printf("\n");
	}
}

/*segment*/

/*
 * retourne -1 en cas d'erreur
 * sinon le id du SHM
 */
int creer_segment(segment_t* seg, key_t cle, char* path) {
	int err;
	int file;
	char dump[4];
	int tmp;
	char * chaine;
	carte_t carte;

	/*ouverture*/
	if((file = open(path, O_RDONLY))==-1) {
		perror("init_carte : Erreur ouverture fichier pour remplir la carte : ");
				exit(EXIT_FAILURE);
	}

	/*lecture*/
	/*taille titre*/
	if((err = read(file, &tmp, sizeof(int)))==-1) {
		perror("init_carte : Erreur lecture taille titre : ");
				exit(EXIT_FAILURE);
	}

	if((seg->idShm = shmget(cle, (sizeof(int)+sizeof(char)*(tmp+1) +sizeof(carte_t)+(sizeof(voiture_t)*MAX_V)),
			S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL ))==-1){
				if(errno == EEXIST)
		      fprintf(stderr, "creer_segment : existe deja\n");
		    else
		      perror("creer_segment : Erreur lors de la creation ");
		    exit(EXIT_FAILURE);
  }

	seg->adr = shmat(seg->idShm, NULL, 0);


	seg->tailleTitre = (int*)seg->adr;
	printf("avant avant %d\n", tmp+1);
	*(seg->tailleTitre) = tmp+1;
	printf("apres avant %d\n", *(seg->tailleTitre));

	/*espaces bizarres*/
	if((err = read(file, &dump, sizeof(char)*4))==-1) {
		perror("init_carte : Erreur lecture esapces : ");
        exit(EXIT_FAILURE);
	}

	/*titre*/
	if((chaine = (char*)malloc(sizeof(char)*(tmp+1)))==NULL){
		perror("erreur malloc ");
		exit(EXIT_FAILURE);
	}
	if((err = read(file, chaine, sizeof(char)*tmp))==-1) {
		perror("init_carte : Erreur lecture titre : ");
        exit(EXIT_FAILURE);
	}
	printf("\tavant\n");
	seg->titre = (char*)(seg->tailleTitre+sizeof(int));

	printf("\tapres\n");
	strcpy(seg->titre, chaine);

	/*grille*/
	if((err = read(file, carte.grille, sizeof(unsigned char)*LI*COL))==-1) {
		perror("init_carte : Erreur lecture titre : ");
        exit(EXIT_FAILURE);
	}
	seg->carte = (carte_t*)(seg->titre + *(seg->tailleTitre));
	memcpy(seg->carte, &carte, sizeof(carte_t));

	seg->positions = (voiture_t*)(&seg->carte + sizeof(carte_t));

	return seg->idShm;
}

int ouvrir_segment(segment_t* seg, key_t cle, int size) {
	if((seg->idShm = shmget(cle, (sizeof(int)+sizeof(char)*size +sizeof(carte_t)+(sizeof(voiture_t)*MAX_V)),0))==-1) {
		perror("ouvrir_segment : ");
		return seg->idShm;
	}

	seg->adr = shmat(seg->idShm, NULL, 0);
	seg->tailleTitre = seg->adr;
	seg->titre = (char*)(seg->tailleTitre + sizeof(int));
	seg->carte = (carte_t*)(seg->titre + *(seg->tailleTitre));
	seg->positions = (voiture_t*)(&seg->carte + sizeof(carte_t));


	return seg->idShm;
}


/*
* vérifier si on peut aller tout droit, x ou y
* si oui, aller tout droit
* si non, retirer une direction
*/
void deplacer_voiture(voiture_t *v, carte_t *carte, int *direction) {
  int allerToutDroit = 0;
  int axeY = 0;
	int booleenDuSauvetage;

  carte->grille[(v->y*LI)+v->x]=ROUTE;
  if(*direction % 2==0) {
    axeY = 1;
    allerToutDroit = (*direction != 0
											&& v->y+(*direction/2) < LI && v->y+(*direction/2) >= 0
											&& carte->grille[((v->y+(*direction/2))*LI)+v->x] == ROUTE);
  }else{
    allerToutDroit = (*direction !=0
											&& v->x+(*direction) < COL && v->x+(*direction) >= 0
											&& carte->grille[((v->y)*LI)+v->x+ *direction] == ROUTE);
    axeY = 0;
  }
  if(!allerToutDroit){
		printf("Je peux pas aller tout droit\n");
    /*retirer une direction*/
    do {
			booleenDuSauvetage = 1;
      *direction=rand()%4;
			if(*direction < 2){
				*direction-=2;
			}else{
				*direction = *direction -1;
			}
			printf("\tDirection : %d\n", *direction);
			if(*direction % 2 == 0){
				if(	v->y+ (*direction/2) < 0
						|| v->y +(*direction/2) >=LI
						|| carte->grille[((v->y+ (*direction/2))*LI)+v->x] != ROUTE){
								booleenDuSauvetage =  0;
				}
				printf("\n\t\tDu coup je suis pair ! et je suis %d\n", booleenDuSauvetage);
			}
			else{
				if(v->x+ *direction < 0
					|| v->x +*direction >= COL
					|| carte->grille[(v->y)*LI+(v->x+ *direction)] != ROUTE)
								booleenDuSauvetage = 0;
				printf("\n\t\tDu coup je suis impair ! et je suis %d\n", booleenDuSauvetage);
			}
    }while(!booleenDuSauvetage);
    axeY = ( *direction % 2 == 0);
  }
  /*realisation du deplacement*/
  if(axeY) {
		carte->grille[((v->y+(*direction/2))*LI)+v->x] = v->num;
		v->y+=( *direction/2);
	}
  else {
		carte->grille[(v->y*LI)+v->x+(*direction)] = v->num;
		v->x+= *direction;
	}
}
