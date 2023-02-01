#ifndef UTILITY_H
#define UTILITY_H
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define fori(size) for(int i=0; i < (size); i+= 1)

struct Line{
    string text;
    int index;
};

class treeNode{
public:
    int max;
    string type;
    string text;
    vector<treeNode *> children;

    treeNode(int max, string type,string text, vector<treeNode *> children)
    {
        this->max = max;
        this->type = type;
        this->text = text;
        this->children = children;
    }
};


class Utility
{
private: vector <string> tags {"users", "user", "id", "name", "posts", "post", "body", "topics", "topic", "followers", "follower"};
         vector <string> table; // a table to contain opening and closing tags
         vector <string> JSONTable;
         hash<string> hasher;
         ifstream fileInputStream2;



public:  Utility()
    {
        table.resize(100);
        JSONTable.resize(90);
        for (string tag : tags)
        {
            table[hasher('<'+ tag +'>')%100]    = '<'+tag+'>';
            table[hasher("</" + tag +">")%100]  = "</" + tag +">";
            JSONTable[hasher("\"" + tag +"\"")%90] = "\"" + tag +"\"";
        }
    }

public:

    vector<Line> get_xml(string inputFileName) {

             fileInputStream2.open(inputFileName);
             string current_line;
             string str;
             string s = "";
             vector<Line> xml;
             //a queue to store any text(other than tags) and its line number
             queue<pair<string, int>> q;
             int idx = 0;


             while (getline(fileInputStream2, current_line)) {
                 //current line number
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
                 if (x == -1)continue;
                 if (position == x) {
                     xml.push_back({removeSpacesFromLine(current_line), idx});
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
                         q.push({str, idx});

                         text_at_start = false;

                     }
                     //if the line consists only of text
                     if (first == -1 && position == -1) {
                         q.push({current_line, idx});
                         position = x;

                     }
                     //found an opening tag
                     if (current_line[first] == '<' && current_line[first + 1] != '/') {
                         //this means there is text that has not been pushed to the xml vector yet
                         if (!q.empty()) {
                             int temp = q.front().second;
                             while (!q.empty()) {
                                 s += q.front().first;
                                 q.pop();

                             }
                             xml.push_back({removeSpacesFromLine(s), temp});
                             s = "";

                         }
                         text_at_start = false;
                         str = current_line.substr(first, position - first + 1);
                         xml.push_back({removeSpacesFromLine(str), idx});

                         //if the line consists of an opening tag then text
                         if (next == -1 && x - position != 0) {
                             str = current_line.substr(position + 1, x - position);
                             q.push({str, idx});
                             position = x;
                         }
                         //if the line consists of an opening tag then text then closing tag
                         if (next - position - 1 > 0) {

                             str = current_line.substr(position + 1, next - position - 1);
                             q.push({str, idx});

                         }
                     }
                     //found a closing tag
                     if (current_line[first] == '<' && current_line[first + 1] == '/') {
                         //this means there is text that has not been pushed to the xml vector yet
                         if (!q.empty()) {
                             int temp = q.front().second;
                             while (!q.empty()) {
                                 s += q.front().first;
                                 q.pop();

                             }

                             xml.push_back({removeSpacesFromLine(s), temp});
                             s = "";

                         }

                         str = current_line.substr(first, position - first + 1);
                         xml.push_back({removeSpacesFromLine(str), idx});
                         text_at_start = false;
                         //if the line consists of an closing tag then text
                         if (next == -1 && x - position != 0) {
                             str = current_line.substr(position + 1, x - position);
                             q.push({str, idx});
                             position = x;
                         }

                         if (next - position - 1 > 0) {

                             str = current_line.substr(position + 1, next - position - 1);
                             q.push({str, idx});

                         }
                     }


                 }

             }

             fileInputStream2.close();
             return xml;
         }

    bool isValidTag(string x)
    {
        if(find(table.begin(), table.end(),x) != table.end() || find(JSONTable.begin(), JSONTable.end(),x) != JSONTable.end())
        {
            return true;
        }
        return false;
    }

    string codeToStringXML(unsigned char x)
    {
        if(x-128 < 0) return "";
        return table[(short)x-128];
    }

    unsigned char stringToCodeXML(string x)
    {
       return (isValidTag(x))? hasher(x)%100+128 : '%';
    }

    string codeToStringJSON(unsigned char x)
    {
        if(x-128 < 0) return "";
        return JSONTable[(short)x-128];
    }

    unsigned char stringToCodeJSON(string x)
    {
        return (isValidTag(x))? (hasher(x)%90)+128 : '%';
    }

    string printPosts(vector<pair<int,int>>v){

        string ans = "";
        string s = "";
        string r = "";
        fori(v.size()){
            r = "Found in user number ";

            r+= to_string(v[i].first);
            r+= ", post number ";
            r+=to_string(v[i].second);

            ans.append(r);
            ans.append("\n");
        }

        return ans;

    }

    int stringTointeger(string str)
    {
        int temp = 0;
        for (int i = 0; i < str.length(); i++) {

            temp = temp * 10 + (str[i] - '0');
        }
        return temp;
    }

    string insert_tab(string s, int n) {
        string str = " ";

        for (int i = 0; i < 4 * n; i++) {
            s.insert(0, str);
        }
        return s;
    }

    string removeSpacesFromLine(string s) {
        int begin = 0, end = s.length() - 1;

        for (int i = begin; i < s.size(); i++) {
            if (s[i] != ' ') {
                begin = i;
                break;
            }
        }

        for (int i = end; i >= 0; i--) {
            if (s[i] != ' ') {
                end = i;
                break;
            }
        }
        return s.substr(begin, end + 1);
    }

    vector<string> line_to_str(vector<Line>v){
        vector<string>ss;
        for(long long i = 0; i < v.size(); i++) ss.push_back(v[i].text);
        return ss;
    }



};
#endif //COLLEGEPROJECT_HASHUTIL_H
