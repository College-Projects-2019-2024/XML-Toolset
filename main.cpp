#include <bits/stdc++.h>
#include "utility.h"
#include "MainClass.h"

using namespace std;
int main() {
    MainClass x("sample.xml");
    x.CompressXML();
    vector<string> decomp;
    decomp = x.deCompressXML("sampleCompressed.xml");
    cout << "";


   // deCompressJSON("sampleMinfied.json","sampledeMinfied.json");

}

