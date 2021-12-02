%{
#include<stdio.h>
#include<string.h>
#include "y.tab.h"
#include "mylib.h"

struct node * lookup(char[]);
int flag1 = 0;

struct node * head = NULL;

%}
%%

[-+*/;=,]      		{return yytext[0];}
[0-9]+	     		{yylval.nval={"", -1, atoi(yytext), NULL}; return NUM;}
[0-9]*"."[0-9]+    	{yylval.nval={"", -1, ftoi(yytext), NULL}; return FNUM;}
['].[']				{yylval.nval={"", -2, ftoi(yytext), NULL}; return CHARCONST;}
"int"				{yylval.ival=1; return INT;}
"char"				{yylval.ival=0; return CHAR;}
"float"				{yylval.ival=2; return FLOAT;}
([_a-zA-Z][0-9]*)+ 	{yylval.nval=lookup(yytext); return ID;}

%%

struct node * lookup(char str[])
{
	if(flag1 == 0) {
		flag1 = 1;
		struct node *newnode;
		newnode=(struct node *)malloc(sizeof(struct node));
		strcpy(newnode->name,str);
		newnode->type=999;
		newnode->next=NULL;
		head = newnode;
		return newnode; 
	}

	struct node *temp, *newnode;
	temp=head;

	while(temp->next!=NULL){
		if(strcmp(temp->name,str)==0)
			return temp;
		temp=temp->next;
	}

	newnode=(struct node*)malloc(sizeof(struct node));
	strcpy(newnode->name,str);
	newnode->type=999;
	newnode->next=NULL;
	temp->next=newnode;
	return newnode; 
}

int yywrap(){
return 1;
}