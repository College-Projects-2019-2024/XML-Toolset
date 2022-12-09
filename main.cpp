#include <bits/stdc++.h>
#include "compression.h"
#include "Utility.h"

using namespace std;

int main() {

    MinifyXML("sample.xml","sampleMinified.xml");

    CompressXML("sample.xml","sampleCompressed.xml");
    deCompressXML("sampleCompressed.xml","sampledeCompressed.xml");



}

