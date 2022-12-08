#include "string"
#include "vector"
using namespace std;

#ifndef COLLEGEPROJECT_PRETTIFY_XML_H
#define COLLEGEPROJECT_PRETTIFY_XML_H
void prettify(const string& inFileName,const string& outFileName);
string insert_tab(string s,int n);
vector<string>divide_string(string str1);
vector<string> get_xml(string inputFileName);

#endif //COLLEGEPROJECT_PRETTIFY_XML_H
