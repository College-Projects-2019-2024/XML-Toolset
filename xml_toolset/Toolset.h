#include <vector>
#include <queue>
#include <stack>
#include "Utility.h"


#ifndef TOOLSET_H
#define TOOLSET_H
#define MAX 100


class Toolset {
private:
    ifstream fileInputStream2;

    vector<Line> lines;
    vector<string> str;

    Utility util;

    vector<string>xmlCompressed;
    vector<string>corrected;
    vector<Line>detect;
    bool can_increment = true;
    int x = 0;


public:
    //constructor
    Toolset(string input) {
        this->lines = util.get_xml(input);
        this->str = util.line_to_str(lines);
    }

    //getters
    vector<string>getCorrected(){
        return this->corrected;
    }

    vector<Line>getdetected(){
        return this->detect;
    }
    void clear(){
        this->x = 0;
        this->detect.clear();
        this->corrected.clear();
    }

    //functions
    treeNode* ans(treeNode * usersSamp)
    {
        treeNode * myIDSample = new treeNode( -1, "id","my id is 123", {});//0
        treeNode * nameSample = new treeNode( -1, "name","Dallash", {});//1


        treeNode * topicSample = new treeNode( -1, "topic","this is my topic", {});
        treeNode * topicsSample = new treeNode( 0, "topics","", {topicSample});
        treeNode * bodySample =  new treeNode( -1, "body","this is my body", {});
        vector<treeNode *> postChildrenArray = { bodySample,  topicsSample};
        treeNode * postSample = new treeNode( 1, "post","", postChildrenArray);
        treeNode * postsSample = new treeNode( 0, "posts","", {postSample});//2


        treeNode * hisIDSample = new treeNode( -1, "id","his id is 456", {});
        treeNode * followerSample = new treeNode( 0, "follower","", {hisIDSample});
        treeNode * followersSample = new treeNode( 0, "followers","", {followerSample});//3


        vector<treeNode *> userChildrenArray = { myIDSample,  nameSample, postsSample,followersSample};
        treeNode * userSample = new treeNode( 3, "user","", userChildrenArray);


        usersSamp = new treeNode( 0, "users","", {userSample});

        return usersSamp;
    }
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

    bool goOn (treeNode * node, int x)
    {
        string f;
        if (x>=lines.size()) return false;

        f = ""; f+= "<";f+=node->type; f+=">";
        if (f == lines[x].text) return true;

        if (node->max ==-1)
        {
            f = ""; f+= "</";f+=node->type; f+=">";
            if (  (lines[x].text.front() != '<' && lines[x].text.back() != '>')  ||  lines[x].text==f)  return true;
            else return false;
        }
        else  return goOn(node->children[0], x); //check the first child only as it is sufficient
    }

    void checknode(treeNode * node )
    {
        string s,f;
        if (can_increment) s = lines[x++].text;
        f = ""; f+= "<";f+=node->type; f+=">";
        if (f != s)  {
            detect.push_back({f,lines[x-1].index});
            can_increment = false;
        }
        else can_increment = true;
        corrected.push_back(f);



        if (node->max ==-1)
        {
            if (!can_increment)
            {
                if ( !(lines[x-1].text.front() != '<' && lines[x-1].text.front() != '>') )
                {
                    detect.push_back({node->type + "has no text",lines[x-1].index});
                    corrected.push_back("noText");
                }
                else can_increment = true,corrected.push_back(lines[x-1].text);
            }
            else
            {
                if (!(lines[x].text.front() != '<' && lines[x].text.front() != '>'))
                {
                    detect.push_back({node->type + "has no text",lines[x-1].index});
                    corrected.push_back("noText");
                }
                else x++, can_increment = true,corrected.push_back(lines[x-1].text);
            }
        }
        else
        {
            fori(node->max + 1)
            {
                checknode(node->children[i]);
                f = ""; f+= "</";f+=node->type; f+=">";
                if (i== node->max && lines[x].text!=f && goOn(node->children[i],x)) i--;
            }
        }

        if (can_increment) s= lines[x++].text;
        f = ""; f+= "</";f+=node->type; f+=">";
         corrected.push_back(f);



        if (f != s)
        {
            detect.push_back({f,lines[x-1].index});
            can_increment = false;
        }
        else can_increment = true;
    }


};

#endif // TOOLSET_H
