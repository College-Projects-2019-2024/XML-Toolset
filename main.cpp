#include <bits/stdc++.h>

#include "utility.h"



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
    treeNode * myIDSample = new treeNode( -1, "id","my id is 123", nullptr);//0
    treeNode * nameSample = new treeNode( -1, "name","Dallash", nullptr);//1


    treeNode * topicSample = new treeNode( -1, "topic","this is my topic", nullptr);
    treeNode * topicsSample = new treeNode( 0, "topics","", &topicSample);
    treeNode * bodySample =  new treeNode( -1, "body","this is my body", nullptr);
    treeNode * postChildrenArray [] = { bodySample,  topicsSample};
    treeNode * postSample = new treeNode( 1, "post","", postChildrenArray);
    treeNode * postsSample = new treeNode( 0, "posts","", &postSample);//2


    treeNode * hisIDSample = new treeNode( -1, "id","his id is 456", nullptr);
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


string s,f;

vector <Line> v;



int x= 0;






bool goOn (treeNode * node, int x)
{
    if (x>=v.size ()) return false;

    f = ""; f+= "<";f+=node->type; f+=">";
    if (f == v[x].text) return true;

    if (node->max ==-1)
    {
        f = ""; f+= "</";f+=node->type; f+=">";
        if (  (v[x].text.front() != '<' && v[x].text.back() != '>')  ||  v[x].text==f)  return true;
        else return false;
    }
    else  return goOn(node->children[0], x); //check the first child only as it is sufficient
}





vector <string> out;
vector <Line> detect(100);

int it = 0;
int it2=0;
bool can_increment  = true;

void checknode(treeNode * node )
{

    if (can_increment) s = v[x++].text;
    f = ""; f+= "<";f+=node->type; f+=">";
    if (f != s)  {
        detect[it2].text=f;
        detect[it2++].index=v[x-1].index;
        can_increment = false;
    }
    else can_increment = true;

    out[it++]=f;


    if (node->max ==-1)
    {
        if (!can_increment)
        {
            if ( !(v[x-1].text.front() != '<' && v[x-1].text.front() != '>') )
            {
                detect[it2].text=node->type;
                detect[it2++].index=v[x-1].index;
                out[it++]="noTEX";
            }
            else can_increment = true, out[it++]=v[x-1].text;
        }
        else
        {
            if (!(v[x].text.front() != '<' && v[x].text.front() != '>'))
            {
                detect[it2].text=node->type;
                detect[it2++].index=v[x-1].index;
                out[it++]="noTEX";
            }
            else x++, can_increment = true, out[it++]=v[x-1].text;
        }
    }
    else
    {
        fori(node->max + 1)
        {
            checknode(node->children[i]);
            f = ""; f+= "</";f+=node->type; f+=">";
            if (i== node->max && v[x].text!=f && goOn(node->children[i],x)) i--;
        }
    }

    if (can_increment) s= v[x++].text;
    f = ""; f+= "</";f+=node->type; f+=">";

    out[it++]=f;

    if (f != s)
    {
        detect[it2].text=f;
        detect[it2++].index=v[x-1].index;
        can_increment = false;
    }
    else can_increment = true;
}

int main()
{

    freopen("in.in", "r", stdin);

    int line = 0;
    while (cin>>s)  v.push_back({s,++line});

    out.resize(v.size()*3);
    ans();
    checknode(usersSample);

}