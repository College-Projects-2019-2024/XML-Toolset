#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"
using namespace std;

hashUtil x;
ofstream fileOutputStream1;

void MinifyXML(string inputFileName, string outputFileName)
{
    vector<string> file =  get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);
    for (string currentLine : file) fileOutputStream1 << currentLine;
    fileOutputStream1.close();
}

void CompressXML(string inputFileName , string outputFileName)
{
    vector<string> file =  get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "", text = "";
    bool writeTag = false;

    for (string currentLine : file)
    {
        currentLine = removeSpacesFromLine(currentLine);
        for(char c : currentLine)
        {
            if(c=='>')
            {
                text+='>';
                writeTag = false;
                fileOutputStream1 << x.stringToCode(text);
                text = "";

            }
            else if(c == '<' || writeTag)
            {
                if(c == '\"')
                {
                    text+='<';
                    writeTag = true;
                    continue;
                }
                text+=c;
                writeTag = true;
            }
            else
            {
                fileOutputStream1 << c ;
            }
        }
    }
    fileOutputStream1.close();
}

 void deCompressXML(string inputFileName , string outputFileName)
{
    vector<string> file = get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);

    for (string currentLine : file)
    {
        for(char c : currentLine)
        {
            if(x.codeToString(c) != "")
            {
                fileOutputStream1 << x.codeToString(c);
            }
            else
            {
                fileOutputStream1 << c ;
            }
        }
    }
    fileOutputStream1.close();

}


