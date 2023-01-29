#include <bits/stdc++.h>
#include "Utility.h"
#include "XMLtoJSON.h"


#include <iostream>

using namespace std;

treeNode * usersSample;

int main() {
    vector<Line> v = get_xml("sample.xml");
    usersSample = ans(usersSample);
    treeNode * dataRoot = new treeNode(0,"users","", {});
    //XMLtoJSON(usersSample, dataRoot, v, "output.json");



    return 0;
}
