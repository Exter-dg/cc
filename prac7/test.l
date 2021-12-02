%{
   /* Definition section */
  #include<stdio.h>
  #include "y.tab.h"
%}
  
/* Rule Section ([<>]=?|[!=]=)|"++"|"--"    { return yytext; }*/
%%
[0-9]+                      { return NUMBER; }
[-+;/%(){}=><!*]            { return yytext[0]; }
"."													{ return OBJ_OPR; }
"=="                        { return EQL_OPR; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"for"                       { return FOR; }
"class"                     { return CLASS; }
([_a-zA-Z][0-9]*)+          { return ID; }
[ \t\r\n]+                  ;
%%
  
int yywrap()
{
 return 1;
}