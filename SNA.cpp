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