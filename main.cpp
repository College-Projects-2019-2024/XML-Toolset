#include "iostream"
#include "Prettify_XML.h"
#include "vector"
#include "utility.h"
using namespace std;


int main() {
    prettify(get_xml("out.txt"),"out2.txt");
    return 0;
}