%{
   #include<stdio.h>
   int flag=1;
%}

%token NUMBER
%left '+' '-' '*' '/' '%' '(' ')'

%%

AE: E       {printf("\nResult=%d\n", $$);exit(0);};
E : E'+'E   {int t1=$1,t2=$3; printf("temp%d = temp%d + temp%d\n",flag,t1,t2); $$=flag; flag++;}
  | E'-'E   {int t1=$1,t2=$3; printf("temp%d = temp%d - temp%d\n",flag,t1,t2); $$=flag; flag++;}
  | E'*'E   {int t1=$1,t2=$3; printf("temp%d = temp%d * temp%d\n",flag,t1,t2); $$=flag; flag++;}
  | E'/'E   {int t1=$1,t2=$3; printf("temp%d = temp%d / temp%d\n",flag,t1,t2); $$=flag; flag++;}
  | E'%'E   {int t1=$1,t2=$3; printf("temp%d = temp%d % temp%d\n",flag,t1,t2); $$=flag; flag++;}
  | '('E')'
  | NUMBER  {int temp = $$; printf("temp%d = %d\n",flag,temp); $$=flag; flag++;}
  ;

%%

void main()
{
   printf("\nEnter Any Arithmetic Expression :\n");
   yyparse();
   printf("\nEntered arithmetic expression is Valid\n\n");
}

void yyerror()
{
   printf("\nEntered arithmetic expression is Invalid\n\n");
}