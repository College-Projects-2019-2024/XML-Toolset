#include <bits/stdc++.h>
#include "Utility.h"
#include "XMLtoJSON.h"
#include "PostSearch.h"
#include "SNA.h"


#include <iostream>

using namespace std;

treeNode * usersSample;

int main() {
    vector<Line> v = get_xml("sample.xml");
    usersSample = ans(usersSample);
    treeNode * dataRoot = new treeNode(0,"users","", {});
    load_xml(usersSample, dataRoot, v);
    //XMLtoJSON(usersSample, dataRoot, v, "output.json");

    /*string searchWord;
    cin >> searchWord;

    vector<pair<int,int>> output = topic_search(dataRoot, searchWord);

    fori(output.size())
    {
        cout << output[i].first << ", " << output[i].second << endl;
    }
     */

    vector<vector<treeNode*>> adj_list = make_adj_list(dataRoot);
    fori(adj_list.size())
    {
        for(int j = 0; j < adj_list[i].size(); j++)
        {
            cout << adj_list[i][j]->children[0]->text << " ";
        }
        cout << endl;

    }

    vector<string>a = mutual_followers(1,3,adj_list);

    fori(a.size()){
        cout<<a[i]<<" ";
    }

    //cout<<most_active_user(adj_list);

    //cout<<stringTointeger("4");
    return 0;
}
