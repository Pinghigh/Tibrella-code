#include <bitset>
#include <iostream>

using namespace std;

int t, n, m, o, x;

bitset<200005> st;

void solve() {
    st.reset();
    int no = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> o >> x;
        --o;
        if (o) {
            if (st[x] || (no && x != no)) {
                cout << i << endl;
                return;
            }
            no = x;
        } else {
            if (no) {
                if (no == x) {
                    cout << i << endl;
                    return;
                }
            }
            st[x] = true;
            if (st.count() >= n) {
                cout << i << endl;
                return;
            }
        }
    }
    cout << "-1" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}