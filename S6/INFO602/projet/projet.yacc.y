%{
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ncurses.h"
#include "includes.h"
#include "liste.h"
#include <unistd.h>

extern FILE *yyin;
plateau_t *plateau;
robot_t *robot;
liste_t liste_cases;

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
%token TYPE PROC FUNC F_AVANCE F_DROITE F_GAUCHE FINTQ FINPROC FINFUNC INFEG SUPEG EGEG INF SUP

%type <intval> direction
%type <intval> type
%%
/* parser:
    json
    |
    pseudocode; */

json:
    '{' lelems '}';

lelems:
    elemjson ',' lelems
    |
    elemjson;

elemjson:
    LARGEUR ':' ENTIER {
      plateau->largeur = $3;
    }
    |
    HAUTEUR ':' ENTIER {
      plateau->hauteur = $3;
    }
    |
    DEBUT ':' debutjson {}
    |
    CASES ':' tabcases {};

debutjson:
    '{'X':'ENTIER','Y':'ENTIER','DIRECTION':'direction'}'{
      robot->x = $4;
      robot->y = $8;
      robot->direction = $12;
      /* printf("Robot x : %d y : %d direction : %d\n",robot->x,robot->y,robot->direction); */
    };

direction:
    BAS {$$ = M_BAS;}
    |
    HAUT {$$ = M_HAUT;}
    |
    DROITE {$$ = M_DROITE;}
    |
    GAUCHE {$$ = M_GAUCHE;};

tabcases:
    '['cases']' {};

cases:
    scase ',' cases
    |
    scase {};

scase:
    '{'X':'ENTIER','Y':'ENTIER','TYPEJSON':'type'}'{
      cell_t cellule;
      cellule.position.x = $4;
      cellule.position.y = $8;
      cellule.type = $12;
      ajouter_cellule(&liste_cases,&cellule);
      /* printf("Case x : %d y : %d type : %d\n",cellule.position.x,cellule.position.y,cellule.type); */
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

    /* pseudocode: */

%%

int main(int argc, char* argv[]) {
  FILE* fd;
  WINDOW *box, *sokoban, *debug, *debug_box;
  plateau = malloc(sizeof(plateau_t));
  robot = malloc(sizeof(robot_t));
  int hauteur,largeur;
  /* init_liste(&liste_cases); */

  if((fd=fopen(argv[1],"r"))==NULL){
    fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\"",argv[1]);
    exit(EXIT_FAILURE);
  }
  yyin = fd;
  yyparse();
  /* if((fclose(fd))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };
  if((yyin=fopen(argv[2],"r"))==NULL){
    printf("Erreur lors de l'ouverture du fichier \"%s\"",argv[2]);
    exit(EXIT_FAILURE);
  }
  yyparse();
  if((fclose(yyin))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  }; */

  if(plateau->hauteur <= 0){
    fprintf(stderr,"La hauteur du plateau est nulle ou négative.\n");
  }
  hauteur = plateau->hauteur;
  if(plateau->largeur <= 0){
    fprintf(stderr,"La largeur du plateau est nulle ou négative.\n");
  }
  largeur = plateau->largeur;
  plateau->cases = malloc(sizeof(int)*hauteur*largeur);
  init_plateau(plateau,&liste_cases);
  afficher_plateau(plateau);


  ncurses_initialiser();
  sokoban = creer_fenetre(hauteur,largeur);
  mvprintw(0,0, "Projet 3 - GIGOUT Thomas - DAUNIQUE Wilfried");
  update(sokoban,plateau,robot);
  refresh();
  sleep(3);


  /* fin de l'execution */
  ncurses_stopper();
  destroy_liste(&liste_cases);
  free(plateau->cases);
  free(plateau);
  free(robot);

  return EXIT_SUCCESS;
}
