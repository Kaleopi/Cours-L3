#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <sys/types.h>

typedef struct {
    long type;
    pid_t pid;
 }requete_t;

typedef struct {
    long type;
    int cle_shm;
    int cle_sem;
}reponse_t;



#endif /*MESSAGE_H*/