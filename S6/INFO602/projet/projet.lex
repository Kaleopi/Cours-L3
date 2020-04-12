%{
#include "y.tab.h"

int yylex();
void yyerror(const char *erreurMsg);
%}

/* global */
ENTIER    [0-9]+
OPERATEUR [*+-/]
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
PROC      "proc"
FUNC      "procfunc"
FINTQ     "fintantque"
FINPROC   "finproc"
INFEG     "<="
SUPEG     ">="
EGGEGG    "=="
INF       "<"
SUP       ">"
NOM       [a-z]+

%%
{ENTIER}    { yylval.intval = atoi(yytext); return ENTIER; }
{OPERATEUR} { return *yytext; }
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
{PROC}      { return PROC; }
{FUNC}      { return FUNC; }
{FINTQ}     { return FINTQ; }
{FINPROC}   { return FINPROC; }
{NOM}       {
              yylval.string = yytext;
              return NOM;
            }
{INFEG}     { return *yytext; }
{SUPEG}     { return *yytext; }
{EGGEGG}    { return *yytext; }
{INF}       { return *yytext; }
{SUP}       { return *yytext; }

[*-+/:\[\]\{\},\.\(\)=] { return *yytext; }
[ \t\n\r]	 ;

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}
