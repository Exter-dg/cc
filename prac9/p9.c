

#include <stdio.h>
#include<conio.h>
#include <string.h>
void main()
{
char inp[10][30], str[20], opr[10];
int i = 0;
printf("\n Enter intermediate code (terminated by quit()):\n");
do
{
scanf("%s", inp[i]);
}
while (strcmp(inp[i++], "quit()") != 0);
printf("\nOutput:\n");
i = 0;
do
{
strcpy(str, inp[i]);
switch (str[3])
{
case '+':
strcpy(opr, "ADD ");
break;
case '-':
strcpy(opr, "SUB ");
break;
case '*':
strcpy(opr, "MUL ");
break;
case '/':
strcpy(opr, "DIV ");
break;
}
printf("\n\tMOV %c,R%d", str[2], i);
printf("\n\t%s%c,R%d", opr, str[4], i);
printf("\n\tMOV R%d,%c", i, str[0]);
}
while (strcmp(inp[++i], "quit()") != 0);
}

