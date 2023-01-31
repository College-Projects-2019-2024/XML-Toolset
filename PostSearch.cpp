#include "PostSearch.h"
#include "Utility.h"
#include "XMLtoJSON.h"
#include<bits/stdc++.h>
#include "string.h"

using namespace std;


vector<pair<int,int>> topic_search(treeNode* root, string word){

    //declare output vector
    vector<pair<int,int>> found;

    //iterate over every user
    fori(root->children.size())
    {
        //iterate over every post
        for(int post_number = 0; post_number < root->children[i]->children[2]->children.size(); post_number++)
        {
            //check if word is in the post body
            size_t substring_length = root->children[i]->children[2]->children[post_number]->children[0]->text.find(word , 0);


            if(substring_length != std::string::npos)
            {
                //add user id and post number in output vector
                found.push_back(make_pair(stoi(root->children[i]->children[0]->text),post_number + 1));
                continue;
            }

            //iterate over every topic of the post
            for(int topic_number = 0; topic_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); topic_number++)
            {
                //check if the word is found in any topic
                if(root->children[i]->children[2]->children[post_number]->children[1]->children[topic_number]->text.compare(word) == 0)
                {
                    //add user id and post number in output vector
                    found.push_back(make_pair(stoi(root->children[i]->children[0]->text),post_number + 1));
                }
            }
        }
    }

    return found;

}