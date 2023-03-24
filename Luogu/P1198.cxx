#include <iostream>
#include <cmath>

using namespace std;

#define N 200514
#define M 18

int m, d;
int f[N][M];
int ori[N];
char beh;
int dat;
int tail;
int t;

void add(int a) {
    a += t;
    a %= d;
    // cout << "[A] " << a << endl;
    ori[++tail] = a;
    for (int j = 0; tail - (1 << j) + 1 > 0; ++j) {
        if (!j) {
            f[tail][j] = a;
        } else {
            f[tail][j] = max(f[tail][j - 1], f[tail - (1 << j - 1)][j - 1]);
        }
    }
}

void query(int len) {
    int l = tail - len + 1;
    int k = log2(len);
    t =  max(f[tail][k], f[l + (1 << k) - 1][k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> d;
    while (m--) {
        cin >> beh >> dat;
        switch (beh) {
            case ('A'): add(dat); break;
            default: query(dat); cout << t << endl; break;
        }
    }

    return 0;
}