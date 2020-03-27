#ifndef MESSAGE_H
#define MESSAGE_H

#include "defines.h"

#define TYPE_REQUETE 1
#define TYPE_REPONSE 2

/**
 * @struct requete_t
 * @field type type de la requête
 * @field pid pid de la voiture
 */

typedef struct {
    long type;
    pid_t pid;
 }requete_t;

/**
 * @struct reponse_t
 * @field type type de la réponse
 * @field cle_shm clé du segment partagé
 * @field cle_sem clé des sémaphores
 */
typedef struct {
    long type;
    key_t cle_shm;
    key_t cle_sem;
}reponse_t;



#endif /*MESSAGE_H*/
