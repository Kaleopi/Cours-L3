#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "ncurses.h"
#include "functions.h"

int main(int argc, char *argv[]){
    char* fname = argv[1];
    if(exist(fname)!=EXIT_FAILURE){
        int fd = open(fname,O_RDONLY);
        printf("Taille du fichier \"%s\" : %d\n",fname,sizeoffile(fd));

    }

    return EXIT_SUCCESS;
}