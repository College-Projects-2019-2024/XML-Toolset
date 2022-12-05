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
    bool follower_id_flag = false;

    while(getline(myfile, currentLine))
    {

        myfileo << currentLine << endl;

        //dealing with opening tags
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
            if(follower_flag){
                data.root->children[user_no - 1]->children[user_prop - 1]->children[follower_no - 1]->children[0] = new Node("id");
                id_flag = true;
                follower_id_flag = true;
                follower_flag = false;
            }
            else {
                id_flag = true;
                data.root->children[user_no - 1]->children[user_prop] = new Node("id");
                user_prop++;
            }
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

        if (currentLine.find("<topics>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop] = new Node("topics");
            post_prop++;
            continue;
        }

        if (currentLine.find("<topic>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop - 1]->children[topic_no] = new Node("topic");
            topic_no++;
            topic_flag = true;
            continue;
        }

        if (currentLine.find("<followers>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop] = new Node("followers");
            user_prop++;
            continue;
        }

        if (currentLine.find("<follower>") != string::npos)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[follower_no] = new Node("follower");
            follower_no++;
            follower_flag = true;
            continue;
        }



        //dealing with closing tags
        if (currentLine.find("</topics>") != string::npos)
        {
            topic_no = 0;
            continue;
        }

        if (currentLine.find("</post>") != string::npos)
        {
            post_prop = 0;
            continue;
        }

        if (currentLine.find("</posts>") != string::npos)
        {
            post_no = 0;
            continue;
        }

        if (currentLine.find("</followers>") != string::npos)
        {
            follower_no = 0;
            continue;
        }

        if (currentLine.find("</user>") != string::npos)
        {
             user_prop = 0;
            continue;
        }

        if(currentLine.find('/') != string::npos)
        {
            continue;
        }

        //removing tabs, spaces or new lines
        currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\t'), currentLine.end());
        currentLine.erase(remove(currentLine.begin(),currentLine.end(), '\n'), currentLine.end());
        currentLine.erase(currentLine.begin(), std::find_if(currentLine.begin(), currentLine.end(), std::bind1st(std::not_equal_to<char>(), ' ')));


        //dealing with strings
        if(id_flag || name_flag)
        {
            if(follower_id_flag)
            {
                data.root->children[user_no - 1]->children[user_prop - 1]->children[follower_no - 1]->children[0]->value = currentLine;
                follower_id_flag = false;
            }
            else {
                data.root->children[user_no - 1]->children[user_prop - 1]->value = currentLine;
            }
            id_flag = false;
            name_flag = false;
            continue;
        }

        if(body_flag)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop - 1]->value = currentLine;
            body_flag = false;
            continue;
        }

        if (topic_flag)
        {
            data.root->children[user_no - 1]->children[user_prop - 1]->children[post_no - 1]->children[post_prop - 1]->children[topic_no - 1]->value = currentLine;
            topic_flag = false;
            continue;
        }



    }



    myfile.close();
    myfileo.close();
}