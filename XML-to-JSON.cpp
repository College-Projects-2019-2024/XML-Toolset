//
// Created by Marco on 26-Nov-22.
//
#include <bits/stdc++.h>
#include <algorithm>

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
    myfile.open("sample(prettified).xml");
    myfileo.open("output.txt");

    Tree data;

    string currentLine;
    //string content;

    int user_no = 0;
    int user_prop = 0;
    int post_no = 0;
    int follower_no = 0;
    int topic_no = 0;
    int post_prop = 0;

    bool id_flag = false;
    bool name_flag = false;
    bool body_flag = false;
    bool topic_flag = false;
    bool follower_flag = false;

    while(getline(myfile, currentLine))
    {

        myfileo << currentLine << endl;

        if (currentLine.find("<users>") != string::npos)
        {
            data.root = new Node("users");
            continue;
        }

        if (currentLine.find("<user>") != string::npos)
        {
            data.root->children[user_no] = new Node("user");
            user_no++;
            continue;
        }

        if (currentLine.find("<id>") != string::npos)
        {
            /*int start_pos = 0, end_pos = 0;
            start_pos = currentLine.find('>') + 1;
            end_pos = currentLine.find('<', start_pos);

            string id;
            for(int i = start_pos; i < end_pos; i++)
            {
                id = id + currentLine[i];
            }*/

            id_flag = true;
            data.root->children[user_no - 1]->children[user_prop] = new Node("id");
            user_prop++;
            continue;
        }

        if (currentLine.find("<name>") != string::npos)
        {
            name_flag = true;
            data.root->children[user_no - 1]->children[user_prop] = new Node("name");
            user_prop++;
            continue;
        }

        if (currentLine.find("<posts>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop] = new Node("posts");
            user_prop++;
            continue;
        }

        if (currentLine.find("<post>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no] = new Node("post");
            post_no++;
            continue;
        }

        if (currentLine.find("<body>") != string::npos)
        {
            body_flag = true;
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop] = new Node("body");
            post_prop++;
            continue;
        }



        if(currentLine.find('/') != string::npos)
        {
            continue;
        }

        //content = content + currentLine;

        if(id_flag || name_flag)
        {
            currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\t'), currentLine.end());
            currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\n'), currentLine.end());
            data.root->children[user_no - 1]->children[user_prop - 1]->value = currentLine;
            //content = "";
            id_flag = false;
            name_flag = false;
            continue;
        }

        if(body_flag)
        {
            currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\t'), currentLine.end());
            currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\n'), currentLine.end());
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop - 1]->value += currentLine;
            body_flag = false;
            continue;
        }


    }



    myfile.close();
    myfileo.close();
}