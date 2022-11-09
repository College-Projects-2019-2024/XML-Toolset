#include <bits/stdc++.h>
using namespace std;


bool isValidTagOpeningAndClosing(string open,string close)
{
    if(open.size()+1!=close.size() || open==close)
    {
        return false;
    }
    for(int i=0; i<open.size(); i++)
    {
        if(open[i]!=close[i+1])
        {
            return false;
        }
    }
    return true;
    //test change to commit gggggggggggggggggggggggggggg
}


bool openFile(const char *fileName)

{
     freopen("input.xml", "r", stdin);
    stack<char> bracketStack; //the stack where brackets are pushed
    stack<string> tagStack;//the stack where opening and closing brackets are pushed
    string currentLine , tag = "";
    bool tagOpened;
    stack<pair<int,int>> tagLines;
    int lineNumber = 1;
    int charNumber = 1;


    while (getline(cin,currentLine))
    {
        for(char c : currentLine)
        {

            //Case 1 : Error in Opening Bracket
            if(c=='<' && bracketStack.empty())
            {
                bracketStack.push(c);
                tagOpened = true;
            }

            else if(c=='<' && !bracketStack.empty()) //multiple open brackets (needs better way)
            {
                cout << "Problem at Line : " << lineNumber << ", char : " << charNumber << " (Expected closing bracket).";
                return false;
            }

            //Case 2 :  Error in Closing Bracket
            else if(c=='>')
            {
                if(bracketStack.size() != 1 || bracketStack.top() != '<') //Bracket opened but not closed
                {
                    cout << "Problem at Line : " << lineNumber << ", char : " << charNumber << " (Missing opening bracket).";
                    return false;
                }
                else
                {
                    tagOpened = false;
                    if(tag[0]=='/' && !tagStack.empty()) // if this is a closing tag, check that it is the tag for the last open tag
                    {
                        if(isValidTagOpeningAndClosing(tagStack.top(), tag)) // if it is a valid closing tag
                        {
                        tagStack.pop(); // pop the last open tag
                        tagLines.pop();
                        tag = ""; // clear the current tag
                        bracketStack.pop(); // pop the closing bracket
                        continue;
                        }
                        else // if it is not valid
                        {
                            cout << "Problem at Line : " << lineNumber << ", char : " << charNumber<< " (Invalid closing tag).";


                        }
                    }
                    tagStack.push(tag); // push opening tag
                    pair<int,int> x(lineNumber,charNumber);
                    tagLines.push(x);
                    tag = ""; // clear tag
                    bracketStack.pop(); // pop the opened bracket
                }
            }
            if(tagOpened && c !='<')
            {
                tag+=c;
            }
                //Case 3 : No Closing bracket (Corner Case)
            else if (charNumber==currentLine.length() && !bracketStack.empty())
            {
                cout << "Problem at Line : " << lineNumber << " char : " << charNumber << " (Expected closing bracket).";
                return false;
            }

            charNumber++;
        }
        charNumber=1;
        lineNumber++;
    }

    while(!tagStack.empty())
    {
        cout << "Problem at Line : " << tagLines.top().first << ", char : " << tagLines.top().second  << " (Tag \"" << tagStack.top() <<   "\" not closed)." << endl;
        tagStack.pop();
        tagLines.pop();
    }








    return true;

}

int main() {
    freopen("input.xml", "r", stdin);
    openFile("input.xml");





    }
