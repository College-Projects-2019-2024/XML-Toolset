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

//a function that divides large strings into multiple 12 word strings.
vector<string> divide_string(string str1){
    int c = 0,n = 0;
    bool flag = false;
    string s;
    vector<string>v;
    for(int i = 0; i<str1.length(); i++) {
        if (str1[i] == ' ') {
            c++;
        }
        if(c==12 ){
            s = str1.substr(n,i-n+1);
            v.push_back(s);
            n=i;
            c=0;
            flag=true;
        }

    }
    if(c<12 && !flag){
        v.push_back(str1);
    }
    if(flag){
        s = str1.substr(n,str1.length()-n);
        v.push_back(s);
    }
    return v;

}

void prettify(const string& fileName) {
    fileInputStream.open(fileName);
    fileOutputStream.open("out2.txt");

    string current_line;
    stack<int> stac;
    int count = 0;
    string str;
    //string s;
    vector<string>v;


    while (getline(fileInputStream, current_line)) {

        while (current_line[0] == ' ') {
            current_line.erase(0, 1);
        }
        bool text_at_start = true;

        int position = 0;
        int d = position;
        int x = current_line.length() - 1;

        while ( position != x) {

            int first = current_line.find('<', position);
            position = current_line.find('>', first);
            int next = current_line.find('<',position);

            //if the line consists of text then closing tag
            if(d<first && text_at_start){
                str = current_line.substr(d,first);
                v = divide_string(str);
                for(int i = 0; i<v.size(); i++){
                    answer.push_back(insert_tab(v[i], stac.top()+1));
                }

                text_at_start = false;
            }
            //if the line consists only of text
            if ( first == -1 && position == -1){
                v = divide_string(current_line);
                for(int i = 0; i<v.size(); i++){
                    answer.push_back(insert_tab(v[i], count));
                }
                break;
            }

            else if (current_line[first] == '<' && current_line[first+1] != '/') {
                text_at_start = false;
                stac.push(count);
                str = current_line.substr(first,position-first+1);
                answer.push_back(insert_tab(str, count));

                //if the line consists of an opening tag then text
                if(next == -1 && x-position != 0){
                    str = current_line.substr(position+1,x-position);
                    v = divide_string(str);
                    for(int i = 0; i<v.size(); i++){
                        answer.push_back(insert_tab(v[i], count+1));
                    }
                    position = x;
                }
                //if the line has an opening tag then text then closing tag
                if(next-position-1 >0){

                    str = current_line.substr(position+1,next-position-1);
                    v = divide_string(str);
                    for(int i = 0; i<v.size(); i++){
                        answer.push_back(insert_tab(v[i], count+1));
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