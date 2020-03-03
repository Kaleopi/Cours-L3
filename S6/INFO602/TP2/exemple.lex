/*Les déclarations en C*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void digi();
void oppl();
void affpile();
float pile[255];
int sommet=0;
int i=0;
int numLigne = 1;
%}

/*Définitions*/
FLOAT (\-[0-9]+|([0-9]*)"."([0-9]+))|([0-9]+|([0-9]*)"."([0-9]+))
/*Règles*/
%%
{FLOAT} {digi();} 
[+-/^*] {oppl();} 
[=] {affpile();} 
\n      numLigne++;
.       ;
  
%%
void digi() 
{ 
  pile[sommet]=atof(yytext);
  printf("%s\n", yytext);
  printf("'%f'\n",pile[sommet]);
  sommet++;

}
void oppl()
{

  if(sommet>1){
    switch(yytext[0]){
        case '+':
          printf("%f  +  %f", pile[sommet-2] ,pile[sommet-1]);
          pile[sommet-2]=pile[sommet-2]+pile[sommet-1];
          break;
        case '-':
          printf("%f  -  %f ", pile[sommet-2]  ,pile[sommet-1]);
          pile[sommet-2]=pile[sommet-2]-pile[sommet-1];
          break;
        case '*':
          printf("%f  *  %f ", pile[sommet-2]  ,pile[sommet-1]);
          pile[sommet-2]=pile[sommet-2]*pile[sommet-1];
          break;
        case '/':
          printf("%f  /  %f ", pile[sommet-2] ,pile[sommet-1]);
          pile[sommet-2]=pile[sommet-2]/pile[sommet-1];
          break;
        case '^':
          printf("%f ^ %f", pile[sommet-2]  ,pile[sommet-1]);
          pile[sommet-2]=pow(pile[sommet-2],pile[sommet-1]);
          break;
        
    }
     sommet--;

    printf(" = %f \n ", pile[sommet-1]);
  }
}
  void affpile()
  {
    for(i=0;i<sommet;i++){
      printf("[%f]",pile[i]);
    }
  }

int main() {
  yylex();
  printf("Lignes %d\n", numLigne);
  return EXIT_SUCCESS;
}