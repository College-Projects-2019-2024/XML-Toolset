#ifndef COLLEGEPROJECT_UTILITY_H
#define COLLEGEPROJECT_UTILITY_H
#include <string>
using namespace std;
struct Line{
    string text;
    int index;
};
string insert_tab(string s,int n);
string removeSpacesFromLine(string s);
vector<Line> get_xml(string inputFileName);
vector<string> line_to_str(vector<Line>v);

#endif //COLLEGEPROJECT_UTILITY_H
