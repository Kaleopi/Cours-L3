#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "ncurses.h"

int main(int argc, char *argv[]){
    int taille = 0;
    int fd;
    fd = open(argv[1], O_RDWR);
    
    if(fd == -1){
        printf("Erreur lors de l'ouverture du fichier (open).");
        return EXIT_FAILURE;
    }
    else{
        printf("le fichier est bien existant !");
        taille = lseek(fd, 0, SEEK_END);
        if(taille == -1){
            printf("Erreur lors du repositionnement de la tête dans le fichier (lseek).");
            return EXIT_FAILURE;
        }
        printf("\nVotre fichier fait : %d\n", taille);
    }
    close(fd);
    

    return EXIT_SUCCESS;
}