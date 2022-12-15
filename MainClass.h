#ifndef COLLEGEPROJECT_MAINCLASS_H
#define COLLEGEPROJECT_MAINCLASS_H
#include <bits/stdc++.h>
#include "utility.h"

using namespace std;

    class MainClass {
        vector<string> xml;
        ifstream fileInputStream2;
        Utility util;

    public:
        MainClass(string inputFileName)
        {
            fileInputStream2.open(inputFileName);
            string current_line;
            string str;

            while (getline(fileInputStream2, current_line)) {
                //remove spaces from start on the line
                while (current_line[0] == ' ') {
                    current_line.erase(0, 1);
                }
                bool text_at_start = true;

                //a value that keeps track of the position of '>'
                int position = 0;
                //a temp value to hold initial position
                int d = position;
                int x = current_line.length() - 1;

                //if line is empty
                if(x == -1)continue;

                while (position != x) {
                    //first occurrence of '<' starting from position
                    int first = current_line.find('<', position);
                    //first occurrence of '>' starting from the position of the previous '<'
                    position = current_line.find('>', first);
                    //second occurrence of '<' starting from position
                    int next = current_line.find('<', position);

                    //if the line consists of text at start then closing tag
                    if (d < first && text_at_start) {
                        str = current_line.substr(d, first);
                        xml.push_back(util.removeSpacesFromLine(str));
                        text_at_start = false;
                    }
                        //if the line consists only of text
                    else if (first == -1 && position == -1) {
                        xml.push_back(util.removeSpacesFromLine(current_line));
                        position = x;
                    }
                        //found an opening tag
                    else if (current_line[first] == '<' && current_line[first + 1] != '/') {
                        text_at_start = false;
                        str = current_line.substr(first, position - first + 1);
                        xml.push_back(util.removeSpacesFromLine(str));

                        //if the line consists of an opening tag then text
                        if (next == -1 && x - position != 0) {
                            str = current_line.substr(position + 1, x - position);
                            xml.push_back(util.removeSpacesFromLine(str));
                            position = x;
                        }
                        //if the line consists of an opening tag then text then closing tag
                        if (next - position - 1 > 0) {

                            str = current_line.substr(position + 1, next - position - 1);
                            xml.push_back(util.removeSpacesFromLine(str));

                        }
                    }
                        //found a closing tag
                    else if (current_line[first] == '<' && current_line[first + 1] == '/') {

                        str = current_line.substr(first, position - first + 1);
                        xml.push_back(util.removeSpacesFromLine(str));

                    }
                }

            }
            fileInputStream2.close();

        }

        string MinifyXML()
        {
            string result = "";
            for(string currentLine : xml)
                result+=currentLine;
            return result;
        }

        string CompressXML()
        {
            string currentLine="", text = "" , result = "";
            unsigned char flag;
            bool writeTag = false;

            for (string currentLine : xml)
            {
                currentLine = util.removeSpacesFromLine(currentLine);
                for(char c : currentLine)
                {
                    if(c=='>')
                    {
                        text+='>';
                        writeTag = false;
                        flag = util.stringToCodeXML(text);
                        if(flag!='%')
                        {
                            result+= util.stringToCodeXML(text);
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

        vector<string> deCompressXML()
        {

            string flag,text = "";
            vector<string> result;

            for (string currentLine : xml)
            {
                for(char c : currentLine)
                {
                    flag = util.codeToStringXML(c);
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

    };



#endif //COLLEGEPROJECT_MAINCLASS_H
