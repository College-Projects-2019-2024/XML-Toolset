#include <bits/stdc++.h>
#include <iostream>
#include "string"
#include "stack"
#include "vector"
#include "Utility.h"
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



void prettify(vector<string>v,const string& outFileName) {

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
