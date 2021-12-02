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

void find_first(map<char, vector<string>> grammar,
                map<char, set<char>> &first,
                set<char> &first_exists,
                char c)
                {
                    vector<string> productions = grammar[c];
                    set<char> st;

                    // iterate through each production
                    for(auto str : productions)
                    {
                        // if first is non terminal
                        int i = 0;
                        start:;
                        if(i<str.size())
                        {
                            if(str[i]>='A' && str[i]<='Z')
                            {
                                // if first not calculated yet, calculate it
                                if(first_exists.find(str[i]) == first_exists.end())
                                    find_first(grammar, first, first_exists, str[i]);

                                set<char> temp = first[str[i]];
                                st.insert(temp.begin(), temp.end());

                                // check if null is present in the first, if yes continue ahead
                                bool contains_null = false;
                                for(auto itr = first[str[i]].begin(); itr!=first[str[i]].end(); itr++)
                                    if(*itr == 'e')
                                    {
                                        contains_null=true;
                                        break;
                                    }

                                if(contains_null)
                                {
                                    i++;
                                    goto start;
                                }
                            }
                            else
                            {
                                // terminal
                                st.insert(str[i]);
                            }
                        }
                    }
                    first_exists.insert(c);
                    first[c] = st;
                }

void find_follow(map<char, vector<string>> grammar,
                map<char, set<char>> &follow,
                map<char, set<char>> first,
                char c)
                {
                    set<char> st;
                    
                    // iterate through all grammars
                    for(auto p : grammar)
                    {
                        vector<string> v = p.second;
                        for(auto str : v)
                        {
                            for(int i=0;i<str.size();i++)
                            {
                                if(str[i] == c)
                                {
                                    start:;

                                    if(i+1 >= str.size())
                                    {
                                        if(p.first == c)
                                            continue;
                                            
                                        // follow of start
                                        find_follow(grammar, follow, first, p.first);
                                        st.insert(follow[p.first].begin(), follow[p.first].end());
                                    }
                                    else if(str[i+1]>='A' && str[i+1]<='Z')
                                    {
                                        //non terminal
                                        st.insert(first[str[i+1]].begin(), first[str[i+1]].end());

                                        bool contains_null = false;
                                        for(auto itr = first[str[i+1]].begin(); itr!=first[str[i+1]].end(); itr++)
                                            if(*itr == 'e')
                                            {
                                                contains_null=true;
                                                break;
                                            }

                                        if(contains_null)
                                        {
                                            i++;
                                            goto start;
                                        }
                                    }
                                    else
                                    {
                                        // terminal
                                        st.insert(str[i+1]);
                                    }
                                }
                            }
                        }
                    }
            
                    st.erase('e');
                    follow[c].insert(st.begin(), st.end());
                }

int main()
{
    int no_of_nt;
    cout<<"Enter number of non-terminals: ";
    cin>>no_of_nt;
    map<char, vector<string>> grammar;
    char start_symbol;

    cout<<"Enter grammar:\n";

    for(auto i=0; i<no_of_nt; i++)
    {
        // input grammar
        char c;
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

    // * Find first
    map<char, set<char>> first;
    set<char> first_exists;
    for(auto i = grammar.begin() ; i!=grammar.end() ; i++)
    {
        if(first_exists.find(i->first) == first_exists.end())
        {
            find_first(grammar, first, first_exists, i->first);
        }
    }

    cout<<"\n\n\tFIRST\n";
    for(auto p : first)
    {
        cout<<p.first<<"-> { ";
        for(auto ch : p.second)
            cout<<ch<<", ";
        cout<<"}\n";
    }

    // * Find Follow
    map<char, set<char>> follow;
    follow[start_symbol]={'$'};
    for(auto i = grammar.begin() ; i!=grammar.end() ; i++)
    {
        find_follow(grammar, follow, first, i->first);
    }

    cout<<"\n\n\tFOLLOW\n";
    for(auto p : follow)
    {
        cout<<p.first<<"-> { ";
        for(auto ch : p.second)
            cout<<ch<<", ";
        cout<<"}\n";
    }

    return 0;
}

/*

Enter number of non-terminals: 5
Enter grammar:
E -> TR
R -> +TR|e
T -> FY
Y -> *FY|e
F -> (E)|i


	FIRST
E-> { (, i, }
F-> { (, i, }
R-> { +, e, }
T-> { (, i, }
Y-> { *, e, }


	FOLLOW
E-> { $, ), }
F-> { $, ), *, +, }
R-> { $, ), }
T-> { $, ), +, }
Y-> { $, ), +, }


*/

/*

Enter number of non-terminals: 4
Enter grammar:
S-> ACB|CbB|Ba
A-> da|BC
B -> g|e
C -> h|e


	FIRST
A-> { d, e, g, h, }
B-> { e, g, }
C-> { e, h, }
S-> { a, b, d, e, g, h, }


	FOLLOW
A-> { $, g, h, }
B-> { $, a, g, h, }
C-> { $, b, g, h, }
S-> { $, }


*/