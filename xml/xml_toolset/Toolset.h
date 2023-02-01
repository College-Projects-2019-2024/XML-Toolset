#include <vector>
#include <queue>
#include <stack>
#include "Utility.h"


#ifndef TOOLSET_H
#define TOOLSET_H
#define MAX 100

#define fori(size) for(int i=0; i < (size); i+= 1)
#define forj(size) for(int j=0; j < (size); j+= 1)

class Toolset {
private:
    ifstream is;
    Utility *U;
    vector<Line> lines;
    vector<string> str;

    Utility util;

    vector<string>xmlCompressed;
    vector<string>corrected;
    vector<string>out;
    vector<Line>detect;
    bool can_increment = true,arr_object = false;
    int x = 0,currentLine = 0;
    string s,f,print;


    vector<string> CompressXML()
            {
                string currentLine="", text = "" , result = "";
                vector<string> r;
                unsigned char flag;
                bool writeTag = false;

                for (string currentLine : str)
                {
                    currentLine = util.removeSpacesFromLine(currentLine);
                    for(char c : currentLine)
                    {
                        if(c=='>')
                        {
                            text+='>';
                            writeTag = false;
                            flag = util.stringToCodeXML(text);
                            if(flag!='%')
                            {
                                result+= util.stringToCodeXML(text);
                            }
                            else result+= text;

                            text = "";

                        }
                        else if(c == '<' || writeTag)
                        {
                            if(c == '\"')
                            {
                                text+='<';
                                writeTag = true;
                                continue;
                            }
                            text+=c;
                            writeTag = true;
                        }
                        else
                        {
                            result+= c ;
                        }
                    }
                }
                r.push_back(result);
                return r;

            }

    vector<string> deCompressXML(string fileName)
            {
                is.open(fileName);
                string flag,text = "" , currentLine;
                vector<string> result;

                while(getline(is, currentLine))
                {
                    for(char c : currentLine)
                    {
                        flag = util.codeToStringXML(c);
                        if(flag != "")
                        {
                            if(text!="")
                                result.push_back(text);

                            result.push_back(flag);
                            text="";
                        }
                        else
                        {
                            text+=c;
                        }
                    }
                }
                is.close();
                return result;
            }

    vector<string> CompressJSON(string inputFileName) {
                is.open(inputFileName);
                string r = "";
                bool inside = false;
                string currentLine = "";
                unsigned char flag;
                string text = "";

                while (getline(is, currentLine)) {
                    for (char c: currentLine) {
                        if (c == '\"') {
                            text += c;
                            if (inside) {
                                flag = util.stringToCodeJSON(text);
                                if (flag != '%')
                                    r+= flag;
                                else
                                    r+= text;
                                text = "";
                            }
                            inside = !inside;

                        } else if (inside) {
                            text += c;
                        } else if (c != ' ') {
                            r+= c;
                        }

                    }
                }
                vector<string> result;
                result.push_back(r);
                is.close();
                return result;
            }

    vector<string> deCompressJSON(string inputFileName)
            {
                is.open(inputFileName);
                string result = "";
                string currentLine = "";
                string flag;

                while (getline(is, currentLine)) {
                    for (char c: currentLine) {
                        flag = util.codeToStringJSON(c);
                        if (flag != "")
                            result+= flag;

                        else
                        {
                            result += c;
                        }
                    }
                }
                vector<string> r;
                r.push_back(result);
                is.close();
                return r;
            }

    bool goOn (treeNode * node, int x)
    {
        string f;
        if (x>=lines.size()) return false;

        f = ""; f+= "<";f+=node->type; f+=">";
        if (f == lines[x].text) return true;

        if (node->max ==-1)
        {
            f = ""; f+= "</";f+=node->type; f+=">";
            if (  (lines[x].text.front() != '<' && lines[x].text.back() != '>')  ||  lines[x].text==f)  return true;
            else return false;
        }
        else  return goOn(node->children[0], x); //check the first child only as it is sufficient
    }



