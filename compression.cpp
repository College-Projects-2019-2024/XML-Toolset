#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"
using namespace std;

ifstream fileInputStream1;
ofstream fileOutputStream1;


hashUtil x;


void Minify(string inputFileName, string outputFileName)
{
    fixLine();
    removeSpacesFromFile();
    fileInputStream1.open ("out.xml");
    fileOutputStream1.open("out1.xml");
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        for(int i=0; i<currentLine.length(); i++)
        {
            //TODO modify currentLine[i]==' ' && currentLine[i+1]==' ' in a Function
            if(i>0 && currentLine[i]==' ' && currentLine[i+1]==' '  || currentLine[i]=='\n') continue;
            fileOutputStream1 << currentLine[i];

        }
    }
}


void Compress(string inputFileName , string outputFileName)
{
    fixLine();
    removeSpacesFromFile();
    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "", text = "";
    bool writeTag = false;

    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
            if(c=='>')
            {
                text+=c;
                writeTag = false;
                fileOutputStream1 << x.stringToCode(text);
                text = "";

            }
            else if(c == '<' || writeTag)
            {
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
    fileInputStream1.close();
}
void deCompress(string inputFileName , string outputFileName)
{

    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
            if(x.codeToString(c)!="")
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
    fileInputStream1.close();
}



