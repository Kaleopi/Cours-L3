/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ENTIER = 258,
    NOM = 259,
    VRAI = 260,
    FAUX = 261,
    OPERATEUR = 262,
    HAUTEUR = 263,
    LARGEUR = 264,
    X = 265,
    Y = 266,
    TYPEJSON = 267,
    BLOC = 268,
    BILLE = 269,
    CAISSE = 270,
    TROU = 271,
    CASE = 272,
    CASES = 273,
    DEBUT = 274,
    DIRECTION = 275,
    BAS = 276,
    HAUT = 277,
    DROITE = 278,
    GAUCHE = 279,
    TYPE = 280,
    PROC = 281,
    FUNC = 282,
    F_AVANCE = 283,
    F_DROITE = 284,
    F_GAUCHE = 285,
    FINTQ = 286,
    FINPROC = 287,
    FINFUNC = 288,
    INFEG = 289,
    SUPEG = 290,
    EGGEGG = 291,
    INF = 292,
    SUP = 293
  };
#endif
/* Tokens.  */
#define ENTIER 258
#define NOM 259
#define VRAI 260
#define FAUX 261
#define OPERATEUR 262
#define HAUTEUR 263
#define LARGEUR 264
#define X 265
#define Y 266
#define TYPEJSON 267
#define BLOC 268
#define BILLE 269
#define CAISSE 270
#define TROU 271
#define CASE 272
#define CASES 273
#define DEBUT 274
#define DIRECTION 275
#define BAS 276
#define HAUT 277
#define DROITE 278
#define GAUCHE 279
#define TYPE 280
#define PROC 281
#define FUNC 282
#define F_AVANCE 283
#define F_DROITE 284
#define F_GAUCHE 285
#define FINTQ 286
#define FINPROC 287
#define FINFUNC 288
#define INFEG 289
#define SUPEG 290
#define EGGEGG 291
#define INF 292
#define SUP 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "projet.yacc.y" /* yacc.c:1909  */

  int intval;
  char string[100];

#line 135 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
