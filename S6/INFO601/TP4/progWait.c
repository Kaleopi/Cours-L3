#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int main(int argc,char *argv[], char *argve[]){
    int i;
    if(argc!=2){
        printf("Erreur : nombre d'argument invalide.\n\tUsage : progWait <time>\n");
        exit(EXIT_FAILURE);   
    }
    i = atoi(argv[1]);
    printf("Bonjour, grêve de %d secondes. Merci de votre patience. LA SNCF.\n",i);
    sleep(i);
    printf("Attente terminée.\n");
    exit(EXIT_SUCCESS);
}