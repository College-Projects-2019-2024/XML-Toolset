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

string insert_tab(string s,int n){
    string str = " ";

    for(int i = 0; i<4*n; i++){
        s.insert(0,str);
    }
    return s;
}

void prettify(string fileName) {
    fileInputStream.open(fileName);
    fileOutputStream.open("prettified.xml");

    string current_line;
    stack<int> stac;
    int count = 0;
    string str;
    while (getline(fileInputStream, current_line)) {

        while (current_line[0] == ' ') {
            current_line.erase(0, 1);
        }

        int position = 0;
        int x = current_line.length() - 1;

        while ( position != x) {

            int first = current_line.find('<', position);
            position = current_line.find('>', first);
            int next = current_line.find('<',position);



            if ( first == -1 && position == -1){
                answer.push_back(insert_tab(current_line, count));
                break;
            }

            else if (current_line[first] == '<' && current_line[first+1] != '/') {

                stac.push(count);
                str = current_line.substr(first,position-first+1);
                answer.push_back(insert_tab(str, count));
                if(next-position-1 >0){
                    if(next == -1){
                        str = current_line.substr(position+1,x-position);
                        answer.push_back(insert_tab(str, count+1));
                        position = x;
                    }
                    else{
                        str = current_line.substr(position+1,next-position-1);
                        answer.push_back(insert_tab(str, count+1));
                    }

                }
                count++;

            }
            else if (current_line[first] == '<' && current_line[first+1] == '/') {
                str = current_line.substr(first,position-first+1);
                answer.push_back(insert_tab(str, stac.top()));
                stac.pop();
                count--;
            }

        }
    }

    for(auto & i : answer) fileOutputStream << i << endl;

    fileInputStream.close();
    fileOutputStream.close();
}