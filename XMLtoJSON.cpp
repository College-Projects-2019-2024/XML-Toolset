#include <bits/stdc++.h>
#include "Utility.h"

using namespace std;


int currentLine = 0;
string s;
vector<string> out;

string print;

bool arr_object = false;




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
        //cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";
        print += tab; print += "\""; print += data->type; print += "\": {";
        out.push_back(print);
        print = "";

        //cout << tab << "   " << "\"" << "topic" << "\"" << ":" << " " << "[" <<"\n";
        print += tab; print += "   \"topic\": [";
        out.push_back(print);
        print = "";

        fori(data->children.size())
        {
            //cout << tab << "       " << "\"" << data->children[i]->text << "\"";
            print += tab; print += "       \""; print += data->children[i]->text; print += "\"";

            if(i == (data->children.size() -1))
            {
                //cout << "\n";
                out.push_back(print);
                print = "";
            }
            else
            {
                //cout << "," << "\n";
                print += ",";
                out.push_back(print);
                print = "";
            }
        }
        //cout << tab << "   " << "]" << "\n";
        print += tab; print += "   ]";
        out.push_back(print);
        print = "";

        //cout << tab << "}";
        print += tab; print += "}";
        return;
    }

    if (data->max == -1)
    {
        //cout << tab << "\"" << data->type << "\"" << ":" << " ";
        print += tab; print += "\""; print += data->type; print += "\": ";

        //cout << "\"" << data->text << "\"";
        print += "\""; print += data->text; print += "\"";
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
                //cout  << tab << "   " << '{' << "\n";
                print += tab; print += "   {";
                out.push_back(print);
                print = "";
            }
            else
            {
                //cout  << tab << "\"" << data->type << "\"" << ":" << " " << '{' << "\n";
                print += tab; print += "\""; print += data->type; print += "\": {";
                out.push_back(print);
                print = "";
            }

            fori(data->children.size()) {
                arr_object = false;
                print_JSON(data->children[i], n + 1, arr_object);
                if(i == (data->children.size() - 1))
                {
                    //cout << "\n";
                    out.push_back(print);
                    print = "";
                }
                else
                {
                    //cout << "," << "\n";
                    print += ",";
                    out.push_back(print);
                    print = "";
                }
            }
            tab += "    ";
            //cout << tab << '}';
            print += tab; print += "}";

        }
        else
        {
            //cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";
            print += tab; print += "\""; print += data->type; print += "\": {";
            out.push_back(print);
            print = "";

            //cout << tab << "    " << "\"" << data->children[0]->type << "\"" << ":" << " " << "[" << "\n";
            print += tab; print += "    \""; print += data->children[0]->type; print += "\": [";
            out.push_back(print);
            print = "";

            fori(data->children.size()) {
                arr_object = true;
                print_JSON(data->children[i], n + 1, arr_object);
                if(i == (data->children.size() -1))
                {
                    //cout << "\n";
                    out.push_back(print);
                    print = "";
                }
                else
                {
                    //cout << "," << "\n";
                    print += ",";
                    out.push_back(print);
                    print = "";
                }
            }

            //cout << tab << "    " << ']' << "\n";
            print += tab; print += "   ]";
            out.push_back(print);
            print = "";

            //cout << tab << '}';
            print += tab; print += "}";

        }
    }
}

void Convert_to_Json(treeNode* data)
{
    //cout << '{' << "\n";
    out.push_back("{");

    print_JSON(data, 1, arr_object);

    //cout << "\n" << '}' << "\n";
    out.push_back("  }");
    out.push_back("}");
}

vector<string> XMLtoJSON(treeNode* samplenode, treeNode * data, vector<Line> t, const char *filename)
{
    load_xml(samplenode, data, t);
    Convert_to_Json(data);
    return out;
}
