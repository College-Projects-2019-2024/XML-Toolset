#ifndef COLLEGEPROJECT_HASHUTIL_H
#define COLLEGEPROJECT_HASHUTIL_H
#include <bits/stdc++.h>
using namespace std;

struct Line{
    string text;
    int index;
};

class treeNode{
public:
    int max;
    string type;
    string text;
    vector<treeNode *> children;

    treeNode(int max, string type,string text, vector<treeNode *> children)
    {
        this->max = max;
        this->type = type;
        this->text = text;
        this->children = children;
    }
};


class Utility
{
private: vector <string> tags {"users", "user", "id", "name", "posts", "post", "body", "topics", "topic", "followers", "follower"};
         vector <string> table; // a table to contain opening and closing tags
         vector <string> JSONTable;
         hash<string> hasher;
         ifstream fileInputStream2;



public:  Utility()
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

    treeNode* ans(treeNode * usersSamp)
    {
        treeNode * myIDSample = new treeNode( -1, "id","my id is 123", {});//0
        treeNode * nameSample = new treeNode( -1, "name","Dallash", {});//1


        treeNode * topicSample = new treeNode( -1, "topic","this is my topic", {});
        treeNode * topicsSample = new treeNode( 0, "topics","", {topicSample});
        treeNode * bodySample =  new treeNode( -1, "body","this is my body", {});
        vector<treeNode *> postChildrenArray = { bodySample,  topicsSample};
        treeNode * postSample = new treeNode( 1, "post","", postChildrenArray);
        treeNode * postsSample = new treeNode( 0, "posts","", {postSample});//2


        treeNode * hisIDSample = new treeNode( -1, "id","his id is 456", {});
        treeNode * followerSample = new treeNode( 0, "follower","", {hisIDSample});
        treeNode * followersSample = new treeNode( 0, "followers","", {followerSample});//3


        vector<treeNode *> userChildrenArray = { myIDSample,  nameSample, postsSample,followersSample};
        treeNode * userSample = new treeNode( 3, "user","", userChildrenArray);


        usersSamp = new treeNode( 0, "users","", {userSample});

        return usersSamp;
    }

    string insert_tab(string s, int n) {
        string str = " ";

        for (int i = 0; i < 4 * n; i++) {
            s.insert(0, str);
        }
        return s;
    }

    string removeSpacesFromLine(string s) {
        int begin = 0, end = s.length() - 1;

        for (int i = begin; i < s.size(); i++) {
            if (s[i] != ' ') {
                begin = i;
                break;
            }
        }

        for (int i = end; i >= 0; i--) {
            if (s[i] != ' ') {
                end = i;
                break;
            }
        }
        return s.substr(begin, end + 1);
    }

    vector<string> line_to_str(vector<Line>v){
        vector<string>ss;
        for(long long i = 0; i < v.size(); i++) ss.push_back(v[i].text);
        return ss;
    }

};
#endif //COLLEGEPROJECT_HASHUTIL_H
