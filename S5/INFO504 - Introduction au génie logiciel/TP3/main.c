#include <stdlib.h>
#include <stdio.h>
#include "strangeFunction.h"
#include <time.h>
#define TAB 100000
#define MIN 127
#define MAX 2047

int monstrlength(const char* str){
  int i = 0;
  while(str[i]!='\0'){
    i++;
  }
  return i;
}

char* strRandom(int min, int max){
  srand(time(NULL));
  int length = (rand() % (max - min + 1)) + min;
  char *str = malloc(sizeof(char)*length);
  for(int i=0 ; i<length ; i++){
    char c = 'A' + (rand()%26);
    str[i] = c;
  }
  return str;
}

int main(void){
  char* tab1[TAB];
  char* tab2[TAB];
  clock_t t;
  double time;

  for(int i=0 ; i<1 ; i++){
    tab1[i] = strRandom(MIN,MAX);
    tab2[i] = strRandom(MIN,MAX);
  }

  //TEST 1
  t = clock();
  for(int i=0 ; i<TAB ; i++){
    monstrlength(tab1[i]);
  }
  t = clock()-t;
  time = ((double)(t))/CLOCKS_PER_SEC;
  printf("Temps monstrlength sur tab1 : %f",time);

  //TEST 2
  t=clock();
  for(int i=0 ; i<TAB ; i++){
    strange_function(tab1[i]);
  }
  t = clock()-t;
  time=((double)(t))/CLOCKS_PER_SEC;
  printf("\nTemprs strange_function sur tab2 : %f",time);

  //TEST 3
  for(int i=0 ; i<TAB ; i++){
    monstrlength(tab1[i]);
  }
  for(int i=0 ; i<TAB ; i++){
    strange_function(tab1[i]);
  }
  return 0;
}
















// // char* str = "123456789123456789";
// // size_t retour;
// // retour = strange_function(str);
// // printf("%d\n",retour);
// // printf("mon test : %d",monstrlength(str));
//
// char* tab1[TAB];
// char* tab2[TAB];
// printf("test1");
// for(int i=0 ; i<5 ; i++){
//   tab1[i] = strRandom(MIN,MAX);
//   tab2[i] = strRandom(MIN,MAX);
//   printf("test");
//   printf("%s",tab1[i]);
//   printf("\n----\n");
//   printf("%s",tab2[i]);
// }
// printf("test2");
