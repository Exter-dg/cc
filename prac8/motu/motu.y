%{
	void yyerror(char* s);
	int yylex();
	#include "stdio.h"
	#include "stdlib.h"
	#include "ctype.h"
	#include "string.h"
	void ins();
	void insV();
	int flag=0;
	extern char curid[20];
	extern char curtype[20];
	extern char curval[20];
	void insertST(char*, char*);
	char gettype(char*,int);
%}

%nonassoc IF
%token INT FLOAT DOUBLE
%token RETURN MAIN
%token VOID
%token FOR  
%token BREAK
%token ENDIF

%token identifier
%token integer_constant float_constant

%nonassoc ELSE

%right modulo_assignment_operator
%right multiplication_assignment_operator division_assignment_operator
%right addition_assignment_operator subtraction_assignment_operator
%right assignment_operator

%left caret_operator
%left equality_operator inequality_operator
%left lessthan_assignment_operator lessthan_operator greaterthan_assignment_operator greaterthan_operator
%left add_operator subtract_operator
%left multiplication_operator division_operator modulo_operator

%left increment_operator decrement_operator 


%start SS

%%
SS			
			: SS S
			| S
			;
S 			
			: declaration_list
			| expression ';'
			;

declaration_list
			: variable_declaration ;

variable_declaration
			: type_specifier variable_declaration_list ';' 

variable_declaration_list
			: variable_declaration_list ',' variable_declaration_identifier | variable_declaration_identifier;

variable_declaration_identifier 
			: identifier {ins();} vdi;

vdi
			: assignment_operator simple_expression
			| ;			
			
type_specifier 
			: INT | FLOAT  | DOUBLE 

expression 
			: mutable assignment_operator expression              {
																	  if($1==1 && $3==1) 
																	  {
			                                                          $$=1;
			                                                          } 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable addition_assignment_operator expression     {
																	  if($1==1 && $3==1) 
			                                                          $$=1; 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable subtraction_assignment_operator expression  {
																	  if($1==1 && $3==1) 
			                                                          $$=1; 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable multiplication_assignment_operator expression {
																	  if($1==1 && $3==1) 
			                                                          $$=1; 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable division_assignment_operator expression 		{
																	  if($1==1 && $3==1) 
			                                                          $$=1; 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable modulo_assignment_operator expression 		{
																	  if($1==1 && $3==1) 
			                                                          $$=1; 
			                                                          else 
			                                                          {$$=-1; printf("Type mismatch\n"); exit(0);} 
			                                                       }
			| mutable increment_operator 							{if($1 == 1) $$=1; else $$=-1;}
			| mutable decrement_operator 							{if($1 == 1) $$=1; else $$=-1;}
			| simple_expression {if($1 == 1) $$=1; else $$=-1;} ;

simple_expression 
			: regular_expression {if($1 == 1) $$=1; else $$=-1;} ;

regular_expression 
			: regular_expression relational_operators sum_expression {if($1 == 1 && $3==1) $$=1; else $$=-1;}
			  | sum_expression {if($1 == 1) $$=1; else $$=-1;} ;
			
relational_operators 
			: greaterthan_assignment_operator | lessthan_assignment_operator | greaterthan_operator 
			| lessthan_operator | equality_operator | inequality_operator ;

sum_expression 
			: sum_expression sum_operators term  {if($1 == 1 && $3==1) $$=1; else $$=-1;}
			| term {if($1 == 1) $$=1; else $$=-1;};

sum_operators 
			: add_operator 
			| subtract_operator ;

term
			: term MULOP factor {if($1 == 1 && $3==1) $$=1; else $$=-1;}
			| factor {if($1 == 1) $$=1; else $$=-1;} ;

MULOP 
			: multiplication_operator | division_operator | modulo_operator ;


factor 
			: immutable {if($1 == 1) $$=1; else $$=-1;} 
			| mutable {if($1 == 1) $$=1; else $$=-1;} ;

mutable 
			: identifier {
			              if(gettype(curid,0)=='i' || gettype(curid,1)== 'c')
			              $$ = 1;
			              else
			              $$ = -1;
			              }

immutable 
			: '(' expression ')' {if($2==1) $$=1; else $$=-1;}
			| constant {if($1==1) $$=1; else $$=-1;};

constant 
			: integer_constant 	{  insV(); $$=1; } 
			| float_constant	{  insV(); } 
%%

extern FILE *yyin;
extern int yylineno;
extern char *yytext;
void insertSTtype(char *,char *);
void insertSTvalue(char *, char *);
void incertCT(char *, char *);
void printST();
void printCT();

int main(int argc , char **argv)
{
	yyin = fopen(argv[1], "r");
	yyparse();

	if(flag == 0)
	{
		printf("Status: Parsing Complete - Valid\n");
		printf("%30s SYMBOL TABLE \n"," ");
		printf("%30s %s \n"," ", "------------");
		printST();

		printf("\n\n%30s CONSTANT TABLE \n"," ");
		printf("%30s %s \n"," ", "------------");
		printCT();
	}
}

void yyerror(char *s)
{
	printf("Line %d %s %s\n", yylineno, s, yytext);
	flag=1;
	printf("Status: Parsing Failed - Invalid\n");
	exit(7);
}

void ins()
{
	insertSTtype(curid,curtype);
}

void insV()
{
	insertSTvalue(curid,curval);
}

int yywrap()
{
	return 1;
}