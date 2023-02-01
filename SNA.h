#ifndef COLLEGEPROJECT_SNA_H
#define COLLEGEPROJECT_SNA_H
#include "Utility.h"
#include <bits/stdc++.h>



class SNA {

};

vector<vector<treeNode*>> make_adj_list(treeNode* root);
string most_active_user(vector<vector<treeNode*>> adj_list);
string mutual_followers(int user1,int user2,vector<vector<treeNode*>> adj_list);
int stringTointeger(string str);
vector<string> suggest_users_to_follow(string x,vector<vector<treeNode*>> adj_list);
string mostActive(vector<vector<treeNode*>> adj_list);
vector<int> suggestUser(vector<vector<treeNode*>> adj_list);

#endif //COLLEGEPROJECT_SNA_H
