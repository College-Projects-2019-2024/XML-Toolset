#include <bits/stdc++.h>
#include "compression.h"
#include "MainClass.h"

using namespace std;

Utility x;
ofstream fileOutputStream1;
ifstream fileInputStream1;


vector<string> compressJSON(string inputFileName) {
    fileInputStream1.open(inputFileName);
    string r = "";
    bool inside = false;
    string currentLine = "";
    unsigned char flag;
    string text = "";

    while (getline(fileInputStream1, currentLine)) {
        for (char c: currentLine) {
            if (c == '\"') {
                text += c;
                if (inside) {
                    flag = x.stringToCodeJSON(text);
                    if (flag != '%')
                        r+= flag;
                    else
                        r+= text;
                    text = "";
                }
                inside = !inside;

            } else if (inside) {
                text += c;
            } else if (c != ' ') {
                r+= c;
            }

        }
    }
    vector<string> result;
    result.push_back(r);
    fileInputStream1.close();
    return result;
}

vector<string> deCompressJSON(string inputFileName)
{
    fileInputStream1.open(inputFileName);
    string result = "";
    string currentLine = "";
    string flag;

    while (getline(fileInputStream1, currentLine)) {
        for (char c: currentLine) {
            flag = x.codeToStringJSON(c);
            if (flag != "")
                result+= flag;

            else
            {
                result += c;
            }
        }
    }
    vector<string> r;
    r.push_back(result);
    fileInputStream1.close();
    return r;
}