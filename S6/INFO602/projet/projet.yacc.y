%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *erreurMsg);
%}

%union {
  char* string;
}

%token ENTIER
%token <string> NOM
%token SI
%token FINSI
%token FIN
%token ALORS
%token BOOLEEN
%token CASE

%%

%%

int main(void) {
  /*changer les entrées pour lire le fichier*/
  yyparse();
  return EXIT_SUCCESS;
}