    void print_JSON(treeNode * data, int n,bool arr_obj)
    {
        bool object = false;
        string tab;

        fori(n) tab += "    ";

        if(data->type == "topics" && data->children.size() > 1)
        {
            //cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";
            print += tab; print += "\""; print += data->type; print += "\": {";
            out.push_back(print);
            print = "";

            //cout << tab << "   " << "\"" << "topic" << "\"" << ":" << " " << "[" <<"\n";
            print += tab; print += "   \"topic\": [";
            out.push_back(print);
            print = "";

            fori(data->children.size())
            {
                //cout << tab << "       " << "\"" << data->children[i]->text << "\"";
                print += tab; print += "       \""; print += data->children[i]->text; print += "\"";

                if(i == (data->children.size() -1))
                {
                    //cout << "\n";
                    out.push_back(print);
                    print = "";
                }
                else
                {
                    //cout << "," << "\n";
                    print += ",";
                    out.push_back(print);
                    print = "";
                }
            }
            //cout << tab << "   " << "]" << "\n";
            print += tab; print += "   ]";
            out.push_back(print);
            print = "";

            //cout << tab << "}";
            print += tab; print += "}";
            return;
        }

        if (data->max == -1)
        {
            //cout << tab << "\"" << data->type << "\"" << ":" << " ";
            print += tab; print += "\""; print += data->type; print += "\": ";

            //cout << "\"" << data->text << "\"";
            print += "\""; print += data->text; print += "\"";
            return;
        }
        else
        {
            if(data->children.size() == 1) object = true;

            fori(data->children.size() - 1)
            {
                if(data->children[i]->type != data->children[i + 1]->type) object = true;
            }

            if(object){
                if(arr_obj)
                {
                    //cout  << tab << "   " << '{' << "\n";
                    print += tab; print += "   {";
                    out.push_back(print);
                    print = "";
                }
                else
                {
                    //cout  << tab << "\"" << data->type << "\"" << ":" << " " << '{' << "\n";
                    print += tab; print += "\""; print += data->type; print += "\": {";
                    out.push_back(print);
                    print = "";
                }

                fori(data->children.size()) {
                    arr_object = false;
                    print_JSON(data->children[i], n + 1, arr_object);
                    if(i == (data->children.size() - 1))
                    {
                        //cout << "\n";
                        out.push_back(print);
                        print = "";
                    }
                    else
                    {
                        //cout << "," << "\n";
                        print += ",";
                        out.push_back(print);
                        print = "";
                    }
                }
                tab += "    ";
                //cout << tab << '}';
                print += tab; print += "}";

            }
            else
            {
                //cout << tab << "\"" << data->type << "\"" << ":" << " " << "{" << "\n";
                print += tab; print += "\""; print += data->type; print += "\": {";
                out.push_back(print);
                print = "";

                //cout << tab << "    " << "\"" << data->children[0]->type << "\"" << ":" << " " << "[" << "\n";
                print += tab; print += "    \""; print += data->children[0]->type; print += "\": [";
                out.push_back(print);
                print = "";

                fori(data->children.size()) {
                    arr_object = true;
                    print_JSON(data->children[i], n + 1, arr_object);
                    if(i == (data->children.size() -1))
                    {
                        //cout << "\n";
                        out.push_back(print);
                        print = "";
                    }
                    else
                    {
                        //cout << "," << "\n";
                        print += ",";
                        out.push_back(print);
                        print = "";
                    }
                }

                //cout << tab << "    " << ']' << "\n";
                print += tab; print += "   ]";
                out.push_back(print);
                print = "";

                //cout << tab << '}';
                print += tab; print += "}";

            }
        }
    }

    void Convert_to_Json(treeNode* data)
    {
        //cout << '{' << "\n";
        out.push_back("{");

        print_JSON(data, 1, arr_object);

        //cout << "\n" << '}' << "\n";
        out.push_back("  }");
        out.push_back("}");
    }


public:
    //constructor
    Toolset(string input) {
        this->lines = util.get_xml(input);
        this->str = util.line_to_str(lines);
    }

    //getters and setters
    vector<string>getCorrected(){
        return this->corrected;
    }

    vector<Line>getdetected(){
        return this->detect;
    }

    void set_str(vector<string>v){
        this->str = v;
    }

