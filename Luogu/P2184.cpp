#include <iostream>

using namespace std;

int a[10010],area[10010],tmp=0,dl=1,note[10010];
bool book[10010];

void insert(int l,int r,int val) {
	a[l] = val;
	area[l] += val;
	area[r+1] -= val;
}

int sear(int l,int r) {
	int var = a[l], sum = 0, i = l,k = 0;
	if (var == 0) {
		for (int j = l; j > 0; j --) {
			if (area[i]) {
				var = area[i];
				break;
			}
		}
	}
	
	while (i <= r) {
		if (area[i] == 0 || book[var]) {
			i ++;
			continue;
		}
		book[var] = 1;
		note[k] = var;
		k ++;
		i ++;
		sum += 1;
		var += area[i];
	}
	for (int j = 0; j <= k; j ++) {
		book[note[j]] = 0;
	}
	
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int l,r,n,m,q;
	
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> q;
		cin >> l >> r;
		if (q == 1) {
			insert(l,r,dl);
			dl ++;
		} else {
			cout << sear(l,r) << endl;
		}
	}

	return 0;
}