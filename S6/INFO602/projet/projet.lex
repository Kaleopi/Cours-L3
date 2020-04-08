%{
#include "y.tab.h"

int yylex();
void yyerror(const char *erreurMsg);
%}

/* global */
ENTIER    [0-9]+
VRAI      "true"
FAUX      "false"

/* json */
HAUTEUR   "\"hauteur\""
LARGEUR   "\"largeur\""
X         "\"x\""
Y         "\"y\""
TYPEJSON  "\"type\""
BLOC      "\"BLOC\""
BILLE     "\"BILLE\""
CAISSE    "\"CAISSE\""
TROU      "\"TROU\""
CASE      "\"case\""
CASES     "\"cases\""
DEBUT     "\"debut\""
DIRECTION "\"direction\""
BAS       "\"BAS\""
HAUT      "\"HAUT\""
DROITE    "\"DROITE\""
GAUCHE    "\"GAUCHE\""

/* pseudo-code */
TYPE      (entier|bool)
PROC      "proc"
FUNC      "func"
NOM       [A-Za-z]+
F_AVANCE  "avance()"
F_DROITE  "droite()"
F_GAUCHE  "gauche()"
FINTQ     "fintantque"
FINPROC   "finproc"
FINFUNC   "finfunc"
INFEG     "<="
SUPEG     ">="
EGEG      "=="
INF       "<"
SUP       ">"
%%
{ENTIER}    { return *yytext; }
{VRAI}      { return VRAI; }
{FAUX}      { return FAUX; }

{HAUTEUR}   { return HAUTEUR; }
{LARGEUR}   { return LARGEUR; }
{X}         { return X; }
{Y}         { return Y; }
{TYPEJSON}  { return TYPEJSON; }
{BLOC}      { return BLOC; }
{BILLE}     { return BILLE; }
{CAISSE}    { return CAISSE; }
{TROU}      { return TROU; }
{CASE}      { return CASE; }
{CASES}     { return CASES; }
{DEBUT}     { return DEBUT; }
{DIRECTION} { return DIRECTION; }
{BAS}       { return BAS; }
{HAUT}      { return HAUT; }
{DROITE}    { return DROITE; }
{GAUCHE}    { return GAUCHE; }

{TYPE}      { return *yytext; }
{PROC}      { return PROC; }
{FUNC}      { return FUNC; }
{NOM}       { return NOM; }
{F_AVANCE}  { return F_AVANCE; }
{F_DROITE}  { return F_DROITE; }
{F_GAUCHE}  { return F_GAUCHE; }
{FINTQ}     { return FINTQ; }
{FINPROC}   { return FINPROC; }
{FINFUNC}   { return FINFUNC; }
{INFEG}     { return INFEG; }
{SUPEG}     { return SUPEG; }
{EGEG}      { return EGEG; }
{INF}       { return INF; }
{SUP}       { return SUP; }

[*-+/\[\]\{\},:\.] { return *yytext; }
[ \t\n]	 ;
.        yyerror("Caractère non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}
