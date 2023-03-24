#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>


#define N 100010
#define ll long long

using std::max;
using std::min;

signed a[N], b[N];
signed ia, ib;
signed n, m, q, i;
signed l1, r1, l2, r2;
signed zhmax, mimax, zhmin, mimin;
signed bmax, bmin;
ll aRes, bRes;
bool minus, zheng;

int read() {
    int f = 1, x = 0;
    char c;
    c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return f * x;
}

struct node {
    int u;
    int l, r, mid;
    int zhMinVal = INT_MAX, zhMaxVal, miMinVal, miMaxVal = INT_MIN, absMin;
    int minVal, maxVal;
    int lChild, rChild;
} tr1[N * 4], tr2[N * 4];

int ta1l = 1, ta2l = 1;

void aBuild(int u, int L, int R) {
    // give L&R
    tr1[u].l = L;
    tr1[u].r = R;
    // leaf node
    if (L == R) {
        tr1[u].l = tr1[u].r = 0;
        if (a[L] >= 0)
            tr1[u].zhMinVal = tr1[u].zhMaxVal = a[L];
        else
            tr1[u].miMinVal = tr1[u].miMaxVal = a[L];
        return;
    }

    tr1[u].mid = (L + R) >> 1;
    // build children
    tr1[u].lChild = (++ta1l);
    aBuild(tr1[u].lChild, L, tr1[u].mid);
    tr1[u].rChild = (++ta1l);
    aBuild(tr1[u].rChild, tr1[u].mid + 1, R);
    // min&max value
    tr1[u].zhMaxVal = max(tr1[tr1[u].lChild].zhMaxVal, tr1[tr1[u].rChild].zhMaxVal);
    tr1[u].zhMinVal = min(tr1[tr1[u].lChild].zhMinVal, tr1[tr1[u].rChild].zhMinVal);
    // printf("maxval: %d query u.L %d u.R %d L: %d R: %d\n",tr1[u].maxVal,tr1[u].l,tr1[u].r,L,R);
    tr1[u].miMaxVal = max(tr1[tr1[u].lChild].miMaxVal, tr1[tr1[u].rChild].miMaxVal);
    tr1[u].miMinVal = min(tr1[tr1[u].lChild].miMinVal, tr1[tr1[u].rChild].miMinVal);
}

void bBuild(int u, int L, int R) {
    // give L&R
    tr2[u].l = L;
    tr2[u].r = R;
    // leaf node
    if (L == R) {
        tr2[u].l = tr2[u].r = L;
        tr2[u].minVal = tr2[u].maxVal = b[L];
        return ;
    }

    tr2[u].mid = (L + R) >> 1;
    // build children
    tr2[u].lChild = (++ta2l);
    bBuild(tr2[u].lChild, L, tr2[u].mid);
    tr2[u].rChild = (++ta2l);
    bBuild(tr2[u].rChild, tr2[u].mid + 1, R);
    // min&max value
    tr2[u].maxVal = max(tr2[tr2[u].lChild].maxVal, tr2[tr2[u].rChild].maxVal);
    tr2[u].minVal = min(tr2[tr2[u].lChild].minVal, tr2[tr2[u].rChild].minVal);
}

int aQuery1(int u, int L, int R) {
    // printf("maxval: %d query u.L %d u.R %d L: %d R: %d\n",tr1[u].maxVal,tr1[u].l,tr1[u].r,L,R);
    if (L == R) return a[L];
    if (tr1[u].l == L && tr1[u].r == R) return tr1[u].zhMaxVal;
    if (tr1[u].mid >= R) return aQuery1(tr1[u].lChild, L, R);
    if (tr1[u].mid < L) return aQuery1(tr1[u].rChild, L, R);

    return max(aQuery1(tr1[u].lChild, L, tr1[u].mid), aQuery1(tr1[u].rChild, tr1[u].mid + 1, R));
}

int aQuery2(int u, int L, int R) {
    // printf("maxval: %d query u.L %d u.R %d L: %d R: %d\n",tr1[u].maxVal,tr1[u].l,tr1[u].r,L,R);
    if (L == R) 
        if (a[L] >= 0) return a[L];
        else return INT_MAX;
    if (tr1[u].l == L && tr1[u].r == R) return tr1[u].zhMinVal;
    if (tr1[u].mid >= R) return aQuery2(tr1[u].lChild, L, R);
    if (tr1[u].mid < L) return aQuery2(tr1[u].rChild, L, R);

    return min(aQuery2(tr1[u].lChild, L, tr1[u].mid), aQuery2(tr1[u].rChild, tr1[u].mid + 1, R));
}

