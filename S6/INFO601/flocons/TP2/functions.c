#include "functions.h"

int exist(const char* fname){
    int res;
    int file = open(fname, O_WRONLY);
    if(file==-1){
        printf("Erreur : le fichier \"%s\" n'existe pas.\n",fname);
        res = EXIT_FAILURE;
    }else{
        // printf("Le fichier "%s" existe.\n",fname);
        res = file;
    }
    return res;
}

int sizeoffile(int fd){
    int res = -1;
    if(fd!=-1){
        off_t old=lseek(fd,0,SEEK_CUR);
        off_t end=lseek(fd,0,SEEK_END);
        int i = 0;
        while(old!=end){
            old =lseek(fd,i,SEEK_SET);
            i++;
        }
        close(fd);
        res = i-1;
    }
    return res;
}

int copier(int fd1, int fd2){
    int res;
    char* chaine = malloc(sizeof(char *));

    lseek(fd1, 0, SEEK_SET);
    while ((res = read(fd1, chaine, sizeof(chaine)))){
        chaine[res] = '\0';
        lseek(fd2, 0, SEEK_END);
        res = write(fd2, chaine, strlen(chaine));
        if(res==-1){
            printf("Erreur lors de l'écriture dans le fichier \"%s\".\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    free(chaine);
    return EXIT_SUCCESS;
    

}