#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"
using namespace std;

hashUtil x;
ofstream fileOutputStream1;
ifstream fileInputStream1;

string MinifyXML(vector<string> file)
{
    string result = "";
    for(string currentLine : file)
        result+=currentLine;
    return result;
}

string CompressXML(vector<string> file)
{
    string currentLine="", text = "" , result = "";
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
                    result+= x.stringToCodeXML(text);
                }
                else result+= text;

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
                result+= c ;
            }
        }
    }
    return result;

}
vector<string> deCompressXML(vector<string> file)
{

    string flag,text = "";
    vector<string> result;

    for (string currentLine : file)
    {
        for(char c : currentLine)
        {
            flag = x.codeToStringXML(c);
            if(flag != "")
            {
                if(text!="")
                    result.push_back(text);

                result.push_back(flag);
                text="";
            }
            else
            {
                text+=c;
            }
        }
    }
    return result;
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