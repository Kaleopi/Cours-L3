#ifndef _STRUCTURES_
#define _STRUCTURES_

/* Structure utilisee pour les requetes */
typedef struct {
  long type;
  int cleSem;
  int cleShm;
} reponse_t;

/* Type de message reponse */
#define TYPE_CONFIG 1
#define TYPE_DEPL 2

/* Structure utilisee pour les reponses */
typedef struct {
  long type;
  int pid;
} requete_t;

#endif
