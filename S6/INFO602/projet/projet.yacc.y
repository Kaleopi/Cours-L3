%{
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "ncurses.h"
#include "includes.h"

extern FILE *yyin;
plateau_t *plateau;
robot_t *robot;
liste_t liste_cases;
liste_hachage_t lh;

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
%token <string> OPERATEUR
%token HAUTEUR LARGEUR X Y TYPEJSON BLOC BILLE CAISSE TROU CASE CASES DEBUT DIRECTION BAS HAUT DROITE GAUCHE
%token TYPE PROC FUNC F_AVANCE F_DROITE F_GAUCHE FINTQ FINPROC FINFUNC
%token <string> INFEG
%token <string> SUPEG
%token <string> EGGEGG
%token <string> INF
%token <string> SUP

%type <intval> direction
%type <intval> type
%type <string> comparateur
%type <string> valeur
%type <string> ligne
%type <string> expbool

%%
parser:
    json
    |
    pseudocode;

/* json */
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
      cell_t cellule;
      cellule.position.x = $4;
      cellule.position.y = $8;
      cellule.type = M_ROBOT;
      ajouter_cellule(&liste_cases,&cellule);
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

/* pseudocode */
    pseudocode:
      procedure pseudocode
      |
      procedure;

    procedure:
      PROC signature;

    signature:
      "main()" code FINPROC
      |
      NOM '(' arguments ')' code FINPROC;

    arguments:
      argument ',' arguments
      |
      argument;

    argument:
      NOM ':' TYPE;

    code:
      ligne code
      |
      ligne;

    ligne:
      affectaction
      |
      appelproc
      |
      conditionnelle
      |
      boucle;

    affectaction:
      NOM '=' calcul;

    calcul:
      calcul OPERATEUR valeur
      |
      valeur;

    valeur:
      NOM
      |
      ENTIER{
        sprintf($$,"%d",$1);
      };

    appelproc:
      NOM'('params')'
      |
      NOM"()";

    params:
      param
      |
      params ',' param;

    param:
      NOM{printf("%s",$1);}
      |
      ENTIER{printf("%d",$1);};

    conditionnelle:
      "si(" expbool')' code sinon "finsi"{
        printf("conditionelle : si(%s) %s %s finsi",$2,$4,$5);
      };

    sinon:
      "sinon" code
      |
      ;

    boucle:
      "tantque("expbool")" code FINTQ;

    expbool:
      valeur comparateur valeur;

    comparateur:
      INFEG|SUPEG|EGGEGG|INF|SUP;

%%

int main(int argc, char* argv[]) {
  FILE* fd;
  WINDOW *sokoban, *debug, *legende;
  plateau = malloc(sizeof(plateau_t));
  robot = malloc(sizeof(robot_t));
  int hauteur,largeur;
  init_liste(&liste_cases);

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

  ncurses_initialiser();
  sokoban = creer_fenetre(hauteur,largeur,2,10);
  mvprintw(0,0, "Projet 602 - GIGOUT Thomas - DAUNIQUE Wilfried");
  legende = creer_fenetre(10,20,2,21);
  /* Écriture légendes */
  mvwprintw(legende,0,6, "Légende");
  wattron(legende,COLOR_PAIR(2));
  mvwprintw(legende,2,1," ");
  wattroff(legende,COLOR_PAIR(2));
  wattron(legende,COLOR_PAIR(3));
  mvwprintw(legende,3,1," ");
  wattroff(legende,COLOR_PAIR(3));
  wattron(legende,COLOR_PAIR(4));
  mvwprintw(legende,4,1," ");
  wattroff(legende,COLOR_PAIR(4));
  wattron(legende,COLOR_PAIR(5));
  mvwprintw(legende,5,1," ");
  wattroff(legende,COLOR_PAIR(5));
  wattron(legende,COLOR_PAIR(6));
  mvwprintw(legende,6,1," ");
  wattroff(legende,COLOR_PAIR(6));
  wattron(legende,COLOR_PAIR(7));
  mvwprintw(legende,7,1," ");
  wattroff(legende,COLOR_PAIR(7));
  mvwprintw(legende,2,2," Vide");
  mvwprintw(legende,3,2," Bloc");
  mvwprintw(legende,4,2," Robot");
  mvwprintw(legende,5,2," Caisse");
  mvwprintw(legende,6,2," Bille");
  mvwprintw(legende,7,2," Trou");
  wrefresh(legende);

  update(sokoban,plateau,robot);
  sleep(10);


  /* fin de l'execution */
  ncurses_stopper();
  destroy_liste(&liste_cases);
  free(plateau->cases);
  free(plateau);
  free(robot);

  return EXIT_SUCCESS;
}
