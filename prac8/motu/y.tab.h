/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    IF = 258,
    INT = 259,
    FLOAT = 260,
    DOUBLE = 261,
    RETURN = 262,
    MAIN = 263,
    VOID = 264,
    FOR = 265,
    BREAK = 266,
    ENDIF = 267,
    identifier = 268,
    integer_constant = 269,
    float_constant = 270,
    ELSE = 271,
    modulo_assignment_operator = 272,
    multiplication_assignment_operator = 273,
    division_assignment_operator = 274,
    addition_assignment_operator = 275,
    subtraction_assignment_operator = 276,
    assignment_operator = 277,
    caret_operator = 278,
    equality_operator = 279,
    inequality_operator = 280,
    lessthan_assignment_operator = 281,
    lessthan_operator = 282,
    greaterthan_assignment_operator = 283,
    greaterthan_operator = 284,
    add_operator = 285,
    subtract_operator = 286,
    multiplication_operator = 287,
    division_operator = 288,
    modulo_operator = 289,
    increment_operator = 290,
    decrement_operator = 291
  };
#endif
/* Tokens.  */
#define IF 258
#define INT 259
#define FLOAT 260
#define DOUBLE 261
#define RETURN 262
#define MAIN 263
#define VOID 264
#define FOR 265
#define BREAK 266
#define ENDIF 267
#define identifier 268
#define integer_constant 269
#define float_constant 270
#define ELSE 271
#define modulo_assignment_operator 272
#define multiplication_assignment_operator 273
#define division_assignment_operator 274
#define addition_assignment_operator 275
#define subtraction_assignment_operator 276
#define assignment_operator 277
#define caret_operator 278
#define equality_operator 279
#define inequality_operator 280
#define lessthan_assignment_operator 281
#define lessthan_operator 282
#define greaterthan_assignment_operator 283
#define greaterthan_operator 284
#define add_operator 285
#define subtract_operator 286
#define multiplication_operator 287
#define division_operator 288
#define modulo_operator 289
#define increment_operator 290
#define decrement_operator 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
