#include <stdio.h>

// for windows
//#include <conio.h>

// for linux
//#include <curses.h>

#include <string.h>
#include <stdlib.h>

void pm();
void plus();
void div1();



int i, ch, j, l, addr = 100;

char ex[10], exp0[10], exp1[10], EXP2[10], id1[5], op[5], id2[5];

void main() {
  
  while (1) {
    printf("\n1.assignment\n2.arithmetic\n3.relational\n4.Exit\nEnter the choice:");
    scanf("%d", & ch);
    
    switch (ch) {
    case 1:
      printf("\nEnter the expression with assignment operator:");
      scanf("%s", exp0);
      l = strlen(exp0);
      EXP2[0] = '\0';
      i = 0;
      while (exp0[i] != '=') {
        i++;
      }
      strncat(EXP2, exp0, i);
      strrev(exp0);
      exp1[0] = '\0';
      strncat(exp1, exp0, l - (i + 1));
      strrev(exp1);
      printf("Three address code:\ntemp=%s\n%s=temp\n", exp1, EXP2);
      break;

    case 2:
      printf("\nEnter the expression with arithmetic operator:");
      scanf("%s", ex);
      strcpy(exp0, ex);
      l = strlen(exp0);
      exp1[0] = '\0';

      for (i = 0; i < l; i++) {
        if (exp0[i] == '+' || exp0[i] == '-') {
          if (exp0[i + 2] == '/' || exp0[i + 2] == '*') {
            pm();
            break;
          } else {
            plus();
            break;
          }
        } else if (exp0[i] == '/' || exp0[i] == '*') {
          div1();
          break;
        }
      }
      break;

    case 3:
      printf("Enter the expression with relational operator");
      //scanf("%s%s%s", & id1, & op, & id2);
      scanf("%s",&id1);
      scanf("%s",&op);
      scanf("%s",&id2);
	  if (((strcmp(op, "<") == 0) || (strcmp(op, ">") == 0) || (strcmp(op, "<=") == 0) || (strcmp(op, ">=") == 0) || (strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) == 0)
        printf("Expression is error");
      else {
        printf("\n%d\tif %s%s%s goto %d", addr, id1, op, id2, addr + 3);
        addr++;
        printf("\n%d\t T:=0", addr);
        addr++;
        printf("\n%d\t goto %d", addr, addr + 2);
        addr++;
        printf("\n%d\t T:=1", addr);
      }
      break;
    case 4:
      exit(0);
    }
  }
}



void pm() {
  strrev(exp0);
  j = l - i - 1;
  strncat(exp1, exp0, j);
  strrev(exp1);
  printf("Three address code:\ntemp=%s\ntemp1=%c%ctemp\n", exp1, exp0[j + 1], exp0[j]);
}


void div1() {
  strncat(exp1, exp0, i + 2);
  printf("Three address code:\ntemp=%s\ntemp1=temp%c%c\n", exp1, exp0[i + 2], exp0[i + 3]);
}


void plus() {
  strncat(exp1, exp0, i + 2);
  printf("Three address code:\ntemp=%s\ntemp1=temp%c%c\n", exp1, exp0[i + 2], exp0[i + 3]);
}


