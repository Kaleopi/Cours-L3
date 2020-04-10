%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *erreurMsg);
%}

%union {
  char* string;
}
%token <string> TESTJSON
%token <string> ENTIER
%token <string> NOM
%token VRAI FAUX
%token HAUTEUR LARGEUR X Y TYPEJSON BLOC BILLE CAISSE TROU CASE CASES DEBUT DIRECTION BAS HAUT DROITE GAUCHE
%token TYPE PROC FUNC F_AVANCE F_DROITE F_GAUCHE FINTQ FINPROC FINFUNC INFEG SUPEG EGEG INF SUP

%%
json: TESTJSON{
  printf("%s",$1);
}
/* json: '{' elemjson ',' elemjson ',' elemjson ',' elemjson '}'
    {

    } */
json: '{'elemjson ',' json | elemjson ',' json | '}';

'{'elemjson ',' elemjson ',' '}'


%%

int main(int argc, char* argv[]) {
  /*changer les entrées pour lire le fichier*/
  if((yyin=fopen(argv[1],"r"))==NULL){
    fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\"",argv[1]);
    exit(EXIT_FAILURE);
  }
  yyparse();
  if((fclose(yyin))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };
  if((yyin=fopen(argv[2],"r"))==NULL){
    printf("Erreur lors de l'ouverture du fichier \"%s\"",argv[2]);
    exit(EXIT_FAILURE);
  }
  yyparse();
  if((fclose(yyin))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };
  return EXIT_SUCCESS;
}
