#pragma GCC target("avx2,popcnt,lzcnt,fma,sse4.1,sse4.2,bmi,bmi2,abm,sse2,sse3,sse4,mmx")

#include <bitset>
#include <iostream>

using std::cin;
using std::cout;
#define endl '\n'
#define int long long

int t;
int n, k, m;
int t1, t2, t3;

signed main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--) {
        cin >> n >> k >> m;

        if (k <= m) {
            if (n % 2) {
                for (int i = 0; i < n; ++i) {
                    cout << k << ' ';
                }
            } else {
                cout << "0 ";
                for (int i = 1; i < n; ++i) {
                    cout << k << ' ';
                }
            }
        } else {
            if (__builtin_clz(k) < __builtin_clz(m) || n == 1) {
                cout << "-1";
            } else {
                t1 = 1 << 64 - __builtin_clz(k) - 1;
                t2 = k - t1;
                if (n % 2) {
                    if ((n / 2) % 2) {
                        for (int i = n / 2 + 2; i < n; ++i) {
                            cout << t1 << ' ' << t2 << ' ';
                        }
                        // t3 = 1 << 64 - __builtin_clz(t2) - 1;
                        // t2 -= t3;
                        cout << t1 << " 0 " << t2;
                    } else {
                        cout << "0 0 ";
                        for (int i = (n - 2) / 2 + 4; i < n; ++i) {
                            cout << t1 << ' ' << t2 << ' ';
                        }
                        // t3 = 1 << 64 - __builtin_clz(t2) - 1;
                        // t2 -= t3;
                        cout << t1 << " 0 " << t2;
                    }   
                } else {
                    if ((n / 2) % 2) {
                        for (int i = n / 2; i < n; ++i) {
                            cout << t1 << ' ' << t2 << ' ';
                        }
                    } else {
                        cout << "0 0 ";
                        for (int i = (n - 2) / 2 + 2; i < n; ++i) {
                            cout << t1 << ' ' << t2 << ' ';
                        }
                    }   
                }
            }
        }
        cout << endl;
    }

    return 0;
}