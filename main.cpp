#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"
#include "hashUtil.h"

using namespace std;
hashUtil gg;
int main() {

    MinifyXML("sample.xml","sampleMinified.xml");
    CompressXML("sample.xml","sampleCompressed.xml");
    deCompressXML("sampleCompressed.xml","sampledeCompressed.xml");
    compressJSON("sample.json", "sampleMinfied.json");
    deCompressJSON("sampleMinfied.json","sampledeMinfied.json");

}

