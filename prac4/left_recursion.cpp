#include <bits/stdc++.h>

using namespace std;

vector<string> find_grammar(string s)
{
    vector<string> v;

    int i =0;

    for(i=0 ; i<s.size() ; i++)
        if(s[i]!=' ' && s[i]!='-' && s[i]!='>')
            break;

    // i now points to first nt/t
    string temp="";
    for(; i<s.size();i++)
    {
        // new production
        if(s[i]=='|')
        {
            v.push_back(temp);
            temp="";
            continue;
        }
        temp+=s[i];
    }
    
    // push last production
    v.push_back(temp);  

    return v;
}

void eliminate_immediate_lrecursion(map<string, vector<string>> &grammar, 
                                    string nt)
{
    set<string> alpha;
    set<string> beta;

    // to remove left recursion from this non terminal's productions
    for(auto s : grammar[nt])
    {
            if(s.find(nt) == 0)
                alpha.insert(s.substr(nt.size()));
            else
                beta.insert(s);
    }

    // no immediate left recursion
    if(alpha.empty())
        return;
    
    if(beta.empty())
    {
        cout<<"Error!!! Beta is Empty";
        exit(0);
    }

    map<string, set<string>> new_productions;

    string new_nt = nt+"'";
    for(auto it = beta.begin(); it!=beta.end(); it++)
    {
        // A -> Beta A'
        new_productions[nt].insert(*it + new_nt);
    }

    for(auto it = alpha.begin(); it!=alpha.end(); it++)
    {
        // A' -> alpha A' | e
        new_productions[new_nt].insert(*it + new_nt);
    }
    new_productions[new_nt].insert("e");

    grammar[new_nt] = vector<string> (new_productions[new_nt].begin(), new_productions[new_nt].end());
    grammar[nt] = vector<string> (new_productions[nt].begin(), new_productions[nt].end());
}

int main()
{
    cout<<"\n\n";
    int no_of_nt;
    cout<<"Enter number of non-terminals: ";
    cin>>no_of_nt;
    map<string, vector<string>> grammar;
    string start_symbol;

    cout<<"Enter grammar:\n";

    for(auto i=0; i<no_of_nt; i++)
    {
        // input grammar
        string c;
        cin>>c;
        if(i==0)
            start_symbol = c;
        string s;
        getline(cin, s);

        // store grammar in map
        vector<string> v = find_grammar(s);
        
        grammar[c] = v;
    }

    // print grammar
    /*for(auto p: grammar)
    {
        cout<<p.first<<"->";
        for(auto str : p.second)
            cout<<str<<" | ";
        cout<<"\n";
    }*/

    vector<string> visited_nt;
    // iterate over each non-terminal in grammar
    for(auto it = grammar.begin(); it!= grammar.end(); it++ )
    {
        string curr_nt = it->first;

        // if it is newly added non terminal, skip it - A', A''
        if(curr_nt.find('\'') != -1)
            continue;


        // copy productions to temp vector
        vector<string> temp = it->second;

        // iterate over each visited non-terminal
        for(int i=0; i<visited_nt.size(); i++)
        {
            // iterate through every production in grammar[it->first]
            for(auto s : it->second)
            {
                auto pos = s.find(visited_nt[i]);
                if(pos != -1)
                {
                    // remove production to be replaced
                    temp.erase(find(temp.begin(), temp.end(), s));
                    
                    string prefix = s.substr(0, pos);
                    string suffix = s.substr(pos+ visited_nt[i].size());

                    // add new productions
                    // for each production of visited_nt[i], append rest_of_production and 
                    // add it to our new productions for curr_nt
                    for(auto production_in_visited : grammar[visited_nt[i]])
                    {
                        temp.push_back(prefix+production_in_visited+suffix);
                    }
                }
            }
        }
        // mark current non terminal as visited
        visited_nt.push_back(it->first);

        // replace new productions in grammar
        grammar[curr_nt] = temp;

        // eliminate immediate left_recursion in new productions
        eliminate_immediate_lrecursion(grammar, curr_nt);
    }

    // print grammar
    cout<<"\n\n--------------------------------------\n";
    cout<<"Resulting Grammer:\n";
    cout<<"--------------------------------------\n\n";
    for(auto p: grammar)
    {
        cout<<p.first<<"->";
        for(auto str : p.second)
            cout<<str<<" | ";
        cout<<"\n";
    }

    cout<<"\n\n";

    return 0;
}

/*

Enter number of non-terminals: 2
Enter grammar:
S -> Aa|b    
A -> Ac|Sd|f


--------------------------------------
Resulting Grammer:
--------------------------------------

A->SdA' | fA' | 
A'->cA' | e | 
S->bS' | fA'aS' | 
S'->dA'aS' | e | 



*/