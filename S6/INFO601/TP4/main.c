#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int main(int argc,char *argv[]){
    pid_t p;
    int i,n,r,s,val,ret;

    // srand(time(NULL));
    if(argc!=2){
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);
    val = (rand()%2)+1;
    for (i=0;i<n;++i){
        if((p=fork())==0){
            srand(time(NULL)+getpid());
            r = rand()%n;
            p=wait(&s);
            printf("Processus : %d\n\tRandom : %d \n\tPID : %d\n",i,r,getpid());
            sleep(val);
            exit(0);
        }
    }
    for(int i=0;i<n;i++){
        printf("%d terminé.\n",wait(&s));
    }
    exit(0);
}