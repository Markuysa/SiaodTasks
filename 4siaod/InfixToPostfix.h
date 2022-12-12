#include <iostream>
#include <stack>
#include <string>
#include <climits>
#include <map>
using namespace std;

map <char, int> priority = { {'*',3},{'/',3},{'+',4},{'-',4},{'^',6} };

bool isOperand(char c) {
    return (c >= '0' && c <= '9' || c>='a' && c<='z');
}

string infixToPostfix(string infix)
{
    stack<char> s;
    string postfix;
    for (char c : infix)
    {
        if (isOperand(c)) {
            postfix.push_back(c);
        }      
        else {
            while (!s.empty() && priority[c] >= priority[s.top()]){
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()){
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}
