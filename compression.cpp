#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"
using namespace std;

hashUtil x;
ofstream fileOutputStream1;
ifstream fileInputStream1;

void MinifyXML(string inputFileName, string outputFileName)
{
    vector<string> file =  get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);
    for (string currentLine : file) fileOutputStream1 << currentLine;
    fileOutputStream1.close();
}
void CompressXML(string inputFileName, string outputFileName)
{
    vector<string> file =  get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine="", text = "";
    unsigned char flag;
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
                flag = x.stringToCodeXML(text);
                if(flag!='%')
                {
                    fileOutputStream1 << x.stringToCodeXML(text);
                }
                else fileOutputStream1 << text;

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
void deCompressXML(string inputFileName, string outputFileName)
{
    vector<string> file = get_xml(inputFileName);
    fileOutputStream1.open(outputFileName);
    string flag;

    for (string currentLine : file)
    {
        for(char c : currentLine)
        {
            flag = x.codeToStringXML(c);
            if(flag != "")
            {
                fileOutputStream1 << flag;
            }
            else
            {
                fileOutputStream1 << c ;
            }
        }
    }
    fileOutputStream1.close();
}

void compressJSON(string inputFileName, string outputFileName)
{
    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    bool inside = false;
    string currentLine = "";
    unsigned char flag;
    string text = "";

    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
            if (c=='\"')
            {
                text+=c;
                if(inside)
                {
                    flag = x.stringToCodeJSON(text);
                    if(flag!='%')
                        fileOutputStream1 << flag;
                    else
                        fileOutputStream1 << text;
                    text = "";
                }
                inside=!inside;

            }
            else if(inside)
            {
                text+=c;
            }
            else if(c!=' ')
            {
                fileOutputStream1 << c;
            }

        }
    }
    fileOutputStream1.close();
    fileInputStream1.close();
}

void deCompressJSON(string inputFileName, string outputFileName)
{
    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    bool inside = false;
    string flag;

    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
        flag = x.codeToStringJSON(c);
        if(flag!="") fileOutputStream1 << flag;

        else
        {
            fileOutputStream1 << c;
        }
        }
    }
    fileOutputStream1.close();
    fileInputStream1.close();
}