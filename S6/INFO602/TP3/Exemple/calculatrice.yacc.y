%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *erreurMsg);
%}

%token ENTIER

%%

programme: expression '.' {
           printf("=%d\n", $1);
      }
      programme
      |
      ;

expression: ENTIER
      | expression '+' expression {
        $$ = $1 + $3;
      }
      | '-' expression {
        $$ = -$2;
      }
      | expression '-' expression {
        $$ = $1 - $3;
      }
      | expression '*' expression {
        $$ = $1 * $3;
      }
      | expression '/' expression {
        if($3 == 0){
          printf("Division impossible par 0\n");
          $$ = $1;
        }else{
          $$ = $1/$3;
        }
      }

%%

int main(void) {
  yyparse();
  return EXIT_SUCCESS;
}
