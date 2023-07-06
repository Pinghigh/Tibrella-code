#include <iostream>
#include <climits>

using namespace std;

#define N 114514

int l, r;
int n;
int mid;
int t1, t2, t3;
int mem[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    mem[0]=mem[n+1]=INT_MAX;
    l = 0;
    r = n + 1;
    while (r > l) {
        mid = l + r >> 1;
        for (int i = -1; i < 2; ++i) {
            if (!mem[mid + i]) {
                cout << "? " << mid + i << endl;
                cout.flush();
                cin >> t1;
                mem[mid+i]=t1;
            }
        }
        t1=mem[mid-1];
        t2=mem[mid];
        t3=mem[mid+1];
        if (t2 < t1 && t2 < t3) {
            cout << "! " << mid << endl;
            return 0;
        } else if (t1 < t2) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return 0;
}