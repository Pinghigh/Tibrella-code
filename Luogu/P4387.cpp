#include <iostream>
#include <stack>
#define MAXN 100005

using namespace std;

stack<int> tmp;
int count,n,ps[MAXN],pp[MAXN],k;

bool sol() {
    for (int i = 1; i <= n; i ++) {
        if (!tmp.empty() && tmp.top() == pp[i]) {
            tmp.pop(); // 如果当前元素与当前元素数相等则弹出
        }

        while (k<=n && ps[k] != pp[i]) {
            // 不符合要求就压进去
            tmp.push(ps[k]);
            // 枚举下一个 （ push 序列中）
            k ++;
        }
        
        if (k > n) return false;
        k++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> count;

    while (count--) {
        k=1; // init k = 1 (第一个判断的数字下标为1)
        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> ps[i]; // 入栈序列
        }
        for (int i = 1; i <= n; i ++) {
            cin >> pp[i]; // 出栈序列
        }

        // 清空栈
        while (!tmp.empty()) {
            tmp.pop();
        } 

        if (sol()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}