#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "ncurses.h"
#include "fonctions.c"

int main(int argc, char *argv[]){

    int ret = 0;
    int file1 = 0, file2 = 0;

    if(argv[2] == NULL){
        file1 = creationFichier(argv[1]);
    }
    else{
        file1 = chargerFichierDecors(argv[1], argv[2]);
        file2 = creationFichier(argv[3]);
        ret = copy(file1, file2);
        if(ret == EXIT_FAILURE)
            printf("fail");
    }

    


    close(file1);
    close(file2);

    return EXIT_SUCCESS;
}