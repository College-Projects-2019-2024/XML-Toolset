#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"
using namespace std;

ifstream fileInputStream1;
ofstream fileOutputStream1;


hashUtil x;


void MinifyXML(string inputFileName, string outputFileName)
{
    fixLine(inputFileName,"temp_out1.xml");
    removeSpacesFromFile("temp_out1.xml","temp_out2.xml");
    fileInputStream1.open("temp_out2.xml");
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        currentLine = removeSpacesFromLine(currentLine);
        for(int i=0; i<currentLine.length(); i++)
        {
            if(i>0 && currentLine[i]==' ' && currentLine[i+1]==' '  || currentLine[i]=='\n') continue;
            fileOutputStream1 << currentLine[i];

        }
    }
    remove("temp_out1.xml");
    remove("temp_out2.xml");
}
void CompressXML(string inputFileName , string outputFileName)
{
    fixLine(inputFileName,"temp_out1.xml");
    removeSpacesFromFile("temp_out1.xml","temp_out2.xml");
    fileInputStream1.open("temp_out2.xml");
    fileOutputStream1.open(outputFileName);
    string currentLine = "", text = "";
    bool writeTag = false;

    while (getline(fileInputStream1, currentLine))
    {
        currentLine = removeSpacesFromLine(currentLine);
        for(char c : currentLine)
        {
            if(c=='>')
            {
                text+='>';
                writeTag = false;
                fileOutputStream1 << x.stringToCodeXML(text);
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
    fileInputStream1.close();
    remove("temp_out1.xml");
    remove("temp_out2.xml");
}
void deCompressXML(string inputFileName , string outputFileName)
{

    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
            if(x.codeToStringXML(c) != "")
            {
                fileOutputStream1 << x.codeToStringXML(c);
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



void MinifyJSON(string inputFileName, string outputFileName)
{
    fixLine(inputFileName,"temp_out1.xml");
    removeSpacesFromFile("temp_out1.xml","temp_out2.xml");
    fileInputStream1.open("temp_out2.xml");
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        currentLine = removeSpacesFromLine(currentLine);
        for(int i=0; i<currentLine.length(); i++)
        {
            if(i>0 && currentLine[i]==' ' && currentLine[i+1]==' '  || currentLine[i]=='\n') continue;
            fileOutputStream1 << currentLine[i];

        }
    }
    remove("temp_out1.xml");
    remove("temp_out2.xml");
}
void CompressJSON(string inputFileName , string outputFileName)
{
    fixLine(inputFileName,"temp_out1.xml");
    removeSpacesFromFile("temp_out1.xml","temp_out2.xml");
    fileInputStream1.open("temp_out2.xml");
    fileOutputStream1.open(outputFileName);
    string currentLine = "", text = "";
    bool writeTag = false;

    while (getline(fileInputStream1, currentLine))
    {
        currentLine = removeSpacesFromLine(currentLine);
        for(char c : currentLine)
        {
            if(c=='>')
            {
                text+='>';
                writeTag = false;
                fileOutputStream1 << x.stringToCodeXML(text);
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
    fileInputStream1.close();
    remove("temp_out1.xml");
    remove("temp_out2.xml");
}
void deCompressJSON(string inputFileName , string outputFileName)
{

    fileInputStream1.open(inputFileName);
    fileOutputStream1.open(outputFileName);
    string currentLine = "";
    while (getline(fileInputStream1, currentLine))
    {
        for(char c : currentLine)
        {
            if(x.codeToStringXML(c) != "")
            {
                fileOutputStream1 << x.codeToStringXML(c);
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

