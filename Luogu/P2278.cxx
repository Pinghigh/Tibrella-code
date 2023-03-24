#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
#include <cctype>
#include <stack>

using std::priority_queue;
using std::cin;
using std::cout;

struct proc {
    int num;
    int prio;
    int dead;
    int start;

    bool operator <(proc exa) {
        return prio<exa.prio;
    }
}

priority_queue<proc> wait;
int nu,pr,de,st;
stack<proc> cpu;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (cin >> nu >> pr >> de >> st) {
        
        
        if (cpu.empty()) {
            cpu.push()
        }
    }

    return 0;
}