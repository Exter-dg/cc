#include <bits/stdc++.h>
 
using namespace std;

int main()
{
    int n,i,k;
    int f = 0;
    // stores variable and its type
    map <char, char> mp;
    char variable;
    char type;
    string a;
    char c;
    
    cout<<"Enter the number of variable declarations: ";
    string s;
    while(true)
    {
        s="";
        getline(cin,s);
        if(s =="$")
            break;
        // i or f
        type = s[0];

        // int a,b,c;
        // float d;
        i=0;
        while(s[i]!=' ')
            i++;
        i++;
        while(s[i]!=';')
        {
            if(s[i]==',')
                i++;
            mp[s[i]]=type;
            i++;
        }
    
    }

    
   
    cout<<"\nEnter the Expression (append $ at end): \n";
    i=0;
   
    getline(cin,a);
    while(a[i]!='=')
        i++;
    i++;
    // check if variables on right side of = are float or not
    while(i<a.size())
    {
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z'))
        {
            if(mp.find(a[i])==mp.end())
            {
                //doesnt exist
                cout<<"\nVariable not Declared";
                return 0;
            }
            if(mp[a[i]]=='f')
            {
                f=1;
                break;
            }
        }
        i++;
    }

   
   // variable = expr
    for(auto pr : mp)
    {
        variable = pr.first;
        type = pr.second;
        if(a[0] == variable)
        {
            if(f == 1)
            {
                if(type == 'f')
                {  
                    cout<<"\nThe datatype is correctly defined..!\n";
                    break;  
                }
                else
                {  
                    cout<<"Identifier"<<variable<< "must be a float type..!\n";
                    break;  
                }  
            }
            else
            {  
                cout<<"\nThe datatype is correctly defined..!\n";
                break;  
            }  
        }
    }
    return 0;
}
