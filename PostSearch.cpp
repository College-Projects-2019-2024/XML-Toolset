#include "PostSearch.h"
#include "Utility.h"
#include "XMLtoJSON.h"
#include<bits/stdc++.h>
#include "string.h"

using namespace std;


vector<pair<int,int>> topic_search(treeNode* root, string word){
    vector<pair<int,int>> found;

    fori(root->children.size())
    {
        for(int post_number = 0; post_number < root->children[i]->children[2]->children.size(); post_number++)
        {
            for(int topic_number = 0; topic_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); topic_number++)
            {
                if(root->children[i]->children[2]->children[post_number]->children[1]->children[topic_number]->text.compare(word) == 0)
                {
                    found.push_back(make_pair(stoi(root->children[i]->children[0]->text),post_number + 1));
                }
            }

            for(int body_number = 0; body_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); body_number++)
            {

            }

        }
    }

    return found;

}