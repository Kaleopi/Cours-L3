#include <stdlib.h>     /* Pour EXIT_FAILURE */
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ncurses.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int exists(const char *fname)
{
  int i=0;
   int ret=0;
    int file;
    file = open(fname,O_RDONLY|O_WRONLY);
    if(file!=-1)
    {
      off_t old=lseek(file,0,SEEK_CUR);
      off_t end=lseek(file,0,SEEK_END);

    while(old!=end){
        old =lseek(file,i,SEEK_SET);
        i++;
      }
        close(file);
        return i-1;
    }else{
    file=open(fname,O_CREAT|O_WRONLY| O_APPEND,0666);
      char *res="";
        printf("%d",file);
      printf ("entrez une val :");
      int bouya=scanf("%s",res);
      if (bouya!=0){
        for(int i =0 ;i<strlen(res);i++){
        ret=write(file,res,sizeof(res));
        }
      }

      return ret;
    }


}

int copier(const char *fname,const char *fname2){
  int i=0;
  char buf[255];
    int file;
    int file2;
    int r=0;
    file = open(fname,O_RDONLY);
    file2 = open(fname2,O_RDWR|O_CREAT,S_IRWXU);
      if(file2!=-1){
          if(file!=-1){
            off_t old=lseek(file,0,SEEK_CUR);
            off_t end=lseek(file,0,SEEK_END);

              while(old!=end){
                write(file2,buf,255);
                  old =lseek(file,i,SEEK_SET);
                  i++;
                }
              close(file);
              close(file2);
              return i-1;
          }
    }
    return r;
}

int main(int argc , char * argv[]) {
  char* kek=argv[1];
  char* kek2=argv[2];

    //int taille=exists(kek);
    int val=copier(kek,kek2);
    //printf("%d\n",taille);
        printf("%d\n",val);
}
