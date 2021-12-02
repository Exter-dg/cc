#include <stdio.h>

/*
 * Grammar

    T -> A + T
        |   A - T
        |   A
    A -> n * A
        | n / A
        | n

-----------------------------------------------

    T -> A T'
    A -> n A'
    T' -> + T
        | - T
        | ϵ
    A' -> * A
        | / A
        | ϵ

-----------------------------------------------
*/
// n*n
// n/n+n

// Global Lookahead
char l;

// Error Function
void error() 
{
    printf("Error\n");
    exit(0);    
}

// Match function
void match(char t)
{
    if (l == t) {
        l = getchar();
    }
    else
    {
        error();
    }
}


void T_()
{
    /*
        T' -> + T
        | - T
        | ϵ
    */

   if(l == '+')
   {
       match('+');
       T();
   }
   else if(l == '-')
   {
       match('-');
       T();
   }
   // null acceptable
}

void A_()
{
    /*
         A' -> * A
        | / A
        | ϵ
    */
   if(l == '*')
   {
       match('*');
       A();
   }
   else if(l == '/')
   {
       match('/');
       A();
   }
   // null acceptable
   
}

void T()
{
    // T -> A T'

    A();
    T_();
}

void A()
{
    // A -> n A'

    if(l == 'n')
    {
        match('n');
        A_();
    }
    else
    {
        error();
    }
}


int main()
{
    l = getchar();
    // T is a start symbol.
    T();
 
    // if lookahead = $, it represents the end of the string
    // Here l is lookahead.
    if (l == '$')
        printf("Parsing Successful");
    else
        printf("Error\n");
    
    return 0;
}
 