    void clear(){
        this->x = 0;
        this->detect.clear();
        this->corrected.clear();
        this->out.clear();
        this->currentLine = 0;
        this->print = "";
    }





    //functions
    treeNode* ans(treeNode * usersSamp)
    {
        treeNode * myIDSample = new treeNode( -1, "id","my id is 123", {});//0
        treeNode * nameSample = new treeNode( -1, "name","Dallash", {});//1


        treeNode * topicSample = new treeNode( -1, "topic","this is my topic", {});
        treeNode * topicsSample = new treeNode( 0, "topics","", {topicSample});
        treeNode * bodySample =  new treeNode( -1, "body","this is my body", {});
        vector<treeNode *> postChildrenArray = { bodySample,  topicsSample};
        treeNode * postSample = new treeNode( 1, "post","", postChildrenArray);
        treeNode * postsSample = new treeNode( 0, "posts","", {postSample});//2


        treeNode * hisIDSample = new treeNode( -1, "id","his id is 456", {});
        treeNode * followerSample = new treeNode( 0, "follower","", {hisIDSample});
        treeNode * followersSample = new treeNode( 0, "followers","", {followerSample});//3


        vector<treeNode *> userChildrenArray = { myIDSample,  nameSample, postsSample,followersSample};
        treeNode * userSample = new treeNode( 3, "user","", userChildrenArray);


        usersSamp = new treeNode( 0, "users","", {userSample});

        return usersSamp;
    }

    vector<vector<treeNode*>> make_adj_list(treeNode* root)
    {
        vector<vector<treeNode*>> adj_list;

        fori(root->children.size())
        {
            adj_list.push_back(root->children[i]->children[3]->children);
        }

        return adj_list;
    }

