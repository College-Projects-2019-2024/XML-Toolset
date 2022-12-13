#include <bits/stdc++.h>
#include "Utility.h"
#include "queue"
using namespace std;
ifstream fileInputStream2;

string insert_tab(string s,int n){
    string str = " ";

    for(int i = 0; i<4*n; i++){
        s.insert(0,str);
    }
    return s;
}
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

vector<Line> get_xml(string inputFileName) {

    fileInputStream2.open(inputFileName);
    string current_line;
    string str;
    string s = "";
    vector<Line> xml;
    //a queue to store any text other than tags
    queue<string>q;
    int idx = 0;

    while (getline(fileInputStream2, current_line)) {
        idx++;
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
        if(position == x){
            xml.push_back({removeSpacesFromLine(current_line),idx});
            continue;
        }

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
                q.push(str);
                text_at_start = false;
            }
                //if the line consists only of text
            else if (first == -1 && position == -1) {
                q.push(current_line);
                position = x;
                idx--;
            }
                //found an opening tag
            else if (current_line[first] == '<' && current_line[first + 1] != '/') {
                text_at_start = false;
                str = current_line.substr(first, position - first + 1);
                xml.push_back({removeSpacesFromLine(str),idx});

                //if the line consists of an opening tag then text
                if (next == -1 && x - position != 0) {
                    str = current_line.substr(position + 1, x - position);
                    q.push(str);
                    position = x;
                }
                //if the line consists of an opening tag then text then closing tag
                if (next - position - 1 > 0) {

                    str = current_line.substr(position + 1, next - position - 1);
                    q.push(str);


                }
            }
                //found a closing tag
             if (current_line[first] == '<' && current_line[first + 1] == '/') {
                 //this means there is text that has not been pushed to the xml vector yet
                if(!q.empty()){
                    while(!q.empty()){
                        s+=q.front();
                        q.pop();
                    }
                    xml.push_back({removeSpacesFromLine(s),idx});
                    s="";
                    idx++;
                }

                str = current_line.substr(first, position - first + 1);
                xml.push_back({removeSpacesFromLine(str),idx});
                text_at_start = false;


            }
        }

    }

    fileInputStream2.close();
    return xml;
}


