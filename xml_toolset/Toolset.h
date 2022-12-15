#include <vector>
#include <queue>
#include <stack>
#include "Utility.h"


#ifndef TOOLSET_H
#define TOOLSET_H


class Toolset {
private:
    vector<Line> lines;
    vector<string> str;
    Utility util;
    vector<string> xmlCompressed;
    ifstream fileInputStream2;

public:
    //constructor
    Toolset(string input) {
        this->lines = util.get_xml(input);
        this->str = util.line_to_str(lines);
    }

    //functions
    vector<string> prettify() {
        vector<string> v = str;
        vector<string> answer;
        //a stack to keep track of number of tabs to be inserted
        stack<int> stac;
        //count the number of tabs to be inserted into a string
        int count = 0;
        //count number of spaces in a text
        int n = 0;
        //flag used in dividing large texts
        bool flag = false;

        for (int i = 0; i < v.size(); i++) {
            //opening tag
            if (v[i][0] == '<' && v[i][1] != '/') {
                stac.push(count);
                answer.push_back(util.insert_tab(v[i], count));
                count++;
            }
                //closing tag
            else if (v[i][0] == '<' && v[i][1] == '/') {
                answer.push_back(util.insert_tab(v[i], stac.top()));
                stac.pop();
                count--;
            }
                //a text
            else if (v[i][0] != '<') {
                int k = 0;
                for (int j = 0; j < v[i].length(); j++) {

                    if (v[i][j] == ' ')n++;
                    /*if the text has more than 12 words, divide it into substrings
                    where each substring consists of at least 12 words*/
                    if (n == 12) {
                        answer.push_back(util.insert_tab(v[i].substr(k, j - k + 1), count));
                        k = j;
                        n = 0;
                        flag = true;
                    }
                }
                //the text was less than 12 words
                if (n < 12 && !flag) {
                    answer.push_back(util.insert_tab(v[i], count));
                } else if (flag) {
                    answer.push_back(util.insert_tab(v[i].substr(k, v[i].length() - k), count));

                }

            }
        }
        return answer;
    }

    string CompressXML() {
        string currentLine = "", text = "", result = "";
        unsigned char flag;
        bool writeTag = false;

        for (string currentLine: str) {
            currentLine = util.removeSpacesFromLine(currentLine);
            for (char c: currentLine) {
                if (c == '>') {
                    text += '>';
                    writeTag = false;
                    flag = util.stringToCodeXML(text);
                    if (flag != '%') {
                        result += util.stringToCodeXML(text);
                    } else result += text;

                    text = "";

                } else if (c == '<' || writeTag) {
                    if (c == '\"') {
                        text += '<';
                        writeTag = true;
                        continue;
                    }
                    text += c;
                    writeTag = true;
                } else {
                    result += c;
                }
            }
        }
        xmlCompressed.push_back(result);
        return result;

    }

    vector<string> deCompressXML(string fileName) {
        fileInputStream2.open(fileName);
        string flag, text = "", currentLine;
        vector<string> result;

        while (getline(fileInputStream2, currentLine)) {
            for (char c: currentLine) {
                flag = util.codeToStringXML(c);
                if (flag != "") {
                    if (text != "")
                        result.push_back(text);

                    result.push_back(flag);
                    text = "";
                } else {
                    text += c;
                }
            }
        }
        fileInputStream2.close();
        return result;
    }
    string MinifyXML()
    {
        string result = "";
        for(string currentLine : str)
            result+=currentLine;
        return result;
    }

};

#endif // TOOLSET_H
