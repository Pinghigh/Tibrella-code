#include <bitset>
#include <climits>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;
using std::endl;

#define N 10005140
#define M 15140

int min(int a, int b) { return (a < b ? a : b); }
int max(int a, int b) { return (a > b ? a : b); }

int n, m;
int st[N];
int cnt;
int aut[N];
int lans, rans;
int ltmp, rtmp;
int ans = INT_MAX;
bool flag;

// bool check(int l, int r);
// int rig(int l);
// void lef();

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> aut[i];
    }
    ++st[1];
    ++cnt;
    for (int i = 1, j = 1; i <= n; ++i) {
        flag = 0;
        ++st[aut[i]];
        if (st[aut[i]]==1) {
            ++cnt;
        }
        while (j < i) {
            if (st[aut[j]]==1) {
                break;
            }
            --st[aut[j]];
            ++j;
        }  // std::cerr << "l " << j << " r " << i << endl;
        if (cnt==m&&ans>i-j) {
            ans = i - j;
            lans = j;
            rans = i;
        }
    }
    cout << lans << ' ' << rans << endl;
    return 0;
}

// bool check(int l, int r) {
//     st.reset();
//     for (int i = l; i <= r; ++i) {
//         st[aut[i]] = 1;
//     }
//     return (st.count() >= m);
// }