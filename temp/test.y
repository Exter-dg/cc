%{
   /* Definition section */
  #include <stdio.h>
  //map<string, int> var;
  int symbol[26];
%}

%union {
    int ival;
    float fval;
}


%token <ival> N  
%token <fval> FN 
%token <ival> ID
/* When you use %union to specify multiple value types, 
    you must declare the value type of each nonterminal symbol for which values are used. This is done with a %type declaration */
%type <fval> E 
%right '='
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

  
/* Rule Section 
| ID '=' E        {$$ = $1 = $3;}*
  | ID              {$$=$1;}*/
%%

SS : SS S 
   | S
   ;
S : E ';'           {printf("Answer is %f\n", $1);}
  | ID '=' E ';'    {symbol[$1] = $3;}
  ;
E : E '+' E         {$$ = $1 + $3;}
  | E '-' E         {$$ = $1 - $3;}
  | E '*' E         {$$ = $1 * $3;}
  | E '/' E         {$$ = $1 / $3;}
  | N               {$$ = $1;}
  | FN              {$$ = $1;}
  | ID              {$$ = symbol[$1];}
  ;
%%
  
//driver code
void main()
{
   yyparse();
   
}
  
void yyerror()
{
   printf("error");
   exit(0);
}