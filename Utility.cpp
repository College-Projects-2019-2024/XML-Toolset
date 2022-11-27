#include <bits/stdc++.h>
#include "Utility.h"
using namespace std;
ifstream fileInputStream2;
ofstream fileOutputStream2;

string removeSpacesFromLine(string s)
{
    int begin=0 , end = s.length()-1;

    for(int i = begin; i<s.size(); i++)
    {
        if(s[i]!=' ')
        {
            begin = i;
            break;
        }
    }

    for(int i = end; i>=0; i--)
    {
        if(s[i]!=' ')
        {
            end = i;
            break;
        }
    }
    return s.substr(begin,end+1);
}
void fixLine()
{
    fileInputStream2.open ("sample.xml");
    fileOutputStream2.open("outFixed.xml");
    string currentLine,data="";
    int charNum = 1;
    while (getline(fileInputStream2, currentLine)) {
        for(char c : currentLine)
        {
            if(c=='<')
            {
                fileOutputStream2 << '\n';
            }
            if(c =='>'&&charNum!=currentLine.length())
            {
                fileOutputStream2 << c << '\n';
                charNum++;
                continue;
            }
            fileOutputStream2 << c;
            charNum++;
        }
    }
    fileOutputStream2.close();
    fileInputStream2.close();
}
void removeSpacesFromFile()
{
    //TODO if output file is the same as input file, then create a new file and delete the old one
    fileInputStream2.open ("outFixed.xml");
    fileOutputStream2.open("out.xml");
    string currentLine;
    bool allWhiteSpace = true;
    while (getline(fileInputStream2, currentLine))
    {
        if(currentLine.empty())
        {
            continue;
        }

        for(int i = 0; i<currentLine.length(); i++)
        {
            if(currentLine[i]!=' ')
            {
                allWhiteSpace = false;
                break;
            }
            allWhiteSpace = true;
        }


        if(!allWhiteSpace)
            fileOutputStream2 << removeSpacesFromLine(currentLine) << endl;
    }
    fileOutputStream2.close();
    fileInputStream2.close();
}

