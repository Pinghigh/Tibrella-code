#include <iostream>
#include <queue>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;

priority_queue<int> q1;
priority_queue<int, std::vector<int>, std::greater<int> > q2;  // 小根
int n;
int tmp;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> tmp;

        if (!q1.empty() && tmp >= q1.top()) {
            q2.push(tmp);
        } else {
            q1.push(tmp);
        }
        
        while (!q2.empty() && q1.top() > q2.top()) {
            q1.push(q2.top());
            q2.pop();
        }
        
        while (q1.size() >= q2.size() && !q1.empty()) {
            q2.push(q1.top());
            q1.pop();
        }
        while (q2.size() > q1.size() + 1 && !q2.empty()) {
            q1.push(q2.top());
            q2.pop();
        }

        

        if (i % 2) {
            cout << q2.top() << endl;
        }
    }

    return 0;
}