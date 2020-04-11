%{
#include <stdio.h>
#include <stdlib.h>
#include "includes.h"
#include <string.h>

extern FILE *yyin;
plateau_t *plateau;
robot_t *robot;

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
%type <intval> type
%%
json:
    '{' lelems '}'{
      int i;
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
      plateau->largeur = $3;
      printf("Largeur plateau : %d\n",$3);
    }
    |
    HAUTEUR ':' ENTIER {
      plateau->hauteur = $3;
      printf("Hauteur plateau : %d\n",$3);
    }
    |
    DEBUT ':' debutjson {}
    |
    CASES ':' tabcases {
      printf("ICI %d %d",plateau->largeur,plateau->hauteur);
    };

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
    '['cases']' {
      int i,j;
      /* for(i=0 ; i<plateau->largeur; i++){
        for(j=0 ; j<plateau->hauteur ; j++){
          printf("%d ",plateau->cases[j*plateau->largeur + i]);
        }
        printf("\n");
      } */
    };

cases:
    scase ',' cases
    |
    scase {};

scase:
    '{'X':'ENTIER','Y':'ENTIER','TYPEJSON':'type'}'{
      int choix;
      /* plateau->cases[$8 * plateau->largeur + $4] = choix; */
      printf("%d",$8*plateau->largeur+$4);
      /* printf(" valeur trouvée %d\n",plateau->cases[$8 * plateau->largeur +$4]); */
      printf("Case x : %d y : %d type : %d\n",$4,$8,$12);
    };

type:
    CAISSE {
      $$ = M_CAISSE;
    }
    |
    TROU {
      $$ = M_TROU;
    }
    |
    BILLE {
      $$ = M_BILLE;
    }
    |
    BLOC {
      $$ = M_BLOC;
    };
%%

int main(int argc, char* argv[]) {
  FILE* fd;
  plateau = malloc(sizeof(plateau_t));
  robot = malloc(sizeof(robot_t));

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
