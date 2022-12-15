#include <bits/stdc++.h>
#include "compression.h"
#include "hashUtil.h"
#include "MainClass.h"
using namespace std;

Utility x;
ofstream fileOutputStream1;
ifstream fileInputStream1;


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