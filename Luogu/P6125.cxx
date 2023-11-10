#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using f64 = double;

const f64 eps = 1e-7;

#define N 11
i32 n, l, m;

namespace acam {
    struct Node {
        i32 son[26];
        bool end;
        i32 fail;
    } trie[N * N];
    i32 tot;
    i32 end[N];

    void insert(std::string& str, const i32& id) {
        i32 cur = 0;
        for (auto& c : str) {
            c -= 'A';
            cur = trie[cur].son[c] ? trie[cur].son[c] : (trie[cur].son[c] = ++tot);
        }
        trie[cur].end = true;
        end[id] = cur;
    }

    void build() {
        std::queue<i32> q;
        for (i32 c = 0; c < m; ++c)
            if (trie[0].son[c]) q.emplace(trie[0].son[c]);

        while (!q.empty()) {
            i32 cur = q.front();
            Node &nod = trie[cur], &lfail = trie[trie[cur].fail];
            q.pop();
            for (i32 c = 0; c < m; ++c)
                (nod.son[c] ? (q.emplace(nod.son[c]), trie[nod.son[c]].fail) : nod.son[c]) = lfail.son[c];
        }
    }
}  // namespace acam

f64 p[26];

namespace guass {
    f64 a[N * N][N * N];

    void elimination() {
        i32 n = acam::tot;
        for (i32 i = 0; i <= n; ++i) {  // 枚举的实际上是元，正下方这个循环用于寻找 r
            i32 r = i;
            for (i32 j = i + 1; j <= n; ++j)
                if (std::abs(a[j][i]) > std::abs(a[r][i])) r = j;  // 找到第 i 个元的系数最大的一行。
            // if (abs(a[r][i]) < eps) failed(a[r][i]);
            if (r != i) std::swap(a[r], a[i]);

            for (i32 j = i + 1; j <= n + 1; ++j)
                a[i][j] /= a[i][i];  // 先通过等式性质把 f[i][i] 化为 1

            // 这里是高斯约旦消元和高斯消元的区别所在，j 是行数从 1 枚举就能把每一行的第 i 个元消掉
            for (i32 j = 0; j <= n; ++j) {
                if (i != j) {
                    f64 tmp = a[j][i];  // f[i][i] 已经是 1 了，不必再除
                    for (i32 k = i; k <= n + 1; ++k) {
                        a[j][k] -= a[i][k] * tmp;  // 加减消元
                    }
                }
            }
        }
    }
}  // namespace guass

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.flags(std::ios::fixed);

    cin >> n >> l >> m;
    for (i32 i = 0; i < m; ++i) {
        i32 p, q;
        cin >> p >> q;
        ::p[i] = p * 1.0 / q;
    }
    for (i32 i = 0; i < n; ++i) {
        std::string str;
        cin >> str;
        acam::insert(str, i);
    }

    acam::build();

    guass::a[0][acam::tot + 1] = 1;
    for (i32 i = 0; i <= acam::tot; ++i) {
        guass::a[i][i] = 1;
        if (!acam::trie[i].end)
            for (i32 c = 0; c < m; ++c)
                guass::a[acam::trie[i].son[c]][i] -= p[c];
    }

    guass::elimination();

    for (i32 i = 0; i < n; ++i) {
        f64 ans = guass::a[acam::end[i]][acam::tot + 1];
        if (std::abs(ans) < eps)
            cout << "0.00\n";
        else
            cout << std::setprecision(2) << ans << '\n';
    }

    return 0;
}