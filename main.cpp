#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"

using namespace std;
hashUtil gg;
int main() {
    vector<string> x;
    x.push_back(CompressXML(get_xml("sample.xml")));
    cout << deCompressXML(x)[2];
    //compressJSON("sample.json", "sampleMinfied.json");
   // deCompressJSON("sampleMinfied.json","sampledeMinfied.json");

}

