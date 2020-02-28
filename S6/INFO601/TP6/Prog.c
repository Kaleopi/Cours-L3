/**
 * @author GIGOUT DAUNIQUE
 **/
#include <stdlib.h>     /* Pour exit, EXIT_FAILURE, EXIT_SUCCESS */
#include <stdio.h>      /* Pour printf, perror */
#include <sys/msg.h>    /* Pour msgget, msgctl */
#include <errno.h>      /* Pour errno */
#include <string.h>

#include "structures.h"
#include "fonctions.h"

void error_args(){
    printf("ERROR : Arguments manquants.\n\tCLE : clé de la file de messages.\n\t-R : recevoir message\n\t-S : supprimer message.\n\t-E \"message\" : envoyer \"message\".\n\nExemples :\n\t./Prog CLE -R|-S\n\t./Prog CLE -E \"message\"\n");
}

int main(int argc, char* argv[]){
    if(argc<3){
        error_args();
        return(EXIT_FAILURE);
    }
    else if(argc==3){
        if(strcmp(argv[2],"-R")==0){
            printf("receive");
            /*recevoirmsg();*/
        }
        else if(strcmp(argv[2],"-S")==0){
            /*supprimermsg();*/
            printf("suppr");
        }
        else if(strcmp(argv[2],"-E")==0){
            error_args();
        }
        else{
            printf("Argument %s inconnu.",argv[2]);
        }
    }
    else if(argc==4){
        if(strcmp(argv[2],"-E")==0){
            printf("envoi du message %s avec la clé %s\n",argv[3], argv[1]);
        }
        else{
            printf("Argument %s inconnu.",argv[1]);
        }
    }


    return(EXIT_SUCCESS);
}