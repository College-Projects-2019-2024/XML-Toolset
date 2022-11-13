#include <bits/stdc++.h>


#ifndef ONLINE_JUDGE



#else

#define debug(...) 42


#endif



#include <iostream>

using namespace std;
using ll = long long;





#define all(v) v.begin(),v.end()

#define allr(v) v.rbegin(),v.rend()
#define fori(size) for(int i=0; i < (size); i+= 1)
#define forj(size) for(int j=0; j < (size); j+= 1)
#define fork(size) for(int k=0; k < (size); k+= 1)
#define MOD 1000000007






void printmsg (string s, int line, int CASE)
{
    switch (CASE)
    {
        case 1:
        {
            cout << "line :" <<line;
            cout << ' ' << s<<  " are closed although it was never opened" << endl;
        }
            break;
        case 2:
        {
            cout << "line :" <<line;
            cout << " that was opened and not closed" << ' '<<(s) << endl;
        }
            break;
        case 3:
        {
            cout << "sorry I found the closing of" << ' '<<(s)  << " That was at the line " <<line<< endl;
        }
            break;
        default: {}
    }
}



bool ans()
{
    string  str; stack <pair <string,int>> stac;

    int line  = 0;
    while(getline (cin,str))
    {
        line++;
        int end_pos=0;
        int last_char= str.length() - 1;

        while(end_pos!=string::npos && end_pos != last_char)
        {
            int start_pos=str.find('<',end_pos);
            end_pos = str.find('>', end_pos+1);

            if(end_pos==-1 && start_pos==-1) break;

            if(str[start_pos] == '<' && str[start_pos+1] != '/')
            {
                stac.push({str.substr(start_pos+1,end_pos-start_pos-1), (line)});
            }
            else if (str[start_pos+1] == '/')
            {
                if (stac.empty()) printmsg ( str.substr(start_pos + 2, end_pos - start_pos - 2),  line, 1);
                else
                {
                    list <pair <string,int>> myList;
                    while (! stac.empty() && (stac.top().first) != str.substr(start_pos+2,end_pos-start_pos-2))
                    {
                        printmsg(stac.top().first,stac.top().second,2);
                        myList.push_back(stac.top()) ;
                        stac.pop();
                    }
                    if ( !stac.empty() && stac.top().first == str.substr(start_pos+2,end_pos-start_pos-2)) stac.pop();
                    else
                    {
                        while (!myList.empty())
                        {
                            printmsg(myList.back().first,myList.back().second,3);
                            stac.push(myList.back()) ;
                            myList.pop_back( );
                        }
                        printmsg ( str.substr(start_pos + 2, end_pos - start_pos - 2),  line, 1);
                    }
                }

            }
        }
    }

    while (! stac.empty())
    {
        printmsg(stac.top().first,stac.top().second,2);
        stac.pop();
    }

    return true;
}


int main()
{
    freopen("in.in", "r", stdin);
    ans();
}