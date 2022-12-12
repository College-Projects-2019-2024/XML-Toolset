#include <bits/stdc++.h>
#include "Utility.h"

using namespace std;


int currentLine = 0;
string s;


void load_xml(treeNode * samplenode, treeNode * data, vector<Line> token)
{
    s = token[currentLine++].text;

    if(samplenode->max == -1)
    {
        //store text
        data->text = token[currentLine++].text;
    }
    else
    {
        fori(samplenode->max + 1)
        {
            //create new node nn
            treeNode * createdNode = new treeNode(samplenode->children[i]->max, samplenode->children[i]->type, samplenode->children[i]->text, {});
            load_xml(samplenode->children[i], createdNode, token);
            //add to the vector (push created node)
            data->children.push_back(createdNode);
            string f = ""; f+= "<";f+=samplenode->children[samplenode->max]->type; f+=">";
            if(i== samplenode->max && f == token[currentLine].text) i--;
        }
    }

    s = token[currentLine++].text;
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

void XMLtoJSON(treeNode* samplenode, treeNode * data, vector<Line> t)
{
    load_xml(samplenode, data, t);
    Convert_to_Json(data);
}
