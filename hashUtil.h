#ifndef COLLEGEPROJECT_HASHUTIL_H
#define COLLEGEPROJECT_HASHUTIL_H
#include <bits/stdc++.h>
using namespace std;
class hashUtil
{
private: vector <string> tags {"users", "user", "id", "name", "posts", "post", "body", "topics", "topic", "followers", "follower"};
         vector <string> table; // a table to contain opening and closing tags
         vector <string> JSONTable;
         hash<string> hasher;




public:  hashUtil()
    {
        table.resize(100);
        JSONTable.resize(90);
        for (string tag : tags)
        {
            table[hasher('<'+ tag +'>')%100]    = '<'+tag+'>';
            table[hasher("</" + tag +">")%100]  = "</" + tag +">";
            JSONTable[hasher("\"" + tag +"\"")%90] = "\"" + tag +"\"";
        }
    }

public:
    bool isValidTag(string x)
    {
        if(find(table.begin(), table.end(),x) != table.end() || find(JSONTable.begin(), JSONTable.end(),x) != JSONTable.end())
        {
            return true;
        }
        return false;
    }
    string codeToStringXML(unsigned char x)
    {
        if(x-128 < 0) return "";
        return table[(short)x-128];
    }
    unsigned char stringToCodeXML(string x)
    {
       return (isValidTag(x))? hasher(x)%100+128 : '%';
    }
    string codeToStringJSON(unsigned char x)
    {
        if(x-128 < 0) return "";
        return JSONTable[(short)x-128];
    }
    unsigned char stringToCodeJSON(string x)
    {
        return (isValidTag(x))? (hasher(x)%90)+128 : '%';
    }





};
#endif //COLLEGEPROJECT_HASHUTIL_H
