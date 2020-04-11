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
    HAUTEUR = 262,
    LARGEUR = 263,
    X = 264,
    Y = 265,
    TYPEJSON = 266,
    BLOC = 267,
    BILLE = 268,
    CAISSE = 269,
    TROU = 270,
    CASE = 271,
    CASES = 272,
    DEBUT = 273,
    DIRECTION = 274,
    BAS = 275,
    HAUT = 276,
    DROITE = 277,
    GAUCHE = 278,
    TYPE = 279,
    PROC = 280,
    FUNC = 281,
    F_AVANCE = 282,
    F_DROITE = 283,
    F_GAUCHE = 284,
    FINTQ = 285,
    FINPROC = 286,
    FINFUNC = 287,
    INFEG = 288,
    SUPEG = 289,
    EGEG = 290,
    INF = 291,
    SUP = 292
  };
#endif
/* Tokens.  */
#define ENTIER 258
#define NOM 259
#define VRAI 260
#define FAUX 261
#define HAUTEUR 262
#define LARGEUR 263
#define X 264
#define Y 265
#define TYPEJSON 266
#define BLOC 267
#define BILLE 268
#define CAISSE 269
#define TROU 270
#define CASE 271
#define CASES 272
#define DEBUT 273
#define DIRECTION 274
#define BAS 275
#define HAUT 276
#define DROITE 277
#define GAUCHE 278
#define TYPE 279
#define PROC 280
#define FUNC 281
#define F_AVANCE 282
#define F_DROITE 283
#define F_GAUCHE 284
#define FINTQ 285
#define FINPROC 286
#define FINFUNC 287
#define INFEG 288
#define SUPEG 289
#define EGEG 290
#define INF 291
#define SUP 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "projet.yacc.y" /* yacc.c:1909  */

  int intval;
  char string[100];

#line 133 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
