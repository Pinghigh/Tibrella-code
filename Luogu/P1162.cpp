#include <iostream>
#include <queue>

using namespace std;

int dataa[40][40];
bool st[40][40];
int n;
queue<int> x;
queue<int> y;
int nexta[4][2] = {
    {1,0},
    {-1,0},
    {0,1},
    {0,-1}
};

void bfs() {
    int a = x.front();
    int b = y.front();

    for (int i = 0; i < 4; i ++) {
        int ad = a + nexta[i][0];
        int bd = b + nexta[i][1];

        if (st[ad][bd] == 0 && dataa[ad][bd] == 0 && ad <= n && ad > 0 && bd <= n && bd > 0) {
            x.push(ad);
            y.push(bd);
            st[ad][bd] = 1;
        }
    }

    x.pop(); y.pop();



}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> dataa[i][j];
            if (dataa[i][j] == 1) st[i][j]=1;
            if (dataa[i][j] == 0 && (i == 1 || i == n || j == 1 || j == n)) {
                x.push(i);
                y.push(j);
                st[i][j] = 1;
            }
        }
    }
    
    while (!x.empty()) bfs();

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (st[i][j] == 0) dataa[i][j] = 2;
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << dataa[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}