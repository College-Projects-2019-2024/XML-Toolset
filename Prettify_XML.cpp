//prettify partially done, it works correctly with tags only and not in all cases.



#include <iostream>
#include "string"
#include "stack"
#include "vector"

using namespace std;

vector<string>answer;

string insert_tab(string s,int n){
    string str = " ";

    for(int i = 0; i<4*n; i++){
        s.insert(0,str);
    }
    return s;
}

void prettify(){
    freopen("In.in","r",stdin);

    string current_line;
    stack<int> stac;
    int count = 0;
    string str;
    while(getline(cin, current_line)){

        while(current_line[0] == ' '){
            current_line.erase(0,1);
        }

        int position = 0;
        int x = current_line.length() - 1;

        while (position != string::npos && position != x) {

            int first = current_line.find('<', position);
            position = current_line.find('>', position + 1);

            if (position == -1 && first == -1) break;
        }

        if(current_line[0] == '<' && current_line[1] != '/'){
            if(current_line.find('/') != -1){
                answer.push_back(insert_tab(current_line,count));
            }
            else{
                stac.push(count);
                answer.push_back(insert_tab(current_line,count));
                count++;
            }

        }
        else if(current_line[0] == '<' && current_line[1] == '/'){
            answer.push_back(insert_tab(current_line,stac.top()));
            stac.pop();
            count--;
        }
        else{
            for(int i = 0; i<current_line.size()/50; i+=50)
                str = current_line.substr(i,50);
            answer.push_back(insert_tab(str,stac.top()+1));
        }

    }
    for(auto & i : answer) cout<<i<<endl;
}