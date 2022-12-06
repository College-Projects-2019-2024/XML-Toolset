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
        table.resize(46); //

        for (string tag : tags)
        {
            table [int (hashInTable('<'+ tag +'>'))]  = '<'+tag+'>';
        }
        for (string tag : tags)
        {
            table [int (hashInTable("</" + tag +'>')) ]  = "</" + tag +'>';
        }

    }
private:  unsigned char hashInTable(string s)
    {
        if (!(s.front() == '<' && s.back() == '>'))
        {
            return -1;
        }
        else
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
    }
public:
    string codeToStringXML(unsigned char x)
    {
        if(x-128 < 0) return "";
        return table[(short)x-128];
    }
    unsigned char stringToCodeXML(string x)
    {
        return hashInTable(x)+128;
    }
    string codeToStringJSON(unsigned char x) // return name without brackets
    {
        if(x-128 < 0) return "";
        string result = table[(short)x-128];
        return result.substr(1, result.size()-2);
    }
    unsigned char stringToCodeJSON(string x)//x = name without brackets
    {
        string result="";
        result+="<";
        result+=x;
        result+=">";
        return hashInTable(result)+128;
    }


};
#endif //COLLEGEPROJECT_HASHUTIL_H
