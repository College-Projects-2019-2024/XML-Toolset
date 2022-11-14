#include <bits/stdc++.h>
using namespace std;
unordered_map<string,int> tags(1000);
hash<string> hasher;
ifstream myfile;
ofstream myfileo;



//removes spaces from the start of each line
string removeSpacesFromLine(string s)
{
    int begin=0;
    for(int i =0; i<s.size(); i++)
    {
        if(s[i]!=' ')
        {
            begin = i;
            break;
        }
    }
    return s.substr(begin);
}
//removes spaces from the start of each line in the file
void removeSpacesFromFile()
{
    //TODO if output file is the same as input file, then create a new file and delete the old one
    myfile.open ("outFixed.xml");
    myfileo.open("out.xml");
    string currentLine;
    bool allWhiteSpace = true;
    while (getline(myfile,currentLine))
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
        myfileo << removeSpacesFromLine(currentLine) <<endl;
    }
    myfileo.close();
    myfile.close();
}

void fixLine()
{    myfile.open ("sample.xml");
     myfileo.open("outFixed.xml");
    string currentLine,data="";
    int charNum = 1;
    while (getline(myfile,currentLine)) {
      for(char c : currentLine)
      {
          if(c=='<')
          {
              myfileo << '\n';
          }
          if(c =='>'&&charNum!=currentLine.length())
          {
              myfileo << c << '\n';
              charNum++;
              continue;
          }
          myfileo << c;
          charNum++;
      }

    }
    myfileo.close();
    myfile.close();
}



void Minify()
{
    fixLine();
    removeSpacesFromFile();
    myfile.open ("out.xml");
    myfileo.open("out1.xml");
    string currentLine = "";
    while (getline(myfile,currentLine))
    {
        for(int i=0; i<currentLine.length(); i++)
        {
            //TODO modify currentLine[i]==' ' && currentLine[i+1]==' ' in a Function
            if(i>0 && currentLine[i]==' ' && currentLine[i+1]==' '  || currentLine[i]=='\n') continue;
            myfileo << currentLine[i];

        }
    }

}



//TODO Later
string mapTags(const char* inFileName,const char* outFileName)
{
    myfile.open ("out.xml");
    myfileo.open("outFileName.xml");
    string currentLine;
    while (getline(myfile,currentLine))
    {
        if(removeSpacesFromLine(currentLine)[0]=='<')
        {
           tags[currentLine] = hasher(currentLine)%1000;
           myfileo << hasher(currentLine)%1000<<endl;
        }
        else
        {
            myfileo << currentLine <<endl;
        }
    }
    myfile.close();
    return outFileName;

}

