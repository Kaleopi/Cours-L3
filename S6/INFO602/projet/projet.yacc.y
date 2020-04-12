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
/* %define parse.error verbose */

%union {
  int intval;
  char *string;
}

%token <intval> ENTIER
%token <string> NOM
%token VRAI FAUX
%token <string> OPERATEUR
%token HAUTEUR LARGEUR X Y TYPEJSON BLOC BILLE CAISSE TROU CASE CASES DEBUT DIRECTION BAS HAUT DROITE GAUCHE
%token FUNC FINPROC PROC FINTQ
%token <string> INFEG
%token <string> SUPEG
%token <string> EGGEGG
%token <string> INF
%token <string> SUP


%type <string> pseudocode
%type <string> procedure
%type <string> signature
%type <intval> direction
%type <intval> type
%type <string> conditionnelle
%type <string> comparateur
%type <string> valeur
%type <string> ligne
%type <string> expbool
%type <string> affectaction
%type <string> appelproc
%type <string> boucle
%type <string> code
%type <string> calcul
%type <string> params
%type <string> param
%type <string> argument
%type <string> arguments
%type <string> sinon
%type <string> typearg
%type <string> variable

%%
parser:
    json{
      printf("json\n");
    }
    |
    pseudocode{
      printf("pseudocode\n%s",$1);
    };

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
      procedure pseudocode{
        sprintf($$,"%s %s",$1,$2);
      }
      |
      procedure{
        sprintf($$,"%s",$1);
      };

    procedure:
      PROC signature{
        sprintf($$,"proc %s",$2);
      };

    signature:
      NOM '(' arguments ')' code FINPROC{
        sprintf($$,"%s(%s)\n%s\nfinproc",$1,$3,$5);
      };

    arguments:
      argument{
        sprintf($$,"%s",$1);
      }
      |
      arguments ',' argument{
        sprintf($$,"%s %s",$1,$3);
      };

    argument:
      variable ':' typearg{
        /* printf("j'ai un argument %s", $1); */
        sprintf($$,"%s %s",$1,$3);
        printf("%s",$$);
      };

    variable:
      NOM{
        sprintf($$,"%s",$1);
      }

    typearg:
      NOM{
        sprintf($$,"%s",$1);
      };

    code:
      ligne code
      |
      ligne;

    ligne:
      affectaction{
        sprintf($$,"%s",$1);
      }
      |
      appelproc{
        sprintf($$,"%s",$1);
      }
      |
      conditionnelle{
        sprintf($$,"%s",$1);
      }
      |
      boucle{
        sprintf($$,"%s",$1);
      };

    affectaction:
      NOM '=' calcul{
        sprintf($$,"%s = %s",$1,$3);
      };

    calcul:
      calcul OPERATEUR valeur{
        sprintf($$,"%s %s %s",$1,$2,$3);
      }
      |
      valeur{
        sprintf($$,"%s",$1);
      };

    valeur:
      NOM{
        sprintf($$,"%s",$1);
      }
      |
      ENTIER{
        sprintf($$,"%d",$1);
      };

    appelproc:
      NOM'('params')'{
        sprintf($$,"%s(%s)",$1,$3);
      }
      |
      NOM"()"{
        sprintf($$,"%s()",$1);
      };

    params:
      param{
        sprintf($$,"%s",$1);
      }
      |
      params ',' param{
        sprintf($$,"%s,%s",$1,$3);
      };

    param:
      NOM{
        sprintf($$,"%s",$1);
      }
      |
      ENTIER{
        sprintf($$,"%d",$1);
      };

    conditionnelle:
      "si(" expbool')' code sinon "finsi"{
        sprintf($$,"si(%s)\n%s\n%s\nfinsi",$2,$4,$5);
      };

    sinon:
      "sinon" code{
        sprintf($$,"sinon\n%s",$2);
      }
      |
      {
        sprintf($$,";");
      };

    boucle:
      "tantque("expbool")" code FINTQ{
        sprintf($$,"tantque(%s)\n%s\nfintantque",$2,$4);
      };

    expbool:
      valeur comparateur valeur{
        sprintf($$,"%s %s %s",$1,$2,$3);
      };

    comparateur:
      INFEG{
        sprintf($$,"%s",$1);
      }
      |
      SUPEG{
        sprintf($$,"%s",$1);
      }
      |
      EGGEGG{
        sprintf($$,"%s",$1);
      }
      |
      INF{
        sprintf($$,"%s",$1);
      }
      |
      SUP{
        sprintf($$,"%s",$1);
      };

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
  printf("Parsing %s\n\n",argv[1]);
  yyparse();
  if((fclose(fd))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };
  if((fd=fopen(argv[2],"r"))==NULL){
    printf("Erreur lors de l'ouverture du fichier \"%s\"",argv[2]);
    exit(EXIT_FAILURE);
  }
  yyin = fd;
  printf("Parsing %s\n\n",argv[2]);
  yyparse();
  if((fclose(yyin))==EOF){
    fprintf(stderr, "Erreur lors de la fermeture du fichier");
  };

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
