
#ifndef COLLEGEPROJECT_XMLTOJSON_H
#define COLLEGEPROJECT_XMLTOJSON_H

#include "Utility.h"

void load_xml(treeNode * samplenode, treeNode * data,vector<Line> token);
void print_JSON(treeNode * data, int n,bool arr_obj);
void Convert_to_Json(treeNode* data);
void XMLtoJSON(treeNode* samplenode, treeNode * data, vector<Line> t);

#endif //COLLEGEPROJECT_XMLTOJSON_H
