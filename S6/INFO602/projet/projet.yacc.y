%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *erreurMsg);
%}

%token ENTIER
%token <str> NOM
%token SI
%token FINSI
%token FIN
%token ALORS
%token BOOLEEN
%token CASE

%%

%%

int main(void) {
  yyparse();
  return EXIT_SUCCESS;
}