int aQuery3(int u, int L, int R) {
    // printf("maxval: %d query u.L %d u.R %d L: %d R: %d\n",tr1[u].maxVal,tr1[u].l,tr1[u].r,L,R);
    if (L == R) return min(a[L],0);
    if (tr1[u].l == L && tr1[u].r == R) return tr1[u].miMaxVal;
    if (tr1[u].mid >= R) return aQuery3(tr1[u].lChild, L, R);
    if (tr1[u].mid < L) return aQuery3(tr1[u].rChild, L, R);

    return max(aQuery3(tr1[u].lChild, L, tr1[u].mid), aQuery3(tr1[u].rChild, tr1[u].mid + 1, R));
}

int aQuery4(int u, int L, int R) {
    // printf("maxval: %d query u.L %d u.R %d L: %d R: %d\n",tr1[u].maxVal,tr1[u].l,tr1[u].r,L,R);
    if (L == R) return a[L] <= 0 ? a[L]:INT_MIN;
    if (tr1[u].l == L && tr1[u].r == R) return tr1[u].miMinVal;
    if (tr1[u].mid >= R) return aQuery3(tr1[u].lChild, L, R);
    if (tr1[u].mid < L) return aQuery3(tr1[u].rChild, L, R);

    return min(aQuery4(tr1[u].lChild, L, tr1[u].mid), aQuery4(tr1[u].rChild, tr1[u].mid + 1, R));
}

int bQuery1(int u, int L, int R) {
    // printf("minval:%d bquery u.L %d u.R %d L: %d R: %d\n",tr2[u].minVal,tr2.[u].l,tr2[u].r,L,R);
    if (L == R) return b[L];
    if (tr2[u].l == L && tr2[u].r == R) return tr2[u].maxVal;
    if (tr2[u].mid >= R) return bQuery1(tr2[u].lChild, L, R);
    if (tr2[u].mid < L) return bQuery1(tr2[u].rChild, L, R);

    return max(bQuery1(tr2[u].lChild, L, tr2[u].mid), bQuery1(tr2[u].rChild, tr2[u].mid + 1, R));
}

int bQuery2(int u, int L, int R) {
    // printf("minval:%d bquery u.L %d u.R %d L: %d R: %d\n",tr2[u].minVal,tr2.[u].l,tr2[u].r,L,R);
    if (L == R) return b[L];
    if (tr2[u].l == L && tr2[u].r == R) return tr2[u].minVal;
    if (tr2[u].mid >= R) return bQuery2(tr2[u].lChild, L, R);
    if (tr2[u].mid < L) return bQuery2(tr2[u].rChild, L, R);

    return min(bQuery2(tr2[u].lChild, L, tr2[u].mid), bQuery2(tr2[u].rChild, tr2[u].mid + 1, R));
}

signed main() {
    // 	freopen("game.in","r",stdin); freopen("game.out","w",stdout);

    n = read();
    m = read();
    q = read();

    for (i = 1; i <= n; i++)
        a[i] = read();
    for (i = 1; i <= m; i++)
        b[i] = read();

    aBuild(1, 1, n);
    bBuild(1, 1, m);

    while (q--) {
        l1 = read();
        r1 = read();
        l2 = read();
        r2 = read();
        zhmax = aQuery1(1, l1, r1);
        zhmin = aQuery2(1, l1, r1);
        mimin = aQuery3(1, l1, r1);
        mimax = aQuery4(1, l1, r1);
        bmax = bQuery1(1,l1,r1);
        bmin = bQuery2(1,l1,r1);

        if (bmax > 0) zheng = 1;
        else zheng = 0;
        if (bmin < 0) minus = 1;
        else minus = 0;

        if (zheng && !minus) {
            aRes = zhmax;
        } else if (zheng && minus) {
            aRes = (zhmax*bmin >= mimin*bmax)? zhmax:mimin;
        } else {
            aRes = mimin;
        }

        bRes = (aRes >= 0)? bmin:bmax;

        printf("%lld\n", aRes*bRes);
        // printf("%lld\n", (ll)aQuery(1, l1, r1) * (ll)bQuery(1, l2, r2));
    }

    return 0;
}
