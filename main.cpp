#include <bits/stdc++.h>
#include "XML-to-JSON.h"


#include <iostream>

using namespace std;

#define fori(size) for(int i=0; i < (size); i+= 1)

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

treeNode * usersSample;


bool ans()
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


    usersSample = new treeNode( 0, "users","", {userSample});
    return true;
}

int currentLine = 0;
string s;
vector<string> token;

void load_xml(treeNode * samplenode, treeNode * data)
{
    s = token[currentLine++];

    if(samplenode->max == -1)
    {
        //store text
        data->text = token[currentLine++];
    }
    else
    {
        fori(samplenode->max + 1)
        {
            //create new node nn
            treeNode * createdNode = new treeNode(samplenode->children[i]->max, samplenode->children[i]->type, samplenode->children[i]->text, {});
            load_xml(samplenode->children[i], createdNode);
            //add to the vector (push created node)
            data->children.push_back(createdNode);
            string f = ""; f+= "<";f+=samplenode->children[samplenode->max]->type; f+=">";
            if(i== samplenode->max && f == token[currentLine]) i--;
        }
    }

    s = token[currentLine++];
}

void print_JSON(treeNode * data, int n,bool arr_obj)
{
    bool object = false;
    string tab;

    fori(n) tab += "    ";

    if(data->type == "topics" && data->children.size() > 1)
    {
        cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";
        cout << tab << "   " << "\"" << "topic" << "\"" << ":" << " " << "[" <<"\n";
        fori(data->children.size())
        {
            cout << tab << "       " << "\"" << data->children[i]->text << "\"";
            if(i == (data->children.size() -1))
            {
                cout << "\n";
            }
            else
            {
                cout << "," << "\n";
            }
        }
        cout << tab << "   " << "]" << "\n";
        cout << tab << "}";
        return;
    }

    if (data->max == -1)
    {
        cout << tab << "\"" << data->type << "\"" << ":" << " ";
        cout << "\"" << data->text << "\"";
        return;
    }
    else
    {
        if(data->children.size() == 1) object = true;

        fori(data->children.size() - 1)
        {
            if(data->children[i]->type != data->children[i + 1]->type) object = true;
        }

        if(object){
            if(arr_obj)
            {
                cout  << tab << "   " << '{' << "\n";
            }
            else
            {
                cout  << tab << "\"" << data->type << "\"" << ":" << " " << '{' << "\n";
            }

            fori(data->children.size()) {
                print_JSON(data->children[i], n + 1, false);
                if(i == (data->children.size() - 1))
                {
                    cout << "\n";
                }
                else
                {
                    cout << "," << "\n";
                }
            }
            tab += "    ";
            cout << tab << '}';

        }
        else
        {
            cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";

            cout << tab << "    " << "\"" << data->children[0]->type << "\"" << ":" << " " << "[" << "\n";

            fori(data->children.size()) {
                print_JSON(data->children[i], n + 1, true);
                if(i == (data->children.size() -1))
                {
                    cout << "\n";
                }
                else
                {
                    cout << "," << "\n";
                }
            }

            cout << tab << "    " << ']' << "\n";
            cout << tab << '}';

        }
    }
}

void Convert_to_Json(treeNode* data)
{
    cout << '{' << "\n";

    print_JSON(data, 1, true);

    cout << "\n" << '}' << "\n";
}

void XMLtoJSON(treeNode* samplenode, treeNode * data)
{
    load_xml(samplenode, data);
    Convert_to_Json(data);

}

int main() {
    freopen("sample(prettified).xml", "r", stdin);

    while (cin >> s) token.push_back(s);
    ans();
    treeNode * dataRoot = new treeNode(0,"users","", {});
    XMLtoJSON(usersSample, dataRoot);

    return 0;
}
