#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "ncurses.h"

int main(int argc, char *argv[]){
    char *buff;
    char *temp;
    int ret;
    int taille = 0;
    int fd;

    /* Ouverture / création du fichier */
    temp = malloc(sizeof(char*));
    fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU);
    if(fd != 0 ){
        printf("Que voulez vous écrire dans le fichier (8 caractères maximum) ? ");
        ret = scanf("%8s", temp);

        /* Ecriture dans le fichier */
        if(ret == 1){
            lseek(fd, 0, SEEK_END);
            ret = write(fd, temp, sizeof(char*));
        }
    }
    else if(fd == -1){
        printf("ret lors de l'ouverture du fichier (fonction open).");
        return EXIT_FAILURE;
    }

    /* affichage Ligne par ligne (8 caractères par lignes) */
    buff = malloc(sizeof(char*));
    lseek(fd, 0, SEEK_SET);
    while((ret = read(fd, buff, sizeof(buff)))){
        buff[ret] = '\0';
        printf("Chaîne de caractères : %s\n", buff);
    }

    /* Affichage de la taille */
    taille = lseek(fd, 0, SEEK_END);
    if(errno != 0){
        printf("ret : ");
    }
    printf("\nVotre fichier fait : %d\n", taille);

    /* Fermeture du fichier et destruction de tous les mallocs */
    close(fd);
    free(temp);
    free(buff);

    return EXIT_SUCCESS;
}
