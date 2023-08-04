#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

using i32 = int;
using i64 = long long;
using i128 = __int128;
using f128 = long double;

#define N 100005

template <typename T>
T abs(const T& x) {
    return x < 0 ? -x : x;
}

const i64 inf = 0x3f3f3f3f3f3f3f3f;

i32 t;
string poem[N];
i32 pre[N];  // 最佳决策点
f128 f[N];
i64 s[N];
i32 n, p;
i64 L;

struct d {
    i32 l, r, p;
};

f128 binpow(f128 a) {
    f128 res = 1;
    i32 k = p;
    while (k) {
        if (k & 1) res *= a;
        a *= a;
        k >>= 1;
    }
    return res;
}

f128 calc(const i32& i, const i32& j) {
    return binpow(abs(s[i] - s[j] - 1 - L)) + f[j];
}

i32 find(const d& x, const i32& i) {
    i32 l = x.l, r = x.r, j = x.p, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (calc(mid, j) >= calc(mid, i))
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}

void output(i32 x) {
    if (pre[x]) output(pre[x]);
    for (i32 i = pre[x] + 1; i <= x; ++i) {
        cout << poem[i];
        if (i != x) cout << ' ';
    }
    if (x != n) cout << '\n';
}

void solve() {
    cin >> n >> L >> p;
    for (i32 i = 1; i <= n; ++i) {
        cin >> poem[i];
        s[i] = poem[i].size() + s[i - 1] + 1;
    }

    // DP 部分
    std::deque<d> q;
    q.emplace_front((d){ 1, n, 0 });  // 第一个可决策点就是 0
    for (i32 i = 1; i <= n; ++i) {
        if (!q.empty()) {
            if (q.front().r == i - 1)
                q.pop_front();
            else
                q.front().l = i;  // 没用的决策扔掉
        }
        i32 j = q.front().p;
        f[i] = calc(i, j);
        pre[i] = j;  // 记录最佳决策点

        // 插入新决策

        i32 pos = q.back().l;

        // 情况一：当前决策点比队尾优
        while (!q.empty() && calc(q.back().l, q.back().p) >= calc(q.back().l, i)) {
            pos = q.back().l;
            q.pop_back();
        }

        // 情况二：当前决策点可能部分优于队尾
        if (q.size()) {
            if (calc(q.back().r, q.back().p) <= calc(q.back().r, i))  // i 不优于 队尾
                pos = q.back().r + 1;
            else {
                pos = find(q.back(), i);
            }

            if (pos <= n) {
                q.back().r = pos - 1;
                q.emplace_back((d){ pos, n, i });
            }
        } else
            q.emplace_back((d){ i + 1, n, i });
    }
    if (f[n] > 1e18) goto failed;

    cout << (i64)f[n] << std::endl;

    output(n);
    cout.put('\n');

    return;

failed:
    cout << "Too hard to arrange\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        solve();
        cout << "--------------------";
        if (t) cout.put('\n');
    }

    return 0;
}