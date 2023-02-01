#include "SNA.h"
#include "PostSearch.h"
#include "Utility.h"
#include<bits/stdc++.h>


vector<vector<treeNode*>> make_adj_list(treeNode* root)
{
    vector<vector<treeNode*>> adj_list;

    fori(root->children.size())
    {
        adj_list.push_back(root->children[i]->children[3]->children);
    }

    return adj_list;
}

int most_active_user(vector<vector<treeNode*>> adj_list){
    int max = adj_list[0].size();
    int index = 1;
    fori(adj_list.size()){
        if(max < adj_list[i].size()){
            max = adj_list[i].size();
            index = i+1;
        }
    }

    return index;
}