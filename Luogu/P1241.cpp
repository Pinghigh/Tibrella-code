#include <iostream>
#include <stack>
#include <string>
#include <queue>

using namespace std;

string res = "";
queue<char> rig;
stack<char> tmp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    char in;

    while ((cin >> in)) {
        if (in == ']') {
            if (!tmp.empty() && tmp.top() == '[') {
                res += in;
                tmp.pop();
            } else {
                rig.push(in);
            }
            continue;
        } else if (in == ')') {
            if (!tmp.empty() && tmp.top() == '(') {
                res += in;
                tmp.pop();
            } else {
                rig.push(in);
            }
            continue;
        } 
        res += in;
        tmp.push(in);
    }

    while (!tmp.empty()) {
        switch (tmp.top()) {
            case ('['):
                res += ']';
                if (rig.front() == ']') rig.pop();
                else {
                    if (rig.front() == ']') {
                        res += "[]";
                        rig.pop();
                    } else if (rig.front() == ')') {
                        res += "()";
                        rig.pop();
                    }
                }
                break;
            case('('):
                res += ')';
                if (rig.front() == ')') rig.pop();
                else {
                    if (rig.front() == ']') {
                        res += "[]";
                        rig.pop();
                    } else if (rig.front() == ')') {
                        res += "()";
                        rig.pop();
                    }
                }
                break;
        }
        tmp.pop();
    }

    while (!rig.empty()) {
        
    }
    cout << res;
    return 0;
}