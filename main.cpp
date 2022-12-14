#include <fstream>
#include "iostream"
#include "Prettify_XML.h"
#include "vector"
#include "Utility.h"
using namespace std;
ofstream fileOutput;

int main() {
    vector<string>result;
    result = prettify(line_to_str(get_xml("out.txt")));
    fileOutput.open("out2.txt");
    for(int i = 0; i< result.size(); i++)fileOutput<<result[i]<<endl;
    fileOutput.close();
    return 0;
}