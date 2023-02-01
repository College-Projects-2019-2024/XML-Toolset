#include "SNA.h"
#include "PostSearch.h"
#include "Utility.h"
#include<bits/stdc++.h>


vector<vector<treeNode*>> make_adj_list(treeNode* root)
{
    vector<vector<treeNode*>> adj_list;

    fori(root->children.size())
    {
        adj_list.push_back(root->children[i]->children[3]->children);
    }

    return adj_list;
}

string most_inf_user(vector<vector<treeNode*>> adj_list){
    int max = adj_list[0].size();
    int index = 1;
    fori(adj_list.size()){
        if(max < adj_list[i].size()){
            max = adj_list[i].size();
            index = i+1;
        }
    }
    string g = "User number ";
    g+= to_string(index);
    g+=" is the most active user";

    return g;
}

string mutual_followers(int user1,int user2,vector<vector<treeNode*>> adj_list){
    //vector<string>vec;
    string k = "";
    bool flag = false;
    int freq_arr[adj_list.size()+1];

    fori(adj_list.size()+1){
        freq_arr[i] = 0;
    }
    fori(adj_list[user1-1].size()){
        freq_arr[stringTointeger(adj_list[user1-1][i]->children[0]->text)]++;

    }
    fori(adj_list[user2-1].size()){
        freq_arr[stringTointeger(adj_list[user2-1][i]->children[0]->text)]++;

    }

    fori(adj_list.size()+1){
        if(freq_arr[i] > 1){
            flag = true;
            k+="User ";
            k+=to_string(i);
            k+="\n";

            //vec.push_back(to_string(i));

        }


    }
    if(!flag){
        k = "No mutual users";
        return k;
    }
    else{
        return k;
    }
    //return k;

}

vector<string> extract_graph(vector<vector<treeNode*>> adj_list){

    string s = "";
    vector<string>result;
    fori(adj_list.size()){
        s+= to_string(i+1);
        s+="    ";
        forj(adj_list[i].size()){
            s+=adj_list[i][j]->children[0]->text;
            s+=" ";
        }
        result.push_back(s);
        s="";
    }
    return result;
}

vector<string> suggest_users_to_follow(string x,vector<vector<treeNode*>> adj_list){
    vector<string>followers;
    vector<string>followers_of_followers;
    unordered_set<string> set;
    int number = stringTointeger(x);
    set.insert(x);

    fori(adj_list[number-1].size()){
        followers.push_back(adj_list[number-1][i]->children[0]->text);
        set.insert(adj_list[number-1][i]->children[0]->text);
    }

    fori(followers.size()){
        forj(adj_list[stringTointeger(followers[i])-1].size()){
            if(set.contains(adj_list[stringTointeger(followers[i])-1][j]->children[0]->text))continue;
            followers_of_followers.push_back(adj_list[stringTointeger(followers[i])-1][j]->children[0]->text);
        }
    }

    return followers_of_followers;

}

//1   2 3
//2   1 5
//3   1 2 3 4


string mostActive(vector<vector<treeNode*>> adj_list)
{
    unordered_map<int,int> follows;
    int max = 0;
    int maxID;
    for(vector<treeNode*> user : adj_list)
    {
        for(treeNode* follower : user)
        {
            //fetch current id
            int currentID = stringTointeger(follower->children[0]->text);

            //increment the follows of the current ID
            if(!follows.contains(currentID)) follows[currentID] = 0;
            else follows[currentID]++;

            //get the id with the max follows
            if(follows[currentID]>max) {max = follows[currentID]; maxID = currentID;}

        }
    }



    return to_string(maxID);
}



