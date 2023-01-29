#include "PostSearch.h"
#include "Utility.h"
#include "XMLtoJSON.h"
#include<bits/stdc++.h>


void topic_search(treeNode* root){
    vector<pair<int,int>> found;

    fori(root->children.size())
    {
        for(int post_number = 0; post_number < root->children[i]->children[2]->children.size(); post_number++)
        {
            for(int topic_number = 0; topic_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); topic_number++)
            {

            }

            for(int body_number = 0; body_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); body_number++)
            {

            }

        }
    }

}