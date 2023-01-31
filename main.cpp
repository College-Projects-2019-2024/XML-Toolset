#include <bits/stdc++.h>
#include "Utility.h"
#include "XMLtoJSON.h"
#include "PostSearch.h"


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





    return 0;
}
