%{
#include "y.tab.h"

int yylex();
void yyerror(const char *erreurMsg);
%}

CHIFFRE   [0-9]
ENTIER    [CHIFFRE}+

%%

[0-9]+	 {
           yylval = atoi(yytext);
           return ENTIER;
         }
[*-+/\.]	 { return *yytext; }
[ \t\n]	 ;
.        yyerror("Caractère non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}
