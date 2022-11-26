#include <bits/stdc++.h>
#include "compression.h"

using namespace std;


ifstream myfile;
ofstream myfileo;

class hashUtil
{

private: vector <string> tags {"users", "user", "id", "name", "posts", "post", "body", "topics", "topic", "followers", "follower"};
    vector <string> table; // a table to contain opening and closing tags
public:  hashUtil()
    {
        table.resize(46); //

        for (string tag : tags)
        {
            table [int (hashInTable('<'+ tag +'>'))]  = '<'+tag+'>';
        }
        for (string tag : tags)
        {
            table [int (hashInTable("</" + tag +'>')) ]  = "</" + tag +'>';
        }

    }
private:  unsigned char hashInTable(string s)
    {
        if (!(s.front() == '<' && s.back() == '>'))
        {
            return -1;
        }
        else
        {
            if (s[1]== '/')
            {
                return (( 2* (int(s[2]) - int(s[s.size()-2]) + 23) % 23  )+ 23);
            }
            else
            {
                return ( 2* (int(s[1]) - int(s[s.size()-2]) + 23) % 23 );
            }
        }
    }

public:

    string codeToString(unsigned char x)
    {
        if(x-128 < 0) return "";
        return table[(short)x-128];



    }

    unsigned char stringToCode(string x)
    {

        return (isValidTag(x))? hashInTable(x)+128 : -1;
    }

    bool isValidTag(string x)
    {
        if(find(table.begin(), table.end(),x) != table.end() && hashInTable(x)!=-1)
        {
            return true;
        }
        return false;
    }



};
hashUtil x;
//removes spaces from the start and end of each line
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

void Compress()
{
    fixLine();
    removeSpacesFromFile();
    myfile.open ("out.xml");
    myfileo.open("outCompressed.xml");
    string currentLine = "";
    while (getline(myfile,currentLine))
    {
        if(currentLine[0] == '<' && x.isValidTag(currentLine))
        {
                myfileo << x.stringToCode(currentLine) << endl;
        }
        else
        {
            myfileo << currentLine << endl;
        }
    }
    myfileo.close();
    myfile.close();
}

void deCompress()
{

    myfile.open ("outCompressed.xml");
    myfileo.open("outdeCompressed.xml");
    string currentLine = "";
    while (getline(myfile,currentLine))
    {
        string res = x.codeToString((int)currentLine[0]);

        myfileo << ((res == "")? currentLine : res) << endl;



    }
}



