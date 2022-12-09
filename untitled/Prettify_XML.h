#include "string"
#include "vector"
using namespace std;

#ifndef COLLEGEPROJECT_PRETTIFY_XML_H
#define COLLEGEPROJECT_PRETTIFY_XML_H
void prettify(vector<string>v, const string& outName);
string insert_tab(string s,int n);
vector<string> get_xml(string inputFileName);


#endif //COLLEGEPROJECT_PRETTIFY_XML_H
