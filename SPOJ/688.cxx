#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;

#define N 100005
#define P 500005

i32 t;
i32 n, k, p;
i32 a[P], nxt[P], pos[N];
std::bitset<N> st;

struct Compare {
    bool operator()(const i32& ida, const i32& idb) {
        return nxt[ida] < nxt[idb];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    // t = 1;
    while (t--) {
        cin >> n >> k >> p;
        for (i32 i = 1; i <= p; ++i) {
            cin >> a[i];
        }
        for (i32 i = p; i; --i) {
            nxt[i] = pos[a[i]];
            if (!nxt[i]) nxt[i] = p + 1;
            pos[a[i]] = i;
        }
        std::priority_queue<i32, std::vector<i32>, Compare> q;
        // i32 i;
        // i32 cnt = 0;
        // for (i = 1; i <= p && cnt < k; ++i) {
        //     if (!st[a[i]]) {
        //         st[a[i]] = true;
        //         q.emplace(i);
        //         ++cnt;
        //     }
        // }
        i32 ans = 0;
        for (i32 i = 1; i <= p; ++i) {
            if (!st[a[i]]) {
                if (q.size() == k) {
                    st[a[q.top()]] = false;
                    q.pop();
                }
                ++ans;
                st[a[i]] = true;
            } else
                ++k;

            q.push(i);
        }
        cout << ans << '\n';
        if (t) {
            st.reset();
            memset(pos, 0, sizeof pos);
        }
        // for (i32 i = 1; i <= p; ++ i) cout << nxt[i] << ' ';
    }

    return 0;
}