#ifndef COLLEGEPROJECT_UTILITY_H
#define COLLEGEPROJECT_UTILITY_H
#include <string>
#include <vector>

#define fori(size) for(int i=0; i < (size); i+= 1)
#define forj(size) for(int j=0; j < (size); j+= 1)

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


string insert_tab(string s,int n);
string removeSpacesFromLine(string s);
vector<Line> get_xml(string inputFileName);
treeNode* ans(treeNode * usersSample);
int stringTointeger(string str);

#endif //COLLEGEPROJECT_UTILITY_H
