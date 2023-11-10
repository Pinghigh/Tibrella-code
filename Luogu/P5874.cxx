#include <algorithm>
#include <cmath>
#include <iostream>

using i32 = int;
using i64 = long long;
using f64 = double;
#define log log2

using std::cin;
using std::cout;

#define N 500001

i32 x[N], y[N];

constexpr i32 mod = 1e9+7;

struct Node {
    Node *lc, *rc;
    f64 prod, mx;
    i32 ans, mul;

    i32 l, r, mid;
    void init(i32 L, i32 R) {
        l = L, r = R, mid = (L + R) >> 1;
    }
    
    void push_up() {
    	prod = lc->prod + rc->prod;
    	mx = std::max(lc->mx, lc->prod + rc->mx);
    	mul = lc->mul * (i64)rc->mul % mod;
    	ans = (lc->mx >= lc->prod + rc->mx) ? lc->ans : rc->ans * (i64)lc->mul % mod;
    }
} stree[N << 1], *root = stree + 1, *null = stree, *tot = stree + 1;

void build(Node* nod, i32 l, i32 r) {
    nod->init(l, r);
    if (l == r) {
        nod->mx = log((f64)x[l] * y[l]), nod->prod = log((f64)x[l]), nod->ans = x[l] * (i64)y[l] % mod, nod->mul = x[l];
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++tot, nod->rc = ++tot;
        build(nod->lc, l, nod->mid), build(nod->rc, nod->mid + 1, r);
 		nod->push_up();
    }
}

void modify(Node* nod, i32 pos) {
	if (nod->l == nod->r) 
		return nod->mx = log((f64)x[nod->l] * y[nod->l]), 
		       nod->prod = log((f64)x[nod->l]), nod->ans = x[nod->l] * (i64)y[nod->l] % mod, nod->mul = x[nod->l], 
		       void();
	else
        {((pos > nod->mid)? modify(nod->rc, pos) : modify(nod->lc, pos)); nod->push_up();}
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

	i32 n;
	cin >> n;
	for (i32 i = 1; i <= n; ++ i) {cin >> x[i];x[i]%=mod;}
	for (i32 i = 1; i <= n; ++ i) {cin >> y[i];y[i]%=mod;}
	build(root, 1, n);
	
	cout << root->ans << '\n';
	
	i32 m;
	cin >> m;
	while (m--) {
		i32 op, a;
		i32 b;
		cin >> op >> a >> b;
		++a;
		((op==1)?x:y)[a] = b%mod;
		modify(root, a);
		cout << root->ans << '\n';
	}

    return 0;
}