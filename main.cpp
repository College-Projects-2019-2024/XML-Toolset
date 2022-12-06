#include <bits/stdc++.h>
#include "compression.h"
using namespace std;

int main() {
    CompressXML("sample.xml","sampleCompressed.xml");
    deCompressXML("sampleCompressed.xml","sampleUnCompressed.xml");
    MinifyXML("sample.xml","sampleMinified.xml");




}

