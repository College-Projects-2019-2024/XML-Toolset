#include <bits/stdc++.h>
#include "debug.h"


#include <iostream>

using namespace std;
using ll = long long;


#define all(v) v.begin(),v.end()

#define allr(v) v.rbegin(),v.rend()
#define fori(size) for(int i=0; i < (size); i+= 1)
#define forj(size) for(int j=0; j < (size); j+= 1)
#define fork(size) for(int k=0; k < (size); k+= 1)


class treeNode{
public:
    int max;
    string type;
    string text;
    treeNode** children = nullptr;

    treeNode(int max, string type,string text, treeNode** children)
    {
        this->max = max;
        this->type = type;
        this->text = text;
        this->children = children;
    }
};


treeNode * usersSample;
bool ans()
{
    treeNode * myIDSample = new treeNode( -1, "ID","my id is 123", nullptr);//0
    treeNode * nameSample = new treeNode( -1, "name","Dallash", nullptr);//1


    treeNode * topicSample = new treeNode( -1, "topic","this is my topic", nullptr);
    treeNode * topicsSample = new treeNode( 0, "topics","", &topicSample);
    treeNode * bodySample =  new treeNode( -1, "body","this is my body", nullptr);
    treeNode * postChildrenArray [] = { bodySample,  topicsSample};
    treeNode * postSample = new treeNode( 1, "post","", postChildrenArray);
    treeNode * postsSample = new treeNode( 0, "posts","", &postSample);//2


    treeNode * hisIDSample = new treeNode( -1, "ID","his id is 456", nullptr);
    treeNode * followerSample = new treeNode( 0, "follower","", &hisIDSample);
    treeNode * followersSample = new treeNode( 0, "followers","", &followerSample);//3


    treeNode * userChildrenArray [] = { myIDSample,  nameSample, postsSample,followersSample};
    treeNode * userSample = new treeNode( 3, "user","", userChildrenArray);


    usersSample = new treeNode( 0, "users","", &userSample);
    return true;
}



void printnode(treeNode * node , int depth)
{
    fori(depth*4)cout<<' ';
    cout<<"<"<<node->type<<">"<<endl;

    if (node->max ==-1)
    {
        fori(depth*4+4)cout<<' ';
        cout << node->text << endl;
    }
    else fori(node->max + 1)
    {
        printnode(node->children[i], depth + 1);
    }

    fori (depth*4) cout<<' ';
    cout <<"</"<<node->type<<">"<<endl;
}





string s,f ;
vector <string> v;



int x= 0;



bool can_increment = true;





void checknode(treeNode * node )
{
    if (can_increment) s= v[x++];//
    f = ""; f+= "<";f+=node->type; f+=">";//
    if (f != s) cout<<f <<" was missing"<<endl, can_increment = false;//
    else can_increment = true;//

    if (node->max ==-1)
    {
        if (!can_increment)
        {
            if ( !(v[x-1].front() != '<' && v[x-1].front() != '>') ) cout << node->type << " has no text" << endl;
            else can_increment = true;
        }
        else
        {
            if (!(v[x].front() != '<' && v[x].front() != '>')) cout << node->type << " has no text" << endl;
            else x++, can_increment = true;
        }
    }
    else
    {
        fori(node->max + 1)
        {
            checknode(node->children[i]);
            f = "";f += "<";f += node->children[node->max]->type; f += ">";
            if ( (v[x] == f && i == node->max)) i--;
        }
    }


    if (can_increment) s= v[x++];//
    f = ""; f+= "</";f+=node->type; f+=">";//
    if (f != s) cout << f << " was missing" << endl, can_increment = false;//
    else can_increment = true;//
}
void get_XML(string s)
{
    while(getline (cin,s)) {
        if(s=="") continue;
        int start_pos =0,end_pos=0;
        int i = 0;
        while (s[i] == ' ') i++;
        start_pos = s.find('<', end_pos);
        end_pos = s.find('>', end_pos + 1);
        if ((end_pos == -1 && start_pos == -1) || ((end_pos - start_pos) == s.length() - i -1))
            v.push_back(s.substr(i, s.length()));
        else {
            if (s[i] == '<') {
                v.push_back(s.substr(i, end_pos - i + 1));
                i = end_pos + 1;
                start_pos = s.find('<', end_pos);
                end_pos = s.find('>', end_pos + 1);
                if (start_pos != -1) {
                    v.push_back(s.substr(i, start_pos - i));
                    v.push_back(s.substr(start_pos, end_pos - start_pos + 1));
                }
                else v.push_back(s.substr(i, s.length()-i));
            }
            else {
                if (start_pos != -1) v.push_back(s.substr(i, start_pos - i));
                v.push_back(s.substr(start_pos, end_pos - start_pos + 1));
            }
        }

    }

};


int main()
{

    freopen("in.in", "r", stdin);


    get_XML(s);
    //debug(v);
    ans();
    checknode(usersSample);


}