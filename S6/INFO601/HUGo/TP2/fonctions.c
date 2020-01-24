#include "fonctions.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int creationFichier(char *filename){

    int fd;
    fd = open(filename, O_CREAT | O_RDWR | O_EXCL, S_IRWXU);

    if(fd == -1){
        printf("Erreur lors de la création du fichier (%s)", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Fichier (%s) créé.", filename);
    return fd;
}

int chargerFichier(char *filename){

    int fd; 
    fd = open(filename, O_WRONLY);

    if(fd == -1){
        printf("Erreur lors de l'ouverture du fichier (%s)", strerror(errno));
        return EXIT_FAILURE;
    }

    return fd;
}

int chargerFichierDecors(char *file1, char *nomDecors){

    int fd, ret;

    fd = open(file1, O_CREAT | O_RDWR | O_EXCL, S_IRWXU);
    if(fd == 1){
        printf("Erreur lors de l'ouverture / creation du fichier (%s)", strerror(errno));
        return EXIT_FAILURE;
    }

    ret = write(fd, nomDecors, strlen(nomDecors));
    
    if(ret == -1){
        printf("Erreur lors de l'écriture du nom de décor dans le fichier (%s)", strerror(errno));
    }

    return fd;
}

int copy(int fd1, int fd2){

    int ret;
    char* text;
    text = malloc(sizeof(char *));

    lseek(fd1, 0, SEEK_SET);
    
    while ((ret = read(fd1, text, sizeof(text)))){
        text[ret] = '\0';
        lseek(fd2, 0, SEEK_END);
        ret = write(fd2, text, strlen(text));

        if(ret ==-1){
            printf("Erreur lors de l'écriture dans le fichier (%s).\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    free(text);
    return EXIT_SUCCESS;
    

}