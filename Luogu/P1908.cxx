#include <algorithm>
#include <iostream>

#pragma GCC target("avx2,sse4.2,sse4.1,bmi,bmi2,popcnt,lzcnt")

using std::sort;

#define N 50051400
#define int long long
#define getchar() getchar_unlocked()

char ch;
bool op;
template <typename T>
void read(T& x) {
    x = 0;
    op = 0;
    do {
        ch = getchar();
        if (ch == '-') {
            op = 1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    if (op) {
        x = -x;
    }
}

struct num {
    int id;
    int data;
} nums[N];
int n;
int tree[N];
int fin_data[N];

int lowbit(int& x) {
    return x & (-x);
}

bool cmp(const num& exa1, const num& exa2) {
    return (exa1.data < exa2.data) || ((exa1.data == exa2.data) && (exa1.id < exa2.id));
}

void modify(int nod, int val) {
    for (int i = nod; i <= n; i += lowbit(i)) {
        tree[i] += val;
    }
}

int query(int nod) {
    int res = 0;
    for (int i = nod; i; i -= lowbit(i)) {
        res += tree[i];
    }
    return res;
}

num* nu;
int ans;

signed main() {
    read(n);
    nu = nums;
    for (int i = 1; i <= n; ++i) {
        ++nu;
        read(nu->data);
        nu->id = nu - nums;
    }
    sort(nums + 1, nums + n + 1, cmp);
    nu = nums;
    for (int i = 1; i <= n; ++i) {
        ++nu;
        fin_data[nu->id] = i;
    }
    for (int i = 1; i <= n; ++i) {
        modify(fin_data[i], 1);
        ans += i - query(fin_data[i]);
    }

    printf("%lld\n", ans);

    return 0;
}