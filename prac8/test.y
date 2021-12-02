%{
#include<stdio.h>
#include "mylib.h"
int gtype;
int flag =0;
int yylex();
void yyerror(char *msg);
%}

%union{
 int ival;
 struct node *nval;
}

%left '+' '-'
%left '*' '/'
%token <ival> INT FLOAT CHAR
// type -1 will be treated as non-struct having only value
%token <nval> ID E A NUM FNUM CHARCONST
%type <ival> DT

%% 
SS  : SS S
    | S
    ;
DT : INT		    {gtype=1;}
   | FLOAT		    {gtype=2;}
   | CHAR		    {gtype=0;}
   ;
LIST : LIST ',' ID	{$3->type=gtype;}
     | ID		    {$1->type=gtype;}
     ;
S   : DT LIST ';'
    | A ';'
    ;
A : ID '=' E		{if($3->type == -2 || $3->type==0){if($1->type==0) $1->val = $3->val; else printf("Type Error\n");} else $1 = $3->val;}
  ; 

E : E '+' E         {if(both char, combi of int float, both char variable, both int/float variable else error)}
  | E '-' E         {if($1==-1 ||  $3==-1) $$=-1; else $$=max($1,$3);}
  | E '*' E         {if($1==-1 ||  $3==-1) $$=-1; else $$=max($1,$3);}
  | E '/' E         {if($1==-1 ||  $3==-1) $$=-1; else $$=max($1,$3);}
  | ID              {$$=$1;}
  | NUM             {$$=$1;}
  | FNUM            {$$=$1;}
  | CHARCONST       {$$=$1;}
  ;
%%

void yyerror(char *msg){
    printf("Invalid Arithmetic Expression \nError");
    flag=1;
}

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

int main(){
    printf("Enter Arithmetic expressions : \n");
    yyparse();
    if(flag==0)
        printf("Valid Arithmetic Expression \n");
    return 0;
}