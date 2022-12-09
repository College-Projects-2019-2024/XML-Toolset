#ifndef COLLEGEPROJECT_HASHUTIL_H
#define COLLEGEPROJECT_HASHUTIL_H
#include <bits/stdc++.h>
using namespace std;
class hashUtil
{
private: vector <string> tags {"users", "user", "id", "name", "posts", "post", "body", "topics", "topic", "followers", "follower"};
    vector <string> table; // a table to contain opening and closing tags
public:  hashUtil()
    {
        table.resize(69); //

        for (string tag : tags)
        {
            table [int (hashInTable('<'+ tag +'>'))]  = '<'+tag+'>';
        }
        for (string tag : tags)
        {
            table [int (hashInTable("</" + tag +'>')) ]  = "</" + tag +'>';
        }
        for (string tag : tags)
        {
            table [int (hashInTable("5"  + tag +"5" )) ]  = "5"  + tag +"5" ;
        }

    }
private: unsigned char hashInTable(string s)
    {
        if (s.front() == '<' && s.back() == '>')
        {
            if (s[1]== '/')
            {
                return (( 2* (int(s[2]) - int(s[s.size()-2]) + 23) % 23  )+ 23);
            }
            else
            {
                return ( 2* (int(s[1]) - int(s[s.size()-2]) + 23) % 23 );
            }
        }
        else if (s.front() == '5' && s.back() == '5')
        {
            return (( 2* (int(s[1]) - int(s[s.size()-2]) + 23) % 23  )+ 46);
        }
        else return -1;
    }
public:
    string codeToString(unsigned char x)
    {
        if(x-128 < 0) return "";
        return table[(short)x-128];
    }
    unsigned char stringToCode(string x)
    {

        return (isValidTag(x))? hashInTable(x)+128 : -1;
    }
    bool isValidTag(string x)
    {
        if(find(table.begin(), table.end(),x) != table.end() && hashInTable(x)!=-1)
        {
            return true;
        }
        return false;
    }
};
#endif //COLLEGEPROJECT_HASHUTIL_H
