#ifndef COLLEGEPROJECT_SNA_H
#define COLLEGEPROJECT_SNA_H
#include "Utility.h"
#include <bits/stdc++.h>



class SNA {

};

vector<vector<treeNode*>> make_adj_list(treeNode* root);
int most_active_user(vector<vector<treeNode*>> adj_list);

#endif //COLLEGEPROJECT_SNA_H
