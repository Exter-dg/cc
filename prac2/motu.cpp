/*
CFG
E -> E + E | E - E | F
F -> F * F | F / F | Q
Q -> (E) | id

Removing left recursion
E -> F E1
F -> Q F1
Q -> ( E ) | id
E1 -> + E E1 | - E E1 | ϵ
F1 -> * F F1 | / F F1 | ϵ

id is denoted by N
*/

#include<bits/stdc++.h>
using namespace std;

char c;

void E();
void F();
void Q();
void E1();
void F1();

int main()
{
    c = getchar();
    if(c!='$')
        E();
    if(c=='$')
        cout<<"Accepted\n"; 
    else cout<<"Parse Error\n";
}

void E()
{
    // if(c=='$')
    // {
    //     cout<<"Parse Error\n";
    //     exit(1);
    // }
    F();
    E1();
}

void F()
{
    // if(c=='$')
    // {
    //     cout<<"Parse Error\n";
    //     exit(1);
    // }
    Q();
    F1();
}

void Q()
{
    // if(c=='$')
    // {
    //     cout<<"Parse Error\n";
    //     exit(1);
    // }
    if(c=='(')
    {
        c = getchar();
        E();
        if(c!=')')
        {
            cout<<"Parse Error\n";
            exit(1);
        }
        c = getchar();
    }
    else if(c=='N')
    {
        c = getchar();
    }
    else
    {
        cout<<"\nRejected!";
        exit(0);
    }
}

void E1()
{
    if(c=='$')
        return;
    if(c=='+')
    {
        c = getchar();
        E();
        E1();
    }
    else if(c=='-')
    {
        c = getchar();
        E();
        E1();
    }
}

void F1()
{
    if(c=='$')
        return;
    if(c=='*')
    {
        c = getchar();
        F();
        F1();
    }
    else if(c=='/')
    {
        c = getchar();
        F();
        F1();
    }
}