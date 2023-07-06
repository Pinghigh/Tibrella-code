#include <iostream>
#include <list>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::string;
using i32 = int;

#define N 100006

string s, t;
i32 n;

struct Node {
    i32 son[26], fail;
    i32 cnt;
    i32 fa;
    std::list<i32> id, fail_son;
} trie[N << 1];
i32 tot = 1, idx = 1;
i32 tail[N], tt;

void insert(char c) {
    c -= 'a';
    if (!trie[idx].son[c]) {
        trie[idx].son[c] = ++tot;
        trie[trie[idx].son[c]].fa = idx;
    }
    idx = trie[idx].son[c];
}

void back() {
    idx = trie[idx].fa;
}

void end() {
    ++trie[idx].cnt;
    tail[++tt] = idx;
    trie[idx].id.emplace_back(tt);
}

void build() {
    std::queue<i32> q;
    for (i32 i = 0; i < 26; ++i)
        if (trie[1].son[i]) {
            trie[trie[1].son[i]].fail = 1;
            q.push(trie[1].son[i]);
        }
    while (!q.empty()) {
        i32 nod = q.front(), lfail = trie[q.front()].fail;
        q.pop();
        trie[lfail].fail_son.emplace_back(nod);
        for (i32 i = 0; i < 26; ++i) {
            i32& to = trie[nod].son[i];
            if (to) {
                i32 fail = lfail;
                if (trie[lfail].son[i])
                    trie[to].fail = trie[lfail].son[i];
                else
                    trie[to].fail = 1;
                q.push(to);
            } else
                to = 0;
        }
    }
}

i32 dfn[N], qdfn[N], siz[N], tim;
void dfs(i32 nod) {
    dfn[nod] = ++tim;
    qdfn[tim] = nod;
    siz[nod] = 1;
    for (auto& to : trie[nod].fail_son) {
        if (!dfn[to]) {
            dfs(to);
            siz[nod] += siz[to];
        }
    }
}

i32 tree[N];
i32 lowbit(i32 x) {
    return x & (-x);
}
void modify(i32 pos, i32 v) {
    // if (!pos) return;
    for (; pos <= tim; pos += lowbit(pos))
        tree[pos] += v;
}
i32 que(i32 pos) {
    // if (pos < 0) return 0;
    i32 res = 0;
    for (; pos; pos -= lowbit(pos))
        res += tree[pos];
    return res;
}
i32 query(i32 nod) {
    // cout << dfn[nod] << ' ' << dfn[nod] + siz[nod] - 1 << '\n';
    return que(dfn[nod] + siz[nod] - 1) - que(dfn[nod] - 1);
}

struct qu {
    i32 sid, aid;
};

std::list<qu> q[N];
i32 ans[N];

void answer(i32 nod) {
    modify(dfn[nod], 1);
    // cout << nod << ' ' << trie[nod].cnt << '\n';
    if (trie[nod].cnt) {
        for (auto& id : trie[nod].id)
            for (auto& r : q[id]) {
                ans[r.aid] = query(tail[r.sid]);
                // cout << r.aid << ' ' << r.sid << ' ' << ans[r.aid] << '\n';
            }
    }
    for (i32 i = 0; i < 26; ++i) {
        if (trie[nod].son[i]) answer(trie[nod].son[i]);
    }
    modify(dfn[nod], -1);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    for (auto& c : t) {
        if (c == 'P') {
            end();
        } else if (c == 'B') {
            back();
        } else {
            insert(c);
        }
    }

    build();

    i32 m;
    cin >> m;
    i32 x, y;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        // cout << x << ' ' << y << ' ' << i << '\n';
        q[y].emplace_back((qu){ x, i });
    }
    dfs(1);
    answer(1);
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << '\n';

    // for (int i = 1; i <= tot; ++i) {
    // for (auto& x : trie[i].fail_son)
    //     cout << (i32)x << ' ';
    // cout << '\n';
    // cout << trie[i].cnt << ' ';
    // }

    // cout << tim;

    return 0;
}