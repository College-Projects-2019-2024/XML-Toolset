//prettify done

#include <bits/stdc++.h>
#include <iostream>
#include "string"
#include "stack"
#include "vector"
using namespace std;
ifstream fileInputStream;
ofstream fileOutputStream;

vector<string>answer;

vector<string> get_xml(string inputFileName) {

    fileInputStream.open(inputFileName);
    string current_line;
    string str;
    vector<string> xml;

    while (getline(fileInputStream, current_line)) {
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
                xml.push_back(str);
                text_at_start = false;
            }
            //if the line consists only of text
            else if (first == -1 && position == -1) {
                xml.push_back(current_line);
                position = x;
            }
            //found an opening tag
            else if (current_line[first] == '<' && current_line[first + 1] != '/') {
                text_at_start = false;
                str = current_line.substr(first, position - first + 1);
                xml.push_back(str);

                //if the line consists of an opening tag then text
                if (next == -1 && x - position != 0) {
                    str = current_line.substr(position + 1, x - position);
                    xml.push_back(str);
                    position = x;
                }
                //if the line consists of an opening tag then text then closing tag
                if (next - position - 1 > 0) {

                    str = current_line.substr(position + 1, next - position - 1);
                    xml.push_back(str);

                }
            }
            //found a closing tag
            else if (current_line[first] == '<' && current_line[first + 1] == '/') {

                str = current_line.substr(first, position - first + 1);
                xml.push_back(str);


            }
        }

    }
    fileInputStream.close();
    return xml;
}

string insert_tab(string s,int n){
    string str = " ";

    for(int i = 0; i<4*n; i++){
        s.insert(0,str);
    }
    return s;
}



void prettify(const string& inFileName,const string& outFileName) {

    vector<string>v = get_xml(inFileName);
    fileOutputStream.open(outFileName);
    //a stack to keep track of number of tabs to be inserted
    stack<int> stac;
    //count the number of tabs to be inserted into a string
    int count = 0;
    //count number of spaces in a text
    int n = 0;
    //flag used in dividing large texts
    bool flag = false;

    for(int i = 0; i<v.size(); i++){
        //opening tag
        if(v[i][0] == '<' && v[i][1] != '/'){
            stac.push(count);
            answer.push_back(insert_tab(v[i],count));
            count++;
        }
        //closing tag
        else if(v[i][0] == '<' && v[i][1] == '/'){
            answer.push_back(insert_tab(v[i],stac.top()));
            stac.pop();
            count--;
        }
        //a text
        else if(v[i][0] != '<'){
            int k = 0;
            for(int j = 0; j<v[i].length(); j++) {

                if (v[i][j] == ' ')n++;
                /*if the text has more than 12 words, divide it into substrings
                where each substring consists of at least 12 words*/
                if (n == 12) {
                    answer.push_back(insert_tab(v[i].substr(k, j - k + 1),count));
                    k=j;
                    n=0;
                    flag = true;
                }
            }
            //the text was less than 12 words
            if(n<12 && !flag){
                answer.push_back(insert_tab(v[i],count));
            }

            else if(flag){
                answer.push_back(insert_tab(v[i].substr(k,v[i].length()-k),count));

            }

        }
    }
    //write the answer to the output file
    for(auto & i : answer) fileOutputStream << i << endl;

    fileOutputStream.close();
}
