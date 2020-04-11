%{
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;

int yylex();
void yyerror(const char *erreurMsg);
%}
%define parse.error verbose

%union {
  int intval;
  char string[100];
}

%token <intval> ENTIER
%token <string> NOM
%token VRAI FAUX
%token HAUTEUR LARGEUR X Y TYPEJSON BLOC BILLE CAISSE TROU CASE CASES DEBUT DIRECTION BAS HAUT DROITE GAUCHE

%type <string> json
%type <string> lelems
%type <string> elemjson
%type <string> debutjson
%type <string> direction
%type <string> tabcases
%type <string> scase
%type <string> cases
%type <string> type
%%
json:
    '{' lelems '}'{
      printf("%s",$2);
    };

lelems:
    elemjson ',' lelems{
      printf("%s",$1);
    }
    |
    elemjson{
      printf("%s",$1);
    };

elemjson:
    LARGEUR ':' ENTIER {
      printf("Largeur plateau : %d\n",$3);
    }
    |
    HAUTEUR ':' ENTIER {
      printf("Hauteur plateau : %d\n",$3);
    }
    |
    DEBUT ':' debutjson {}
    |
    CASES ':' tabcases {};

debutjson:
    '{'X':'ENTIER','Y':'ENTIER','DIRECTION':'direction'}'{
      printf("Robot x : %d y : %d direction : %s\n",$4,$8,$12);
    };

direction:
    BAS {sprintf($$,"BAS");}
    |
    HAUT {sprintf($$,"HAUT");}
    |
    DROITE {sprintf($$,"DROITE");}
    |
    GAUCHE {sprintf($$,"GAUCHE");};

tabcases:
    '['cases']' {};

cases:
    scase ',' cases
    |
    scase {};

scase:
    '{'X':'ENTIER','Y':'ENTIER','TYPEJSON':'type'}'{
      printf("Case x : %d y : %d type : %s\n",$4,$8,$12);
    };

type:
    CAISSE {
      sprintf($$,"CAISSE");
    }
    |
    TROU {
      sprintf($$,"TROU");
    }
    |
    BILLE {
      sprintf($$,"BILLE");
    }
    |
    BLOC {
      sprintf($$,"BLOC");
    };
%%

int main(int argc, char* argv[]) {
  FILE* fd;
  if((fd=fopen(argv[1],"r"))==NULL){
    fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\"",argv[1]);
    exit(EXIT_FAILURE);
  }
  yyin = fd;
  yyparse();
  if((fclose(fd))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };
  /* if((yyin=fopen(argv[2],"r"))==NULL){
    printf("Erreur lors de l'ouverture du fichier \"%s\"",argv[2]);
    exit(EXIT_FAILURE);
  }
  yyparse();
  if((fclose(yyin))==EOF){
    printff(stderr, "Erreur lors de la fermeture du fichier");
  }; */
  return EXIT_SUCCESS;
}
