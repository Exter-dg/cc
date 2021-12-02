%{
   /* Definition section */
  #include <stdio.h>
%}
  
%token NUMBER ID IF ELSE FOR CLASS EQL_OPR OBJ_OPR
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%start SS
  
/* Rule Section */
%%

SS : SS S
   | S
   ;

S  :   A ';'
   |   I ';'
   |   IFST
   |   FORST
   |   CLASSST
   |   OBJST ';'
   ;

OBJST :  ID OBJ_OPR ID '=' N
      ;

IFST : IF '(' R ')' S ELSEST
     | IF '(' R ')' '{' SS '}' ELSEST
     ;

ELSEST : ELSE S
       | ELSE '{' SS '}'
       |
       ;

FORST : FOR '(' FA ';' FR ';' FI ')' S
      | FOR '(' FA ';' FR ';' FI ')' '{' SS '}'
      ;

FA    : A
      | 
      ;

FR    : R
      |
      ;

FI    : I
      |
      ;

CLASSST : CLASS ID '{' SS '}' ';'
        ;

N  :   N '+' N   
   |   N '-' N  
   |   N '*' N   
   |   N '/' N   
   |   N '%' N  
   |   '(' N ')'  
   |   NUMBER 
   |   ID
   ;

R  :  R '<' R
   |  R '>' R
   |  R '>''=' R
   |  R '<''=' R
   |  R EQL_OPR R
   |  ID
   |  NUMBER
   ;


I  :  I '+''+'
   |  I '-''-'
   |  ID
   ;

A  :  ID '=' N
   |  ID '=' R
   |  ID '+''=' N
   |  ID '-''=' N
   |  ID '*''=' N 
   |  ID '/''=' N 
   ;
  
%%
  
//driver code
void main()
{
   yyparse();
   printf("\nEntered expression is valid\n\n");
}
  
void yyerror()
{
   printf("\nEntered expression is Invalid\n\n");
   exit(0);
}