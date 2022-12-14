#ifndef COLLEGEPROJECT_COMPRESSION_H
#define COLLEGEPROJECT_COMPRESSION_H
using namespace std;

string MinifyXML(vector<string> file);
string CompressXML(vector<string> file);
vector<string> deCompressXML(vector<string> file);
void compressJSON(string inputFileName, string outputFileName);
void deCompressJSON(vector<string> input);
#endif //COLLEGEPROJECT_COMPRESSION_H
