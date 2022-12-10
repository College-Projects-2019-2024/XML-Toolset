#ifndef COLLEGEPROJECT_UTILITY_H
#define COLLEGEPROJECT_UTILITY_H
#include <string>
using namespace std;
struct Line{
    string text;
    int index;
};
string removeSpacesFromLine(string s);
vector<Line> get_xml(string inputFileName);

#endif //COLLEGEPROJECT_UTILITY_H
