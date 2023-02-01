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

int stringTointeger(string str)
{
    int temp = 0;
    for (int i = 0; i < str.length(); i++) {

        temp = temp * 10 + (str[i] - '0');
    }
    return temp;
}

vector<int> mutual_followers(int user1,int user2,vector<vector<treeNode*>> adj_list){
    vector<int>vec;
    int freq_arr[adj_list.size()+1];

    fori(adj_list.size()+1){
        freq_arr[i] = 0;
    }
    fori(adj_list[user1-1].size()){
        freq_arr[stringTointeger(adj_list[user1-1][i]->children[0]->text)]++;

    }
    fori(adj_list[user2-1].size()){
        freq_arr[stringTointeger(adj_list[user2-1][i]->children[0]->text)]++;

    }

    fori(adj_list.size()+1){
        if(freq_arr[i] > 1)vec.push_back(i);

    }
    return vec;
}