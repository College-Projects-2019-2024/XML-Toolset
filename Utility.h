#ifndef COLLEGEPROJECT_UTILITY_H
#define COLLEGEPROJECT_UTILITY_H
#include <string>
#define fori(size) for(int i=0; i < (size); i+= 1)

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

struct Line{
    string text;
    int index;
};
string insert_tab(string s,int n);
string removeSpacesFromLine(string s);
vector<Line> get_xml(string inputFileName);
vector<string> line_to_str(vector<Line>v);
treeNode* ans(treeNode* usersSample);
#endif //COLLEGEPROJECT_UTILITY_H
