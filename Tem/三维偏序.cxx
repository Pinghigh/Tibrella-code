#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200005

struct ele {
    i32 x, y, z;
    i32 cnt, ans;

    void get() {
        cin >> x >> y >> z;
    }

    bool operator!=(const ele& b) const {
        return x != b.x || y != b.y || z != b.z;
    }
} p[N], ori[N];

struct Compare {
    struct fir {
        bool operator()(const ele& a, const ele& b) {
            // return a.x < b.x || (a.x == b.x && (a.y < b.y || (a.y == b.y && a.z < b.z)));
            if (a.x == b.x) {
                if (a.y == b.y) return a.z < b.z;
                return a.y < b.y;
            }
            return a.x < b.x;
        }
    } k1;
    struct sec {
        bool operator()(const ele& a, const ele& b) {
            // return a.y < b.y || (a.y == b.y && a.z < b.z);
            if (a.y == b.y) return a.z < b.z;
            return a.y < b.y;
        }
    } k2;
} cmp;

i32 n, k, len;

i32 tree[N];

i32 lowbit(i32 x) {
    return x & -x;
}

void modify(i32 pos, i32 val) {
    while (pos <= k) {
        tree[pos] += val;
        pos += lowbit(pos);
    }
}

i32 query(i32 pos) {
    i32 res = 0;
    while (pos) {
        res += tree[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void cdq(i32 l, i32 r) {
    // cout << l << ' ' << r << std::endl;
    if (l == r) return;
    i32 mid = (l + r) >> 1;

    cdq(l, mid);
    cdq(mid + 1, r);

    // std::sort(p + l, p + mid + 1, cmp.k2);
    // std::sort(p + mid + 1, p + r + 1, cmp.k2);

    i32 i, j;
    for (i = mid + 1, j = l; i <= r; ++i) {
        while (p[j].y <= p[i].y && j <= mid) {
            modify(p[j].z, p[j].cnt);
            ++j;
        }
        p[i].ans += query(p[i].z);
    }
    for (i = l; i < j; ++i)
        modify(p[i].z, -p[i].cnt);
    std::inplace_merge(p + l, p + mid + 1, p + r + 1, cmp.k2);
    // for (i32 i = l; i <= r; ++i)
    //     cout << p[i].y << ' ';
    // cout << std::endl;
}

i32 ans[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (i32 i = 1; i <= n; ++i)
        ori[i].get();

    std::sort(ori + 1, ori + n + 1, cmp.k1);

    // p[++len] = ori[1];
    // ++p[len].cnt;
    for (i32 i = 1; i <= n; ++i) {
        if (ori[i] != p[len]) p[++len] = ori[i];
        ++p[len].cnt;
        // if (!(ori[i] != p[len])) cout << ori[i].x << ' ' << ori[i].y << ' ' << ori[i].z << ' ' << p[len].x << ' ' << p[len].y << ' ' << p[len].z << '\n';
    }
    // cout << len << std::endl;

    cdq(1, len);

    for (i32 i = 1; i <= len; ++i) {
        // cout << p[i].ans << std::endl;
        ans[p[i].ans + p[i].cnt - 1] += p[i].cnt;
    }

    for (i32 i = 0; i < n; ++i)
        cout << ans[i] << '\n';

    return 0;
}