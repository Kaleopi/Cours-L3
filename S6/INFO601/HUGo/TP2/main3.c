#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "ncurses.h"

int main(int argc, char *argv[]){
    
    int fichierBase, fichierCopie, ret;
    char *temp;

    /* Ouverture du fichier de base */
    fichierBase = open(argv[1], O_RDONLY);
    if(fichierBase == -1){
        printf("Erreur lors de l'ouverture du fichier (open).\n");
        return EXIT_FAILURE;
    }
    else{
        /* Création du fichier ou l'on copie les informations */
        fichierCopie = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, S_IRWXU);
        if(fichierCopie == -1){
            printf("Erreur lors de la création du fichier (Fichier déja existant).\n");
            return EXIT_FAILURE;
        }
        else {
            /* Copie des donnée dans le fichier ou l'on doit copier les données du fichier de base */
            temp = malloc(sizeof(char *));
            lseek(fichierCopie, 0, SEEK_END);
            lseek(fichierBase, 0, SEEK_SET);
            while((ret = read(fichierBase, temp, sizeof(temp)))){
                temp[ret] = '\0';
                lseek(fichierCopie, 0, SEEK_END);
                ret = write(fichierCopie, temp, strlen(temp));
                if(ret == -1){
                    printf("Erreur lors de l'écriture dans le fichier (write).\n");
                    perror(strerror(errno));
                    return EXIT_FAILURE;
                }
            }
        }
    }

    /* Fermeture des fichier et destruction des mallocs */
    close(fichierBase);
    close(fichierCopie);
    free(temp);

    return EXIT_SUCCESS;
}
