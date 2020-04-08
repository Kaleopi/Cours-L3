%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *erreurMsg);
%}

%union {
  char* string;
}

%token <string> ENTIER
%token <string> TYPE
%token VARIABLE

%%
test: ENTIER {
           printf("=%s\n", $1);
      }
%%

int main(int argc, char* argv[]) {
  /*changer les entrées pour lire le fichier*/

  yyparse();
  return EXIT_SUCCESS;
}
