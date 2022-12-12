#ifndef COLLEGEPROJECT_UTILITY_H
#define COLLEGEPROJECT_UTILITY_H
#include <string>
#include <vector>
using namespace std;
struct Line{
    string text;
    int index;
};
string insert_tab(string s,int n);
string removeSpacesFromLine(string s);
vector<Line> get_xml(string inputFileName);

#endif //COLLEGEPROJECT_UTILITY_H