    vector<string> extract_graph(vector<vector<treeNode*>> adj_list){

        string s = "";
        vector<string>result;
        fori(adj_list.size()){
            s+=to_string(i+1);
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

    void load_xml(treeNode * samplenode, treeNode * data)
    {

        s = lines[currentLine++].text;

        if(samplenode->max == -1)
        {
            //store text
            data->text = lines[currentLine++].text;
        }
        else
        {
            fori(samplenode->max + 1)
            {
                //create new node nn
                treeNode * createdNode = new treeNode(samplenode->children[i]->max, samplenode->children[i]->type, samplenode->children[i]->text, {});
                load_xml(samplenode->children[i], createdNode);
                //add to the vector (push created node)
                data->children.push_back(createdNode);
                string f = ""; f+= "<";f+=samplenode->children[samplenode->max]->type; f+=">";
                if(i== samplenode->max && f == lines[currentLine].text) i--;
            }
        }

        s = lines[currentLine++].text;
    }

    vector<string> prettify() {
        vector<string> v = str;
        vector<string> answer;
        //a stack to keep track of number of tabs to be inserted
        stack<int> stac;
        //count the number of tabs to be inserted into a string
        int count = 0;
        //count number of spaces in a text
        int n = 0;
        //flag used in dividing large texts
        bool flag = false;

        for (int i = 0; i < v.size(); i++) {
            //opening tag
            if (v[i][0] == '<' && v[i][1] != '/') {
                stac.push(count);
                answer.push_back(util.insert_tab(v[i], count));
                count++;
            }
                //closing tag
            else if (v[i][0] == '<' && v[i][1] == '/') {
                answer.push_back(util.insert_tab(v[i], stac.top()));
                stac.pop();
                count--;
            }
                //a text
            else if (v[i][0] != '<') {
                int k = 0;
                for (int j = 0; j < v[i].length(); j++) {

                    if (v[i][j] == ' ')n++;
                    /*if the text has more than 12 words, divide it into substrings
                    where each substring consists of at least 12 words*/
                    if (n == 12) {
                        answer.push_back(util.insert_tab(v[i].substr(k, j - k + 1), count));
                        k = j;
                        n = 0;
                        flag = true;
                    }
                }
                //the text was less than 12 words
                if (n < 12 && !flag) {
                    answer.push_back(util.insert_tab(v[i], count));
                } else if (flag) {
                    answer.push_back(util.insert_tab(v[i].substr(k, v[i].length() - k), count));

                }

            }
        }
        return answer;
    }

    vector<string> Compress(string inputFileName)
            {
                string extension = inputFileName.substr(inputFileName.size()-4,inputFileName.size()-1);
                vector <string> result;
                if(extension == ".xml")
                {
                    result = CompressXML();
                }
                else
                {
                    result = CompressJSON(inputFileName);
                }
                return result;
            }

    vector<string> DeCompress(string inputFileName)
            {
                string extension = inputFileName.substr(inputFileName.size()-4,inputFileName.size()-1);
                vector <string> result;
                if(extension == ".xml")
                {
                    result = deCompressXML(inputFileName);
                }
                else
                {
                    result = deCompressJSON(inputFileName);
                }
                return result;

            }

    string MinifyXML()
    {
        string result = "";
        for(string currentLine : str)
            result+=currentLine;
        return result;
    }

    void checknode(treeNode * node )
    {

        if (can_increment) s = lines[x++].text;
        f = ""; f+= "<";f+=node->type; f+=">";
        if (f != s)  {
            detect.push_back({f,lines[x-1].index});
            can_increment = false;
        }
        else can_increment = true;
        corrected.push_back(f);



        if (node->max ==-1)
        {
            if (!can_increment)
            {
                if ( !(lines[x-1].text.front() != '<' && lines[x-1].text.front() != '>') )
                {
                    detect.push_back({node->type + "has no text",lines[x-1].index});
                    corrected.push_back("noText");
                }
                else can_increment = true,corrected.push_back(lines[x-1].text);
            }
            else
            {
                if (!(lines[x].text.front() != '<' && lines[x].text.front() != '>'))
                {
                    detect.push_back({node->type + "has no text",lines[x-1].index});
                    corrected.push_back("noText");
                }
                else x++, can_increment = true,corrected.push_back(lines[x-1].text);
            }
        }
        else
        {
            fori(node->max + 1)
            {
                checknode(node->children[i]);
                f = ""; f+= "</";f+=node->type; f+=">";
                if (i== node->max && lines[x].text!=f && goOn(node->children[i],x)) i--;
            }
        }

        if (can_increment) s= lines[x++].text;
        f = ""; f+= "</";f+=node->type; f+=">";
         corrected.push_back(f);



        if (f != s)
        {
            detect.push_back({f,lines[x-1].index});
            can_increment = false;
        }
        else can_increment = true;
    }

    vector<string> XMLtoJSON(treeNode* samplenode, treeNode * data)
    {
        //vector<string>temp = out;
        load_xml(samplenode, data);
        Convert_to_Json(data);
        return out;
    }

    vector<pair<int,int>> topic_search(treeNode* root, string word){

        //declare output vector
        vector<pair<int,int>> found;

        //iterate over every user
        fori(root->children.size())
        {
            //iterate over every post
            for(int post_number = 0; post_number < root->children[i]->children[2]->children.size(); post_number++)
            {
                //check if word is in the post body
                size_t substring_length = root->children[i]->children[2]->children[post_number]->children[0]->text.find(word);

                if( substring_length != std::string::npos)
                {
                    //add user id and post number in output vector
                    found.push_back(make_pair(stoi(root->children[i]->children[0]->text),post_number + 1));
                    continue;
                }

                //iterate over every topic of the post
                for(int topic_number = 0; topic_number < root->children[i]->children[2]->children[post_number]->children[1]->children.size(); topic_number++)
                {
                    //check if the word is found in any topic
                    if(root->children[i]->children[2]->children[post_number]->children[1]->children[topic_number]->text.compare(word) == 0)
                    {
                        //add user id and post number in output vector
                        found.push_back(make_pair(stoi(root->children[i]->children[0]->text),post_number + 1));
                    }
                }
            }
        }

        return found;

    }

    string most_influencer_user(vector<vector<treeNode*>> adj_list){
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
        g+=" is the most influencer user";

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
            freq_arr[U->stringTointeger(adj_list[user1-1][i]->children[0]->text)]++;

        }
        fori(adj_list[user2-1].size()){
            freq_arr[U->stringTointeger(adj_list[user2-1][i]->children[0]->text)]++;

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

};

#endif // TOOLSET_H
