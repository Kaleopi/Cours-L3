/**
 * @author GIGOUT DAUNIQUE
 **/
#include <stdlib.h>     /* Pour exit, EXIT_FAILURE, EXIT_SUCCESS */
#include <stdio.h>      /* Pour printf, perror */
#include <sys/msg.h>    /* Pour msgget, msgctl */
#include <errno.h>      /* Pour errno */
#include <string.h>

#include "structures.h"

int main(int argc, char* argv[]){
    if(argc<2 && argc>3){
        printf("ERROR : utilisation : ");
        return(EXIT_FAILURE);
    }
    else if(argc==2){
        if(strcmp(argv[1],"-R")==0){

        }
        else if(strcmp(argv[1],"-S")==0){

        }
        else{
            printf("Argument inconnu.");
        }
    }
    else if(argc==3){
        if(strcmp(argv[1],"-E")==0){

        }
        else{
            printf("Argument %s inconnu.",argv[1]);
        }
    }
}