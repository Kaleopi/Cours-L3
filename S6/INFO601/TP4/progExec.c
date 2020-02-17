#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

// void execution(char *argve[]);

int main(int argc,char *argv[], char *argve[]){
    int i;
    i = 20;
    pid_t pid;
    if(pid==fork()==-1){
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        // execution(argve);
        printf("%s",argve);
    }
    if(waitpid(pid, NULL, 0)==-1){
        perror("Erreur lors de l'attente de la fin du programme.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// void execution(char *argve[]){
//     printf("Je démarre le programme...\n");
//     if(execve("./execWait"))
// }