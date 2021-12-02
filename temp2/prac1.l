%{
#include<stdio.h>
%}
%%
"//"[^(\n)]*|"/*"("*"[^/]|[^*])*"*/"			    {}
"\n"                                                {printf("\n");} 
"#include "((<[^>]+>)|(\"[^\"]+\"))                 {printf("Preprocessor_Directive ");}
"using"[^(\n)]*                                     {printf("Namespace ");}

"{"|"}"                                             {printf("%s ", yytext);}
"class"                                             {printf("CLASS ");}
"main"                                              {printf("MAIN ");}
"return"                                            {printf("RETURN ");} 
">>"                                                {printf("CIN_OP ");} 
"<<"                                                {printf("COUT_OP ");} 
"auto"|"typedef"|"enum"|"switch"|"case"|"char"|"struct"|"break"|"while"|"goto"|"continue"|"cin"|"cout"|"public"|"endl"       {printf("Keyword ");}
"int"|"float"|"string"|"double"|"long"              {printf("Data_Type ");}
"if"|"else"                                         {printf("Control_Block ");}
"for"                                               {printf("FOR ");}
","|":"|"\""                                        {printf("Separator ");}
"\t"*|" "*|"++"|"--"|[+*/=-]|(?:<=?|>=?|==|!=)|"%"|";"|"("|")"             {printf("%s ", yytext);}
"&&"|"||"|"!"                                       {printf("Logical_Op ");}
"."													{printf("Obj_Op ");}
["][^"]*["]                                         {printf("String ");}
[0-9]*"."[0-9]+                                     {printf("Float_Literal ");}
[0-9]+                                              {printf("Number ");}
([_a-zA-Z][0-9]*)+                                  {printf("Identifier ");}
.                                                   {printf("INVALID ");}
%%
int main()
{ 
    yylex(); 
    return 0;
}
int yywrap()
{
    return 1;
}
