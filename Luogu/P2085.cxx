#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

#define N 11451

struct num {
    int from;
    int data;
    num(int pa, int dat) : data(dat), from(pa) {}
    bool operator>(const num b) const { return data > b.data; }
};

struct fn {
    int a, b, c;
    int no;
    num calc(int x) { return num(no, a * x * x + b * x + c); }
    // int mid;
} func[N];



int n,
    m;
priority_queue<num, vector<num>, greater<num>> q;
int nums[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int hav = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> func[i].a >> func[i].b >> func[i].c;
        func[i].no = i;
        // func[i].mid =
    }

    while (hav <= m) {
        if (q.empty()) {
            for (int j = 1; j <= n; ++j) {
                q.push(func[j].calc(++nums[j]));
            }
        } else {
            cout << q.top().data << ' ';
            q.push(func[q.top().from].calc(++nums[q.top().from]));
            q.pop();
        }
        ++ hav;
    }

    return 0;
}