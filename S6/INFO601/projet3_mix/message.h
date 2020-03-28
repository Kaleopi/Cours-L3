#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <errno.h>
#include <pthread.h>
#define TYPE_CONNEXION 0
#define TYPE_CONNEXION_AUTHORIZED 0

typedef struct case_tag {					/* Description d'une case sur la grille de simulation */
	int element;							/* Ce qui est present sur la case */
	pthread_t *poisson;						/* Identifiant du thread de la poisson presente sur la case */
	pthread_mutex_t mutex;					/* Protection de la case */
} case_t;

/**
 * @struct requete_t
 * @field type type de la requête (connexion, etc)
 */
typedef struct{
  long type;
}requete_t;

/**
 * @struct response_t
 * @field type type de la réponse
 */
typedef struct{
  long type;
  int port;
  case_t grille;
}reponse_t;


typedef struct coord_tag {					/* Coordonnees d'une case sur la grille de simulation*/
	int y;
	int x;
} coord_t;

#endif /*_MESSAGE_H_*/
