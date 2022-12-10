#include <bits/stdc++.h>


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


string s,f,cf,open,close ;
vector <string> v;



int x= 0;



bool can_increment = true;




bool goOn (treeNode * node, int x)
{
    f = ""; f+= "<";f+=node->type; f+=">";
    if (f == v[x]) return true;

    if (node->max ==-1)
    {
        if (v[x].front() != '<' && v[x].back() != '>' ) return true;
        else return false;
    }
    else fori(node->max + 1)
    {
           return goOn(node->children[i], x);
    }

    f = ""; f+= "</";f+=node->type; f+=">";//
    if (f == v[x]) return true;
}








void checknode(treeNode * node )
{
    if (can_increment) s = v[x++];
    f = ""; f+= "<";f+=node->type; f+=">";
    if (f != s) cout<<f <<" was missing"<<endl, can_increment = false;
    else can_increment = true;

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
            f = ""; f+= "</";f+=node->type; f+=">";
            if (i== node->max && v[x]!=f && goOn(node->children[i],x)) i--;
        }
    }

    if (can_increment) s= v[x++];
    f = ""; f+= "</";f+=node->type; f+=">";
    if (f != s) cout << f << " was missing" << endl, can_increment = false;
    else can_increment = true;
}


int main()
{

    freopen("in.in", "r", stdin);

    while (cin>>s) v.push_back(s);

    ans();
    checknode(usersSample);


}