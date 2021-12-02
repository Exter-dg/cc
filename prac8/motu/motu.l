%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "y.tab.h"

    int strcount=0;
	struct symboltable
	{
		char name[100];
		char type[100];
		char value[100];
	}ST[1001];

	struct constanttable
	{
		char name[100];
		char type[100];

	}CT[1001];

	extern int yylval;

	int hash(char *str)
	{
		int value = 0;
		for(int i = 0 ; i < strlen(str) ; i++)
		{
			value = 10*value + (str[i] - 'A');
			value = value % 1001;
			while(value < 0)
				value = value + 1001;
		}
		return value;
	}

	int lookupST(char *str)
	{
		int value = hash(str);
        if(strcmp(ST[value].name, '\0') == 0)
            return 0;
		else if(strcmp(ST[value].name,str)==0)
		{
			return value;
		}
		else
		{
			for(int i = value + 1 ; i!=value ; i = (i+1)%1001)
			{
				if(strcmp(ST[i].name,str)==0)
				{
					return i;
				}
			}
			return 0;
		}
	}

	int lookupCT(char *str)
	{
		int value = hash(str);
        if(strcmp(CT[value].name, '\0') == 0)
            return 0;
		else if(strcmp(CT[value].name,str)==0)
			return 1;
		else
		{
			for(int i = value + 1 ; i!=value ; i = (i+1)%1001)
			{
				if(strcmp(CT[i].name,str)==0)
				{
					return 1;
				}
			}
			return 0;
		}
	}

	void insertST(char *str1, char *str2)
	{
		if(lookupST(str1))
		{
			return;
		}
		else
		{
			int value = hash(str1);
			if(strcmp(ST[value].name, '\0') == 0)
			{
				strcpy(ST[value].name,str1);
				return;
			}

			int pos = 0;
			for (int i = value + 1 ; i!=value ; i = (i+1)%1001)
			{
				if(strcmp(ST[i].name, '\0') == 0)
				{
					pos = i;
					break;
				}
			}

			strcpy(ST[pos].name,str1);
		}
	}

	void insertSTtype(char *str1, char *str2)
	{
		for(int i = 0 ; i < 1001 ; i++)
		{
			if(strcmp(ST[i].name,str1)==0)
			{
				strcpy(ST[i].type,str2);
			}
		}
    }

	void insertSTvalue(char *str1, char *str2)
	{
		for(int i = 0 ; i < 1001 ; i++)
		{
			if(strcmp(ST[i].name,str1)==0)
			{
				strcpy(ST[i].value,str2);
			}
		}
	}

	void insertCT(char *str1, char *str2)
	{
		if(lookupCT(str1))
			return;
		else
		{
			int value = hash(str1);

			if(strcmp(CT[value].name, '\0') == 0)
			{
				strcpy(CT[value].name,str1);
				strcpy(CT[value].type,str2);
				return;
			}

			int pos = 0;

			for (int i = value + 1 ; i!=value ; i = (i+1)%1001)
			{
				if(strcmp(CT[i].name, '\0') == 0)
				{
					pos = i;
					break;
				}
			}
			strcpy(CT[pos].name,str1);
			strcpy(CT[pos].type,str2);
		}
	}

	char gettype(char *s, int flag)
	{
			for(int i = 0 ; i < 1001 ; i++ )
			{
				if(strcmp(ST[i].name,s)==0)
				{
					return ST[i].type[0];
				}
			}
	}

	void printST()
	{
		printf("%10s | %15s | %10s |\n","SYMBOL", "TYPE","VALUE");
		for(int i=0;i<100;i++) {
			printf("-");
		}
		printf("\n");
		for(int i = 0 ; i < 5 ; i++)
		{
			if(strcmp(ST[i].name, '\0') == 0)
			{
				continue;
			}
			printf("%10s | %15s | %10s |\n",ST[i].name, ST[i].type, ST[i].value);
			
		}	
    }


	void printCT()
	{
		printf("%10s | %15s\n","NAME", "TYPE");
		for(int i=0;i<81;i++) {
			printf("-");
		}
		printf("\n");
		for(int i = 0 ; i < 5 ; i++)
		{
			if(strcmp(CT[i].name, '\0') == 0)
				continue;
			printf("%10s | %15s\n",CT[i].name, CT[i].type);
		}
	}
	char curid[20];
	char curtype[20];
	char curval[20];

%}

DE "define"
IN "include"

%option yylineno
%%
\n 	{yylineno++;}
[ \n\t] ;
";"				{ return(';'); }
","				{ return(','); }
("{")			{ return('{'); }
("}")			{ return('}'); }
"("				{ return('('); }
")"				{ return(')'); }
":"				{ return(':'); }
"."				{ return('.'); }

"double"		{ strcpy(curtype,yytext); insertST(yytext, "Keyword"); return DOUBLE;}
"else"			{ insertST(yytext, "Keyword"); return ELSE;}
"float"			{ strcpy(curtype,yytext); insertST(yytext, "Keyword"); return FLOAT;}
"for"			{ insertST(yytext, "Keyword"); return FOR;}
"if"			{ insertST(yytext, "Keyword"); return IF;}
"int"			{ strcpy(curtype,yytext); insertST(yytext, "Keyword"); return INT;}
"return"		{ insertST(yytext, "Keyword"); return RETURN;}
"void"			{ strcpy(curtype,yytext);   insertST(yytext, "Keyword");  return VOID;}
"break"			{ insertST(yytext, "Keyword");  return BREAK;}



"++"			{ return increment_operator; }
"--"			{ return decrement_operator; }
"<="			{ return lessthan_assignment_operator; }
"<"				{ return lessthan_operator; }
">="			{ return greaterthan_assignment_operator; }
">"				{ return greaterthan_operator; }
"=="			{ return equality_operator; }
"!="			{ return inequality_operator; }
"^"				{ return caret_operator; }
"*="			{ return multiplication_assignment_operator; }
"/="			{ return division_assignment_operator; }
"%="			{ return modulo_assignment_operator; }
"+="			{ return addition_assignment_operator; }
"-="			{ return subtraction_assignment_operator; }
"-"				{ return subtract_operator; }
"+"				{ return add_operator; }
"*"				{ return multiplication_operator; }
"/"				{ return division_operator; }
"%"				{ return modulo_operator; }
\=				{ return assignment_operator;}

[1-9][0-9]|0/[;|,|" "|\)|<|>|=|\!|\||&|\+|\-|\|\/|\%|~|\]|\}|:|\n|\t|\^] 	{strcpy(curval,yytext); insertCT(yytext, "Number Constant"); yylval = atoi(yytext); return integer_constant;}
([0-9])\.([0-9]+)/[;|,|" "|\)|<|>|=|\!|\||&|\+|\-|\|\/|\%|~|\n|\t|\^] 	{strcpy(curval,yytext); insertCT(yytext, "Floating Constant"); return float_constant;}
[A-Za-z_][A-Za-z_0-9]* {strcpy(curid,yytext); insertST(curid,"Identifier"); return identifier;}

(.?) {
		printf("ERROR at line no. %d\n",yylineno);

		printf("%s\n", yytext);
		return 0;
}

%%