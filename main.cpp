#include <bits/stdc++.h>
#include "compression.h"
using namespace std;



class hashUtil
{
public:

    vector <string> values{"users","user","id","name","posts","post","body","topics","topic","followers","follower"};

    vector <string> table;

    hashUtil()
    {
        fori(50) table.push_back("null");

        cout<<"hash utility class is done"<<endl;

        for (auto x : values)
        {
            table [int (Hash_to_code('<'+x+'>'))]  = '<'+x+'>';
        }
        for (auto x : values)
        {
            table [int (Hash_to_code("</" + x +'>')) ]  = "</" + x +'>';
        }

    }
    char Hash_to_code(string s)
    {
        if (!(s.front() == '<' && s.back() == '>'))
        {
            return -1;
        }
        else
        {
            if (s[1]== '/')
            {
                return (( 2* (int(s[2]) - int(s[s.size()-2]) + 23) % 23  )+ 23)  ;
            }
            else
            {
                return ( 2* (int(s[1]) - int(s[s.size()-2]) + 23) % 23 );
            }
        }
    }

    string codeToString(char x)
    {
        return (table[int(x)]);
    }

};


int main() {

   Minify();



}

