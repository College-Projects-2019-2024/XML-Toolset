#include <bits/stdc++.h>
#include "Utility.h"
using namespace std;
ifstream fileInputStream2;


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

vector<string> get_xml(string inputFileName) {

    fileInputStream2.open(inputFileName);
    string current_line;
    string str;
    vector<string> xml;

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
                xml.push_back(removeSpacesFromLine(str));
                text_at_start = false;
            }
                //if the line consists only of text
            else if (first == -1 && position == -1) {
                xml.push_back(removeSpacesFromLine(current_line));
                position = x;
            }
                //found an opening tag
            else if (current_line[first] == '<' && current_line[first + 1] != '/') {
                text_at_start = false;
                str = current_line.substr(first, position - first + 1);
                xml.push_back(removeSpacesFromLine(str));

                //if the line consists of an opening tag then text
                if (next == -1 && x - position != 0) {
                    str = current_line.substr(position + 1, x - position);
                    xml.push_back(removeSpacesFromLine(str));
                    position = x;
                }
                //if the line consists of an opening tag then text then closing tag
                if (next - position - 1 > 0) {

                    str = current_line.substr(position + 1, next - position - 1);
                    xml.push_back(removeSpacesFromLine(str));

                }
            }
                //found a closing tag
            else if (current_line[first] == '<' && current_line[first + 1] == '/') {

                str = current_line.substr(first, position - first + 1);
                xml.push_back(removeSpacesFromLine(str));


            }
        }

    }
    fileInputStream2.close();
    return xml;
}
