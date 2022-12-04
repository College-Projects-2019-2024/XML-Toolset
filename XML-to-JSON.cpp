//
// Created by Marco on 26-Nov-22.
//
#include <bits/stdc++.h>

#include "XML-to-JSON.h"

#define MAX_NO_OF_CHILDREN 100


using namespace std;

ifstream myfile;
ofstream myfileo;



class Node{
public:
    string type;
    string value;
    Node * children[MAX_NO_OF_CHILDREN];

    Node(string t, string v)
    {
        value = v;
        type = t;
    }
    Node(string t)
    {
        type = t;
    }


};

class Tree{
public:
    Node * root;

};


void load_tree (){
    myfile.open("sample.xml");
    myfileo.open("output.txt");

    Tree data;

    string currentLine;

    int user_no = 0;
    int user_prop = 0;
    int post_no = 0;
    int follower_no = 0;

    while(getline(myfile, currentLine))
    {

        myfileo << currentLine << endl;
        if (currentLine.find("<users>") != string::npos)
        {
            data.root = new Node("users");
        }
        if (currentLine.find("<user>") != string::npos)
        {
            data.root->children[user_no] = new Node("user");
            user_no++;
        }
        if (currentLine.find("<id>") != string::npos)
        {
            int start_pos = 0, end_pos = 0;
            start_pos = currentLine.find('>') + 1;
            end_pos = currentLine.find('<', start_pos);

            string id;
            for(int i = start_pos; i < end_pos; i++)
            {
                id = id + currentLine[i];
            }
            data.root->children[user_no - 1]->children[user_prop] = new Node("id", id);
            user_prop++;
        }
        if (currentLine.find("<name>") != string::npos)
        {
            int start_pos = 0, end_pos = 0;
            start_pos = currentLine.find('>') + 1;
            end_pos = currentLine.find('<', start_pos);

            string name;
            for(int i = start_pos; i < end_pos; i++)
            {
                name = name + currentLine[i];
            }
            data.root->children[user_no - 1]->children[user_prop] = new Node("name", name);
            user_prop++;
        }





    }



    myfile.close();
    myfileo.close();
}